#pragma once
enum class WorkerType{Sender, TextBrowser,Processor, Start,
};
class Worker;
class SocketManager;
class ProcessNumWindow;
class WorkerTypeSpec;

class WorkerFactory
{
public:
	WorkerFactory(WorkerTypeSpec* WorkerSpec);
	Worker* creat();
private:
	//WorkerType type;
	Worker* m_worker;
};

