#include <QtGui>
#include "interface.h"

Interface::Interface() {
	currentLiveState = false;
	livescreen = new LiveScreen;
	
	goLiveButton = new QPushButton("Go Live");
	goLiveButton->setCheckable(true);
	
	QPushButton *liveTrue = new QPushButton("Live True");
	QPushButton *liveFalse = new QPushButton("Live False");
	
	connect(goLiveButton, SIGNAL(clicked()), this, SLOT(toggleLiveWindow()));
	connect(this, SIGNAL(isLiveSignal(bool)), goLiveButton, SLOT(setChecked(bool)));
	connect(liveTrue, SIGNAL(clicked()), this, SLOT(openLiveWindow()));
	connect(liveFalse, SIGNAL(clicked()), this, SLOT(closeLiveWindow()));
	
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(goLiveButton);
	//layout->addWidget(liveTrue);
	//layout->addWidget(liveFalse);
	
	setLayout(layout);
	
	setWindowTitle(tr("Peanuts"));
}

void Interface::openLiveWindow() {
	setLiveState(true);
}

void Interface::closeLiveWindow() {
	setLiveState(false);
}

void Interface::toggleLiveWindow() {
	if (isLive())
		closeLiveWindow();
	else
		openLiveWindow();
}

bool Interface::isLive() {
	return (currentLiveState) ? true : false; // I know this is the same as just returning the value of currentLiveState, but I'm sure I read somewhere that this is better practice ... can't remember why though :/
}

void Interface::setLiveState(bool state) {
	if (state == currentLiveState)
		return;
	
	currentLiveState = (state) ? true : false;
	livescreen->setVisible(currentLiveState);
	emit isLiveSignal(currentLiveState);
}