#include "hardwareserialui.h"
#include <QSerialPort>
#include <sstream>
#include <QDebug>
#include <QThread>

using namespace std;

HardwareSerialUI::HardwareSerialUI()
{
    m_killSignalled = false;

    m_serialThread = std::thread([&] () {
        SerialComsThreadProc();
    });
}

HardwareSerialUI::~HardwareSerialUI()
{
    m_killSignalled = true;
    m_serialThread.join();
}

void HardwareSerialUI::RegisterEventHandler(std::shared_ptr<IUIEventHandler> pControlEventHandler)
{
    m_UIEventHandlers.push_back(pControlEventHandler);
}

void HardwareSerialUI::OnPositionChanged(double newPosition)
{
    // do nothing - currently no LCD or whatever to feed back to
}

void HardwareSerialUI::SerialComsThreadProc()
{
    QSerialPort serial;
    // change this to be the serial port to open - this is for
    // my Arduino Uno R3
    serial.setPortName("cu.usbmodem1421");
    serial.setBaudRate(9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setReadBufferSize(0);

    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Can't open serial device: " << serial.error();
        return;
    }

    vector<char> comsBuffer;
    comsBuffer.resize(1024);

    while (m_killSignalled == false)
    {
        if (serial.waitForReadyRead(2000))
        {
            while (serial.canReadLine())
            {
                serial.readLine(comsBuffer.data(), 1024);

                int dialId, samplePeriod, delta = 0;
                stringstream ss;
                ss << comsBuffer.data();
                qDebug() << "read " << ss.str().c_str();
                ss >> dialId >> samplePeriod >> delta;

                if (dialId != 0) // first messages may be sporadic
                    continue;

                for (auto eventHandler : m_UIEventHandlers)
                {
                    auto pObj = eventHandler.lock();
                    if (pObj != nullptr)
                    {
                        pObj->OnDialMoved(dialId, delta);
                    }
                }
            }
        }
    }

    serial.close();
}
