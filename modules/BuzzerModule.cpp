#include <ctime>
#include <QtGui>
#include <QSerialPort/QSerialPortInfo>
#include "BuzzerModule.h"

BuzzerModule::BuzzerModule() {
	setTitle("Buzzer");
	setControlWidget(new BuzzerControl);
	setLiveWidget(new BuzzerLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
}

BuzzerControl::BuzzerControl() {
	QHBoxLayout *layout = new QHBoxLayout();
    QListWidget *serialPortList = new QComboBox(this);

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        serialPortList->addItem(info.portName());

    layout->addWidget(serialPortList);
    setLayout(layout);
}

BuzzerLive::BuzzerLive() {
    QHBoxLayout *layout = new QHBoxLayout();
    setLayout(layout);
}
