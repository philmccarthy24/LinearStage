#ifndef HARDWARESERIALUI_H
#define HARDWARESERIALUI_H

#include "icontrolinterface.h"
#include <thread>
#include <vector>
#include <atomic>

class HardwareSerialUI : public IControlInterface
{
public:
    HardwareSerialUI();
    virtual ~HardwareSerialUI();

    // IControlInterface interface
public:
    virtual void RegisterEventHandler(std::shared_ptr<IUIEventHandler> pControlEventHandler) override;
    virtual void OnPositionChanged(double newPosition) override;

private:
    void SerialComsThreadProc();

    std::thread m_serialThread;

    std::vector<std::weak_ptr<IUIEventHandler>> m_UIEventHandlers;
    std::atomic<bool> m_killSignalled;
};

#endif // HARDWARESERIALUI_H
