#include "WorkerTypeSpec.h"
#include "WorkerFactory.h"

WorkerType StartWorkerSpec::getType()
{
	return WorkerType::Start;
}

SendWorkerSpec::SendWorkerSpec(SocketManager * socketManager):m_socketManager(socketManager)
{
}

WorkerType SendWorkerSpec::getType()
{
	return WorkerType::Sender;
}

WorkerType ProcessWorkerSpec::getType()
{
	return WorkerType::Processor;
}

WorkerType TextWorkerSpec::getType()
{
	return WorkerType::TextBrowser;
}
