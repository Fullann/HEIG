#include "mythread.h"
#include <iostream>
#include <vector>
#include <algorithm>


int factorielle(int n) {
    return (n == 0 || n == 1) ? 1 : n * factorielle(n - 1);
}

std::vector<int> getPermutation(std::vector<int> seq, int k){
    int n = seq.size();
    std::vector<int> availableElements = seq;
    std::vector<int> permutation;

    for (int i = 0; i < n; ++i) {
        int fact = factorielle(n - 1 - i);
        int index = k / fact;
        permutation.push_back(availableElements[index]);
        availableElements.erase(availableElements.begin() + index);
        k = k % fact;
    }

    return permutation;
}

void bogosort(std::vector<int> seq, ThreadManager* pManager, int k, int nbThread)
{
    int totalPermutations = factorielle((int)seq.size());

    while (!pManager->finished){
        if(PcoThread::thisThread()->stopRequested()) {
            return;
        }

        seq = getPermutation(seq, k);

        if (k + nbThread < totalPermutations){
            k += nbThread;
        } else {
            k = (k + nbThread) % totalPermutations;
        }

        if (std::is_sorted(seq.begin(), seq.end())){
            pManager->finished =  true;
            pManager->result = seq;
            return;
        }

        pManager->incrementPercentComputed((double)1 / totalPermutations);

    }
}
