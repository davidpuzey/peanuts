#include <QtGui>
#include "livescreen.h"

LiveScreen::LiveScreen() {
	setWindowTitle("Live Screen");
}

void LiveScreen::closeEvent(QCloseEvent *event) {
	emit liveClosed();
	event->accept();
}