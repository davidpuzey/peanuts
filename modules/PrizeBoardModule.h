#include <QtGui>
#include "BaseModule.h"

class PrizeBoardModule : public BaseModule {
	public:
		PrizeBoardModule();
};

class PrizeBoardControl : public BaseControl {
	public:
		PrizeBoardControl();
	
	signals:
		void numberClicked(int);
	
	public slots:
		void buttonClicked(int number);
};

class PrizeBoardLive : public BaseLive {
	public:
		PrizeBoardLive();
	
	public slots:
		void chooseNumber(int number);
	
	private:
		QLabel *numbers[25];
};