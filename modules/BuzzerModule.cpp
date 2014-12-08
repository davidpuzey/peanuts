#include <ctime>
#include <QtWidgets>
#include <QtSerialPort/QSerialPortInfo>
#include "BuzzerModule.h"

BuzzerModule::BuzzerModule() {
	setTitle("Buzzer");
	setControlWidget(new BuzzerControl);
	setLiveWidget(new BuzzerLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
}

BuzzerControl::BuzzerControl() {
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *confLayout = new QHBoxLayout();
    serialPortList = new QComboBox(this);
	QPushButton *start = new QPushButton("Connect");
	QPushButton *refresh = new QPushButton("Refresh");
	connect(refresh, SIGNAL(clicked()), this, SLOT(updateSerialPortList()));

	updateSerialPortList();

    confLayout->addWidget(serialPortList);
	confLayout->addWidget(start);
	confLayout->addWidget(refresh);
	
	layout->addLayout(confLayout);
    setLayout(layout);
}

void BuzzerControl::updateSerialPortList() {
	serialPortList->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        serialPortList->addItem(info.portName());
}

BuzzerLive::BuzzerLive() {
    QHBoxLayout *layout = new QHBoxLayout();
    setLayout(layout);
}
