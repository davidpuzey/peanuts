#include <QtGui>
#include "MainWindow.h"

MainWindow::MainWindow() {
	currentLiveState = false;
	livescreen = new LiveScreen;
	QShortcut *quitShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), livescreen);
	
	goLiveButton = new QPushButton("Go Live");
	goLiveButton->setCheckable(true);
	blackoutButton = new QPushButton("Blackout");
	blackoutButton->setCheckable(true);
	
	connect(goLiveButton, SIGNAL(clicked()), this, SLOT(toggleLiveScreen()));
	connect(blackoutButton, SIGNAL(clicked()), livescreen, SLOT(blackoutWindow()));
	connect(this, SIGNAL(isLiveSignal(bool)), goLiveButton, SLOT(setChecked(bool)));
	connect(livescreen, SIGNAL(liveClosed()), this, SLOT(closeLiveScreen()));
	connect(quitShortcut, SIGNAL(activated()), this, SLOT(closeLiveScreen()));
	
	QVBoxLayout *layout = new QVBoxLayout(this);
	
	QHBoxLayout *toolBar = new QHBoxLayout();
	toolBar->addWidget(goLiveButton);
	toolBar->addWidget(blackoutButton);
	
	QHBoxLayout *mainArea = new QHBoxLayout();
	mainArea->addWidget(new QTabWidget);
	
	layout->addLayout(toolBar);
	layout->addLayout(mainArea);
	
	setLayout(layout);
	
	setWindowTitle(tr("Peanuts"));
}

void MainWindow::closeEvent(QCloseEvent *event) {
	closeLiveScreen();
	event->accept();
}

void MainWindow::openLiveScreen() {
	setLiveState(true);
}

void MainWindow::closeLiveScreen() {
	setLiveState(false);
}

void MainWindow::toggleLiveScreen() {
	if (isLive())
		closeLiveScreen();
	else
		openLiveScreen();
}

bool MainWindow::isLive() {
	return (currentLiveState) ? true : false; // I know this is the same as just returning the value of currentLiveState, but I'm sure I read somewhere that this is better practice ... can't remember why though :/
}

void MainWindow::setLiveState(bool state) {
	if (state == currentLiveState)
		return;
	
	currentLiveState = (state) ? true : false;
	livescreen->setVisible(currentLiveState);
	emit isLiveSignal(currentLiveState);
}