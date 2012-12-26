#include <QtGui>
#include "interface.h"

Interface::Interface() {
	currentLiveState = false;
	livescreen = new LiveScreen;
	QShortcut *quitShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), livescreen);
	
	goLiveButton = new QPushButton("Go Live");
	goLiveButton->setCheckable(true);
	
	connect(goLiveButton, SIGNAL(clicked()), this, SLOT(toggleLiveScreen()));
	connect(this, SIGNAL(isLiveSignal(bool)), goLiveButton, SLOT(setChecked(bool)));
	connect(livescreen, SIGNAL(liveClosed()), this, SLOT(closeLiveScreen()));
	connect(quitShortcut, SIGNAL(activated()), this, SLOT(closeLiveScreen()));
	
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(goLiveButton);
	
	setLayout(layout);
	
	setWindowTitle(tr("Peanuts"));
}

void Interface::closeEvent(QCloseEvent *event) {
	closeLiveScreen();
	event->accept();
}

void Interface::openLiveScreen() {
	setLiveState(true);
}

void Interface::closeLiveScreen() {
	setLiveState(false);
}

void Interface::toggleLiveScreen() {
	if (isLive())
		closeLiveScreen();
	else
		openLiveScreen();
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