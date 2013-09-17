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
		QVBoxLayout *bLayout;
		QVBoxLayout *gLayout;
		QLabel *bScore;
		QLabel *gScore;
	
	public slots:
		void updateBoysScore(int score);
		void updateGirlsScore(int score);
		void showBoysScore(bool show);
		void showGirlsScore(bool show);
};