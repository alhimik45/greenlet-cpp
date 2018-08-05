#include "greenletcontroller.h"
#include "continuation.h"


GreenletController::GreenletController(unsigned short threadsCount)
{
    this->threadsCount=threadsCount;
    this->greenPool = new boost::thread*[threadsCount];
    this->threads = new Fibers_Sheduler[threadsCount];
    this->tasks_mutex = new boost::mutex[threadsCount];
    for(unsigned short i=0;i<threadsCount;i++)
    {

        this->threads[i].tasks_mutex=&this->tasks_mutex[i];
        greenPool[i] = new boost::thread(boost::ref(this->threads[i]));
    }
    this->thrNow=0;
}



void GreenletController::add(Fiber *task)
{
    (thrNow==(threadsCount-1))?thrNow=0:thrNow++;

    boost::mutex::scoped_lock lock(this->tasks_mutex[thrNow]);
    this->threads[thrNow].tasks.add(task);
    this->threads[thrNow].numberOfTasks++;



}

void GreenletController::doAll()
{
    for(int i =0;i<this->threadsCount;i++)
        greenPool[i]->join();
}

