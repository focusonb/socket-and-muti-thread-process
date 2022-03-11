#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProcessNum.h"

#include "socketManager.h"
#include "ThreadControler.h"


class ProcessNumWindow : public QMainWindow
{
    Q_OBJECT

public:
    ProcessNumWindow(WorkerTypeSpec* startType , 
		WorkerTypeSpec* textType,
		QWidget *parent2 = Q_NULLPTR);
	~ProcessNumWindow();
	
public slots:
	void print();
	void startSendData();
	void setTextBrowserText();

private:
    Ui::ProcessNumClass ui;
	//SocketManager socketManager;
	ThreadControler m_Controler;
	ThreadControler m_textBrowserControler;
};
