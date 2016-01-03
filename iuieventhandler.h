#ifndef ICONTROLEVENTHANDLER
#define ICONTROLEVENTHANDLER

class IUIEventHandler
{
public:
    virtual ~IUIEventHandler() {}

    virtual void OnDialMoved(int dialId, int delta) = 0;
};

#endif // ICONTROLEVENTHANDLER

