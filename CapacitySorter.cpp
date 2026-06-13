/*
    CapacitySorter.cpp  —  Feature 5 : Max Heap (array-based)
*/

struct Vehicle {
    int    vehicleId;
    string driverName;
    string vehicleType;
    string plateNumber;
    int    availableSeats;
    string currentArea;

    Vehicle()
        : vehicleId(0), driverName(""), vehicleType(""),
          plateNumber(""), availableSeats(0), currentArea("") {}
    Vehicle(int id, string d, string t, string p, int s, string a)
        : vehicleId(id), driverName(d), vehicleType(t),
          plateNumber(p), availableSeats(s), currentArea(a) {}
};

class CapacitySorter {
private:
    vector<Vehicle> heap;

    int parent(int i)     { return (i - 1) / 2; }
    int leftChild(int i)  { return 2 * i + 1;   }
    int rightChild(int i) { return 2 * i + 2;   }

    void heapifyUp(int i) {
        while (i > 0 &&
               heap[parent(i)].availableSeats < heap[i].availableSeats) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int largest = i;
        int l = leftChild(i), r = rightChild(i), n = (int)heap.size();
        if (l < n && heap[l].availableSeats > heap[largest].availableSeats) largest = l;
        if (r < n && heap[r].availableSeats > heap[largest].availableSeats) largest = r;
        if (largest != i) { swap(heap[i], heap[largest]); heapifyDown(largest); }
    }

    // seat bar — uses string::append to avoid const char* concat issues
    string seatBar(int seats) {
        const char* color = (seats >= 5) ? GREEN : (seats >= 3 ? YELLOW : RED);
        string bar = "  ";
        for (int i = 0; i < seats; i++) {
            bar.append(color);
            bar.append("■");
            bar.append(RESET);
        }
        for (int i = seats; i < 7; i++) {
            bar.append(DIM);
            bar.append("□");
            bar.append(RESET);
        }
        return bar;
    }

public:
    CapacitySorter() {}
    bool isEmpty() { return heap.empty(); }
    int  getSize() { return (int)heap.size(); }

    // Insert — O(log n)
    void insertVehicle(Vehicle v) {
        heap.push_back(v);
        heapifyUp((int)heap.size() - 1);
        cout << "  " << BOLD << GREEN << "✔ " << RESET << GREEN
             << v.plateNumber << "  " << v.driverName
             << "  " << v.availableSeats << " seats" << RESET << "\n";
    }

    // Extract max — O(log n)
    Vehicle extractMax() {
        if (isEmpty()) { printError("No vehicles available."); return Vehicle(); }
        Vehicle best = heap[0];
        heap[0] = heap.back(); heap.pop_back();
        if (!isEmpty()) heapifyDown(0);
        return best;
    }

    // Peek — O(1)
    Vehicle peekMax() {
        if (isEmpty()) { printError("No vehicles available."); return Vehicle(); }
        return heap[0];
    }

    void displayAllVehicles() {
        if (isEmpty()) { printError("No vehicles."); return; }
        cout << "\n";
        printLine(GREEN);
        cout << "  " << BOLD << BG_GREEN << BLACK
             << "  ALL VEHICLES  " << RESET
             << BOLD << GREEN << "  Max Heap  heap[1] = best  ("
             << getSize() << " vehicles)" << RESET << "\n";
        printLine(GREEN);
        for (int i = 0; i < (int)heap.size(); i++) {
            const char* rc = (i == 0) ? GREEN : (i == 1 ? YELLOW : WHITE);
            cout << "  " << BOLD << rc << "  [" << i+1 << "]" << RESET;
            if (i == 0) cout << BOLD << GREEN << "  ◄ BEST" << RESET;
            cout << "\n";
            cout << "  " << tML << tH << tH << " "
                 << BOLD << WHITE << heap[i].driverName << RESET
                 << DIM  << "  "  << heap[i].vehicleType
                 << "  " << heap[i].plateNumber << RESET << "\n";
            cout << "  " << tV << "  " << seatBar(heap[i].availableSeats)
                 << "  " << BOLD << heap[i].availableSeats << " seats" << RESET
                 << DIM  << "   " << heap[i].currentArea << RESET << "\n";
            if (i < (int)heap.size() - 1) cout << "  " << tML;
            else                           cout << "  " << tBL;
            for (int j = 0; j < 46; j++) cout << tH;
            if (i < (int)heap.size() - 1) cout << tMR; else cout << tBR;
            cout << "\n";
        }
        cout << "\n";
    }

    void loadSampleData() {
        insertVehicle(Vehicle(3001,"Suresh Kamble","Sedan",    "MH-01-AB-1234",3,"Andheri"));
        insertVehicle(Vehicle(3002,"Deepak Verma", "SUV",      "MH-02-CD-5678",6,"Thane"));
        insertVehicle(Vehicle(3003,"Manoj Tiwari", "Hatchback","MH-03-EF-9012",2,"Borivali"));
        insertVehicle(Vehicle(3004,"Ganesh Pawar", "SUV",      "MH-04-GH-3456",5,"Dadar"));
        insertVehicle(Vehicle(3005,"Sanjay Yadav", "Sedan",    "MH-05-IJ-7890",4,"Kurla"));
        insertVehicle(Vehicle(3006,"Ramesh Gupta", "Sedan",    "MH-06-KL-2345",1,"Powai"));
        insertVehicle(Vehicle(3007,"Ashok Jadhav", "MPV",      "MH-07-MN-6789",7,"Mulund"));
        insertVehicle(Vehicle(3008,"Pravin Shinde","Hatchback","MH-08-OP-0123",2,"Vashi"));
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n";
            printLine(GREEN);
            cout << "  " << BOLD << BG_GREEN << BLACK
                 << "  CAPACITY SORTER  " << RESET
                 << BOLD << GREEN << "  Max Heap  O(log n) insert/extract" << RESET << "\n";
            printThinLine(GREEN);
            cout << "  " << BOLD << "  Vehicles : " << RESET
                 << GREEN << BOLD << getSize() << RESET;
            if (!isEmpty())
                cout << DIM << "   best → " << RESET
                     << GREEN << heap[0].driverName
                     << "  (" << heap[0].availableSeats << " seats)" << RESET;
            cout << "\n";
            printLine(GREEN);
            cout << "  " << GREEN << "  1" << RESET << "  Add Vehicle\n";
            cout << "  " << GREEN << "  2" << RESET << "  Assign Best Vehicle  " << DIM << "(Extract Max)" << RESET << "\n";
            cout << "  " << GREEN << "  3" << RESET << "  View Best Vehicle    " << DIM << "(Peek)" << RESET << "\n";
            cout << "  " << GREEN << "  4" << RESET << "  Display All\n";
            cout << "  " << GREEN << "  5" << RESET << "  Back\n";
            printThinLine(GREEN);
            cout << "  " << BOLD << GREEN << "  ➤  Choice: " << RESET;
            cin >> choice;

            if (choice == 1) {
                Vehicle v;
                printThinLine(GREEN);
                cout << "  " << YELLOW << "  Vehicle ID      : " << RESET; cin >> v.vehicleId; cin.ignore();
                cout << "  " << YELLOW << "  Driver Name     : " << RESET; getline(cin, v.driverName);
                cout << "  " << YELLOW << "  Vehicle Type    : " << RESET; getline(cin, v.vehicleType);
                cout << "  " << YELLOW << "  Plate Number    : " << RESET; getline(cin, v.plateNumber);
                cout << "  " << YELLOW << "  Available Seats : " << RESET; cin >> v.availableSeats; cin.ignore();
                cout << "  " << YELLOW << "  Current Area    : " << RESET; getline(cin, v.currentArea);
                insertVehicle(v);
            }
            else if (choice == 2) {
                Vehicle best = extractMax();
                if (best.vehicleId != 0) {
                    cout << "\n";
                    printLine(GREEN);
                    cout << "  " << BOLD << BG_GREEN << BLACK
                         << "  VEHICLE DISPATCHED  " << RESET << "\n";
                    printThinLine(GREEN);
                    printLabel("  Driver  :", best.driverName);
                    printLabel("  Type    :", best.vehicleType);
                    printLabel("  Plate   :", best.plateNumber);
                    cout << "  " << BOLD << YELLOW << "  Seats   : " << RESET
                         << seatBar(best.availableSeats)
                         << "  " << BOLD << best.availableSeats << RESET << "\n";
                    printLabel("  Area    :", best.currentArea);
                    cout << "  " << BOLD << GREEN << "  Status  :  ✔ DISPATCHED" << RESET << "\n";
                    printLine(GREEN);
                }
            }
            else if (choice == 3) {
                Vehicle top = peekMax();
                if (top.vehicleId != 0) {
                    cout << "\n";
                    printThinLine(GREEN);
                    cout << "  " << BOLD << GREEN << "  BEST AVAILABLE" << RESET << "\n";
                    printThinLine(GREEN);
                    printLabel("  Driver  :", top.driverName);
                    printLabel("  Type    :", top.vehicleType);
                    printLabel("  Plate   :", top.plateNumber);
                    cout << "  " << BOLD << YELLOW << "  Seats   : " << RESET
                         << seatBar(top.availableSeats)
                         << "  " << BOLD << top.availableSeats << RESET << "\n";
                    printLabel("  Area    :", top.currentArea);
                    printThinLine(GREEN);
                }
            }
            else if (choice == 4) { displayAllVehicles(); }
            else if (choice != 5) { printError("Invalid choice."); }

        } while (choice != 5);
    }
};
