#include <QtGui>
//#include <Phonon/VideoPlayer>
#include "BaseModule.h"

typedef QLabel* QLabelArray;

class SongsModule : public BaseModule {
	Q_OBJECT
	
	public:
		SongsModule();
};

class SongsControl : public BaseControl {
	Q_OBJECT
	
	public:
		SongsControl();
};

class SongsLive : public BaseLive {
	Q_OBJECT
	
	
	public:
		SongsLive();
};
