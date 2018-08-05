#ifndef GREENLETCONTROLLER_H
#define GREENLETCONTROLLER_H
#define BOOST_THREAD_USE_LIB
#include<boost/thread.hpp>
#include"continuation.h"
#include"vector"

/*
    Author: Alexey Kolpakov
    E-mail: alhimik45@gmail.com
    MIT License
  */

struct Fibers_Sheduler
{
    FiberList tasks;
    unsigned int numberOfTasks;
    boost::mutex *tasks_mutex;
    Fibers_Sheduler():tasks(),numberOfTasks(0){}
    void operator()()
    {


        unsigned int num=0;
        while(1)
        {
            {
             boost::mutex::scoped_lock lock(*tasks_mutex);
             num+=numberOfTasks;
             numberOfTasks=0;
            }

                tasks.go(num);
                tasks.go(num);
                tasks.go(num);
                tasks.go(num);
                tasks.go(num);
                tasks.go(num);
                tasks.go(num);
                tasks.go(num);
                tasks.go(num);
                num=tasks.go(num);

        }

        exe:
            std::cout<<"EXECUTED!!!";

    }


} ;



class GreenletController
{
    unsigned short threadsCount;
    boost::thread **greenPool;
    unsigned short thrNow;
    Fibers_Sheduler * threads;
    boost::mutex *tasks_mutex;
public:
    GreenletController(unsigned short threadsCount);
    void add(Fiber *task);
    void doAll();
};
#include "greenletcontroller.cpp"
#endif // GREENLETCONTROLLER_H
