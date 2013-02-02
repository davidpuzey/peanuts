#include <QtGui>
#include "BaseModule.h"

class PrizeBoardModule : public BaseModule {
	Q_OBJECT
	
	public:
		PrizeBoardModule();
};

class PrizeBoardControl : public BaseControl {
	Q_OBJECT
	
	public:
		PrizeBoardControl();
	
	signals:
		void numberClicked(int);
};

class PrizeBoardLive : public BaseLive {
	Q_OBJECT
	
	public:
		PrizeBoardLive();
	
	public slots:
		void chooseNumber(int number);
	
	private:
		QLabel *numbers[25];
};