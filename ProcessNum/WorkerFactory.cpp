#include "WorkerFactory.h"
#include "worker.h"
#include "WorkerTypeSpec.h"

WorkerFactory::WorkerFactory(WorkerTypeSpec* WorkerSpec)
{
	WorkerType type = WorkerSpec->getType();
	switch (type)
	{
		case WorkerType::Sender: {
			SendWorkerSpec* sPec = static_cast<SendWorkerSpec*>(WorkerSpec);
			m_worker = new SendWorker(sPec->m_socketManager);
			break;
		}
		case WorkerType::TextBrowser: {
			m_worker = new textPrintWork;
			break;
		}
		case WorkerType::Processor: {
			m_worker = new ProcessWorker;
			break;
		}
		case WorkerType::Start: {
			m_worker = new StartWorker;
		}
	}
}

Worker * WorkerFactory::creat()
{
	return m_worker;
}
