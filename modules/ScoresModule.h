#include <QtGui>
#include "BaseModule.h"

typedef QLabel* QLabelArray;

class ScoresModule : public BaseModule {
	Q_OBJECT
	
	public:
		ScoresModule();
};

class ScoresControl : public BaseControl {
	Q_OBJECT
	
	public:
		ScoresControl();
};

class ScoresLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		ScoresLive();
	
	private:
		QPixmap outlineText(QString text);
};