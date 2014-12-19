#include <QtWidgets>
#include "BaseModule.h"

#define MAX_TEAMS 2
typedef QLabel* QLabelArray;

class BuzzerModule : public BaseModule {
	Q_OBJECT
	
	public:
		BuzzerModule();

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
        void sendTeamWin(QString*);
        void openSerialPort(QString&);
        void closeSerialPort();
        void readSerialPort();
	
	private slots:
		void updateSerialPortList();
        void teamWin(int team);
        void serialGo(bool);
};

class BuzzerLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		BuzzerLive();
	
	private:
        //QMediaPlayer *winSound;
	
	signals:
	
	public slots:
        void teamWin(QString *teamName);

    private slots:
        void playRandomSound();
};
