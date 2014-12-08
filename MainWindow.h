#include <QtWidgets>
#include "livescreen.h"
#include "modules/BaseModule.h"

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
		QPushButton *clearButton;
		QPushButton *blackoutButton;
		QPushButton *goLiveButton;
		bool currentLiveState;
		LiveScreen *livescreen;
		QTabWidget *tehTabs;
		QHBoxLayout *liveSelectButtons;
		QButtonGroup *liveSelectGroup;
		bool isLive();
		void setLiveState(bool);
		void addModule(BaseModule *module);
		void closeEvent(QCloseEvent *event);
};