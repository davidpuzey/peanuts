#include <QtGui>

class BaseModule : public QWidget {
	Q_OBJECT
	
	public:
		BaseModule();
		BaseControl getControlWidget();
		BaseLive getLiveWidget();
	
	private:
		BaseControl *controlWidget;
		BaseLive *liveWidget;
		void setControlWidget(BaseControl *widget);
		void setLiveWidget(BaseLive *widget);
}

class BaseControl : public QWidget {
	Q_OBJECT
	
	public:
		BaseControl();
};

class BaseLive : public QWidget {
	Q_OBJECT
	
	public:
		BaseLive();
	
	private:
		void pause();
		void hideEvent(QHideEvent *event);
		void showEvent(QShowEvent *event);
};