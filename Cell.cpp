#include "Cell.h"

Cell::Cell( const int cellNumber, QWidget * parent ) :
QWidget	( parent )
{
	QPalette * color = new QPalette;
	color->setColor( this->backgroundRole(), QColor( 254, 228, 167 ) ); // желтый	

	lbl = new QLabel( this );
	if ( cellNumber != 16 ) {
		lbl->setText( QString::number( cellNumber ) );
	}
	else {
		lbl->setText( QString::number( cellNumber ) );
		color->setColor( this->backgroundRole( ), QColor( 129, 130, 127 ) );
	}

	lbl->setAlignment( Qt::AlignCenter );
	QVBoxLayout * lyt = new QVBoxLayout;
	lyt->addWidget( lbl );
	this->setLayout( lyt );	

	this->setPalette( *color );
	this->setAutoFillBackground( true );
	this->setFixedSize( C_SIZE, C_SIZE);
	
	delete color;
}

void Cell::changeColor( QColor color )
{
	if ( this ) {
		QPalette palette;
		palette.setColor( this->backgroundRole(), color );
		this->setPalette( palette );
	}
}

void Cell::setCellNumber( int n )
{
	lbl->setText( QString::number( n ) );
}
