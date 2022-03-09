#pragma once
#include <qobject.h>
#include <WinSock2.h>
#include <string>

#include "ThreadControler.h"
#include "MyStrProcessor.h"

using std::string;
class SocketManager :public QObject
{
	Q_OBJECT
public:
	SocketManager(WorkerType type = WorkerType::Processor, WorkerType type2 = WorkerType::Sender
	);
	static void updateData();
	static void updateCountIn();
	static void updateCountOut();

	static void inputData(int input);

	static int getData();
	static int getCountIn();
	static int getCountOut();

	static void sendData();
	static char msg[100];
	static SOCKET hServSock;
	static int count;

	static std::mutex mtx;
	static std::mutex mtx1;
	static std::mutex mtx2;
public slots:
	void initialize();
protected:
	void loopConnection(WSAEVENT&event, SOCKET&sock, int size);
	void makeEvent(SOCKET&sock, WSAEVENT&event, int fd);
	void ErrorHandling(string s);
	void processData(string s);
	void useOtherThread();
private:
	WSADATA wsaData;
	SOCKET loopsock;
	WSAEVENT newEvent;
	WSANETWORKEVENTS netevent;
	ThreadControler m_sendthreadControler;
	ThreadControler m_processthreadControler1;
	ThreadControler m_processthreadControler2;

	int autoSwitchControler = 0;

	static volatile int data;
	static volatile int countIn;
	static volatile int countOut;
};

