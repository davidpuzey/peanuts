#include <QtGui>
#include "livescreen.h"

LiveScreen::LiveScreen() {
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::SplashScreen); // Setting up for full screen (on show we set the position of the window)
	setCursor(QCursor(Qt::BlankCursor));
	setWindowTitle(tr("Live Screen"));
	
	screenStack = new QStackedWidget(this);
	
	blackoutScreen = new QWidget(this); // This feels like a hack, but after some research I decided that it was the easiest way. Will look into a better solution once everything is done.
	blackoutScreen->setStyleSheet("background-color: black;"); // Black as it's the blackout screen
	//screenStack->addWidget(blackoutScreen);
	blackoutScreen->hide(); // Ensure that it isn't shown to begin with
	//setLayout(screenStack);
	
	QHBoxLayout *layout = new QHBoxLayout();
	layout->setContentsMargins(0,0,0,0);
	layout->addWidget(screenStack);
	setLayout(layout);
}

/**
 * Toggles blackout screen and sends out a signal indicating the new state of the blackout screen
 */
void LiveScreen::blackoutWindow() {
	blackoutScreen->raise(); // Ensure that the blackout screen is always on top of the everything
	if (blackoutScreen->isHidden())
		blackoutScreen->show();
	else
		blackoutScreen->hide();
	emit isBlackout(!blackoutScreen->isHidden());
}

/**
 * Toggles whether the screen stack is shown or not
 */
void LiveScreen::clearWindow() {
	if (screenStack->isHidden())
		screenStack->show();
	else
		screenStack->hide();
	emit isCleared(screenStack->isHidden());
}

/**
 * addModule - Adds a livescreen module to the livescreen stack and returns it's index position
 */
int LiveScreen::addModule(BaseModule *module) {
	return screenStack->addWidget(module->getLiveWidget());
}

/**
 * switchLivescreen - Switches to a specific livescreen based upon a provided index
 */
 void LiveScreen::switchLivescreen(int index) {
	screenStack->setCurrentIndex(index);
 }

/**
 * Capture events
 */
/**
 * Emit a signal to indicate that the window has been closed
 */
void LiveScreen::closeEvent(QCloseEvent *event) {
	emit liveClosed();
	event->accept();
}

/**
 * Ensure that the window is full screen
 */
void LiveScreen::showEvent(QShowEvent *event) {
	QPalette palette;
	QRect sGeometry = QApplication::desktop()->screenGeometry(1);
	QPixmap bgimage = QPixmap("media/images/background.jpg").scaled(sGeometry.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
	bgimage.scroll((sGeometry.width()-bgimage.width())/2, (sGeometry.height()-bgimage.height())/2, bgimage.rect());
	palette.setBrush(QPalette::Background,bgimage);
	setPalette(palette);
	
	setGeometry(sGeometry);
	blackoutScreen->resize(size()); // Ensure that the blackout screen is the size of the screen
	event->accept();
}