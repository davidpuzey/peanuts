#include <ctime>
#include <QtGui>
#include "ScoresModule.h"

ScoresModule::ScoresModule() {
	setTitle("Scores");
	setControlWidget(new ScoresControl);
	setLiveWidget(new ScoresLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
	connect(control, SIGNAL(updateGirlsScore(int)), live, SLOT(updateGirlsScore(int)));
	connect(control, SIGNAL(updateBoysScore(int)), live, SLOT(updateBoysScore(int)));
	connect(control, SIGNAL(showGirlsScore(bool)), live, SIGNAL(showGirlsScore(bool)));
	connect(control, SIGNAL(showBoysScore(bool)), live, SIGNAL(showBoysScore(bool)));
}

ScoresControl::ScoresControl() {
	boysScore = 0;
	girlsScore = 0;
	
	QVBoxLayout *layout = new QVBoxLayout(this);
	
	QPushButton *switchBtn = new QPushButton("<- Switch ->");
	layout->addWidget(switchBtn);
	
	QHBoxLayout *controlLayout = new QHBoxLayout();
	
	QFont titleFont = QFont("Arial", 16, QFont::Bold);
	
	QVBoxLayout *boysLayout = new QVBoxLayout();
	
	// Boys
	QLabel *bTitleLabel = new QLabel("Boys");
	bTitleLabel->setFont(titleFont);
	bTitleLabel->setAlignment(Qt::AlignCenter);
	boysLayout->addWidget(bTitleLabel);
	
	QPushButton *bDispBtn = new QPushButton("Display Scores");
	bDispBtn->setCheckable(true);
	boysLayout->addWidget(bDispBtn);
	
	boysLayout->addWidget(new QLabel("Amount to add:"));
	bScoreAddTxt = new QLineEdit();
	bScoreAddTxt->setValidator(new QIntValidator(this));
	bScoreAddTxt->setAlignment(Qt::AlignCenter);
	connect(bScoreAddTxt, SLOT(returnPressed()), this, SLOT(boysAddScore()));
	boysLayout->addWidget(bScoreAddTxt);
	
	QPushButton *bAddBtn = new QPushButton("Add to score");
	connect(bAddBtn, SIGNAL(clicked()), this, SLOT(boysAddScore()));
	boysLayout->addWidget(bAddBtn);
	
	boysLayout->addWidget(new QLabel("Current Score:"));
	bScoreTxt = new QLineEdit();
	bScoreTxt->setValidator(new QIntValidator(this));
	bScoreTxt->setText("0");
	bScoreTxt->setAlignment(Qt::AlignCenter);
	boysLayout->addWidget(bScoreTxt);
	
	QPushButton *bUpdateScoreTxt = new QPushButton("Update Score");
	
	boysLayout->addWidget(bUpdateScoreTxt);
	
	// Girls
	QVBoxLayout *girlsLayout = new QVBoxLayout();
	
	QLabel *gTitleLabel = new QLabel("Girls");
	gTitleLabel->setFont(titleFont);
	gTitleLabel->setAlignment(Qt::AlignCenter);
	girlsLayout->addWidget(gTitleLabel);
	
	QPushButton *gDispBtn = new QPushButton("Display Scores");
	gDispBtn->setCheckable(true);
	girlsLayout->addWidget(gDispBtn);
	
	girlsLayout->addWidget(new QLabel("Amount to add:"));
	gScoreAddTxt = new QLineEdit();
	gScoreAddTxt->setValidator(new QIntValidator(this));
	gScoreAddTxt->setAlignment(Qt::AlignCenter);
	connect(gScoreAddTxt, SLOT(returnPressed()), this, SLOT(girlsAddScore()));
	girlsLayout->addWidget(gScoreAddTxt);
	
	QPushButton *gAddBtn = new QPushButton("Add to score");
	connect(gAddBtn, SIGNAL(clicked()), this, SLOT(girlsAddScore()));
	girlsLayout->addWidget(gAddBtn);
	
	girlsLayout->addWidget(new QLabel("Current Score:"));
	gScoreTxt = new QLineEdit();
	gScoreTxt->setValidator(new QIntValidator(this));
	gScoreTxt->setText("0");
	gScoreTxt->setAlignment(Qt::AlignCenter);
	girlsLayout->addWidget(gScoreTxt);
	
	QPushButton *gUpdateScoreTxt = new QPushButton("Update Score");
	
	girlsLayout->addWidget(gUpdateScoreTxt);
	
	
	controlLayout->addLayout(boysLayout);
	controlLayout->addLayout(girlsLayout);
	layout->addLayout(controlLayout);
	
	setLayout(layout);
	
	connect(gDispBtn, SIGNAL(clicked(bool)), this, SIGNAL(showGirlsScore(bool)));
	connect(bDispBtn, SIGNAL(clicked(bool)), this, SIGNAL(showBoysScore(bool)));
}

void ScoresControl::boysAddScore() {
	boysScore += bScoreAddTxt->text().toInt();
	bScoreTxt->setText(QString::number(boysScore));
	bScoreAddTxt->setText("");
	emit updateBoysScore(boysScore);
}

void ScoresControl::girlsAddScore() {
	girlsScore += gScoreAddTxt->text().toInt();
	gScoreTxt->setText(QString::number(girlsScore));
	gScoreAddTxt->setText("");
	emit updateGirlsScore(girlsScore);
}

void ScoresControl::boysUpdateScore() {

}

void ScoresControl::girlsUpdateScore() {

}

ScoresLive::ScoresLive() {
	QHBoxLayout *layout = new QHBoxLayout(this);
	
	QVBoxLayout *bLayout = new QVBoxLayout();
	QLabel *bTitle = new QLabel();
	bTitle->setAlignment(Qt::AlignCenter);
	bTitle->setPixmap(outlineText("Boys"));
	bLayout->addWidget(bTitle);
	bScore = new QLabel();
	bScore->setVisible(false);
	bScore->setAlignment(Qt::AlignCenter);
	bScore->setPixmap(outlineText("0"));
	bLayout->addWidget(bScore);
	layout->addLayout(bLayout);
	
	QVBoxLayout *gLayout = new QVBoxLayout();
	QLabel *gTitle = new QLabel();
	gTitle->setAlignment(Qt::AlignCenter);
	gTitle->setPixmap(outlineText("Girls"));
	gLayout->addWidget(gTitle);
	gScore = new QLabel();
	gScore->setVisible(false);
	gScore->setAlignment(Qt::AlignCenter);
	gScore->setPixmap(outlineText("0"));
	gLayout->addWidget(gScore);
	layout->addLayout(gLayout);
	setLayout(layout);
	
	connect(this, SIGNAL(showBoysScore(bool)), bScore, SLOT(setVisible(bool)));
	connect(this, SIGNAL(showGirlsScore(bool)), gScore, SLOT(setVisible(bool)));
}


/**
 * Slot to update the boys score
 */
void ScoresLive::updateBoysScore(int score) {
	bScore->setPixmap(outlineText(QString::number(score)));
}

/**
 * Slot to update the girls score
 */
void ScoresLive::updateGirlsScore(int score) {
	gScore->setPixmap(outlineText(QString::number(score)));
}

QPixmap ScoresLive::outlineText(QString text) {
	QPixmap *canvas = new QPixmap(1000,1000);
	canvas->fill(Qt::transparent);
	
	QFont font;
	font.setPointSize(150);
	font.setBold(true);
	
	QFontMetrics fontMetrics(font); // So we can determine the position of the text. We use the ascent function, this gives the distance between the baseline of the text and highest point.
	
	QPen pen; // Give a nice black outline
	pen.setWidth(5);
	
	QPainterPath path; // Have to use path to get an outline
	path.addText(0,fontMetrics.ascent(), font, text); // TODO Find out why I have to minus 10 from the ascent, I'm sure it's very simple, but a task for another day I think.
	
	QPainter painter(canvas); // Make the outlines text
	painter.setBrush(QBrush(Qt::green));
	painter.setPen(pen);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPath(path);
	
	painter.setFont(font); // Remove the rubbish from the image so we only have the text
	QRect textBounds = painter.boundingRect(canvas->rect(), 0, text);
	
	return canvas->copy(textBounds);
}