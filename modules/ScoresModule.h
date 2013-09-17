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
	
	signals:
		void updateGirlsScore(int);
		void updateBoysScore(int);
		void showGirlsScore(bool);
		void showBoysScore(bool);
};

class ScoresLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		ScoresLive();
	
	private:
		QPixmap outlineText(QString text);
		QLabel *bScore;
		QLabel *gScore;
	
	signals:
		void showBoysScore(bool);
		void showGirlsScore(bool);
	
	public slots:
		void updateBoysScore(int score);
		void updateGirlsScore(int score);
};