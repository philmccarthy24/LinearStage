#include "cstagecontroller.h"
#include <chrono>
#include <cmath>
#include <QThread>
#include <QDebug>

using namespace std;

CStageController::CStageController(std::initializer_list<std::shared_ptr<IControlInterface>> controlInterfaces) :
    m_stagePositionActual(0)
{
    m_killSignalled = false;

    for (auto controlInterface : controlInterfaces)
    {
        // add the control interface to this controller, so
        // we can feed back changes of the system being managed to the
        // UI control output (eg LCD display, software GUI, whatever)
        m_controlInterfaces.push_back(controlInterface);
    }

    m_controllerThread = std::thread([&] () {
        StageControlThreadProc();
    });
}

CStageController::~CStageController()
{
    // signal processing thread terminate
    m_killSignalled = true;

    // wait for thread to exit gracefully
    m_controllerThread.join();
}

// this is asynchronous / non blocking - ie we put the control state change on the queue
// ready to be processed
void CStageController::OnDialMoved(int dialId, int delta)
{
    unique_lock<mutex> lock(m_queueMutex);
    m_eventQueue.push(UIEvent { dialId, delta });
}

void CStageController::StageControlThreadProc()
{
    while (!m_killSignalled)
    {
        double newActual = m_stagePositionActual;

        int samplePeriodDelta = 0;

        {
            unique_lock<mutex> lock(m_queueMutex);
            while (!m_eventQueue.empty())
            {
                UIEvent evt = m_eventQueue.front();
                m_eventQueue.pop();

                // ignore dialId, just sum deltas in this sampling frame
                samplePeriodDelta += evt.delta;
            }
        }

        // handle the ui event - perform non linear transform
        double deltaToApply = pow(samplePeriodDelta, 2); // TODO: make this customisable as sensitivity
        if (samplePeriodDelta < 0)
            deltaToApply = -deltaToApply;
        newActual += deltaToApply;
        // clip between 0-1000
        if (newActual > 1000)
            newActual = 1000;
        if (newActual < 0)
            newActual = 0;

        // and write this to stage here
        //...

        // read from the stage
        //...

        // update UI display(s) with new actual position
        if (newActual != m_stagePositionActual)
        {
            //qDebug() << "got change from control interface";
            m_stagePositionActual = newActual; // this would be updated in the "read from stage" code above, not here
            for (auto controlInterface : m_controlInterfaces)
            {
                controlInterface->OnPositionChanged(m_stagePositionActual);
            }
        }

        QThread::msleep(50);
    }
}
