#include "tri_par_base.h"
#include "tri_rapide.h"
#include <array>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

using SortingInterface = function<void()>;

const unsigned SEED = 1;
constexpr array<size_t, 6> TEST_SIZES = {10, 100, 1000, 10000, 100000, 1000000};

/**
 * Mesure the execution time of a given function
 * @param fn Function to measure
 * @return Execution time in microseconds
 */
double mesureTime(const SortingInterface &fn) {
    auto start = chrono::steady_clock::now();
    fn();
    auto end = chrono::steady_clock::now();
    chrono::duration<double, std::milli> timeMs = end - start;
    return timeMs.count();
}


int main() {
    // We use the same seed for all tests for consistency
    default_random_engine seededRandom(SEED); // NOLINT(cert-msc51-cpp)
    ofstream outfile("../../rapport/csv/data.csv", ofstream::out);

    // CSV header
    outfile << "size,tri_comptage,tri_par_base (1),tri_par_base (2),tri_par_base (4),tri_par_base (8),tri_par_base (16),tri_rapide"
            << endl;

    // Test for each size
    for (size_t size: TEST_SIZES) {
        // Create a new vector and fill it with random values
        vector<unsigned> data(size);
        generate(data.begin(), data.end(), [&]() { return seededRandom() % 100; });

        // Display the size
        outfile << size << ",";

        // Sort using tri_comptage
        vector<unsigned> tmp(data);
        double time = mesureTime([&]() {
            tri_comptage(data.begin(), data.end(), tmp.begin(), [](unsigned a) { return a; }, 100);
        });
        outfile << time << ",";
        // Sort using tri_par_base (1)
        tmp = data;
        time = mesureTime([&]() {
            tri_par_base<vector<unsigned>::iterator, 1>(tmp.begin(), tmp.end());
        });
        outfile << time << ",";
        // Sort using tri_par_base (2)
        tmp = data;
        time = mesureTime([&]() {
            tri_par_base<vector<unsigned>::iterator, 2>(tmp.begin(), tmp.end());
        });
        outfile << time << ",";
        // Sort using tri_par_base (4)
        tmp = data;
        time = mesureTime([&]() {
            tri_par_base<vector<unsigned>::iterator, 4>(tmp.begin(), tmp.end());
        });
        outfile << time << ",";
        // Sort using tri_par_base (8)
        tmp = data;
        time = mesureTime([&]() {
            tri_par_base<vector<unsigned>::iterator, 8>(tmp.begin(), tmp.end());
        });
        outfile << time << ",";
        // Sort using tri_par_base (16)
        tmp = data;
        time = mesureTime([&]() {
            tri_par_base<vector<unsigned>::iterator, 16>(tmp.begin(), tmp.end());
        });
        outfile << time << ",";
        // Sort using tri_rapide
        tmp = data;
        time = mesureTime([&]() {
            tri_rapide(tmp.begin(), tmp.end());
        });
        outfile << time << endl;
    }

    // Close the file
    outfile.close();

    return EXIT_SUCCESS;
}

