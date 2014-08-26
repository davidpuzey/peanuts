#ifndef BASEMODULE
#define BASEMODULE

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
		QString getTitle();
	
	private:
		BaseControl *controlWidget;
		BaseLive *liveWidget;
		QString title;
	
	protected:
		void setControlWidget(BaseControl *widget);
		void setLiveWidget(BaseLive *widget);
		void setTitle(QString newTitle);
};

class BaseSettings : public QWidget {
    Q_OBJECT

    public:
        BaseSettings();
        QString get(QString var);
};

#endif
