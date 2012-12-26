#include <QtGui>

class LiveScreen : public QWidget {
	Q_OBJECT
	
	public:
		LiveScreen();
	
	signals:
		void liveClosed(); // Used to indicate when the live screen has been closed
	
	private:
		void closeEvent(QCloseEvent *event);
};