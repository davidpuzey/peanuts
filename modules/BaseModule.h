#ifndef BASEMODULE
#define BASEMODULE

#include <QtGui>

class BaseControl : public QWidget {
	Q_OBJECT

	public:
		BaseControl();

    private:
        BaseSettings *settings;

    protected:
        void setSettingsWidget(BaseSettings *widget);
};

class BaseLive : public QWidget {
	Q_OBJECT

	public:
		BaseLive();

	private:
        BaseSettings *settings;
		void pause();
		void showEvent(QShowEvent *event);
		void hideEvent(QHideEvent *event);

    protected:
        void setSettingsWidget(BaseSettings *widget);
};

class BaseModule : public QWidget {
	Q_OBJECT

	public:
		BaseModule();
		BaseControl* getControlWidget();
		BaseLive* getLiveWidget();
        BaseSettings* getSettingsWidget();
		QString getTitle();

	private:
		BaseControl *controlWidget;
		BaseLive *liveWidget;
        BaseSettings *settings;
		QString title;

	protected:
		void setControlWidget(BaseControl *widget);
		void setLiveWidget(BaseLive *widget);
        void setSettingsWidget(BaseSettings *widget);
		void setTitle(QString newTitle);
};

class BaseSettings : public QWidget {
    Q_OBJECT

    public:
        BaseSettings();
        QString get(QString var);
};

#endif
