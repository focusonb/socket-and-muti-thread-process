#include "ThreadControler.h"
#include "worker.h"

ThreadControler::ThreadControler(WorkerType type, SocketManager* parent,
	ProcessNumWindow* processNumWindow):m_factory(type, processNumWindow, parent)
{
	m_worker = m_factory.creat();
	m_worker->moveToThread(&m_thread);
	connect(&m_thread, &QThread::finished, m_worker, &QObject::deleteLater);
	connect(this, &ThreadControler::operate, m_worker, &Worker::doWork);
	m_thread.start();
}
ThreadControler::~ThreadControler() {
	m_thread.quit();
	m_thread.wait();
}
void ThreadControler::work()
{
	emit operate();
}
Worker* ThreadControler::getWorker()
{
	return m_worker;
}