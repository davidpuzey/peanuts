#include <QtGui>
#include "BaseModule.h"

typedef QLabel* QLabelArray;

class BuzzerModule : public BaseModule {
	Q_OBJECT
	
	public:
		BuzzerModule();
};

class BuzzerControl : public BaseControl {
	Q_OBJECT
	
	public:
		BuzzerControl();
	
	private:
	
	private slots:
	
	signals:
};

class BuzzerLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		BuzzerLive();
	
	private:
	
	signals:
	
	public slots:
};
