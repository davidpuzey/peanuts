#include <ctime>
#include <QtWidgets>
#include <QtSerialPort/QSerialPortInfo>
#include <QMediaPlayer>
#include "BuzzerModule.h"

BuzzerModule::BuzzerModule() {
	setTitle("Buzzer");
	setControlWidget(new BuzzerControl);
	setLiveWidget(new BuzzerLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
	
	serial = new QSerialPort();
	teamLocked = false;
	
    connect(control, SIGNAL(sendTeamWin(QString)), live, SLOT(teamWin(QString)));
    connect(control, SIGNAL(openSerialPort(QString&)), this, SLOT(openSerialPort(QString&)));
    connect(control, SIGNAL(closeSerialPort()), this, SLOT(closeSerialPort()));
	connect(this, SIGNAL(teamWin(int)), control, SLOT(teamWin(int)));
	connect(serial, SIGNAL(readyRead()), this, SLOT(readSerialPort()));
	connect(live, SIGNAL(unlockTeam()), this, SLOT(unlockTeam()));
}

void BuzzerModule::openSerialPort(QString &portName) {
	serial->setPortName(portName);
	serial->open(QIODevice::ReadWrite);
}

void BuzzerModule::closeSerialPort() {
	serial->close();
}

void BuzzerModule::readSerialPort() {
	QByteArray input = serial->readLine(5);
	if (input[1] == '1' && !teamLocked) {
		emit teamWin(((int) input[0])-1);
		//teamLocked = true;
		serial->readAll(); // Flush read buffer
	}
}

void BuzzerModule::unlockTeam() {
	teamLocked = false;
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
	if (team >= MAX_TEAMS)
		return;
	QString tmpTeamName = teamName[team]->text();
    emit sendTeamWin(tmpTeamName);
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
	player = new QMediaPlayer;
	inWin = false;
	buzzDir = new QDir("media/buzzer/");
	mp3Files = buzzDir->entryList(QDir::Files);
	
	textTimeout = new QTimer;
	textTimeout->setInterval(3000);
	connect(textTimeout, SIGNAL(timeout()), this, SLOT(killText()));
	
    QHBoxLayout *layout = new QHBoxLayout();
	dTeamName = new QLabel();
	dTeamName->setWordWrap(true);
	dTeamName->setAlignment(Qt::AlignCenter);
	dTeamName->setStyleSheet("margin: 0; padding: 0; background-color: black; color: white; font: 100pt;");
	layout->addWidget(dTeamName);
    setLayout(layout);
}

void BuzzerLive::teamWin(QString teamName) {
	if (inWin)
		return;
	inWin = true;
	playRandomSound();
	dTeamName->setText(teamName);
	dTeamName->update();
	textTimeout->start();
}

void BuzzerLive::killText() {
	dTeamName->clear();
	emit unlockTeam();
	inWin = false;
}

void BuzzerLive::playRandomSound() {
	int rnum = qrand() % mp3Files.count();
	player->setMedia(QUrl::fromLocalFile(buzzDir->path() + "/" + mp3Files[rnum]));
	player->play();
}