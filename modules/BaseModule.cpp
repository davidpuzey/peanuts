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
BaseSettings::BaseSettings() {
    // TODO Get the settings based on the current title .. refresh when 'setSettingsWidget' is called
}

QString BaseSettings::get(QString var) {
    return var;
}
