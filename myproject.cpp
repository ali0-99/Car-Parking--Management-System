#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string plateNumber;
public:
    Vehicle(string plate) {
        plateNumber = plate;
    }
    string getPlateNumber() {
        return plateNumber;
    }
    virtual int calculateFee(int hours) = 0;
};
class Car : public Vehicle {
public:
    Car(string plate) : Vehicle(plate) {}
    int calculateFee(int hours) override {
        return hours * 50; 
    }
};
class ParkingLot {
private:
    int capacity;
    int count;
    Vehicle* slots[10]; 
public:
    ParkingLot(int cap) {
        capacity = cap;
        count = 0;
    }

    void parkVehicle(Vehicle* v) {
        cout << "\n----------------------------------\n";
        cout << "🚗 Attempting to park vehicle...\n";
        if (count < capacity) {
            slots[count] = v;
            cout << "✅ Vehicle [" << v->getPlateNumber() << "] parked successfully.\n";
            cout << "Current Occupancy: " << count + 1 << "/" << capacity << endl;
            count++;
        }
        else {
            cout << "❌ Parking lot is FULL! Cannot park vehicle [" << v->getPlateNumber() << "].\n";
        }
        cout << "----------------------------------\n";
    }

    void removeVehicle(string plate, int hours) {
        cout << "\n----------------------------------\n";
        cout << "🚗 Attempting to remove vehicle...\n";
        for (int i = 0; i < count; i++) {
            if (slots[i]->getPlateNumber() == plate) {
                int fee = slots[i]->calculateFee(hours);
                cout << "✅ Vehicle [" << plate << "] removed successfully.\n";
                cout << "Parking Duration: " << hours << " hour(s)\n";
                cout << "Total Fee: Rs." << fee << endl;

           
                for (int j = i; j < count - 1; j++) {
                    slots[j] = slots[j + 1];
                }
                count--;
                cout << "Current Occupancy: " << count << "/" << capacity << endl;
                cout << "----------------------------------\n";
                return;
            }
        }
        cout << "❌ Vehicle [" << plate << "] not found in parking lot.\n";
        cout << "----------------------------------\n";
    }

    void displayStatus() {
        cout << "\n========== Parking Lot Status ==========\n";
        cout << "Capacity: " << capacity << " | Occupied: " << count << " | Free Slots: " << capacity - count << endl;
        if (count == 0) {
            cout << "No vehicles currently parked.\n";
        }
        else {
            cout << "Vehicles currently parked:\n";
            for (int i = 0; i < count; i++) {
                cout << " - Slot " << i + 1 << ": " << slots[i]->getPlateNumber() << endl;
            }
        }
        cout << "========================================\n";
    }
};

int main() {
    cout << "========================================\n";
    cout << "🚘 Welcome to Car Parking Lot System 🚘\n";
    cout << "========================================\n";

    ParkingLot lot(3);

    Car c1("BMW M5 F90-360");
    Car c2("Corvette C8-45");
    Car c3("AUDI RS6-320");

    lot.parkVehicle(&c1);
    lot.parkVehicle(&c2);
    lot.parkVehicle(&c3);

    lot.displayStatus();

    cout << "\n>>> Removing vehicle AUDI RS6  after 2 hours...\n";
    lot.removeVehicle("AUDI RS6-320", 2);

    lot.displayStatus();

    cout << "\n✅ Program finished successfully.\n";
    cout << "========================================\n";
    return 0;
}
