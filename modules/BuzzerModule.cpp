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
    connect(control, SIGNAL(setVideo(QString)), live, SLOT(setVideo(QString)));
    connect(control, SIGNAL(setVideoPlaying(bool)), live, SLOT(setVideoPlaying(bool)));
    connect(live, SIGNAL(videoPlaying(bool)), control, SLOT(videoPlaying(bool)));
    connect(live, SIGNAL(videoFinished()), control, SLOT(videoFinished()));
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
		serial->readAll(); // Flush read buffer
	}
}

void BuzzerModule::unlockTeam() {
	teamLocked = false;
}

BuzzerControl::BuzzerControl() {
    QHBoxLayout *layout = new QHBoxLayout();
	QVBoxLayout *settingsLayout = new QVBoxLayout();
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

    teamLayout->addWidget(new QLabel("Teams:"), 0, 1);
    for (int i = 0; i < MAX_TEAMS; i++) {
        teamName[i] = new QLineEdit();
        QPushButton *triggerButton = new QPushButton("Trigger");

        teamLayout->addWidget(new QLabel(QString::number(i+1)), i+1, 0);
        teamLayout->addWidget(teamName[i], i+1, 1);
        teamLayout->addWidget(triggerButton, i+1, 2);
		connect(triggerButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(triggerButton, i);
    }

	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(teamWin(int)));

    QWidget *confWidget = new QWidget();
    confWidget->setLayout(confLayout);
    QWidget *teamWidget = new QWidget();
    teamWidget->setLayout(teamLayout);

	settingsLayout->addWidget(confWidget);
    settingsLayout->addWidget(teamWidget);

    QWidget *settingsWidget = new QWidget();
    settingsWidget->setLayout(settingsLayout);

    QDir *videosDir = new QDir("media/buzzer/videos/");
    videosDir->setFilter(QDir::Files);
    QFileInfoList videoFiles = videosDir->entryInfoList();

    QListWidget *videoPlaylist = new QListWidget();
	for (int i = 0; i < videoFiles.size(); i++)
		new QListWidgetItem(videoFiles[i].fileName(), videoPlaylist);
    videoPlaylist->setCurrentRow(0);

	QPushButton *startBtn = new QPushButton("Start");
    connect(videoPlaylist, SIGNAL(itemDoubleClicked(QListWidgetItem *)), startBtn, SLOT(animateClick()));
	pauseBtn = new QPushButton("Pause");
    pauseBtn->setEnabled(false);

    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(startBtn);
    controlsLayout->addWidget(pauseBtn);

    QWidget *controlsWidget = new QWidget();
    controlsWidget->setLayout(controlsLayout);

    QVBoxLayout *playlistLayout = new QVBoxLayout();
    playlistLayout->addWidget(new QLabel("Videos:"));
    playlistLayout->addWidget(videoPlaylist);
    playlistLayout->addWidget(controlsWidget);

    QWidget *playlistWidget = new QWidget();
    playlistWidget->setLayout(playlistLayout);

    layout->addWidget(settingsWidget);
    layout->addWidget(playlistWidget);
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

void BuzzerControl::videoPlaying(bool playing) {
    // pauseBtn -> set Text to resume and pause etc
}

void BuzzerControl::videoFinished() {
}

BuzzerLive::BuzzerLive() {
	soundPlayer = new QMediaPlayer();
	inWin = false;
	buzzDir = new QDir("media/buzzer/sounds/");
	mp3Files = buzzDir->entryList(QDir::Files);

	textTimeout = new QTimer;
	textTimeout->setInterval(3000);
	connect(textTimeout, SIGNAL(timeout()), this, SLOT(killText()));

	dTeamName = new QLabel();
	dTeamName->setWordWrap(true);
	dTeamName->setAlignment(Qt::AlignCenter);
	dTeamName->setStyleSheet("margin: 0; padding: 0; background-color: black; color: white; font: 100pt;");

    videoPlayer = new QMediaPlayer();
    videoWidget = new QVideoWidget();
    videoPlayer->setVideoOutput(videoWidget);
    connect(videoPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this , SLOT(videoStateChanged(QMediaPlayer::State)));

    layout = new QStackedLayout();
	layout->addWidget(dTeamName);
    layout->addWidget(videoWidget);
    layout->setCurrentWidget(dTeamName);
    connect(layout, SIGNAL(currentChanged(int)), this, SLOT(checkVideoHidden(int)));

    setLayout(layout);
}

void BuzzerLive::teamWin(QString teamName) {
	if (inWin)
		return;
	inWin = true;
    layout->setCurrentWidget(dTeamName);
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
	soundPlayer->setMedia(QUrl::fromLocalFile(buzzDir->path() + "/" + mp3Files[rnum]));
	soundPlayer->play();
}

void BuzzerLive::checkVideoHidden(int index) {
    if (layout->widget(index) != videoWidget)
        videoPlayer->pause();

}

void BuzzerLive::videoStateChanged(QMediaPlayer::State state) {
    switch (state) {
        case QMediaPlayer::PlayingState:
            layout->setCurrentWidget(videoWidget);
            emit videoPlaying(true);
            break;
        case QMediaPlayer::PausedState:
            emit videoPlaying(false);
            break;
        default:
            break;
    }
}

void BuzzerLive::videoStatusChanged(QMediaPlayer::MediaStatus status) {
    switch (status) {
        case QMediaPlayer::EndOfMedia:
            emit videoFinished();
            layout->setCurrentWidget(dTeamName);
            break;
        default:
            break;
    }
}

void BuzzerLive::setVideoPlaying(bool state) {
    if (state)
        videoPlayer->play();
    else
        videoPlayer->pause();
}

void BuzzerLive::setVideo(QString path) {
    videoPlayer->stop();
    videoPlayer->setMedia(QUrl::fromLocalFile(path));
    videoPlayer->play();
}
