#include <QtGui>
#include "BaseModule.h"

typedef QLabel* QLabelArray;

class QuestionsModule : public BaseModule {
	Q_OBJECT
	
	public:
		QuestionsModule();
};

class QuestionsControl : public BaseControl {
	Q_OBJECT
	
	public:
		QuestionsControl();
	
	private:
	
	private slots:
	
	signals:
};

class QuestionsLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		QuestionsLive();
	
	private:
	
	signals:
	
	public slots:
};