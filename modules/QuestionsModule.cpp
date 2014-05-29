#include <ctime>
#include <QtGui>
#include "QuestionsModule.h"

QuestionsModule::QuestionsModule() {
	setTitle("Questions");
	setControlWidget(new QuestionsControl);
	setLiveWidget(new QuestionsLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
}

QuestionsControl::QuestionsControl() {
}

QuestionsLive::QuestionsLive() {
}