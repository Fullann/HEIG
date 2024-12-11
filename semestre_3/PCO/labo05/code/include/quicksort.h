#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <queue>

#include <pcosynchro/pcothread.h>
#include <pcosynchro/pcomutex.h>
#include <pcosynchro/pcoconditionvariable.h>
#include "multithreadedsort.h"

/**
 * @brief The Quicksort class implements the multi-threaded Quicksort algorithm.
 */
template<typename T>
class Quicksort: public MultithreadedSort<T>
{
public:
    Quicksort(unsigned int nbThreads) : MultithreadedSort<T>(nbThreads) {}

    /**
     * @brief sort Manages the threads to sort the given sequence.
     * @param array is the sequence to sort
     */
    void sort(std::vector<T>& array) override {
        this->arrayToSort = &array;
        produce(0, array.size() - 1);
        std::vector<std::unique_ptr<PcoThread>> threads;
        // Create threads
        for (int i = 0; i < this->nbThreads; i++){
            PcoThread *thread = new PcoThread(&Quicksort::work, this);
            threads.push_back(std::unique_ptr<PcoThread>(thread));
        }
        // Join threads
        for ( int i = 0; i < this->nbThreads; i++){
            threads[i]->join();
        }
    }
    /**
     * @brief work The main function of the threads. It consumes tasks from the queue and sorts the corresponding part of the array.
     */
    void work(){
        while (true) {
            if (!consume())
                break; // No more tasks to consume
        }
    }

    private:

    /**
     * @brief partition Partitions the array between the indexes lo and hi.
     * @param lo is the lower index of the array
     * @param hi is the higher index of the array
     */
    int partition(int lo, int hi) {
            T pivot = (*arrayToSort)[hi];
            int i = lo;

            for (int j = lo; j < hi; j++) {
                if ((*arrayToSort)[j] <= pivot) {
                    std::swap((*arrayToSort)[i], (*arrayToSort)[j]);
                    i++;
                }
            }
            std::swap((*arrayToSort)[i], (*arrayToSort)[hi]);
            return i;
        }

    /**
     * @brief quicksort Sorts the array between the indexes lo and hi.
     * @param lo is the lower index of the array
     * @param hi is the higher index of the array
     */
    void quicksort(int lo, int hi) {
        //Check if the array is empty or if the indexes are invalid
        if (lo >= hi || lo < 0) {
            return;
        }

        int p = partition(lo, hi);

        produce(lo, p - 1); // Left part of the pivot
        produce(p + 1, hi); // Right part of the pivot
    }

    /**
     * @brief produce Produces a task to sort the array between the indexes lo and hi.
     * @param lo is the lower index of the array
     * @param hi is the higher index of the array
     */
    void produce(int lo, int hi) {
        mutex.lock();
        if (lo < hi) {
            tasks.push({lo, hi});
            cv.notifyOne();
        }
        mutex.unlock();
    }
    /**
     * @brief consume Consumes a task from the queue and sorts the corresponding part of the array.
     */
    bool consume() {
            mutex.lock();
            while (tasks.empty() && !isSorted) {
                cv.wait(&mutex);
            }

            if (tasks.empty()) {
                mutex.unlock();
                return false;
            }

            std::pair<int, int> range = tasks.front();
            tasks.pop();
            if (tasks.empty()) {
                isSorted = true;
                cv.notifyAll();
            }

            mutex.unlock();
            quicksort(range.first, range.second);

            return true;
        }

    std::vector<T>* arrayToSort;
    PcoMutex mutex;
    PcoConditionVariable cv;
    std::queue<std::pair<int, int>> tasks;
    bool isSorted;
};


#endif // QUICKSORT_H
