
#include <QRandomGenerator>
#include <iostream>

#include "threadmanager.h"
#include "mythread.h"

ThreadManager::ThreadManager(QObject *parent) :
    QObject(parent)
{}


/**
 * @brief Cette fonction trie une séquence générée aléatoirement
 * @param seq séquence à trier
 * @param nbThreads le nombre de threads à lancer
 * @return séquence triée
 */
std::vector<int> ThreadManager::startSorting(
        std::vector<int> seq,
        unsigned int nbThreads
)
{
    std::vector<std::unique_ptr<PcoThread>> threadList{};
    finished = false;
    
    // TODO création des threads et du vecteur de résultats
    // TODO lancement des threads avec la fonction Bogosort
    // TODO arrêt des threads et récupération du tableau trié
    // TODO retourner le tableau trié
    for (long unsigned int i = 0; i < nbThreads; i++)
    {
        PcoThread *currentThread = new PcoThread(bogosort, seq, this, i, nbThreads);
        threadList.push_back(std::unique_ptr<PcoThread>(currentThread));
    }

    for (long unsigned int i=0; i<nbThreads; i++)
    {
        threadList[i]->join();
    }

    threadList.clear();

    return this->result;
}


void ThreadManager::incrementPercentComputed(double percentComputed)
{
    emit sig_incrementPercentComputed(percentComputed);
}
