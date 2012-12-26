#include <QtGui>
#include "livescreen.h"

class Interface : public QWidget {
    Q_OBJECT
	
	public:
		Interface();

	private slots:
		void openLiveWindow();
		void closeLiveWindow();
		void toggleLiveWindow();
	
	signals:
		void isLiveSignal(bool); // Determines the live states, set true for live, set false for not live

	private:
		QPushButton *goLiveButton;
		bool isLive();
		void setLiveState(bool);
		bool currentLiveState;
		LiveScreen *livescreen;
};