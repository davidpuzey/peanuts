#include <QtGui>
#include "livescreen.h"

LiveScreen::LiveScreen() {
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint); // Setting up for full screen (on show we set the position of the window)
	setCursor(QCursor(Qt::BlankCursor));
	setWindowTitle(tr("Live Screen"));
	
	blackout = new QWidget(this); // This feels like a hack, but after some research I decided that it was the easiest way. Will look into a better solution once everything is done.
	blackout->setStyleSheet("background-color: black;"); // Black as it's the blackout screen
	blackout->hide(); // Ensure that it isn't shown to begin with
}

void LiveScreen::blackoutWindow() {
	if (blackout->isHidden())
		blackout->show();
	else
		blackout->hide();
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
	QPixmap bgimage = QPixmap("background.jpg").scaled(sGeometry.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
	bgimage.scroll((sGeometry.width()-bgimage.width())/2, (sGeometry.height()-bgimage.height())/2, bgimage.rect());
	palette.setBrush(QPalette::Background,bgimage);
	setPalette(palette);
	
	setGeometry(sGeometry);
	blackout->resize(size()); // Ensure that the blackout screen is the size of the screen
	event->accept();
}