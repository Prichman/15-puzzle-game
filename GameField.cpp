#include "GameField.h"

void swapInt( int * a, int * b ) {
	int t = *a;
	*a = *b;
	*b = t;
}

void swapCells( Cell ** a, Cell ** b ) {
	Cell * t = *a;
	*a = *b;
	*b = t;
}

void GameField::createSequence() 
{
	int i, j;
	srand( time( NULL ) );
	bool isRepeat = 0;

	int * a = new int[16];

	for ( i = 0; i < 16; i++ ) {
		do {
			a[i] = rand() % 16 + 1;
			isRepeat = 0;
			for ( j = 0; j < i && !isRepeat; j++ ) {
				if ( a[i] == a[j] )
					isRepeat = 1;
			}
		} while ( isRepeat );
	}

	// Проверка возможности выигрыша
	int k, e, s = 0;
	for ( i = 0; i < 16; i++ ) {
		k = 0;
		if ( a[i] == 16 )
			e = i / 4 + 1;
		else {
			for ( j = i + 1; j < 16; j++ ) {
				if ( a[i] > a[j] )
					k++;
			}
		}
		s += k;
	}
	s += e;
	if ( s % 2 == 0 ) {
		for ( i = 0; i < 16; i++ ) {
			intCell[i] = a[i];
		}
	}
	else {
		for ( i = 0; i < 4; i++ ) {
			for ( j = 0; j < 4; j++ ) {
				intCell[( 3 - j ) * 4 + i] = a[i * 4 + j];
			}
		}
	}

	delete [] a;
}

void GameField::initCells()
{
	int i, j;

	// Нахождение пустого элемента
	bool t = true;
	for ( i = 0; i < 16 && t; i++ ) {
		if ( intCell[i] == 16 ) {
			for ( int j = 0; j < 16 && t; j++ )
			if ( widgets[j] == NULL ) {
				swapCells( &widgets[i], &widgets[j] );
				t = false;
			}
		}
	}

	for ( i = 0; i < 16; i++ ) {
		if ( intCell[i] != 16 )
			widgets[i]->setCellNumber( intCell[i] );
		else
			emptyNumber = i;
	}

}

void GameField::locateCells()
{
	for ( int i = 0; i < 16; i++ ) {
		if ( widgets[i] != NULL )
			widgets[i]->move( ( i % 4 ) * ( C_SIZE + 10 ) + 10, ( i / 4 ) * ( C_SIZE + 10 ) + 10 );
	}
}

GameField::GameField( QWidget * parent ) :
QWidget( parent )
{
	createSequence();

	int i, j;
	for ( i = 0; i < 16; i++ ) {
		if ( intCell[i] == 16 ){
			emptyNumber = i;
			widgets[i] = NULL;
		}
		else {
			widgets[i] = new Cell( intCell[i], this ); // intCell[i] - number
		}
	}

	locateCells();
	isWin();
}

void GameField::isWin()
{
	bool t = true;
	int i;
	QColor color;
	for ( i = 0; i < 16 && t; i++ ) {
		if ( intCell[i] != ( i + 1 ) ) {
			t = false;
			color.setRgb( 254, 228, 167 );
		}
		else
			color.setRgb( 149, 255, 114 );
		widgets[i]->changeColor( color );
	}

	for ( i = i; i < 16 && !t; i++ ) {
		widgets[i]->changeColor( QColor( 254, 228, 167 ) );
	}
	if ( t )
		emit gameWon();
}

void GameField::step( myDir dr)
{
	int curRow = emptyNumber / 4;
	int curColumn = emptyNumber % 4;

	switch ( dr ) {
	case downD:
	{
				  if ( curRow != 0 ) {
					  QPropertyAnimation * anima = new QPropertyAnimation( widgets[emptyNumber - 4], "pos" );
					  anima->setDuration( secDur );
					  anima->setEndValue( QPoint( curColumn * ( C_SIZE + 10 ) + 10, curRow * ( C_SIZE + 10 ) + 10 ) );
					  anima->start();

					  swapCells( &widgets[emptyNumber], &widgets[emptyNumber - 4] );
					  swapInt( &intCell[emptyNumber], &intCell[emptyNumber - 4] );
					  emptyNumber -= 4;

					  emit stepDone(); // ход сделан, сигнал
				  }
				  break;
	}
	case upD:
	{
				if ( curRow != 3 ) {
					QPropertyAnimation * anima = new QPropertyAnimation( widgets[emptyNumber + 4], "pos" );
					anima->setDuration( secDur );
					anima->setEndValue( QPoint( curColumn * ( C_SIZE + 10 ) + 10, curRow * ( C_SIZE + 10 ) + 10 ) );
					anima->start();

					swapCells( &widgets[emptyNumber], &widgets[emptyNumber + 4] );
					swapInt( &intCell[emptyNumber], &intCell[emptyNumber + 4] );
					emptyNumber += 4;

					emit stepDone(); // ход сделан, сигнал
				}
				break;
	}
	case leftD:
	{
				  if ( curColumn != 3 ) {
					  QPropertyAnimation * anima = new QPropertyAnimation( widgets[emptyNumber + 1], "pos" );
					  anima->setDuration( secDur );
					  anima->setEndValue( QPoint( curColumn * ( C_SIZE + 10 ) + 10, curRow * ( C_SIZE + 10 ) + 10 ) );
					  anima->start();

					  swapCells( &widgets[emptyNumber], &widgets[emptyNumber + 1] );
					  swapInt( &intCell[emptyNumber], &intCell[emptyNumber + 1] );
					  emptyNumber += 1;

					  emit stepDone(); // ход сделан, сигнал
				  }
				  break;
	}
	case rightD:
	{
				   if ( curColumn != 0 ) {
					   QPropertyAnimation * anima = new QPropertyAnimation( widgets[emptyNumber - 1], "pos" );
					   anima->setDuration( secDur );
					   anima->setEndValue( QPoint( curColumn * ( C_SIZE + 10 ) + 10, curRow * ( C_SIZE + 10 ) + 10 ) );
					   anima->start();

					   swapCells( &widgets[emptyNumber], &widgets[emptyNumber - 1] );
					   swapInt( &intCell[emptyNumber], &intCell[emptyNumber - 1] );
					   emptyNumber -= 1;

					   emit stepDone(); // ход сделан, сигнал
				   }
				   break;
	}

	}
}
