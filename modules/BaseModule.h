#include <QtGui>

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
		void showEvent(QShowEvent *event);
		void hideEvent(QHideEvent *event);
};

class BaseModule : public QWidget {
	Q_OBJECT
	
	public:
		BaseModule();
		BaseControl* getControlWidget();
		BaseLive* getLiveWidget();
	
	private:
		BaseControl *controlWidget;
		BaseLive *liveWidget;
	
	protected:
		void setControlWidget(BaseControl *widget);
		void setLiveWidget(BaseLive *widget);
};