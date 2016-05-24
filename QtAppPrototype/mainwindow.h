#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "icontrolinterface.h"
#include <vector>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IControlInterface
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void RegisterEventHandler(std::shared_ptr<IUIEventHandler> pUIEventHandler) override;
    virtual void OnPositionChanged(double newPosition) override;

public slots:
    void on_dial_moved(int position);
    void onSerialInfoBtnClicked();

signals:
    void updateSlider(int newPos);
    void updateLCD(double newReadout);

private:
    Ui::MainWindow *ui;
    int m_prevDialPos;

    std::vector<std::weak_ptr<IUIEventHandler>> m_UIEventHandlers;
};

#endif // MAINWINDOW_H
