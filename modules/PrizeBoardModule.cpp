#include <QtGui>
#include "PrizeBoardModule.h"

PrizeBoardModule::PrizeBoardModule() {
	setControlWidget(new PrizeBoardControl);
	setLiveWidget(new PrizeBoardLive);
	setTitle("Prize Board");
}

PrizeBoardControl::PrizeBoardControl() {
	QGridLayout *layout = new QGridLayout(this);
	QHBoxLayout *lastRow = new QHBoxLayout();
	
	int noButtons = 24;
	int cols = qCeil(qSqrt(noButtons)); // The closest square root value (works out best fit for the items)
	int cellSwitch = noButtons - (noButtons % cols); // The cell at which the last row starts
	
	for (int i = 0; i < noButtons; i++) {
		if (i < cellSwitch)
			layout->addWidget(new QPushButton(QString::number(i+1), this), i / cols, i % cols); // To work out rows we divide the current item number by the number of items. To work out columns we take the remainder from the devision (ie use modulus).
		else
			lastRow->addWidget(new QPushButton(QString::number(i+1), this));
	}
	
	if (cellSwitch != 0)
		layout->addLayout(lastRow, layout->rowCount(), 0, 1, cols); // Add the last row in seperately, this allows us to centre the buttons is there are less than the number of columns
	
	setLayout(layout);
}

PrizeBoardLive::PrizeBoardLive() {
	QPushButton("Stuff", this);
}