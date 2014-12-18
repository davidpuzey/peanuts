#include <QtWidgets>
#include "BaseModule.h"

#define MAX_TEAMS 8
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
        QTextBox *teanName[MAX_TEAMS];
	
	private:
		QComboBox *serialPortList;
        QPushButton *start;
	
	signals:
        void sendTeamWin(QString&);
	
	private slots:
		void updateSerialPortList();
        void teamWin(int team);
        serialGo(bool);
};

class BuzzerLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		BuzzerLive();
	
	private:
        QMediaPlayer *winSound;
	
	signals:
	
	public slots:
        void teamWin(QString &teamName);

    private slots:
        void playRandomSound();
};
