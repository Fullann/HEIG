#include "locomotivebehavior.h"
#include "ctrain_handler.h"

// Constructeur utilisant LocomotiveConfig
LocomotiveBehavior::LocomotiveBehavior(Locomotive& loco, const LocomotiveConfig& config)
    : loco(loco),
      sharedSection(config.sharedSection),
      station(config.station),
      cRequest(config.cRequest),
      ccRequest(config.ccRequest),
      cAccess(config.cAccess),
      ccAccess(config.ccAccess),
      cLeave(config.cLeave),
      ccLeave(config.ccLeave),
      cStation(config.cStation),
      ccStation(config.ccStation),
      cAiguillage(config.cAiguillage),
      ccAiguillage(config.ccAiguillage),
      aigDirection(config.aigDirection),
      nbTours(config.nbTours),
      nbToursFaits(0),
      clockwise(true) {
    // Initialisation de la priorité aléatoire
    changeRandomPriority();
}

void LocomotiveBehavior::run()
{
    // Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    while (true) {
        // Attendre le contact de demande
        attendre_contact(clockwise ? cRequest : ccRequest);
        loco.afficherMessage("Contact Request");
        sharedSection->request(loco, loco.priority);

        // Attendre le contact d'accès
        attendre_contact(clockwise ? cAccess : ccAccess);
        loco.afficherMessage("Contact Access");
        sharedSection->access(loco, loco.priority);
        diriger_aiguillage(clockwise ? cAiguillage : ccAiguillage, aigDirection, 0);

        // Attendre le contact de sortie
        attendre_contact(clockwise ? cLeave : ccLeave);
        loco.afficherMessage("Contact Leave");
        sharedSection->leave(loco);

        // Attendre le contact de la gare
        attendre_contact(clockwise ? cStation : ccStation);
        loco.afficherMessage("Contact Station");

        // Gestion des tours et arrivée à la station
        if (++nbToursFaits >= nbTours) {
            station->arriveAtStation(loco);
            changerSens();
            changeRandomPriority();
            nbToursFaits = 0;
            sharedSection->togglePriorityMode();
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

void LocomotiveBehavior::changeRandomPriority()
{
    std::srand(std::time(nullptr));
    loco.priority = std::rand() % 11;
}

void LocomotiveBehavior::changerSens()
{
    loco.inverserSens();
    clockwise = !clockwise;
}
