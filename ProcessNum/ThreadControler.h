#pragma once
#include <qobject.h>
#include <qthread.h>

#include "WorkerFactory.h"

class ThreadControler :
	public QObject
{
	Q_OBJECT
public:
	ThreadControler(WorkerTypeSpec* spec);
	//ThreadControler& operator= (ThreadControler&) = default ;

	void work();
	Worker* getWorker();
	~ThreadControler();
signals:
	void operate();

private:
	QThread m_thread;
	WorkerFactory m_factory;
};

