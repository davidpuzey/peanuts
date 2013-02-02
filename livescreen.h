#include <QtGui>
#include "modules/BaseModule.h"

class LiveScreen : public QWidget {
	Q_OBJECT
	
	public:
		LiveScreen();
	
	signals:
		void liveClosed(); // Used to indicate when the live screen has been closed
		void isBlackout(bool); // Indicates whether the screen is blacked out or not
		void isCleared(bool); // Indicates whether the screen is cleared or not
	
	public slots:
		void blackoutWindow();
		void clearWindow();
		int addModule(BaseModule *module);
		void switchLivescreen(int index);
	
	private:
		void closeEvent(QCloseEvent *event);
		void showEvent(QShowEvent *event);
		QStackedWidget *screenStack;
		QWidget *blackoutScreen;
};