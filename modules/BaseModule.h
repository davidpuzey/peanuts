#ifndef BASEMODULE
#define BASEMODULE

#include <QtGui>

class BaseSettings : public QWidget {
    Q_OBJECT

    public:
        BaseSettings();
        void set(QString var, QString val);
        QString get(QString var, QVariant def);
        void setGroup(QString groupName);

    private:
        static QString filename;
        QString group;
        static QSettings *settings;
        static void createSettings();
};

class BaseControl : public QWidget {
	Q_OBJECT

	public:
		BaseControl();
        void setSettingsWidget(BaseSettings *widget);

    private:
        BaseSettings *settings;
};

class BaseLive : public QWidget {
	Q_OBJECT

	public:
		BaseLive();
        void setSettingsWidget(BaseSettings *widget);

	private:
        BaseSettings *settings;
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
        BaseSettings* getSettingsWidget();
        void setSettingsWidget(BaseSettings *widget);
		QString getTitle();

	private:
		BaseControl *controlWidget;
		BaseLive *liveWidget;
        BaseSettings *settings;
		QString title;

	protected:
		void setControlWidget(BaseControl *widget);
		void setLiveWidget(BaseLive *widget);
		void setTitle(QString newTitle);
};

#endif
