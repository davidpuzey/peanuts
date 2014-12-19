#include <QtWidgets>
#include <QtSerialPort>
#include <QMediaPlayer>
#include "BaseModule.h"

#define MAX_TEAMS 2
typedef QLabel* QLabelArray;

class BuzzerModule : public BaseModule {
	Q_OBJECT
	
	public:
		BuzzerModule();
		
	private:
		QSerialPort *serial;

	signals:
		void teamWin(int);

    public slots:
        void openSerialPort(QString&);
        void closeSerialPort();
        void readSerialPort();
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
	
	signals:
        void sendTeamWin(QString);
        void openSerialPort(QString&);
        void closeSerialPort();
        void readSerialPort();
	
	public slots:
        void teamWin(int team);
	
	private slots:
		void updateSerialPortList();
        void serialGo(bool);
};

class BuzzerLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		BuzzerLive();
	
	private:
        QMediaPlayer *player;
		bool inWin;
		QLabel *dTeamName;
		QDir *buzzDir;
		QStringList mp3Files;
	
	signals:
	
	public slots:
        void teamWin(QString teamName);

    private slots:
        void playRandomSound();
};
