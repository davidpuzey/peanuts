#include <QtGui>
#include "BaseModule.h"

typedef QLabel* QLabelArray;

class QuestionsModule : public BaseModule {
	Q_OBJECT
	
	public:
		ScoresModule();
};

class QuestionsControl : public BaseControl {
	Q_OBJECT
	
	public:
		QuestionsControl();
	
	private:
		int boysScore;
		int girlsScore;
		QPushButton *bDispBtn;
		QPushButton *gDispBtn;
		QLineEdit *bScoreAddTxt;
		QLineEdit *bScoreTxt;
		QLineEdit *gScoreAddTxt;
		QLineEdit *gScoreTxt;
	
	private slots:
		void showAllSlot();
		void hideAllSlot();
		void boysAddScore();
		void girlsAddScore();
		void boysUpdateScore();
		void girlsUpdateScore();
	
	signals:
		void updateGirlsScore(int);
		void updateBoysScore(int);
		void showGirlsScore(bool);
		void showBoysScore(bool);
};

class QuestionsLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		QuestionsLive();
	
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