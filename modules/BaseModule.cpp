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

BaseControl* BaseModule::getControlWidget() {
	return controlWidget;
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


/********* BASE LIVE *********/
BaseLive::BaseLive() {
}

void BaseLive::showEvent(QShowEvent *widget) {
}

void BaseLive::hideEvent(QHideEvent *widget) {
}