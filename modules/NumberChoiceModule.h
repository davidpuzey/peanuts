#include <QtGui>
#include "BaseModule.h"

typedef QLabel* QLabelArray;

class NumberChoiceModule : public BaseModule {
	Q_OBJECT
	
	public:
		NumberChoiceModule();
};

class NumberChoiceControl : public BaseControl {
	Q_OBJECT
	
	public:
		NumberChoiceControl();
	
	signals:
		void numberClicked(int);
};

class NumberChoiceLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		NumberChoiceLive();
	
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