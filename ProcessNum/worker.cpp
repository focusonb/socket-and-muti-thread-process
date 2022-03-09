#include "worker.h"

#include <iostream>
#include <QTimer>
#include <qobject.h>

#include "ProcessNumWindow.h"
#include "socketManager.h"
using std::cout;
using std::endl;
void StartWorker::doWork()
{
	m_socketManager.initialize();
}

SendWorker::SendWorker(SocketManager* socketManager)
	:m_socketManager(socketManager)
{
	
}

void SendWorker::doWork()
{
	//QTimer m_timer;
	//while(1){
	//	connect(&m_timer, &QTimer::timeout, this, &SendWorker::timerSlot);
	//	m_timer.start(50);
	//}
	while (1) {
		if (SocketManager::getData() != 0)
			m_socketManager->sendData();
		Sleep(50);
	}
}

ProcessWorker::ProcessWorker()
{
	
}

void ProcessWorker::doWork()
{
	/*string recstr(SocketManager::data);
	int i = stoi(recstr);
	i++;*/
	//QTimer m_timer(this);
	//connect(&m_timer, &QTimer::timeout, this, &ProcessWorker::timerSlot);
	//m_timer.start(2);
	SocketManager::updateCountOut();
	SocketManager::updateData();
	SocketManager::sendData();
	Sleep(200);
}


textPrintWork::textPrintWork(ProcessNumWindow*  parent):m_processNumWindow(parent)
{
	
}

void textPrintWork::doWork()
{
	//QTimer m_timer;
	//connect(&m_timer, &QTimer::timeout, this, &textPrintWork::timerSlot);
	//m_timer.start(200);
	while (1) {
		//string outStr = std::to_string(SocketManager::countOut);
		//m_processNumWindow->setTextBrowserText(outStr);
		emit print();
		Sleep(400);
	}
}

