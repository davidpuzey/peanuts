#include <QtWidgets>
#include "BaseModule.h"

typedef QLabel* QLabelArray;

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
		QLabelArray *numbers;
		char *prizes;
		QPixmap *prizeBronze;
		QPixmap *prizeSilver;
		QPixmap *prizeGold;
		QPixmap outlineText(QString text);
};