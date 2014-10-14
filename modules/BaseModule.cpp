#include <QtGui>
#include "BaseModule.h"

/********* BASE MODULE *********/
BaseModule::BaseModule() {
	controlWidget = new BaseControl;
	liveWidget = new BaseLive;
    settings = new BaseSettings;
	setTitle("Base");
}

void BaseModule::setControlWidget(BaseControl *widget) {
	controlWidget = widget;
    controlWidget->setSettingsWidget(settings);
}

void BaseModule::setLiveWidget(BaseLive *widget) {
	liveWidget = widget;
    liveWidget->setSettingsWidget(settings);
}

void BaseModule::setSettingsWidget(BaseSettings *widget) {
    settings = widget;
    settings->setGroup(title);
}

BaseControl* BaseModule::getControlWidget() {
	return controlWidget;
}

BaseSettings* BaseModule::getSettingsWidget() {
    return settings;
}

BaseLive* BaseModule::getLiveWidget() {
	return liveWidget;
}

void BaseModule::setTitle(QString newTitle) {
	title = newTitle;
}

QString BaseModule::getTitle() {
	return title;
}


/********* BASE CONTROL *********/
BaseControl::BaseControl() {
}

void BaseControl::setSettingsWidget(BaseSettings *widget) {
    settings = widget;
}


/********* BASE LIVE *********/
BaseLive::BaseLive() {
}

void BaseLive::showEvent(QShowEvent *widget) {
}

void BaseLive::hideEvent(QHideEvent *widget) {
}

void BaseLive::setSettingsWidget(BaseSettings *widget) {
    settings = widget;
}


/******* BASE SETTINGS *******/
struct setting {
    QString name;
    QString value;
};

struct module_settings {
    QString name;
    struct setting settings[];
};


BaseSettings::BaseSettings() {
    group = "General";
}

QString BaseSettings::filename = "settings";
QSettings *BaseSettings::settings = new QSettings(BaseSettings::filename, QSettings::IniFormat);

void BaseSettings::setGroup(QString groupName) {
    group = groupName;
}

void BaseSettings::set(QString var, QString val) {
    // TODO Investigate whether static QSetting will cause problems here
    // ??? Maybe use settings.setValue(group + '/' + var, val) instead???
    settings->beginGroup(group);
    settings->setValue(var, val);
    settings->endGroup();
}

QString BaseSettings::get(QString var, QVariant def = QVariant()) {
    // TODO See comment in 'set()' method
    QString val;

    settings->beginGroup(group);
    val = settings->value(var, def).toString();
    settings->endGroup();

    return val;
}
