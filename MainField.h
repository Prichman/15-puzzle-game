#ifndef MAINFIELD_H
#define MAINFIELD_H

#include "Cell.h"

#include <time.h>
#include <QPropertyAnimation>
#include <QLabel>
#include <QWidget>
#include <QKeyEvent>
#include <QBoxLayout>

enum myDir { upD, downD, leftD, rightD };
const int secDur = 200; // Длительность анимации

class GameField : public QWidget
{
	Q_OBJECT
public:
	GameField( QWidget * parent = 0 );
	void createSequence( ); // Генерация последовательности 
	void initCells(); // инициализация ячеек
	void locateCells(); // размещение ячеек в игровом поле

signals:
	void stepDone();
	void gameWon();

public slots:
	void step( myDir );
	void isWin( );

private:
	Cell * widgets[16]; // сами виджеты
	int intCell[16]; // положение виджетов
	int emptyNumber; // номер пустой ячейки (в таблице (0-15))
};

#endif
