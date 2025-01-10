package test.poo;

import java.util.ArrayList;
import java.util.List;

enum Country {
    Switzerland("SwissFrancs"),
    France("Euros"),
    UnitedKingdom("BritishPounds"),
    Germany("Euros");

    private final String currency;

    Country(String currency) {
        this.currency = currency;
    }

    public String getCurrency() {
        return currency;
    }
}

abstract class Vehicle {
    protected static List<Vehicle> rentedVehicles = new ArrayList<>();
    protected String name;
    protected Country country;

    public Vehicle(String name, Country country) {
        this.name = name;
        this.country = country;
    }

    public abstract void status();

    public static void printVehicles() {
        System.out.println("Rented vehicles:");
        for (Vehicle v : rentedVehicles) {
            v.status();
        }
    }

    public void move(Country newCountry) {
        this.country = newCountry;
    }
}

class Scooter extends Vehicle {
    private static int scooterCount = 1;
    private final int id;

    public Scooter(Country country) {
        super("Scooter", country);
        this.id = scooterCount++;
    }
    public String getName() {
        return name + " #" + id;
    }

    @Override
    public void status() {
        System.out.println("Hop on and zip around : " + this.getName() + ", currently in  " + country + " (pay in " + country.getCurrency() + ")");
    }

    @Override
    public void move(Country newCountry) {
        System.out.println(this.name +" #" + id + " moves to " + newCountry.name());
    }
}

class Car extends Vehicle {
    private final Scooter scooter;
    private boolean isScooterActive;

    public Car(String name, Country country) {
        super(name, country);
        this.isScooterActive = false;
        this.scooter = new Scooter(country); // Integrated scooter
    }

    @Override
    public void status() {
        System.out.println(name + "means eco-friendly family transport: " + name + " currently in " + country + " (pay in " + country.getCurrency() + ")");
        if (isScooterActive && scooter.country != this.country) {
            System.out.println("Warning: The scooter is in a different country than the car!");
        }
    }

    public Scooter activateScooter() {
        if (!isScooterActive) {
            isScooterActive = true;
            rentedVehicles.add(scooter);
            System.out.println("Built in " + scooter.getName() + "activated in "+ name);
        }
        return scooter;
    }

    @Override
    public void move(Country newCountry) {
        super.move(newCountry);
        if (scooter.country != this.country) {
            System.out.println("Warning: The "+ scooter.getName() +" is not in the same country as "+ name +" !");
        }
    }
}

class Main {
    public static void main(String... args) {
        System.out.println("-- Standard scooter");
        Scooter b1 = new Scooter(Country.Switzerland);
        b1.status();
        b1.move(Country.Germany);

        System.out.println("\n-- MiniSpark");
        Car miniSpark = new Car("MiniSpark", Country.Switzerland);
        miniSpark.status();
        Scooter b2 = miniSpark.activateScooter();
        b2.status();

        System.out.println("\n-- EcoVoyager");
        Car ecoVoyager = new Car("EcoVoyager", Country.France);
        ecoVoyager.status();
        Scooter b3 = ecoVoyager.activateScooter();
        b3.status();

        System.out.println("\n-- EcoVoyager's scooter moves to UK");
        b3.move(Country.UnitedKingdom);
        b3.status();

        System.out.println("\n-- MiniSpark moves to Germany");
        miniSpark.move(Country.Germany);
        b2.status();

        System.out.println("\n-- Currently rented vehicles");
        Vehicle.printVehicles();
    }
}
