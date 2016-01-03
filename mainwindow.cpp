#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_prevDialPos(0)
{
    ui->setupUi(this);
    ui->lcdNumber->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RegisterEventHandler(std::shared_ptr<IUIEventHandler> pUIEventHandler)
{
    m_UIEventHandlers.push_back(pUIEventHandler);
}

void MainWindow::OnPositionChanged(double newPosition)
{
    emit updateSlider((int)newPosition);
    emit updateLCD(newPosition);
}

void MainWindow::on_dial_moved(int position)
{   
    int dialMax = ui->dial->maximum();
    int nDelta = position - m_prevDialPos;
    // detect if dial has looped around
    if (abs(nDelta) > dialMax / 2)
    {
        if (nDelta > 0)
            nDelta -= dialMax;
        else
            nDelta += dialMax;
    }

    for (auto eventHandler : m_UIEventHandlers)
    {
        auto pObj = eventHandler.lock();
        if (pObj)
        {
            pObj->OnDialMoved(0, nDelta);
        }
    }
    m_prevDialPos = position;
}

void MainWindow::onSerialInfoBtnClicked()
{
    QString msg = "";
    QList<QSerialPortInfo> serialPortInfoList = QSerialPortInfo::availablePorts();

    foreach (const QSerialPortInfo &serialPortInfo, serialPortInfoList)
    {
        msg.append(serialPortInfo.portName());
        msg.append("\n");
    }

    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}
