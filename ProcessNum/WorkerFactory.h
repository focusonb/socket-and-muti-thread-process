#pragma once
enum class WorkerType{Sender, TextBrowser,Processor, Start,
};
class Worker;
class SocketManager;
class ProcessNumWindow;
class WorkerFactory
{
public:
	WorkerFactory(WorkerType type,  SocketManager* socketManager = nullptr);
	Worker* creat();
private:
	WorkerType type;
	Worker* m_worker;
};

