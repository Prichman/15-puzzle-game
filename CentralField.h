#ifndef CENTRAL_FIELD_H
#define CENTRAL_FIELD_H

#include "GameField.h"

#include <QWidget>
#include <QLabel>

class CentralField : public QWidget
{
	Q_OBJECT
public:
	CentralField( QWidget * parent = 0 );
	int getCountOfSteps() const;
	void setCountOfSteps( int );
	GameField * getGameField() const;

signals:
	void changeCountOfSteps();

public slots:
	void changeText();
	void incCountOfSteps();

private:
	GameField * gameField;
	QLabel gameStats;
	int countOfSteps = 0;
};

#endif
