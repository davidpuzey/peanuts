#include <QtGui>
#include "livescreen.h"

class MainWindow : public QWidget {
    Q_OBJECT
	
	public:
		MainWindow();

	private slots:
		void openLiveScreen();
		void closeLiveScreen();
		void toggleLiveScreen();
	
	signals:
		void isLiveSignal(bool); // Determines the live states, set true for live, set false for not live

	private:
		QPushButton *goLiveButton;
		bool isLive();
		void setLiveState(bool);
		bool currentLiveState;
		LiveScreen *livescreen;
		void closeEvent(QCloseEvent *event);
};