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
	QPushButton *bDispBtn = new QPushButton("Display Scores");
	QLineEdit *bScoreAddTxt = new QLineEdit();
	bScoreAddTxt->setValidator(new QIntValidator(this);
	QPushButton *bAddBtn = new QPushButton("Add to score");
	QLineEdit *bScoreTxt = new QLineEdit();
	bScoreTxt->setValidator(new QIntValidator(this);
	QPushButton *bUpdateScoreTxt = new QPushButton("Update Score");
	boysLayout->addWidget(bDispBtn);
	boysLayout->addWidget(bScoreAddTxt);
	boysLayout->addWidget(bAddBtn);
	boysLayout->addWidget(bScoreTxt);
	boysLayout->addWidget(bUpdateScoreTxt);
	
	QVBoxLayout *girlsLayout = new QVBoxLayout();
	QPushButton *gDispBtn = new QPushButton("Display Scores");
	QLineEdit *gScoreAddTxt = new QLineEdit();
	gScoreAddTxt->setValidator(new QIntValidator(this);
	QPushButton *gAddBtn = new QPushButton("Add to score");
	QLineEdit *gScoreTxt = new QLineEdit();
	gScoreTxt->setValidator(new QIntValidator(this);
	QPushButton *gUpdateScoreTxt = new QPushButton("Update Score");
	girlsLayout->addWidget(gDispBtn);
	girlsLayout->addWidget(gScoreAddTxt);
	girlsLayout->addWidget(gAddBtn);
	girlsLayout->addWidget(gScoreTxt);
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