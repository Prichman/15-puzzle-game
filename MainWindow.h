/*
*	Заголовочный файл для главного окна приложения.
*	
*	TODO: Доделать статистику
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameField.h"
#include "CentralField.h"

#include <QMediaPlayer>
#include <QMainWindow>
#include <QMessageBox>
#include <QBoxLayout>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow( QWidget * parent = 0 );

public slots:
	void createNewGame();
	void gracio();

signals:
	void startNewGame();
	void goodbye();

protected:
	virtual void keyPressEvent( QKeyEvent * pe );

signals:
	void direct( myDir );

private:
	CentralField * mainWidget;

};

#endif
