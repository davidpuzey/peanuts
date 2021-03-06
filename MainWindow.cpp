#include <QtWidgets>
#include "MainWindow.h"
#include "modules/PrizeBoardModule.h"
#include "modules/ThemeCutModule.h"
#include "modules/NumberChoiceModule.h"
#include "modules/BalloonsModule.h"
#include "modules/ScoresModule.h"
#include "modules/QuestionsModule.h"
#include "modules/SongsModule.h"
#include "modules/BuzzerModule.h"

MainWindow::MainWindow() {
	setWindowTitle(tr("Peanuts"));
	currentLiveState = false;
	livescreen = new LiveScreen;
	QShortcut *quitShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);

    QPushButton *settingsButton = new QPushButton("Settings");
    QFrame *divider = new QFrame();
    divider->setFrameShape(QFrame::VLine);
	clearButton = new QPushButton("Clear");
	clearButton->setCheckable(true);
	blackoutButton = new QPushButton("Blackout");
	blackoutButton->setCheckable(true);
	goLiveButton = new QPushButton("Go Live");
	goLiveButton->setCheckable(true);
	
	QVBoxLayout *layout = new QVBoxLayout(this);
	
	QHBoxLayout *toolBar = new QHBoxLayout();
    toolBar->addWidget(settingsButton);
    toolBar->addWidget(divider);
	toolBar->addWidget(clearButton);
	toolBar->addWidget(blackoutButton);
	toolBar->addWidget(goLiveButton);
	
	liveSelectButtons = new QHBoxLayout();
	liveSelectGroup = new QButtonGroup();
	
	QHBoxLayout *mainArea = new QHBoxLayout();
	tehTabs = new QTabWidget();
	mainArea->addWidget(tehTabs);
	addModule(new ScoresModule);
	addModule(new PrizeBoardModule);
	addModule(new SongsModule);
	addModule(new BalloonsModule);
	addModule(new NumberChoiceModule);
	addModule(new ThemeCutModule);
	addModule(new QuestionsModule);
    addModule(new BuzzerModule);
	
	liveSelectButtons->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
	layout->addLayout(toolBar);
	layout->addLayout(liveSelectButtons);
	layout->addLayout(mainArea);
	
	setLayout(layout);
	
	/*QPixmap *tehballon = new QPixmap("BalloonRed.png");
	QWidget *balloons = new QWidget();
	balloons->render(tehballon);
	balloons->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::SplashScreen);
	balloons->show();
	QPushButton *buttonthing = new QPushButton("Stuff", balloons);
	buttonthing->show();*/
	
	// Decided that this stuff is best down here as things go wrong if objects haven't been created before I try to connect them
	connect(goLiveButton, SIGNAL(clicked()), this, SLOT(toggleLiveScreen()));
	connect(blackoutButton, SIGNAL(clicked()), livescreen, SLOT(blackoutWindow()));
	connect(clearButton, SIGNAL(clicked()), livescreen, SLOT(clearWindow()));
	connect(this, SIGNAL(isLiveSignal(bool)), goLiveButton, SLOT(setChecked(bool)));
	connect(livescreen, SIGNAL(liveClosed()), this, SLOT(closeLiveScreen()));
	connect(quitShortcut, SIGNAL(activated()), this, SLOT(closeLiveScreen()));
	connect(liveSelectGroup, SIGNAL(buttonClicked(int)), livescreen, SLOT(switchLivescreen(int)));
}

void MainWindow::closeEvent(QCloseEvent *event) {
	closeLiveScreen();
	event->accept();
}

void MainWindow::openLiveScreen() {
	setLiveState(true);
}

void MainWindow::closeLiveScreen() {
	setLiveState(false);
}

void MainWindow::toggleLiveScreen() {
	if (isLive())
		closeLiveScreen();
	else
		openLiveScreen();
}

bool MainWindow::isLive() {
	return (currentLiveState) ? true : false; // I know this is the same as just returning the value of currentLiveState, but I'm sure I read somewhere that this is better practice ... can't remember why though :/
}

void MainWindow::setLiveState(bool state) {
	if (state == currentLiveState)
		return;
	
	currentLiveState = (state) ? true : false;
	livescreen->setVisible(currentLiveState);
	emit isLiveSignal(currentLiveState);
}

void MainWindow::addModule(BaseModule *module) {
	// Add the livescreen module
	int moduleIndex = livescreen->addModule(module);
	
	// Add a button to switch the livescreen module
	QPushButton *zeButton = new QPushButton(module->getTitle());
	zeButton->setCheckable(true);
	liveSelectButtons->addWidget(zeButton);
	liveSelectGroup->addButton(zeButton);
	liveSelectGroup->setId(zeButton, moduleIndex);
	zeButton->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
	
	//Add a tab to switch to the controls
	tehTabs->addTab(module->getControlWidget(), module->getTitle());
}                               
