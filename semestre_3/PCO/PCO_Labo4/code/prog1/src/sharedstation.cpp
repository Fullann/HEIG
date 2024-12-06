//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include <chrono>
#include <thread>

#include "sharedstation.h"
#include "locomotive.h"
#include "ctrain_handler.h"
#include <pcosynchro/pcothread.h>

void SharedStation::arriveAtStation(Locomotive& loco){
    afficher_message(qPrintable(QString("The engine no. %1 is at the station.").arg(loco.numero())));
    mutex.acquire();
    if(trainWaiting){
        trainWaiting = false;
        trainWait.release();
        mutex.release();
        loco.arreter();
    } else {
        trainWaiting = true;
        mutex.release();
        loco.arreter();
        trainWait.acquire();
    }
    // Sleep 2 sec
    PcoThread::usleep(2000000);
    loco.demarrer();
}
