#include <ctime>
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
		button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
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
	
	
	/* Assign and randomise prizes */
	int i = 0; // Keep track of the current array item
	int x = qCeil((noButtons*0.3)+0.5); // The point at which the prizes switch from silver to bronze, I'm thinking maybe about 30% of the total number are silver prizes
	prizes = new char[noButtons];
	
	prizes[0] = 'G'; // Since we only want 1 gold we shall assign that now
	for (i = 1; i < x; i++) prizes[i] = 'S'; // Assign silver prizes
	for (;i < noButtons; i++) prizes[i] = 'B'; // Assing the rest as silver prizes
	
	qsrand(time(0));
	for (i = 0; i < noButtons; i++) { // Shuffle prizes
		int j = qrand() % noButtons;
		char cur = prizes[i];
		prizes[i] = prizes[j];
		prizes[j] = cur;
	}
	
	numbers = new QLabelArray[noButtons];
	
	for (int i = 0; i < noButtons; i++) {
		numbers[i] = new QLabel(QString::number(i+1), this);
		numbers[i]->setStyleSheet("font-size: 50pt; color: red; font-weight: bold; qproperty-alignment: AlignCenter;");
		
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
	numbers[number]->setText(QString(QChar(prizes[number])));
	if (isVisible())
		switch(prizes[number]) {
			case 'B':
				QSound::play("PrizeBronze.wav");
				return;
			case 'S':
				QSound::play("PrizeSilver.wav");
				return;
			case 'G':
				QSound::play("PrizeGold.wav");
				return;
		}
}