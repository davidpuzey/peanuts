#include <ctime>
#include <QtGui>
#include "QuestionsModule.h"

QuestionsModule::QuestionsModule() {
	setTitle("Questions");
	setControlWidget(new QuestionsControl);
	setLiveWidget(new QuestionsLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
}

QuestionsControl::QuestionsControl() {
	QHBoxLayout *layout = new QHBoxLayout();
    QListWidget *questionList = new QListWidget(this);
    QFile file("files/questions");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QByteArray background = file.readLine();
        background.chop(1);
        QByteArray line = file.readLine();
        line.chop(1);
        if (line != "")
            new QListWidgetItem(line, questionList);
        else
            new QListWidgetItem(background, questionList);
    }


    layout->addWidget(questionList);
    setLayout(layout);
}

QuestionsLive::QuestionsLive() {
    QHBoxLayout *layout = new QHBoxLayout();
    QLabel *text = new QLabel();
    text->setAlignment(Qt::AlignCenter);
    QFont font = text->font();
    font.setPointSize(72);
    text->setFont(font);
    QPalette palette = text->palette();
    palette.setColor(text->foregroundRole(), Qt::black);
    text->setPalette(palette);
    text->setStyleSheet("background-image: url(./media/images/PrizeBronze.png); background-repeat: no-repeat;");
    text->setText("Testing Stuff");
    layout->addWidget(text);
/*	QPalette palette;
	QRect sGeometry = QApplication::desktop()->screenGeometry(1);
	QPixmap bgimage = QPixmap("media/images/PrizeBronze.png").scaled(sGeometry.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
	bgimage.scroll((sGeometry.width()-bgimage.width())/2, (sGeometry.height()-bgimage.height())/2, bgimage.rect());
	palette.setBrush(QPalette::Background,bgimage);
	setPalette(palette);

	setGeometry(sGeometry);*/
    setLayout(layout);
}
