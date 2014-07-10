#include "CentralField.h"

CentralField::CentralField( QWidget * parent ) :
QWidget( parent )
{
	setFixedSize( 5 * ( C_SIZE + 10 ) + 10, 700 );

	gameField = new GameField( this );

	gameStats.setParent( this );
	gameStats.setText( "Steps: 0" );
	gameStats.move( 15, ( C_SIZE + 10 ) * 4 + 20 );
	gameStats.resize( 70, 20 );

	connect( gameField, SIGNAL( stepDone() ), this, SLOT( incCountOfSteps() ) ); // изменить количество шагов
	connect( this, SIGNAL( changeCountOfSteps() ), this, SLOT( changeText() ) ); // изменить текст
	connect( gameField, SIGNAL( stepDone( ) ), gameField, SLOT( isWin( ) ) ); // связь шага и проверки на победу
}

int CentralField::getCountOfSteps() const
{
	return countOfSteps;
}

void CentralField::setCountOfSteps( int n )
{
	countOfSteps = n;
	changeText();
}

GameField * CentralField::getGameField() const
{
	return gameField;
}

void CentralField::incCountOfSteps()
{
	countOfSteps++;
	emit changeCountOfSteps();
}

void CentralField::changeText()
{
	gameStats.setText( "Steps: " + QString::number( countOfSteps ) );
}
