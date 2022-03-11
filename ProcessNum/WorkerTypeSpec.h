#pragma once
enum class WorkerType;
class SocketManager;

class WorkerTypeSpec 
{
public:
	virtual WorkerType getType() = 0;

};

class StartWorkerSpec : public WorkerTypeSpec
{
public:
	virtual WorkerType getType();
};

class SendWorkerSpec : public WorkerTypeSpec
{
public:
	SendWorkerSpec(SocketManager* socketManager = nullptr);
	virtual WorkerType getType();
	SocketManager* m_socketManager;
};

class ProcessWorkerSpec : public WorkerTypeSpec
{
public:
	virtual WorkerType getType();
};

class TextWorkerSpec : public WorkerTypeSpec
{
public:
	virtual WorkerType getType();
};