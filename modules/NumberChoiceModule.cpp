#include <ctime>
#include <QtGui>
#include "NumberChoiceModule.h"

NumberChoiceModule::NumberChoiceModule() {
	setTitle("Number Choice");
	setControlWidget(new NumberChoiceControl);
	setLiveWidget(new NumberChoiceLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
	connect(control, SIGNAL(numberClicked(int)), live, SLOT(chooseNumber(int)));
	connect(control, SIGNAL(resetAll(bool)), live, SIGNAL(resetAll(bool)));
}

NumberChoiceControl::NumberChoiceControl() {
	QVBoxLayout *controlBtns = new QVBoxLayout(this);
	QGridLayout *layout = new QGridLayout();
	QHBoxLayout *lastRow = new QHBoxLayout();
	
	int noButtons = 25;
	int cols = qCeil(qSqrt(noButtons)); // The closest square root value (works out best fit for the items)
	int cellSwitch = noButtons - (noButtons % cols); // The cell at which the last row starts
	
	QPushButton *resetButton = new QPushButton("Reset");
	controlBtns->addWidget(resetButton);
	connect(resetButton, SIGNAL(clicked(bool)), this, SIGNAL(resetAll(bool)));
	
	// QSignalMapper seems to be the only way to pass the number clicked through (or at least the only way my limited googling turned up)
	QSignalMapper *signalMapper = new QSignalMapper(this);
	
	for (int i = 0; i < noButtons; i++) {
		QPushButton *button = new QPushButton(QString::number(i+1), this);
		button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		button->setCheckable(true);
		connect(button, SIGNAL(clicked(bool)), button, SLOT(setDisabled(bool)));
		connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
		connect(this, SIGNAL(resetAll(bool)), button, SLOT(setDisabled(bool)));
		connect(this, SIGNAL(resetAll(bool)), button, SLOT(setChecked(bool)));
		signalMapper->setMapping(button, i);
		
		if (i < cellSwitch)
			layout->addWidget(button, i / cols, i % cols); // To work out rows we divide the current item number by the number of items. To work out columns we take the remainder from the devision (ie use modulus).
		else
			lastRow->addWidget(button);
	}
	
	if (cellSwitch != 0)
		layout->addLayout(lastRow, layout->rowCount(), 0, 1, cols); // Add the last row in seperately, this allows us to centre the buttons is there are less than the number of columns
	
	controlBtns->addLayout(layout);
	
	connect(signalMapper, SIGNAL(mapped(int)), this, SIGNAL(numberClicked(int)));
	
	setLayout(controlBtns);
}

NumberChoiceLive::NumberChoiceLive() {
	QGridLayout *layout = new QGridLayout(this);
	QHBoxLayout *lastRow = new QHBoxLayout();
	prizeBronze = new QPixmap("Prize5.png");
	prizeSilver = new QPixmap("Prize10.png");
	prizeGold = new QPixmap("Prize25.png");
	
	noButtons = 25;
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
	connect(this, SIGNAL(resetAll(bool)), this, SLOT(randomizePrizes()));
	
	numbers = new QLabelArray[noButtons];
	
	for (int i = 0; i < noButtons; i++) {
		//numbers[i] = new QLabel(QString::number(i+1), this);
		numbers[i] = new QLabel(this);
		numbers[i]->setPixmap(outlineText(QString::number(i+1)));
		numbers[i]->setStyleSheet("qproperty-alignment: AlignCenter;");
		
		if (i < cellSwitch)
			layout->addWidget(numbers[i], i / cols, i % cols); // To work out rows we divide the current item number by the number of items. To work out columns we take the remainder from the devision (ie use modulus).
		else
			lastRow->addWidget(numbers[i]);
	}
	
	if (cellSwitch != 0)
		layout->addLayout(lastRow, layout->rowCount(), 0, 1, cols); // Add the last row in seperately, this allows us to centre the buttons is there are less than the number of columns
	
	setLayout(layout);
}

void NumberChoiceLive::chooseNumber(int number) {
	//numbers[number]->setText(QString(QChar(prizes[number])));
	QPixmap *prizeImage;
	
	switch(prizes[number]) {
		case 'B':
			if (isVisible()) QSound::play("PrizeBronze.wav");
			prizeImage = prizeBronze;
			break;
		case 'S':
			if (isVisible()) QSound::play("PrizeSilver.wav");
			prizeImage = prizeSilver;
			break;
		case 'G':
			if (isVisible()) QSound::play("PrizeGold.wav");
			prizeImage = prizeGold;
			break;
	}
	QPixmap smallerPrize = prizeImage->scaled(numbers[number]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	QLabel *medal = new QLabel(numbers[number]->parentWidget());
	medal->setAttribute(Qt::WA_DeleteOnClose);
	medal->setPixmap(smallerPrize);
	medal->resize(smallerPrize.size()); // Using . rather than -> with smallerPrize because smallerPrize isn't a pointer
	medal->move(numbers[number]->geometry().center() - medal->geometry().center());
	medal->show();
	connect(this, SIGNAL(resetAll(bool)), medal, SLOT(close()));
}

QPixmap NumberChoiceLive::outlineText(QString text) {
	QPixmap *canvas = new QPixmap(200,200);
	canvas->fill(Qt::transparent);
	
	QFont font;
	font.setPointSize(60);
	font.setBold(true);
	
	QPen pen; // Give a nice black outline
	pen.setWidth(5);
	
	QPainterPath path; // Have to use path to get an outline
	path.addText(0,90, font, text);
	
	QPainter painter(canvas); // Make the outlines text
	painter.setBrush(QBrush(Qt::yellow));
	painter.setPen(pen);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPath(path);
	
	painter.setFont(font); // Remove the rubbish from the image so we only have the text
	QRect textBounds = painter.boundingRect(canvas->rect(), 0, text);
	
	return canvas->copy(textBounds);
}

void NumberChoiceLive::randomizePrizes() {
	qsrand(time(0));
	for (int i = 0; i < noButtons; i++) { // Shuffle prizes
		int j = qrand() % noButtons;
		char cur = prizes[i];
		prizes[i] = prizes[j];
		prizes[j] = cur;
	}
}