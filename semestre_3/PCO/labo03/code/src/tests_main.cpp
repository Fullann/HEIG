#include <gtest/gtest.h>
#include "supplier.h"
#include "ambulance.h"
#include "clinic.h"
#include "iwindowinterface.h"
#include "fakeinterface.h"
#include <pcosynchro/pcothread.h>
#include <iostream>
#include <vector>
#include <random>
#include "utils.h"

class HospitalTest : public ::testing::Test {
protected:
    void SetUp() override {
        windowInterface = new FakeInterface();
        Hospital::setInterface(windowInterface);
        Clinic::setInterface(windowInterface);
    }

    void TearDown() override {
        delete windowInterface;
    }

    IWindowInterface* windowInterface;
};

class SupplierTest : public ::testing::Test {
protected:
    void SetUp() override {
        windowInterface = new FakeInterface();
        Supplier::setInterface(windowInterface);
    }

    void TearDown() override {
        delete windowInterface;
    }

    IWindowInterface* windowInterface;
};

class ClinicTest : public ::testing::Test {
protected:
    void SetUp() override {
        windowInterface = new FakeInterface();
        Clinic::setInterface(windowInterface);
        Supplier::setInterface(windowInterface);
        Hospital::setInterface(windowInterface);
    }

    void TearDown() override {
        delete windowInterface;
    }

    IWindowInterface* windowInterface;
};


class TestableHospital : public Hospital {
public:
    TestableHospital(int uniqueId, int fund, int maxBeds)
        : Hospital(uniqueId, fund, maxBeds) {}

    using Hospital::stocks;

    //using Hospital::healedPatients;

    using Hospital::freeHealedPatient;

    using Hospital::transferPatientsFromClinic;

    using Hospital::getItemsForSale;

    using Hospital::getNumberPatients;

    using Hospital::setClinics;

    using Hospital::run;
};

class TestableClinic : public Clinic {
public:
    TestableClinic(int uniqueId, int fund)
        : Clinic(uniqueId, fund, {ItemType::PatientSick, ItemType::Pill, ItemType::Thermometer}) {}

    using Clinic::stocks;
    using Clinic::money;
    using Clinic::verifyResources;
    using Clinic::treatPatient;
    using Clinic::orderResources;
};

class TestableSupplier : public Supplier {
public:
    TestableSupplier(int uniqueId, int fund)
        : Supplier(uniqueId, fund, {ItemType::Pill, ItemType::Thermometer, ItemType::Stethoscope}) {}

    using Supplier::stocks;
    using Supplier::money;
};

/***************************************************** */
/*********** START TEST HOSPITAL ********************* */
/***************************************************** */

// Test du constructeur
TEST_F(HospitalTest, ConstructorInitializesCorrectly) {
    TestableHospital hospital(1, 10000, 10);
    EXPECT_EQ(hospital.getFund(), 10000);
    EXPECT_EQ(hospital.getNumberPatients(), 0);
}

// Test de la méthode request
TEST_F(HospitalTest, RequestPatientSuccess) {
    TestableHospital hospital(1, 10000, 10);
    hospital.stocks[ItemType::PatientSick] = 5;
    int cost = hospital.request(ItemType::PatientSick, 2);

    EXPECT_EQ(cost, 2 * getCostPerUnit(ItemType::PatientSick));
    EXPECT_EQ(hospital.stocks[ItemType::PatientSick], 3);
}

// Test de la méthode request pour stock insuffisant
TEST_F(HospitalTest, RequestPatientInsufficientStock) {
    TestableHospital hospital(1, 10000, 10);
    hospital.stocks[ItemType::PatientSick] = 1;
    int cost = hospital.request(ItemType::PatientSick, 2);

    EXPECT_EQ(cost, 0);
    EXPECT_EQ(hospital.stocks[ItemType::PatientSick], 1);
}

// Test de la méthode send
TEST_F(HospitalTest, SendPatientSuccess) {
    TestableHospital hospital(1, 10000, 10);
    int qtySent = hospital.send(ItemType::PatientSick, 1, getCostPerUnit(ItemType::PatientSick));
    
    EXPECT_EQ(qtySent, 1);
    EXPECT_EQ(hospital.getFund(), 10000 - getCostPerUnit(ItemType::PatientSick) - hospital.getAmountPaidToWorkers());
}

// Test de la méthode send si pas de fond
TEST_F(HospitalTest, SendPatientFailureFund) {
    TestableHospital hospital(1, 0, 10);
    int qtySent = hospital.send(ItemType::PatientSick, 1, getCostPerUnit(ItemType::PatientSick));
    
    EXPECT_EQ(qtySent, 0);
}

// Test de la méthode send si pas de place
TEST_F(HospitalTest, SendPatientFailureMaxBeds) {
    TestableHospital hospital(1, 10000, 10);
    int j = 0;
    int qtySent = 0;
    for (int i = 0; i < 11; ++i) {
        j = hospital.send(ItemType::PatientSick, 1, getCostPerUnit(ItemType::PatientSick));
        qtySent += j;
    }

    EXPECT_EQ(j, 0);
    EXPECT_EQ(hospital.getFund(), 10000 - (qtySent*getCostPerUnit(ItemType::PatientSick)) - hospital.getAmountPaidToWorkers());
}


// Test de la méthode transferPatientsFromClinic avec fonds insuffisants
TEST_F(HospitalTest, TransferPatientInsufficientFunds) {
    TestableHospital hospital(1, 10, 10); // Fond insuffisant pour le transfert
    
    Cardiology clinic(0, 100); // Une clinique avec fonds pour simuler un transfert
    hospital.setClinics({ &clinic });

    hospital.transferPatientsFromClinic();

    // Vérifier qu'aucun patient n'a été transféré
    EXPECT_EQ(hospital.getNumberPatients(), 0);
    EXPECT_EQ(hospital.getFund(), 10);
}

// Test de la méthode run
TEST_F(HospitalTest, RunHospitalRoutine) {
    TestableHospital hospital(1, 10000, 10);

    Cardiology clinic(0, 100);
    hospital.setClinics({ &clinic });

    PcoThread thread([&hospital]() { hospital.run(); });
    thread.requestStop();
    thread.join();

    EXPECT_TRUE(true);
}

// Test de la méthode freeHealedPatient
TEST_F(HospitalTest, FreeHealedPatient) {
    TestableHospital hospital(1, 10000, 10);

    TestableClinic clinic(0, 10000);
    clinic.stocks[ItemType::PatientHealed] = 10;

    hospital.setClinics({ &clinic });

    for (int i = 0; i < 4; ++i){
        hospital.transferPatientsFromClinic();
    }

    for(int i = 0; i < 5; ++i){
        hospital.freeHealedPatient();
        hospital.transferPatientsFromClinic();
    }

    EXPECT_EQ(hospital.stocks[ItemType::PatientHealed], 5);
    EXPECT_EQ(hospital.getNumberPatients(), 9);
}


void sendPatients(Hospital& hospital, ItemType itemType, std::atomic<int>& totalPaid) {
    int tot = 0;
    for (int i = 0; i < 20000; ++i) {
        int qty = 1;
        int bill = getCostPerUnit(itemType) * qty;
        if (hospital.send(itemType, qty, bill) > 0) { 
            tot += bill; 
        }
    }

    totalPaid += tot;
}

void requestPatients(Hospital& hospital, ItemType itemType, std::atomic<int>& totalGained) {
    int tot = 0;
    for (int i = 0; i < 20000; ++i) {
        int qty = 1;
        tot += hospital.request(itemType, qty);
    }

    totalGained += tot;
}

TEST(SellerTest, StressHospital) {
    const int uniqueId = 0;
    const int initialFund = 20000;
    const unsigned int maxBeds = MAX_BEDS_PER_HOSTPITAL;
    const unsigned int nbThreads = 4;
    int endFund = 0;
    std::atomic<int> totalPaid = 0;
    std::atomic<int> totalGained = 0;

    IWindowInterface* windowInterface = new FakeInterface();
    Hospital::setInterface(windowInterface);

    Hospital hospital(uniqueId, initialFund, maxBeds);

    std::vector<std::unique_ptr<PcoThread>> threads;

    for (unsigned int i = 0; i < nbThreads / 2; ++i) {
        threads.emplace_back(std::make_unique<PcoThread>(requestPatients, std::ref(hospital), ItemType::PatientSick, std::ref(totalGained)));
        threads.emplace_back(std::make_unique<PcoThread>(sendPatients, std::ref(hospital), ItemType::PatientSick, std::ref(totalPaid))); 
    }

    for (auto& thread : threads) {
        thread->join();
    }

    endFund += hospital.getFund();
    endFund += hospital.getAmountPaidToWorkers();
    endFund += totalPaid; // <- En test cet argent est perdu
    endFund -= totalGained; // <- En test cette argent vient de nulle part

    EXPECT_EQ(endFund, initialFund);
    EXPECT_GE(hospital.getNumberPatients(), 0);
    EXPECT_LE(hospital.getNumberPatients(), maxBeds);
}

/***************************************************** */
/************* END TEST HOSPITAL ********************* */
/***************************************************** */


/***************************************************** */
/*********** START TEST CLINIC *********************** */
/***************************************************** */
TEST_F(ClinicTest, VerifyResourcesSuccess) {
    TestableClinic clinic(0, 10000);
    clinic.stocks[ItemType::PatientSick] = 1;
    clinic.stocks[ItemType::Pill] = 1;
    clinic.stocks[ItemType::Thermometer] = 1;
    EXPECT_TRUE(clinic.verifyResources());
}

TEST_F(ClinicTest, VerifyResourcesFailure) {
    TestableClinic clinic(0, 10000);
    EXPECT_FALSE(clinic.verifyResources());
}

TEST_F(ClinicTest, RequestSuccess) {
    TestableClinic clinic(0, 10000);
    clinic.stocks[ItemType::PatientHealed] = 10;
    int cost = clinic.request(ItemType::PatientHealed, 5);
    
    EXPECT_EQ(cost, 5 * getCostPerUnit(ItemType::PatientHealed));
    EXPECT_EQ(clinic.stocks[ItemType::PatientHealed], 5);
}

TEST_F(ClinicTest, RequestInsufficientStock) {
    TestableClinic clinic(0, 10000);
    clinic.stocks[ItemType::PatientHealed] = 2;
    int cost = clinic.request(ItemType::PatientHealed, 5);
    
    EXPECT_EQ(cost, 0);
    EXPECT_EQ(clinic.stocks[ItemType::PatientHealed], 2);
}

TEST_F(ClinicTest, TreatPatientSuccess) {
    TestableClinic clinic(0, 10000);
    clinic.stocks[ItemType::PatientSick] = 1;
    clinic.stocks[ItemType::Pill] = 1;
    clinic.stocks[ItemType::Thermometer] = 1;

    clinic.treatPatient();

    EXPECT_EQ(clinic.stocks[ItemType::PatientHealed], 1);
    EXPECT_EQ(10000, clinic.money + clinic.getAmountPaidToWorkers());
}

TEST_F(ClinicTest, OrderResources) {
    TestableClinic clinic(0, 10000);
    TestableHospital hospital(1, 10000, 10);
    TestableSupplier supplier(2, 10000);

    hospital.stocks[ItemType::PatientSick] = 10;
    supplier.stocks[ItemType::Thermometer] = 10;
    supplier.stocks[ItemType::Pill] = 10;


    std::vector<Seller*> hospitals = { &hospital };
    std::vector<Seller*> suppliers = { &supplier };
    clinic.setHospitalsAndSuppliers(hospitals, suppliers);

    clinic.orderResources();

    EXPECT_GT(clinic.stocks[ItemType::PatientSick], 0);
    EXPECT_GT(clinic.stocks[ItemType::Thermometer], 0);
    EXPECT_GT(clinic.stocks[ItemType::Pill], 0);
}

TEST_F(ClinicTest, RunSupplierRoutine) {
    TestableClinic clinic(0, 10000);
    TestableHospital hospital(1, 10000, 10);
    TestableSupplier supplier(2, 10000);

    std::vector<Seller*> hospitals = { &hospital };
    std::vector<Seller*> suppliers = { &supplier };
    clinic.setHospitalsAndSuppliers(hospitals, suppliers);

    PcoThread thread([&clinic]() { clinic.run(); });
    thread.requestStop();
    thread.join();

    EXPECT_GE(clinic.money, 0);
}

void requestClinic(TestableClinic& clinic, ItemType itemType, std::atomic<int>& totalGained) {
    int tot = 0;
    for (int i = 0; i < 20000; ++i) {
        int qty = 1;
        tot += clinic.request(itemType, qty);
    }

    totalGained += tot;
}

TEST_F(ClinicTest, StressClinic) {
    const int uniqueId = 0;
    const int initialFund = 20000;
    const unsigned int nbThreads = 4;
    int endFund = 0;
    std::atomic<int> totalPaid = 0;
    std::atomic<int> totalGained = 0;

    TestableClinic clinic(uniqueId, initialFund);
    clinic.stocks[ItemType::PatientHealed] = 1000;

    std::vector<std::unique_ptr<PcoThread>> threads;

    for (unsigned int i = 0; i < nbThreads / 2; ++i) {
        threads.emplace_back(std::make_unique<PcoThread>(requestClinic, std::ref(clinic), ItemType::PatientHealed, std::ref(totalGained)));
    }

    for (auto& thread : threads) {
        thread->join();
    }

    endFund += clinic.getFund();
    endFund += clinic.getAmountPaidToWorkers();
    endFund += totalPaid;
    endFund -= totalGained;

    EXPECT_EQ(endFund, initialFund);
}

/***************************************************** */
/************* END TEST CLINIC *********************** */
/***************************************************** */


/***************************************************** */
/*********** START TEST SUPPLIER ********************* */
/***************************************************** */

TEST_F(SupplierTest, RequestSuccess) {
    TestableSupplier supplier(0, 10000);
    supplier.stocks[ItemType::Thermometer] = 10;
    int cost = supplier.request(ItemType::Thermometer, 5);
    
    EXPECT_EQ(cost, 5 * getCostPerUnit(ItemType::Thermometer)); 
    EXPECT_EQ(supplier.stocks[ItemType::Thermometer], 5);
}

TEST_F(SupplierTest, RequestInsufficientStock) {
    TestableSupplier supplier(0, 10000);
    supplier.stocks[ItemType::Thermometer] = 2;
    int cost = supplier.request(ItemType::PatientSick, 5);
    
    EXPECT_EQ(cost, 0);
    EXPECT_EQ(supplier.stocks[ItemType::Thermometer], 2);
}

TEST_F(SupplierTest, RunSupplierRoutine) {
    TestableSupplier supplier(0, 0);
    PcoThread thread([&supplier]() { supplier.run(); });
    thread.requestStop();
    thread.join();

    EXPECT_GE(supplier.money, 0);
}

void requestSupplier(TestableSupplier& supplier, ItemType itemType, std::atomic<int>& totalGained) {
    int tot = 0;
    for (int i = 0; i < 20000; ++i) {
        int qty = 1;
        tot += supplier.request(itemType, qty);
    }

    totalGained += tot;
}

TEST_F(SupplierTest, StressSupplier) {
    const int uniqueId = 0;
    const int initialFund = 20000;
    const unsigned int nbThreads = 4;
    int endFund = 0;
    std::atomic<int> totalPaid = 0;
    std::atomic<int> totalGained = 0;

    TestableSupplier supplier(uniqueId, initialFund);
    supplier.stocks[ItemType::Thermometer] = 1000;

    std::vector<std::unique_ptr<PcoThread>> threads;

    for (unsigned int i = 0; i < nbThreads / 2; ++i) {
        threads.emplace_back(std::make_unique<PcoThread>(requestSupplier, std::ref(supplier), ItemType::Thermometer, std::ref(totalGained)));
    }

    for (auto& thread : threads) {
        thread->join();
    }

    endFund += supplier.getFund();
    endFund += supplier.getAmountPaidToWorkers();
    endFund += totalPaid;
    endFund -= totalGained;

    EXPECT_EQ(endFund, initialFund);
}


/***************************************************** */
/************* END TEST SUPPLIER ********************* */
/***************************************************** */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
