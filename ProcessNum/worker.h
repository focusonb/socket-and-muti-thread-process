#pragma once
#include <qobject.h>
#include <qthread>
#include <qtimer.h>
#include "socketManager.h"

class ProcessNumWindow;

class Worker : public QObject
{
	Q_OBJECT
public slots:
	virtual void doWork()=0;
};
class StartWorker : public Worker
{
	Q_OBJECT
public slots:
	void doWork() override;
private:
	SocketManager m_socketManager;
}; 

class SendWorker : public Worker
{
	Q_OBJECT
public:
		SendWorker(SocketManager* socketManager);
public slots:
	void doWork() override;
private:
	SocketManager* m_socketManager;
	//QTimer m_timer;
};

class ProcessWorker : public Worker
{
	Q_OBJECT
public:
		ProcessWorker();
public slots:
	void doWork() override;
	
private:
	//QTimer m_timer;
};


class textPrintWork : public Worker
{
	Q_OBJECT
public:
	textPrintWork();
	~textPrintWork() { closesocket(SocketManager::hServSock); };
public slots:
	void doWork() override;
signals:
	void print();
private:
	//ProcessNumWindow* m_processNumWindow;
	//QTimer m_timer;
};
