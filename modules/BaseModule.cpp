#include <QtGui>
#include "BaseModule.h"

/********* BASE MODULE *********/
BaseModule::BaseModule() {
	controlWidget = new BaseControl;
	liveWidget = new BaseLive;
	setTitle("Base");
}

void BaseModule::setControlWidget(BaseControl *widget) {
	controlWidget = widget;
}

void BaseModule::setLiveWidget(BaseLive *widget) {
	liveWidget = widget;
}

void BaseModule::setSettingsWidget(BaseSettings *widget) {
    settings = widget;
    controlWidget->setSettingsWidget(widget);
    liveWidget->setSettingsWidget(widget);
    widget->setGroup(title);
}

BaseControl* BaseModule::getControlWidget() {
	return controlWidget;
}

BaseSettings* BaseModule::getSettingsWidget() {
    return settingsWidget;
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

BaseControl::setSettingsWidget(BaseSettings *widget) {
    settings = widget
}


/********* BASE LIVE *********/
BaseLive::BaseLive() {
}

void BaseLive::showEvent(QShowEvent *widget) {
}

void BaseLive::hideEvent(QHideEvent *widget) {
}

BaseLive::setSettingsWidget(BaseSettings *widget) {
    settings = widget
}


/******* BASE SETTINGS *******/
struct setting {
    QString name;
    QString value;
}

struct module_settings {
    QString name;
    struct setting settings[];
}


BaseSettings::BaseSettings() {
    filename = "settings";
    group = "General";
}

static void BaseSettings::loadSettingsFile() {
    if (settings_loaded)
        return;

    // TODO Investigate whether this will create difficulties with 'beginGroup' ???
    settings = QSettings(filename, QSettings::IniFormat);
    settings_loaded = true;
}

void BaseSettings::setGroup(QString groupName) {
    group = groupName;
}

void BaseSettings::set(QString var, QString val) {
    // TODO Investigate whether static QSetting will cause problems here
    // ??? Maybe use settings.setValue(group + '/' + var, val) instead???
    settings.beginGroup(group);
    settings.setValue(var, val);
    settings.endGroup();
}

QString BaseSettings::get(QString var, QVariant default = QVariant()) {
    // TODO See comment in 'set()' method
    QString val;

    settings.beginGroup(group);
    val = settings.value(var, default).toString();
    settings.endGroup();

    return val;
}
