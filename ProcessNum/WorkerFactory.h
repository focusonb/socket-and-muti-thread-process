#pragma once
enum class WorkerType{Sender, TextBrowser,Processor, Start,
};
class Worker;
class SocketManager;
class ProcessNumWindow;
class WorkerFactory
{
public:
	WorkerFactory(WorkerType type, ProcessNumWindow* processNumWindow = nullptr
		, SocketManager* socketManager = nullptr);
	Worker* creat();
private:
	WorkerType type;
	SocketManager* m_socketManager;
	ProcessNumWindow* m_processNumWindow;
};

