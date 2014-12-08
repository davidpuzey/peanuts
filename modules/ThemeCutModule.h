#include <QtWidgets>
#include "BaseModule.h"

typedef QLabel* QLabelArray;

class ThemeCutModule : public BaseModule {
	Q_OBJECT
	
	public:
		ThemeCutModule();
};

class ThemeCutControl : public BaseControl {
	Q_OBJECT
	
	public:
		ThemeCutControl();
	
	public slots:
		void playTheme();
		void playCut();
};

class ThemeCutLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		ThemeCutLive();
};