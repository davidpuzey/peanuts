#include <QtGui>
#include "modules/BaseModule.h"

class LiveScreen : public QWidget {
	Q_OBJECT
	
	public:
		LiveScreen();
	
	signals:
		void liveClosed(); // Used to indicate when the live screen has been closed
		void isBlackout(bool); // Indicates whether the screen is blacked out or not
	
	public slots:
		void blackoutWindow();
		void addModule(BaseModule *module);
	
	private:
		void closeEvent(QCloseEvent *event);
		void showEvent(QShowEvent *event);
		QStackedLayout *screenStack;
		QWidget *blackoutScreen;
};