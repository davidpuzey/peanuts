#include <QtGui>
#include "SongsModule.h"

SongsModule::SongsModule() {
	setTitle("Songs");
	setControlWidget(new SongsControl);
	setLiveWidget(new SongsLive);
	BaseControl *control = getControlWidget();
	BaseLive *live = getLiveWidget();
}

SongsControl::SongsControl() {
	QDir songFiles("media/songs/");
	songFiles.setFilter(QDir::Files | QDir::Hidden);
	QStringList songNames = songFiles.entryList();
	QHBoxLayout *layout = new QHBoxLayout();
	
	QListWidget *songList = new QListWidget(this);
	
	for (int i = 0; i < songNames.size(); i++) {
		new QListWidgetItem(songNames.at(i), songList);
	}
	
	QPushButton *playBtn = new QPushButton("Play");
	
	layout->addWidget(songList);
	layout->addWidget(playBtn);
	
	setLayout(layout);
}

SongsLive::SongsLive() {
	//Phonon::VideoPlayer *player = new Phonon::VideoPlayer(Phonon::VideoCategory, this);
	//player->play("D:\\Kings\\Kids Work\\program\\release\\media\\songs\\Hillsong Kids - (Jesus You're My) Superhero.mp4");
}