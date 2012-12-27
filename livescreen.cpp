#include <QtGui>
#include "livescreen.h"

LiveScreen::LiveScreen() {
	QPalette palette;
	palette.setBrush(QPalette::Background,QPixmap("background.jpg").scaled(QApplication::desktop()->screenGeometry().size(), Qt::KeepAspectRatioByExpanding));
	setPalette(palette);
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint); // Setting up for full screen (on show we set the position of the window)
	setWindowTitle(tr("Live Screen"));
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
	setGeometry(QApplication::desktop()->screenGeometry());
	event->accept();
}