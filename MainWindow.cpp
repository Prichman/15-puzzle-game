#include "MainWindow.h"

MainWindow::MainWindow( QWidget * parent ) :
QMainWindow( parent )
{
	setWindowTitle( "15-puzzle" );
	setWindowIcon( QIcon( "Resources/15-puzzleIcon.ico" ) );
	setFixedSize( 4 * ( C_SIZE + 10 ) + 10, 4 * ( C_SIZE + 10 ) + 70 );

	mainWidget = new CentralField;
	setCentralWidget( mainWidget );
	
	QPalette * color = new QPalette;
	color->setColor( QPalette::Background, QColor( 175, 174, 174 ) ); // цвет фона (серый)
	setPalette( *color );
	delete color;

	QMenu * myMenu = new QMenu( "Game" );

	QAction * menuNewGame = new QAction( "New game", 0);
	QAction * menuExit = new QAction( "Exit", 0 );

	myMenu->addAction( menuNewGame );
	myMenu->addSeparator();
	myMenu->addAction( menuExit );
	
	QMenuBar * myBar = new QMenuBar;
	myBar->addMenu( myMenu );
	setMenuBar( myBar );

	connect( menuNewGame, SIGNAL( triggered() ), this, SLOT( createNewGame() ) );
	connect( menuExit, SIGNAL( triggered() ), this, SLOT( close() ) );

	connect( this, SIGNAL( direct( myDir ) ), mainWidget->getGameField(), SLOT( step( myDir ) ) ); // связь хода
	connect( this, SIGNAL( startNewGame() ), this,  SLOT( createNewGame() ) ); // связь для создания новой игры
	connect( mainWidget->getGameField(), SIGNAL( gameWon() ), this, SLOT( gracio() ) ); // Игра выиграна, нужно показать окно
	connect( this, SIGNAL( goodbye() ), this, SLOT( close() ) ); // выход из игры
}

void MainWindow::keyPressEvent( QKeyEvent * pe )
{
	if ( !pe->modifiers() ) {
		switch ( pe->key() ) {
		case Qt::Key_Up: {
							 emit direct( upD );
							 break;
		}
		case Qt::Key_Down: {
							   emit direct( downD );
							   break;
		}
		case Qt::Key_Left: {
							   emit direct( leftD );
							   break;
		}
		case Qt::Key_Right: {
								emit direct( rightD );
								break;
		}
		}
	}
}

void MainWindow::createNewGame()
{
	mainWidget->setCountOfSteps( 0 );

	GameField * gameField = mainWidget->getGameField();
	gameField->createSequence();
	gameField->initCells();
	gameField->locateCells();

	gameField->isWin();
}

void MainWindow::gracio()
{

	QMediaPlayer player;
	player.setMedia( QUrl::fromLocalFile( "Resources/winAudio.mp3" ) );
	player.play();

	QString winText = "You won the game!\n";
	winText += "Count of steps: ";
	winText += QString::number( mainWidget->getCountOfSteps() );
	winText += "\nDo you want to play again now?";

	QMessageBox * winWindow = new QMessageBox( QMessageBox::NoIcon,
											   "Congratulations",
											   winText,
												QMessageBox::Yes | QMessageBox::No
										   	  );
	winWindow->setWindowIcon( QIcon( "Resources/15-puzzleIcon.ico" ) );

	int n = winWindow->exec();
	delete winWindow;

	if ( n == QMessageBox::Yes ) {
		emit startNewGame();
		
	}
	else if ( n == QMessageBox::No) {
		emit goodbye();
	}
}
