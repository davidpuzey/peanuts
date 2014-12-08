#include <QtWidgets>
#include "BaseModule.h"

typedef QLabel* QLabelArray;

class BalloonsModule : public BaseModule {
	Q_OBJECT
	
	public:
		BalloonsModule();
};

class BalloonsControl : public BaseControl {
	Q_OBJECT
	
	public:
		BalloonsControl();
	
	signals:
};

class BalloonsLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		BalloonsLive();
	
	public slots:
	
	private:
};