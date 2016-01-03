#ifndef CSYSTEMCONTROLLER_H
#define CSYSTEMCONTROLLER_H

#include "iuieventhandler.h"
#include "icontrolinterface.h"
#include <memory>
#include <vector>
#include <thread>
#include <queue>

struct UIEvent
{
    int dialId;
    int delta;
};

class CStageController : public IUIEventHandler
{
public:
    CStageController(std::initializer_list<std::shared_ptr<IControlInterface>> controlInterfaces);
    virtual ~CStageController();

    // IControlEventHandler interface
    virtual void OnDialMoved(int dialId, int delta) override;

private:
    void StageControlThreadProc();

    std::thread m_controllerThread;

    // list of control interfaces (front ends) connected to this controller
    std::vector<std::shared_ptr<IControlInterface>> m_controlInterfaces;

    // ui event queue
    std::queue<UIEvent> m_eventQueue;
    std::mutex m_queueMutex;

    std::atomic<bool> m_killSignalled;

    double m_stagePositionActual;
};

#endif // CSYSTEMCONTROLLER_H
