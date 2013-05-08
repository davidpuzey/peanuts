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
		void resetAll(bool);
};

class NumberChoiceLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		NumberChoiceLive();
	
	signals:
		void resetAll(bool);
	
	public slots:
		void chooseNumber(int number);
	
	private slots:
		void randomizePrizes();
	
	private:
		QLabelArray *numbers;
		char *prizes;
		int noButtons;
		QPixmap *prizeBronze;
		QPixmap *prizeSilver;
		QPixmap *prizeGold;
		QPixmap outlineText(QString text);
};