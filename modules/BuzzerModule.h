#include <QtWidgets>
#include <QtSerialPort>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "BaseModule.h"

#define MAX_TEAMS 2
typedef QLabel* QLabelArray;

class BuzzerModule : public BaseModule {
	Q_OBJECT

	public:
		BuzzerModule();

	private:
		QSerialPort *serial;
		bool teamLocked;

	signals:
		void teamWin(int);

    public slots:
        void openSerialPort(QString&);
        void closeSerialPort();
        void readSerialPort();

	private slots:
		void unlockTeam();
};

class BuzzerControl : public BaseControl {
	Q_OBJECT

	public:
		BuzzerControl();
        QLineEdit *teamName[MAX_TEAMS];

	private:
		QComboBox *serialPortList;
        QPushButton *start;
		QPushButton *refresh;
        QPushButton *pauseBtn;

	signals:
        void sendTeamWin(QString);
        void openSerialPort(QString&);
        void closeSerialPort();
        void readSerialPort();
        void setVideo(QString);
        void setVideoPlaying(bool);

	public slots:
        void teamWin(int team);
        void videoPlaying(bool);
        void videoFinished();

	private slots:
		void updateSerialPortList();
        void serialGo(bool);
};

class BuzzerLive : public BaseLive {
	Q_OBJECT


	public:
		BuzzerLive();

	private:
        QStackedLayout *layout;
        QMediaPlayer *soundPlayer;
		bool inWin;
		QLabel *dTeamName;
		QDir *buzzDir;
		QStringList mp3Files;
		QTimer *textTimeout;
        QMediaPlayer *videoPlayer;
        QVideoWidget *videoWidget;

	signals:
		void unlockTeam();
        void videoPlaying(bool);
        void videoFinished();

	public slots:
        void teamWin(QString teamName);
        void setVideoPlaying(bool);
        void setVideo(QString path);

    private slots:
        void playRandomSound();
		void killText();
        void videoStateChanged(QMediaPlayer::State);
        void videoStatusChanged(QMediaPlayer::MediaStatus);
        void checkVideoHidden(int);
};
