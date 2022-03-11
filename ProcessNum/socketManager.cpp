#pragma comment(lib, "Ws2_32.lib")

#include "socketManager.h"
#include <iostream>
#include <qmessagebox.h>
#include <string.h>
#include <Windows.h>
#include <mutex>

#include <stdlib.h>




using std::cout;
using std::endl;

SOCKET SocketManager:: hServSock;
char SocketManager::msg[100];
int SocketManager::count = 0;
volatile int SocketManager::data = 0;
volatile int SocketManager::countIn = 0;
volatile int SocketManager::countOut = 0;
std::mutex SocketManager::mtx;
std::mutex SocketManager::mtx1;
std::mutex SocketManager::mtx2;


SocketManager::SocketManager(WorkerTypeSpec* type, WorkerTypeSpec* type2):
	m_processthreadControler1(type2), m_processthreadControler2(type2), m_sendthreadControler(type)
{
		//ThreadControler controler(new SendWorkerSpec(this));
		//m_sendthreadControler = controler;
}

void SocketManager::initialize()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		string tmp("WSAStartup() error!");
		ErrorHandling(tmp);
	}
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN servAdr;
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	//servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_addr.s_addr = htonl(0x7f000001);
	//servAdr.sin_addr.s_addr = htonl(0x84a10068);
	servAdr.sin_port = htons(atoi("9198"));

	if (::connect(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) != SOCKET_ERROR)
	{
		//string tmp("connect error!");
		//cout << "connect succeed!" << endl;
		newEvent = WSACreateEvent();
		makeEvent(hServSock, newEvent, FD_READ);

		data = 1;//initial input

		m_sendthreadControler.work();
		loopConnection(newEvent, hServSock, sizeof(msg));
	}
	else
	{
		loopsock = socket(PF_INET, SOCK_STREAM, 0);
		SOCKADDR_IN loopAdr;
		memset(&loopAdr, 0, sizeof(loopAdr));
		loopAdr.sin_family = AF_INET;
		loopAdr.sin_addr.s_addr = htonl(INADDR_ANY);
		loopAdr.sin_port = htons(atoi("9198"));
		if (::bind(loopsock, (SOCKADDR*)&loopAdr, sizeof(loopAdr)) == SOCKET_ERROR)
		{
			QMessageBox message(QMessageBox::Warning, "Information", "bind error", QMessageBox::Yes, NULL);
			message.exec();
			return;
		}

		if (::listen(loopsock, 5) == SOCKET_ERROR)
		{
			QMessageBox message(QMessageBox::Warning, "Information", "listen error", QMessageBox::Yes, NULL);
			message.exec();
		}
		SOCKADDR_IN clntAdr;
		int clntAdrLen = sizeof(clntAdr);
		hServSock = ::accept(loopsock, (SOCKADDR*)&clntAdr, &clntAdrLen);
		if (hServSock == SOCKET_ERROR)
		{
			QMessageBox message(QMessageBox::Warning, "Information", "accept error", QMessageBox::Yes, NULL);
			message.exec();
		}
		newEvent = WSACreateEvent();
		makeEvent(hServSock, newEvent, FD_READ);

		//sendData();
		m_sendthreadControler.work();
		loopConnection(newEvent, hServSock, sizeof(msg));

	}

}

void SocketManager::ErrorHandling(string s)
{
	fputs(s.c_str(), stderr);
	fputc('\n', stderr);
	exit(1);
}

void SocketManager::loopConnection(WSAEVENT&event, SOCKET&sock, int size)
{

	while (1)
	{
		WSAWaitForMultipleEvents(1, &event, false, WSA_INFINITE, FALSE);
		WSAEnumNetworkEvents(sock, event, &netevent);
		if (netevent.iErrorCode[FD_READ_BIT] != 0)
		{
			cout << "read error" << endl;
			break;
		}
		memset(msg, 0, 100);
		recv(sock, msg, size, 0);

		string recstr(msg);

		processData(recstr);//read data,update with the new data that is received
	
		
		//cout << "i am server\n";
		//Sleep(50);
		//sendData();
		//memset(msg, 0, recstr.size());
	}
}

void SocketManager::makeEvent(SOCKET&sock, WSAEVENT&event, int fd)
{
	if (WSAEventSelect(sock, event, fd) == SOCKET_ERROR)
	{
		string tmp("WSAEventSelect error");
		ErrorHandling(tmp);
	}
}

void SocketManager::updateData()
{
	std::lock_guard<std::mutex> lck(mtx);
	//data++;
	int i = rand() % 10+1;
	cout << i << endl;
	data = i + data;
}

void SocketManager::updateCountIn()
{
	std::lock_guard<std::mutex> lck(mtx2);
	countIn++;
}

void SocketManager::updateCountOut()
{
	std::lock_guard<std::mutex> lck(mtx1);
	countOut++;
}

void SocketManager::inputData(int input)
{
	std::lock_guard<std::mutex> lck(mtx);
	data = input;
}

int SocketManager::getData()
{
	return data;
}

int SocketManager::getCountIn()
{
	return countIn;
}

int SocketManager::getCountOut()
{
	return countOut;
}



void SocketManager::sendData()
{
	string s = std::to_string(data);
	s = s + "a";
	//cout << "data: "<< data <<" int:" << s.c_str() << endl;

	send(hServSock, s.c_str(), s.size(), 0);
	//memset(msg, 0, sizeof(msg));
}

void SocketManager::processData(string s)
{
	//cout << s << endl;
	MyStrProcessor strProcessor(s);
	vector<string> strArr = strProcessor.split('a');

	for (auto it : strArr) {
		int i = stoi(it);
		if (data >= i)
			continue;
		inputData(i);//updateData data
		updateCountIn();
		useOtherThread();
	}
}
void SocketManager::useOtherThread()
{
	switch (autoSwitchControler)//process new data in another processing thread
	{
	case 0: {//a equlity chance to use one of these threads to avoid waiting for a thread
		m_processthreadControler1.work();
		autoSwitchControler = 1;
		break;
	}
	case 1: {
		m_processthreadControler2.work();
		autoSwitchControler = 0;
		break;
	}
	default: {
		autoSwitchControler = 0;
	}
	}
}

SocketManager::~SocketManager()
{
}