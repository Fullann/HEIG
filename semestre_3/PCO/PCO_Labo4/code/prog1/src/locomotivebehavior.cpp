//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include "locomotivebehavior.h"
#include "ctrain_handler.h"

void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    /* A vous de jouer ! */

    // Vous pouvez appeler les méthodes de la section partagée comme ceci :
    //sharedSection->access(loco);
    //sharedSection->leave(loco);

    while(true) {
        // Accès à la section partagée
        attendre_contact((clockwise ? clockwiseTrigger : cclockwiseTrigger));
        loco.afficherMessage("J'ai atteint le contact trigger");
        sharedSection->access(loco);
        diriger_aiguillage((clockwise ? clockwiseSwitch : cclockwiseSwitch),  etatAiguillage, 0);

        // Sort de la section partagée
        attendre_contact((!clockwise ? clockwiseTrigger : cclockwiseTrigger));
        sharedSection->leave(loco);

        // Passe par la gare
        attendre_contact((clockwise ? stationClockwiseTrigger : stationCClockwiseTrigger));
        if((++nbToursFaits) >= nbTours){
            station->arriveAtStation(loco);
            changerSens();
            nbToursFaits = 0;
        }
    }
}

void LocomotiveBehavior::printStartMessage()
{
    qDebug() << "[START] Thread de la loco" << loco.numero() << "lancé";
    loco.afficherMessage("Je suis lancée !");
}

void LocomotiveBehavior::printCompletionMessage()
{
    qDebug() << "[STOP] Thread de la loco" << loco.numero() << "a terminé correctement";
    loco.afficherMessage("J'ai terminé");
}

void LocomotiveBehavior::changerSens(){
    loco.inverserSens();
    clockwise = (!clockwise);
}
