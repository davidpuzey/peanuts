#include <QtGui>
#include "PrizeBoardModule.h"

PrizeBoardModule::PrizeBoardModule() {
	setTitle("Prize Board");
	setControlWidget(new PrizeBoardControl);
	setLiveWidget(new PrizeBoardLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
	connect(control, SIGNAL(numberClicked(int)), live, SLOT(chooseNumber(int)));
}

PrizeBoardControl::PrizeBoardControl() {
	QGridLayout *layout = new QGridLayout(this);
	QHBoxLayout *lastRow = new QHBoxLayout();
	
	int noButtons = 24;
	int cols = qCeil(qSqrt(noButtons)); // The closest square root value (works out best fit for the items)
	int cellSwitch = noButtons - (noButtons % cols); // The cell at which the last row starts
	
	// QSignalMapper seems to be the only way to pass the number clicked through (or at least the only way my limited googling turned up)
	QSignalMapper *signalMapper = new QSignalMapper(this);
	
	for (int i = 0; i < noButtons; i++) {
		QPushButton *button = new QPushButton(QString::number(i+1), this);
		button->setCheckable(true);
		connect(button, SIGNAL(clicked(bool)), button, SLOT(setDisabled(bool)));
		connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(button, i);
		
		if (i < cellSwitch)
			layout->addWidget(button, i / cols, i % cols); // To work out rows we divide the current item number by the number of items. To work out columns we take the remainder from the devision (ie use modulus).
		else
			lastRow->addWidget(button);
	}
	
	if (cellSwitch != 0)
		layout->addLayout(lastRow, layout->rowCount(), 0, 1, cols); // Add the last row in seperately, this allows us to centre the buttons is there are less than the number of columns
	
	connect(signalMapper, SIGNAL(mapped(int)), this, SIGNAL(numberClicked(int)));
	
	setLayout(layout);
}

PrizeBoardLive::PrizeBoardLive() {
	QGridLayout *layout = new QGridLayout(this);
	QHBoxLayout *lastRow = new QHBoxLayout();
	
	int noButtons = 24;
	int cols = qCeil(qSqrt(noButtons)); // The closest square root value (works out best fit for the items)
	int cellSwitch = noButtons - (noButtons % cols); // The cell at which the last row starts
	
	numbers = new QLabelArray[noButtons];
	
	for (int i = 0; i < noButtons; i++) {
		numbers[i] = new QLabel(QString::number(i+1), this);
		numbers[i]->setStyleSheet("font-size: 50pt; color: red; font-weight: bold; border: 10px solid #000; qproperty-alignment: AlignCenter;");
		
		
		if (i < cellSwitch)
			layout->addWidget(numbers[i], i / cols, i % cols); // To work out rows we divide the current item number by the number of items. To work out columns we take the remainder from the devision (ie use modulus).
		else
			lastRow->addWidget(numbers[i]);
	}
	
	if (cellSwitch != 0)
		layout->addLayout(lastRow, layout->rowCount(), 0, 1, cols); // Add the last row in seperately, this allows us to centre the buttons is there are less than the number of columns
	
	setLayout(layout);
}

void PrizeBoardLive::chooseNumber(int number) {
	numbers[number]->hide();
	if (isVisible())
		QSound::play("success.wav");
}