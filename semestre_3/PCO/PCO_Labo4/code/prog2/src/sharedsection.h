//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//                                         //


#ifndef SHAREDSECTION_H
#define SHAREDSECTION_H

#include <QDebug>

#include <pcosynchro/pcosemaphore.h>

#include "locomotive.h"
#include "ctrain_handler.h"
#include "sharedsectioninterface.h"

/**
 * @brief La classe SharedSection implémente l'interface SharedSectionInterface qui
 * propose les méthodes liées à la section partagée.
 */
class SharedSection final : public SharedSectionInterface
{
public:

    /**
     * @brief SharedSection Constructeur de la classe qui représente la section partagée.
     * Initialisez vos éventuels attributs ici, sémaphores etc.
     */
    SharedSection(size_t nbTrains) : nbTrains(nbTrains), mutex(1), wait(0), priorityMode(PriorityMode::HIGH_PRIORITY), counter(0) {}

    /**
     * @brief request Méthode a appeler pour indiquer que la locomotive désire accéder à la
     * section partagée (deux contacts avant la section partagée).
     * @param loco La locomotive qui désire accéder
     * @param priority Priorité de la locomotive
     */
    void request(Locomotive& loco, int priority) override {
        mutex.acquire();
        priorities.push_back(priority);
        mutex.release();

        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 requested the shared section.").arg(loco.numero())));
    }

    /**
     * @brief access Méthode à appeler pour accéder à la section partagée, doit arrêter la
     * locomotive et mettre son thread en attente si la section est occupée ou va être occupée
     * par une locomotive de plus haute priorité. Si la locomotive et son thread ont été mis en
     * attente, le thread doit être reveillé lorsque la section partagée est à nouveau libre et
     * la locomotive redémarée. (méthode à appeler un contact avant la section partagée).
     * @param loco La locomotive qui essaie accéder à la section partagée
     * @param priority Priorité de la locomotive
     */
    void access(Locomotive &loco, int priority) override {
        bool accessGranted = true;

        // Vérification des priorités
        mutex.acquire();
        for (int prio : priorities) {
            if ((priorityMode == PriorityMode::HIGH_PRIORITY && prio > priority) ||
                (priorityMode == PriorityMode::LOW_PRIORITY && prio < priority)) {
                accessGranted = false;
                break; // Pas besoin de continuer si la priorité ne permet pas l'accès
                }
        }

        // Gestion de l'accès si occupé ou priorité refusée
        if (occupied || !accessGranted) {
            nbWaiting++;
            mutex.release();

            loco.arreter();
            afficher_message(QString("The engine no. %1 Stops.").arg(loco.numero()).toStdString().c_str());
            wait.acquire(); // Attente de notification
            loco.demarrer();

            mutex.acquire();
            nbWaiting--;
        }

        // Suppression de la priorité dans le vecteur
        auto it = std::find(priorities.begin(), priorities.end(), priority);
        if (it != priorities.end()) {
            priorities.erase(it);
        }

        // Marquer la section comme occupée
        occupied = true;
        mutex.release();
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section
     * partagée. (reveille les threads des locomotives potentiellement en attente).
     * @param loco La locomotive qui quitte la section partagée
     * @param locoId L'identidiant de la locomotive qui fait l'appel
     */
    void leave(Locomotive& loco) override {
        mutex.acquire();
        occupied = false;
        if(nbWaiting > 0){
            wait.release();
        }
        mutex.release();

        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 leaves the shared section.").arg(loco.numero())));
    }

    void togglePriorityMode() override {
        mutex.acquire();
        counter++;
        if(counter == nbTrains){
            counter = 0;
            priorityMode = (priorityMode == PriorityMode::HIGH_PRIORITY ? PriorityMode::LOW_PRIORITY : PriorityMode::HIGH_PRIORITY);
        }
        mutex.release();
    }

private:

    /* A vous d'ajouter ce qu'il vous faut */

    // Méthodes privées ...
    // Attributes privés ...
    PcoSemaphore mutex;         // Mutex pour l'access au données
    PcoSemaphore wait;          // Semaphore pour l'attente des trains
    int nbWaiting = 0;          // Nombre de trains en attente
    bool occupied = false;      // Indique si la section est occupée par un train
    PriorityMode priorityMode;  // Mode de priorité actif
    std::vector<int> priorities;// Liste des priorité des trains entre le point request et access
    size_t nbTrains;            // Nombre de trains
    size_t counter;             // Compteur
};


#endif // SHAREDSECTION_H
