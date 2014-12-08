#include <ctime>
#include <QtWidgets>
#include <QSound>
#include "ThemeCutModule.h"

ThemeCutModule::ThemeCutModule() {
	setTitle("Theme Cut");
	setControlWidget(new ThemeCutControl);
	setLiveWidget(new ThemeCutLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
}

ThemeCutControl::ThemeCutControl() {
	QHBoxLayout *layout = new QHBoxLayout();
	
	QPushButton *theme = new QPushButton("Play Theme", this);
	QPushButton *cut = new QPushButton("Cut", this);
	
	layout->addWidget(theme);
	layout->addWidget(cut);
	
	connect(theme, SIGNAL(clicked()), this, SLOT(playTheme()));
	connect(cut, SIGNAL(clicked()), this, SLOT(playCut()));
	
	setLayout(layout);
}

void ThemeCutControl::playTheme() {
	QSound::play("media/sounds/theme.wav");
}

void ThemeCutControl::playCut() {
	QSound::play("media/sounds/cut.wav");
}

ThemeCutLive::ThemeCutLive() {
}