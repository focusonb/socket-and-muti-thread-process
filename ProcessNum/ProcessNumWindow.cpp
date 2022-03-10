#include "ProcessNumWindow.h"
#include <qtextdocument.h>
#include "worker.h"
#include <windows.h>
#include <qthread>
#include <iostream>
#include <string.h>



ProcessNumWindow::ProcessNumWindow(WorkerType type,  QWidget *parent2)
    : m_Controler(type)
	//m_textBrowserControler(WorkerType::TextBrowser, nullptr, this)
{
    ui.setupUi(this);
	m_textBrowserControler = new ThreadControler(WorkerType::TextBrowser, nullptr);
	Worker* worker = m_textBrowserControler->getWorker();
	textPrintWork* pWork = static_cast<textPrintWork*>(worker);
	connect(pWork, &textPrintWork::print,this,
		&ProcessNumWindow::setTextBrowserText);
	m_textBrowserControler->work();
}

ProcessNumWindow::~ProcessNumWindow()
{
}
void ProcessNumWindow::print()
{
	std::cout << "hello" << std::endl;
}

void ProcessNumWindow::startSendData()
{
	m_Controler.work();
}

void ProcessNumWindow::setTextBrowserText()
{
	string strOut = std::to_string(SocketManager::getCountOut());
	QString qstrOut(strOut.c_str());
	string strIn = std::to_string(SocketManager::getCountIn());
	QString qstrIn(strIn.c_str());
	string strData = std::to_string(SocketManager::getData());
	QString qstrData(strData.c_str());
	QString output = "count of output bumber =" + qstrOut + "\n"
		+ "count of input number =" + qstrIn + "\n"
		+ "count of data number =" + qstrData + "\n";
		
	(ui.textBrowser)->setText(output);
}