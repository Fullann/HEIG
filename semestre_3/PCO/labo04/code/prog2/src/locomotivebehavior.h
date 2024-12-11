#ifndef LOCOMOTIVEBEHAVIOR_H
#define LOCOMOTIVEBEHAVIOR_H

#include "locomotive.h"
#include "launchable.h"
#include "sharedsectioninterface.h"
#include "sharedstation.h"

/**
 * @brief Configuration pour le comportement de la locomotive
 */
struct LocomotiveConfig {
    std::shared_ptr<SharedSectionInterface> sharedSection;
    std::shared_ptr<SharedStation> station;
    size_t cRequest, ccRequest, cAccess, ccAccess, cLeave, ccLeave, cStation, ccStation;
    size_t cAiguillage, ccAiguillage, aigDirection;
    size_t nbTours;
};

/**
 * @brief La classe LocomotiveBehavior représente le comportement d'une locomotive
 */
class LocomotiveBehavior : public Launchable
{
public:
    /*!
     * \brief LocomotiveBehavior Constructeur de la classe
     * \param loco La locomotive dont on représente le comportement
     * \param config Configuration de la locomotive
     */
    LocomotiveBehavior(Locomotive& loco, const LocomotiveConfig& config);

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
     * @brief changeRandomPriority Change la priorité de la loco avec un nombre aléatoire entre 0 et 10
     */
    void changeRandomPriority();

    /**
     * @brief changerSens Change le sens de la locomotive et de la variable clockwise
     */
    void changerSens();

private:
    /**
     * @brief loco La locomotive dont on représente le comportement
     */
    Locomotive& loco;

    /**
     * @brief sharedSection Pointeur sur la section partagée
     */
    std::shared_ptr<SharedSectionInterface> sharedSection;

    /**
     * @brief station Pointeur sur la gare
     */
    std::shared_ptr<SharedStation> station;

    // Contacts "Trigger"
    size_t cRequest, ccRequest, cAccess, ccAccess, cLeave, ccLeave, cStation, ccStation;
    // Aiguillages liés à ce train
    size_t cAiguillage, ccAiguillage, aigDirection;
    // Nombre de tours faits et voulus avant l'arrêt en gare
    size_t nbToursFaits, nbTours;
    // Sens de rotation du train
    bool clockwise;
};

#endif // LOCOMOTIVEBEHAVIOR_H
