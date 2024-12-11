//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#ifndef LOCOMOTIVEBEHAVIOR_H
#define LOCOMOTIVEBEHAVIOR_H

#include "locomotive.h"
#include "launchable.h"
#include "sharedsectioninterface.h"
#include "sharedstation.h"

/**
 * @brief La classe LocomotiveBehavior représente le comportement d'une locomotive
 */
class LocomotiveBehavior : public Launchable
{
public:
    /*!
     * \brief locomotiveBehavior Constructeur de la classe
     * \param loco la locomotive dont on représente le comportement
     */
    LocomotiveBehavior(Locomotive& loco, std::shared_ptr<SharedSectionInterface> sharedSection, std::shared_ptr<SharedStation> station, size_t clockwiseTrigger, size_t clockwiseSwitch, size_t cclockwiseTrigger, size_t cclockwiseSwitch, size_t etatAiguillage, size_t nbTours, size_t stationClockwiseTrigger, size_t stationCClockwiseTrigger /*, autres paramètres éventuels */)
        : loco(loco), sharedSection(sharedSection), station(station), clockwiseTrigger(clockwiseTrigger), cclockwiseTrigger(cclockwiseTrigger), clockwiseSwitch(clockwiseSwitch), cclockwiseSwitch(cclockwiseSwitch), etatAiguillage(etatAiguillage), nbTours(nbTours), nbToursFaits(0), stationClockwiseTrigger(stationClockwiseTrigger), stationCClockwiseTrigger(stationCClockwiseTrigger) {
        // Eventuel code supplémentaire du constructeur
    }

    /*!
     * \brief changerSens Changer le sens de rotation de la locomotive
     */
    void changerSens();

    /*!
     * \brief stopTrain arrêter le train
     */
    void stopTrain(){
        loco.arreter();
    }

    /*!
     * \brief startTrain démarrer le train
     */
    void startTrain(){
        loco.demarrer();
    }

    size_t nbTours, nbToursFaits;

private:
    size_t clockwiseTrigger, cclockwiseTrigger, clockwiseSwitch, cclockwiseSwitch, etatAiguillage, stationClockwiseTrigger, stationCClockwiseTrigger;
    bool clockwise = true;


protected:
    /*!
     * \brief run Fonction lancée par le thread, représente le comportement de la locomotive
     */
    void run() override;

    /*!
     * \brief printStartMessage Message affiché lors du démarrage du thread
     */
    void printStartMessage() override;

    /*!
     * \brief printCompletionMessage Message affiché lorsque le thread a terminé
     */
    void printCompletionMessage() override;

    /**
     * @brief loco La locomotive dont on représente le comportement
     */
    Locomotive& loco;

    /**
     * @brief sharedSection Pointeur sur la section partagée
     */
    std::shared_ptr<SharedSectionInterface> sharedSection;

    std::shared_ptr<SharedStation> station;

    /*
     * Vous êtes libres d'ajouter des méthodes ou attributs
     *
     * Par exemple la priorité ou le parcours
     */
};

#endif // LOCOMOTIVEBEHAVIOR_H
