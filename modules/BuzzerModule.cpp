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
    connect(control, SIGNAL(sendTeamWin(QString*)), live, SLOT(teamWin(QString*)));
    connect(control, SIGNAL(openSerialPort(QString&)), this, SLOT(openSerialPort(QString&)));
}

void BuzzerModule::openSerialPort(QString &portName) {
}

void BuzzerModule::closeSerialPort() {
}

void BuzzerModule::readSerialPort() {
}

BuzzerControl::BuzzerControl() {
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *confLayout = new QHBoxLayout();
	QGridLayout *teamLayout = new QGridLayout();

    serialPortList = new QComboBox();
	start = new QPushButton("Connect");
    start->setCheckable(true);
	refresh = new QPushButton("Refresh");
    QPushButton *reset = new QPushButton("Reset");

	connect(refresh, SIGNAL(clicked()), this, SLOT(updateSerialPortList()));
    connect(start, SIGNAL(clicked(bool)), this, SLOT(serialGo(bool)));

	updateSerialPortList();

    confLayout->addWidget(serialPortList);
	confLayout->addWidget(start);
	confLayout->addWidget(refresh);
    confLayout->addWidget(reset);

	QSignalMapper *signalMapper = new QSignalMapper();

    for (int i = 0; i < MAX_TEAMS; i++) {
        teamName[i] = new QLineEdit();
        QPushButton *triggerButton = new QPushButton("Trigger");

        teamLayout->addWidget(new QLabel(QString::number(i+1)), i, 0);
        teamLayout->addWidget(teamName[i], i, 1);
        teamLayout->addWidget(triggerButton, i, 2);
		connect(triggerButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(triggerButton, i);
    }

	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(teamWin(int)));

	layout->addLayout(confLayout);
    layout->addLayout(teamLayout);
    setLayout(layout);
}

void BuzzerControl::updateSerialPortList() {
	serialPortList->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        serialPortList->addItem(info.portName());
}

void BuzzerControl::teamWin(int team) {
	QString tmpTeamName = teamName[team]->text();
    emit sendTeamWin(&tmpTeamName);
}

void BuzzerControl::serialGo(bool state) {
    if (state) {
		QString serialPort = serialPortList->currentText();
        start->setText("Disconnect");
        emit openSerialPort(serialPort);
		serialPortList->setEnabled(false);
		refresh->setEnabled(false);
    } else {
        start->setText("Connect");
        emit closeSerialPort();
		serialPortList->setEnabled(true);
		refresh->setEnabled(true);
    }
}

BuzzerLive::BuzzerLive() {
    QHBoxLayout *layout = new QHBoxLayout();
    setLayout(layout);
}

void BuzzerLive::teamWin(QString *teamName) {
    // Flash *teamName
    // Play random mp3
}

void BuzzerLive::playRandomSound() {
}