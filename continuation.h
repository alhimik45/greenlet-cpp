#ifndef CONTINUATION_H
#define CONTINUATION_H



#define GL_ENDED 0
#define GL_ERROR 1
#define GL_YIELDED 2
#define GL_WAITING 3
#include "queue"


class Fiber
{
protected:
    unsigned int _context;
    char _status;
    Fiber();
public:
virtual unsigned char operator ()()=0;


};
Fiber::Fiber()
{
    _context=0;
    _status=GL_WAITING;
}

//#define NEW_GL_THREADS_DISPATCHER GreenletController _GLTD_

//#define GL_THREADS_DISPATCHER_INIT(threads) _GLTD_.init(threads)

#define GL_THREAD_BEGIN(name) class name:public Fiber {


#define GL_THREAD_BODY(name) public:\
    name():Fiber(){}\
  virtual unsigned char operator()(){ \
    switch(_context) { case 0:

#define GL_THREAD_END   }return GL_ENDED;} }

#define GL_INIT(name,thr) name* thr= new name;

#define GL_SHEDULE(thr)  (*thr)()

#define GL_YIELD do { _status=GL_YIELDED;_context = __LINE__; return _status; case __LINE__:;} while(0)

struct list
{
    list * next;
    Fiber * elem;
    list():next(0),elem(0){}


};
class FiberList
{
    list * head;
    list * end;
    unsigned short size;
public:
    FiberList()
    {
        head=0;
        end=0;
        size=0;
    }

    void add(Fiber* fib)
    {
        if (head==0)
        {
            head = new list;
            head->elem=fib;
            end=head;
        }
        else
        {
            list * l;
            l= new list;
            l->elem=fib;
            end->next=l;
            end=l;

        }
        size++;
    }
  char go(unsigned short size)
    {
        list * pt = head;
        int x = size;
        int i=0;
        while ((pt!=0)&&(GL_SHEDULE(pt->elem)<=GL_ERROR))
        {
            head=pt->next;
            delete(pt->elem);
            delete(pt);
            pt=head;
            i++;
            x--;
        }
        list * prev;
        while((pt!=0)&&(i<size-1))
        {
            prev=pt;
            pt=pt->next;
            if (GL_SHEDULE(pt->elem)<=1)
            {
                prev->next=pt->next;
                delete(pt->elem);
                delete(pt);
                pt=prev;
                x--;
            }
            i++;

        }
        return x;
    }
};

template <class Type>
class Chan
{
    std::queue<Type> chan;
    boost::mutex takeMut;
public:
    Chan();
    void operator<<(Type val)
    {
        boost::mutex::scoped_lock lock(takeMut);
        chan.push(val);
    }
    void operator>>(Type& val)
    {
        while(chan.empty());
        boost::mutex::scoped_lock lock(takeMut);
        val=chan.back();
        chan.pop();


    }
};
template<class Type>
Chan<Type>::Chan()
{

}














//vvvcv heiio опрвпр привет пока ляляляля нанан ааа меня лёха проганяет




#endif // CONTINUATION_H
