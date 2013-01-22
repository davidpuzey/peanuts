#include <QtGui>
#include "BaseModule.h"

/********* BASE MODULE *********/
BaseModule::BaseModule() {
}

BaseModule::setControlWidget(BaseControl *widget) {
	controlWidget = widget;
}

BaseModule::setLiveWidget(BaseLive *widget) {
	liveWidget = widget;
}

BaseModule::getControlWidget() {
	return controlWidget;
}

BaseModule::getLiveWidget() {
	return liveWidget;
}


/********* BASE CONTROL *********/
BaseControl::BaseControl() {
}


/********* BASE LIVE *********/
BaseLive::BaseLive() {
}