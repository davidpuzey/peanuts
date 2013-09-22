#include <ctime>
#include <QtGui>
#include "ScoresModule.h"

ScoresModule::ScoresModule() {
	setTitle("Scores");
	setControlWidget(new ScoresControl);
	setLiveWidget(new ScoresLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
}

ScoresControl::ScoresControl() {
	QVBoxLayout *layout = new QVBoxLayout(this);
	
	QPushButton *switchBtn = new QPushButton("<- Switch ->");
	layout->addWidget(switchBtn);
	
	QHBoxLayout *controlLayout = new QHBoxLayout();
	
	QVBoxLayout *boysLayout = new QVBoxLayout();
	QLabel *bTitleLabel = new QLabel("Boys");
	bTitleLabel->setAlignment(Qt::AlignCenter);
	boysLayout->addWidget(bTitleLabel);
	QPushButton *bDispBtn = new QPushButton("Display Scores");
	boysLayout->addWidget(bDispBtn);
	boysLayout->addWidget(new QLabel("Amount to add:"));
	QLineEdit *bScoreAddTxt = new QLineEdit();
	bScoreAddTxt->setValidator(new QIntValidator(this));
	boysLayout->addWidget(bScoreAddTxt);
	QPushButton *bAddBtn = new QPushButton("Add to score");
	boysLayout->addWidget(bAddBtn);
	boysLayout->addWidget(new QLabel("Current Score:"));
	QLineEdit *bScoreTxt = new QLineEdit();
	bScoreTxt->setValidator(new QIntValidator(this));
	boysLayout->addWidget(bScoreTxt);
	QPushButton *bUpdateScoreTxt = new QPushButton("Update Score");
	boysLayout->addWidget(bUpdateScoreTxt);
	
	QVBoxLayout *girlsLayout = new QVBoxLayout();
	QLabel *gTitleLabel = new QLabel("Girls");
	gTitleLabel->setAlignment(Qt::AlignCenter);
	girlsLayout->addWidget(gTitleLabel);
	QPushButton *gDispBtn = new QPushButton("Display Scores");
	girlsLayout->addWidget(gDispBtn);
	girlsLayout->addWidget(new QLabel("Amount to add:"));
	QLineEdit *gScoreAddTxt = new QLineEdit();
	gScoreAddTxt->setValidator(new QIntValidator(this));
	girlsLayout->addWidget(gScoreAddTxt);
	QPushButton *gAddBtn = new QPushButton("Add to score");
	girlsLayout->addWidget(gAddBtn);
	girlsLayout->addWidget(new QLabel("Current Score:"));
	QLineEdit *gScoreTxt = new QLineEdit();
	gScoreTxt->setValidator(new QIntValidator(this));
	girlsLayout->addWidget(gScoreTxt);
	QPushButton *gUpdateScoreTxt = new QPushButton("Update Score");
	girlsLayout->addWidget(gUpdateScoreTxt);
	
	controlLayout->addLayout(boysLayout);
	controlLayout->addLayout(girlsLayout);
	layout->addLayout(controlLayout);
	
	setLayout(layout);
}

ScoresLive::ScoresLive() {
	
}

QPixmap ScoresLive::outlineText(QString text) {
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
	painter.setBrush(QBrush(Qt::red));
	painter.setPen(pen);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPath(path);
	
	painter.setFont(font); // Remove the rubbish from the image so we only have the text
	QRect textBounds = painter.boundingRect(canvas->rect(), 0, text);
	
	return canvas->copy(textBounds);
}