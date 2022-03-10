#include "ThreadControler.h"
#include "worker.h"

ThreadControler::ThreadControler(WorkerType type, SocketManager* parent):m_factory(type, parent)
{
	Worker* worker = m_factory.creat();
	worker->moveToThread(&m_thread);
	connect(&m_thread, &QThread::finished, worker, &QObject::deleteLater);
	connect(this, &ThreadControler::operate, worker, &Worker::doWork);
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
	return m_factory.creat();
}