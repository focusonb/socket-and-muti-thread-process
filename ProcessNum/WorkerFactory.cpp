#include "WorkerFactory.h"
#include "worker.h"

WorkerFactory::WorkerFactory(WorkerType type, ProcessNumWindow* processNumWindow
	,SocketManager* socketManager):type(type), m_processNumWindow(processNumWindow)
	, m_socketManager(socketManager)
{
}

Worker * WorkerFactory::creat()
{
	switch (type)
	{
	case WorkerType::Sender:
		return new SendWorker(m_socketManager);
	case WorkerType::TextBrowser:
		return new textPrintWork(m_processNumWindow);
	case WorkerType::Processor:
		return new ProcessWorker;
	case WorkerType::Start:
		return new StartWorker;
	}
	return nullptr;
}
