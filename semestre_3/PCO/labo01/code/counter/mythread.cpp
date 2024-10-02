#include "mythread.h"
#include <mutex>

static volatile long unsigned int counter;
static std::mutex mtx;

void runTask(unsigned long nbIterations)
{
    long unsigned int i = 0;

    mtx.lock();
    while (i < nbIterations)
    {
        counter++;
        i++;
    }
    mtx.unlock();
}

void initCounter()
{
    counter = 0;
}

long unsigned int getCounter()
{
    return counter;
}
