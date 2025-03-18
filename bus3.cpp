#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Seat {
    int seatNumber;
    bool isBooked;
};

struct Bus {
    int busID;
    string route;
    string time;
    vector<Seat> seats;
};

vector<Bus> buses = {
    {101, "Qasimabad to Autobhan", "10:00 AM", {{1, false}, {2, true}, {3, false}, {4, false}}},
    {102, "Qasimabad to latifabad no 8", "1:00 PM", {{1, true}, {2, false}, {3, true}, {4, false}}},
    {103, "latifabad no 8 to latifabad no 10","2:00", {{1, false}, {2, false}, {3, false}, {4, true}}},
    {104, "latifadab no 10 to kohsar","3:00",{{1,true},{2,false},{3,true},{4,true}}},
    {105,"latifabad no 8 to latifabad no 12","4:00",{{1,false},{2,false},{3,true},{4,true}}}
};

void displayBuses() {
    cout << "\nAvailable Bus Schedules:" << endl;
    for (const auto& bus : buses) {
        cout << "Bus ID: " << bus.busID << " | Route: " << bus.route << " | Time: " << bus.time << " | Available Seats: ";
        int count = 0;
        for (const auto& seat : bus.seats) {
            if (!seat.isBooked) count++;
        }
        cout << count << endl;
    }
}

void bookTicket() {
    int busID, seatNum;
    displayBuses();
    cout << "Enter Bus ID to book: "; cin >> busID;
    cout << "Enter Seat Number: "; cin >> seatNum;
    for (auto& bus : buses) {
        if (bus.busID == busID) {
            if (seatNum > 0 && seatNum <= bus.seats.size() && !bus.seats[seatNum - 1].isBooked) {
                bus.seats[seatNum - 1].isBooked = true;
                cout << "Ticket booked successfully!\n";
                return;
            } else {
                cout << "Invalid seat selection or already booked!\n";
                return;
            }
        }
    }
    cout << "Bus not found!\n";
}

void cancelTicket() {
    int busID, seatNum;
    cout << "Enter Bus ID to cancel ticket: "; cin >> busID;
    cout << "Enter Seat Number: "; cin >> seatNum;
    for (auto& bus : buses) {
        if (bus.busID == busID) {
            if (seatNum > 0 && seatNum <= bus.seats.size() && bus.seats[seatNum - 1].isBooked) {
                bus.seats[seatNum - 1].isBooked = false;
                cout << "Ticket cancelled successfully!\n";
                return;
            } else {
                cout << "Invalid seat selection or not booked!\n";
                return;
            }
        }
    }
    cout << "Bus not found!\n";
}

void manageBusSchedule() {
    int choice;
    cout << "1. Add Bus\n2. Modify Bus\n3. Delete Bus\nEnter choice: ";
    cin >> choice;
    if (choice == 1) {
        Bus newBus;
        cout << "Enter Bus ID: "; cin >> newBus.busID;
        cout << "Enter Route: "; cin.ignore(); getline(cin, newBus.route);
        cout << "Enter Time: "; getline(cin, newBus.time);
        cout << "Enter Number of Seats: ";
        int numSeats; cin >> numSeats;
        for (int i = 1; i <= numSeats; ++i) newBus.seats.push_back({i, false});
        buses.push_back(newBus);
        cout << "Bus added successfully!\n";
    }
    else if (choice == 2) {
        int busID;
        cout << "Enter Bus ID to modify: "; cin >> busID;
        for (auto& bus : buses) {
            if (bus.busID == busID) {
                cout << "Enter New Route: "; cin.ignore(); getline(cin, bus.route);
                cout << "Enter New Time: "; getline(cin, bus.time);
                cout << "Bus modified successfully!\n";
                return;
            }
        }
        cout << "Bus not found!\n";
    }
    else if (choice == 3) {
        int busID;
        cout << "Enter Bus ID to delete: "; cin >> busID;
        for (auto it = buses.begin(); it != buses.end(); ++it) {
            if (it->busID == busID) {
                buses.erase(it);
                cout << "Bus deleted successfully!\n";
                return;
            }
        }
        cout << "Bus not found!\n";
    }
}

void generateReport() {
    cout << "\nBooking Report:\n";
    for (const auto& bus : buses) {
        cout << "Bus ID: " << bus.busID << " | Route: " << bus.route << " | Time: " << bus.time << "\nSeats:\n";
        for (const auto& seat : bus.seats) {
            cout << "Seat " << seat.seatNumber << ": " << (seat.isBooked ? "Booked" : "Available") << endl;
        }
    }
}

int main() {
	cout << "...............................WELCOME TO BUS TICKET RESERVATION SYSTEM..................................."<<endl;
    int choice;
    while (true) {
        cout << "\n1. View Bus Schedules\n2. Book Ticket\n3. Cancel Ticket\n4. Manage Bus Schedule\n5. Generate Report\n6. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: displayBuses(); break;
            case 2: bookTicket(); break;
            case 3: cancelTicket(); break;
            case 4: manageBusSchedule(); break;
            case 5: generateReport(); break;
            case 6: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}