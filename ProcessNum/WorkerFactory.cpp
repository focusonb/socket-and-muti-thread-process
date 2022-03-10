#include "WorkerFactory.h"
#include "worker.h"

WorkerFactory::WorkerFactory(WorkerType type
	,SocketManager* socketManager):type(type)
{
	switch (type)
	{
	case WorkerType::Sender:
		m_worker = new SendWorker(socketManager);
		break;
	case WorkerType::TextBrowser:
		m_worker = new textPrintWork;
		break;
	case WorkerType::Processor:
		m_worker = new ProcessWorker;
		break;
	case WorkerType::Start:
		m_worker = new StartWorker;
	}
}

Worker * WorkerFactory::creat()
{
	return m_worker;
}
