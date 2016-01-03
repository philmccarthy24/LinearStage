#ifndef ICONTROLINTERFACE
#define ICONTROLINTERFACE

#include "iuieventhandler.h"
#include <memory>

class IControlInterface
{
public:
    virtual ~IControlInterface() {}

    virtual void RegisterEventHandler(std::shared_ptr<IUIEventHandler> pControlEventHandler) = 0;

    virtual void OnPositionChanged(double newPosition) = 0;
};

#endif // ICONTROLINTERFACE

