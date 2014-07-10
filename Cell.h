#ifndef _CELL_H
#define _CELL_H

#include <QWidget>
#include <QLabel>
#include <QPalette>
#include <QBoxLayout>

const int C_SIZE = 100; // Размер ячейки

class Cell : public QWidget
{
	Q_OBJECT
public:
	Cell( const int cellNumber, QWidget * parent = 0 );
	void changeColor( QColor color );
	void setCellNumber( int n );

private:
	QLabel * lbl;
};

#endif
