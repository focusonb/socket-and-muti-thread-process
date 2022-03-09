#pragma once
#include <qobject.h>
#include <qthread.h>

#include "WorkerFactory.h"

class ThreadControler :
	public QObject
{
	Q_OBJECT
public:
	ThreadControler(WorkerType type, SocketManager* parent = nullptr,
		ProcessNumWindow* processNumWindow = nullptr);

	void work();
	Worker* getWorker();
	~ThreadControler();
signals:
	void operate();

private:
	QThread m_thread;
	WorkerFactory m_factory;
	Worker* m_worker;
};

