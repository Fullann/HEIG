#ifndef SHARED_STATION_H
#define SHARED_STATION_H

#include <pcosynchro/pcosemaphore.h>
#include "locomotive.h"

class SharedStation
{
public:
    SharedStation() : trainWait(0), mutex(1){}

    /*!
     * \brief arriveAtStation
     * \param locoBehaviour
     */
    void arriveAtStation(Locomotive& loco);

    /* Implémentez toute la logique que vous avez besoin pour que les locomotives
     * s'attendent correctement à la station */

private:
    PcoSemaphore trainWait;
    PcoSemaphore mutex;
    bool trainWaiting = false;
};

#endif // SHARED_STATION_H
