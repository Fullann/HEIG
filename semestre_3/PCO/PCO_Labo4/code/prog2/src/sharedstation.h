#ifndef SHARED_STATION_H
#define SHARED_STATION_H

#include <pcosynchro/pcosemaphore.h>
#include "locomotive.h"

class SharedStation
{
public:
    SharedStation() : trainWait(0), mutex(1), trainWaiting(false) {}

    /*!
     * \brief arriveAtStation Arrivée d'un train en gare. Il attends l'autre train plus attends 2 secondes avant de repartir.
     * \param locoBehaviour
     */
    void arriveAtStation(Locomotive& loco);

    /* Implémentez toute la logique que vous avez besoin pour que les locomotives
     * s'attendent correctement à la station */

private:
    PcoSemaphore trainWait;
    PcoSemaphore mutex;
    bool trainWaiting;
};

#endif // SHARED_STATION_H
