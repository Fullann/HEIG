#include "hospital.h"
#include "costs.h"
#include <iostream>
#include <pcosynchro/pcothread.h>

IWindowInterface* Hospital::interface = nullptr;

Hospital::Hospital(int uniqueId, int fund, int maxBeds)
    : Seller(fund, uniqueId), maxBeds(maxBeds), currentBeds(0), nbHospitalised(0), nbFree(0)
{
    interface->updateFund(uniqueId, fund);
    interface->consoleAppendText(uniqueId, "Hospital Created with " + QString::number(maxBeds) + " beds");
    
    std::vector<ItemType> initialStocks = { ItemType::PatientHealed, ItemType::PatientSick };

    for(const auto& item : initialStocks) {
        stocks[item] = 0;
    }
}

int Hospital::request(ItemType what, int qty){
    // Mutex
    mutex.lock();
    if(getItemsForSale()[what] >= qty){
        currentBeds -= qty;
        stocks[what] -= qty;
        mutex.unlock();
        interface->consoleAppendText(uniqueId, "Patient went to clinic");
        return 1;
    }
    mutex.unlock();
    return 0;
}

void Hospital::freeHealedPatient() {
    mutex.lock();
    for(int i = 0; i < (int)patientHealedDays.size();){
        if(patientHealedDays.at(i) < 5){
            // Incrémente les jours passés hospitalisé
            patientHealedDays[i]++;
            i++;
        } else {
            patientHealedDays.pop_front();
            currentBeds -= 1;
            stocks[ItemType::PatientHealed] -= 1;
            nbFree += 1;
            interface->consoleAppendText(uniqueId, "Patient freed");
        }
    }
    mutex.unlock();
    return;
}

void Hospital::transferPatientsFromClinic() {
    // Mutex
    mutex.lock();
    // Si l'hopital ne peut pas prendre le patient
    if(getFund() < getEmployeeSalary(EmployeeType::Nurse) || (maxBeds - currentBeds < 1) || !chooseRandomSeller(clinics)->request(ItemType::PatientHealed, 1)){
        mutex.unlock();
        // Fin mutex
        return;
    }

    payNurse();
    currentBeds += 1;
    stocks[ItemType::PatientHealed] += 1;
    nbHospitalised += 1;
    patientHealedDays.push_back(0);
    mutex.unlock();
    // Fin mutex
    interface->consoleAppendText(uniqueId, "Patient came from clinic");
    return;
}

int Hospital::send(ItemType it, int qty, int bill) {
    // Mutex
    mutex.lock();
    // Ne peut pas prendre de patient
    if(getFund() < (bill + getEmployeeSalary(EmployeeType::Nurse)) || maxBeds - currentBeds < qty){
        mutex.unlock();
        // Fin mutex
        return 0;
    }
    money -= bill;
    payNurse();
    currentBeds += qty;
    stocks[it] += qty;
    nbHospitalised += qty;
    mutex.unlock();
    // Fin mutex
    interface->consoleAppendText(uniqueId, "Received sick patient");
    return 1;
}

void Hospital::run()
{
    if (clinics.empty()) {
        std::cerr << "You have to give clinics to a hospital before launching is routine" << std::endl;
        return;
    }

    interface->consoleAppendText(uniqueId, "[START] Hospital routine");

    while (!PcoThread::thisThread()->stopRequested()) {
        transferPatientsFromClinic();

        freeHealedPatient();

        interface->updateFund(uniqueId, money);
        interface->updateStock(uniqueId, &stocks);
        interface->simulateWork(); // Temps d'attente
    }

    interface->consoleAppendText(uniqueId, "[STOP] Hospital routine");
}

int Hospital::getAmountPaidToWorkers() {
    return nbHospitalised * getEmployeeSalary(EmployeeType::Nurse);
}

int Hospital::getNumberPatients(){
    return stocks[ItemType::PatientSick] + stocks[ItemType::PatientHealed] + nbFree;
}

std::map<ItemType, int> Hospital::getItemsForSale()
{
    return stocks;
}

void Hospital::setClinics(std::vector<Seller*> clinics){
    this->clinics = clinics;

    for (Seller* clinic : clinics) {
        interface->setLink(uniqueId, clinic->getUniqueId());
    }
}

void Hospital::setInterface(IWindowInterface* windowInterface){
    interface = windowInterface;
}

void Hospital::payNurse(){
    money -= getEmployeeSalary(EmployeeType::Nurse);
    return;
}
