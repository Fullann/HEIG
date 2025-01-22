#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <stack>
#include <vector>
#include <chrono>
#include <cassert>
#include <pcosynchro/pcologger.h>
#include <pcosynchro/pcothread.h>
#include <pcosynchro/pcohoaremonitor.h>

class Runnable {
public:
    virtual ~Runnable() = default;
    virtual void run() = 0;
    virtual void cancelRun() = 0;
    virtual std::string id() = 0;
};

class ThreadPool: public PcoHoareMonitor {
public:
    ThreadPool(int maxThreadCount, int maxNbWaiting, std::chrono::milliseconds idleTimeout)
        : maxThreadCount(maxThreadCount), maxNbWaiting(maxNbWaiting), idleTimeout(idleTimeout), activeThreads(0) {
    }

    ~ThreadPool() {
        monitorIn();

        // Stop the pool and cancel remaining tasks
        stop = true;

        // Cancel remaining tasks in the queue
        while (!items.empty()) {
            auto task = std::move(items.front());
            items.pop();
            task->cancelRun();  // Call cancel for each task
        }

        // Wake up all waiting threads to allow them to terminate
        signalAll(notEmpty);
        signalAll(notFull);

        monitorOut();

        // Wait for all threads to finish
        for (std::unique_ptr<PcoThread> &thread : threads) {
            thread->join();
        }

        // Clear the thread pool
        threads.clear();
    }

    /*
     * Start a runnable. If a thread in the pool is available, assign the
     * runnable to it. If no thread is available but the pool can grow, create a new
     * pool thread and assign the runnable to it. If no thread is available and the
     * pool is at max capacity and there are less than maxNbWaiting threads waiting,
     * block the caller until a thread becomes available again, and else do not run the runnable.
     * If the runnable has been started, returns true, and else (the last case), return false.
     */
    bool start(std::unique_ptr<Runnable> runnable) {
        monitorIn();

        if (stop) {
            monitorOut();
            return false;
        }

        // Wait if the queue is full and we haven't reached maxNbWaiting threads
        while (items.size() >= maxNbWaiting && !stop) {
            wait(notFull);
        }

        if (stop) {
            monitorOut();
            return false;
        }

        // Add the task to the queue
        items.push(std::move(runnable));
        signal(notEmpty);

        // Create a new thread if possible and needed
        if (activeThreads < maxThreadCount) {
            PcoThread *thread = new PcoThread([this]() { this->get(); });
            threads.push_back(std::unique_ptr<PcoThread>(thread));
            ++activeThreads;
        }

        monitorOut();
        return true;
    }

    /* Returns the number of currently running threads. They do not need to be executing a task,
     * just to be alive.
     */
    size_t currentNbThreads() {
        monitorIn();
        size_t count = activeThreads;
        monitorOut();
        return count;
    }

    void get() {
        while (true) {
            std::unique_ptr<Runnable> task;

            monitorIn();

            // Gestion du timeout
            auto startTime = std::chrono::steady_clock::now();

            while (items.empty() && !stop) {
                // Calcul du temps restant
                auto now = std::chrono::steady_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
                auto remainingTime = idleTimeout - elapsedTime;

                if (remainingTime <= std::chrono::milliseconds(0)) {
                    // Timeout atteint, terminer le thread
                    --activeThreads;
                    monitorOut();
                    return;
                }

                // Attendre avec la condition
                wait(notEmpty);
            }

            if (stop && items.empty()) {
                --activeThreads;
                monitorOut();
                return;
            }

            // Récupérer la tâche
            task = std::move(items.front());
            items.pop();
            signal(notFull);

            monitorOut();

            // Exécuter la tâche
            if (task) {
                task->run();
            }
        }
    }

private:
    std::vector<std::unique_ptr<PcoThread>> threads{};        // Threads in the pool
    std::queue<std::unique_ptr<Runnable>> items{};            // Tasks waiting to be executed

    size_t activeThreads;  // Number of active threads (protected by monitor)
    Condition notFull, notEmpty;  // Conditions for managing the task queue
    bool stop = false;  // Indicates whether the thread pool is stopping

    size_t maxThreadCount;     // Max number of threads the pool can grow to
    size_t maxNbWaiting;      // Max number of tasks that can wait
    std::chrono::milliseconds idleTimeout;  // Timeout after which a thread will be terminated if idle
};

#endif // THREADPOOL_H
