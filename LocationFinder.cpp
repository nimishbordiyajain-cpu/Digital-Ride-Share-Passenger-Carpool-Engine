/*
    LocationFinder.cpp  —  Feature 4 : Hash Table (unordered_map)
*/

struct PassengerLocation {
    int    userId;
    string requestToken;
    string passengerName;
    string area;
    double latitude;
    double longitude;
    string landmark;

    PassengerLocation()
        : userId(0), requestToken(""), passengerName(""),
          area(""), latitude(0.0), longitude(0.0), landmark("") {}
    PassengerLocation(int id, string tok, string name, string a,
                      double lat, double lon, string land)
        : userId(id), requestToken(tok), passengerName(name),
          area(a), latitude(lat), longitude(lon), landmark(land) {}
};

class LocationFinder {
private:
    unordered_map<int, PassengerLocation> locationMap;

    void printCard(PassengerLocation* loc) {
        cout << "\n";
        printThinLine(CYAN);
        cout << "  " << BOLD << BG_CYAN << BLACK
             << "  LOCATION FOUND  " << RESET << "\n";
        printThinLine(CYAN);
        printLabel("  User ID   :", to_string(loc->userId));
        printLabel("  Token     :", loc->requestToken);
        printLabel("  Passenger :", loc->passengerName);
        printLabel("  Area      :", loc->area);
        cout << "  " << BOLD << YELLOW << "  GPS       : " << RESET
             << CYAN << "(" << loc->latitude
             << ", " << loc->longitude << ")" << RESET << "\n";
        printLabel("  Landmark  :", loc->landmark);
        printThinLine(CYAN);
    }

public:
    LocationFinder() {}

    // Add — O(1) average
    void addLocation(int userId, PassengerLocation loc) {
        locationMap[userId] = loc;
        cout << "  " << BOLD << GREEN << "✔ " << RESET << GREEN
             << "ID " << userId << "  " << loc.passengerName
             << "  →  " << loc.area << RESET << "\n";
    }

    // Search by ID — O(1) average
    PassengerLocation* searchById(int userId) {
        auto it = locationMap.find(userId);
        if (it != locationMap.end()) return &(it->second);
        return nullptr;
    }

    // Search by token — O(n) scan
    PassengerLocation* searchByToken(string token) {
        for (auto& e : locationMap)
            if (e.second.requestToken == token) return &(e.second);
        return nullptr;
    }

    void removeLocation(int userId) {
        if (locationMap.erase(userId) > 0)
            printSuccess("Location removed for ID: " + to_string(userId));
        else
            printError("No record for ID: " + to_string(userId));
    }

    void displayAllLocations() {
        if (locationMap.empty()) { printError("No locations stored."); return; }
        cout << "\n";
        printLine(CYAN);
        cout << "  " << BOLD << BG_CYAN << BLACK
             << "  ALL PASSENGER LOCATIONS  " << RESET
             << BOLD << CYAN << "  Hash Table  ("
             << locationMap.size() << " entries)" << RESET << "\n";
        printLine(CYAN);
        for (auto& e : locationMap) {
            PassengerLocation& loc = e.second;
            cout << "  " << BOLD << CYAN  << "  " << loc.userId << RESET
                 << DIM  << "  "           << loc.requestToken  << RESET
                 << BOLD << "  "           << loc.passengerName << RESET
                 << "  " << GREEN          << loc.area          << RESET
                 << DIM  << "  ("          << loc.latitude
                 << ", "                   << loc.longitude << ")"
                 << "  " << loc.landmark   << RESET << "\n";
        }
        printLine(CYAN);
    }

    void loadSampleData() {
        addLocation(1001,PassengerLocation(1001,"REQ-2001","Arjun Sharma","Andheri West",  19.1136,72.8697,"Near D-Mart"));
        addLocation(1002,PassengerLocation(1002,"REQ-2002","Priya Mehta", "Thane West",    19.1974,72.9666,"Jupiter Hospital"));
        addLocation(1003,PassengerLocation(1003,"REQ-2003","Ravi Kumar",  "Borivali East", 19.2307,72.8567,"Old Petrol Pump"));
        addLocation(1004,PassengerLocation(1004,"REQ-2004","Sneha Patil", "Vashi Sector5", 19.0771,73.0078,"Inorbit Mall"));
        addLocation(1005,PassengerLocation(1005,"REQ-2005","Amit Joshi",  "Powai",         19.1176,72.9060,"Hiranandani Garden"));
        addLocation(1006,PassengerLocation(1006,"REQ-2006","Neha Desai",  "Mulund West",   19.1726,72.9594,"R Mall"));
        addLocation(1007,PassengerLocation(1007,"REQ-2007","Rahul Nair",  "Kalyan West",   19.2403,73.1305,"Station Road"));
        addLocation(1008,PassengerLocation(1008,"REQ-2008","Kavya Singh", "Panvel",        18.9894,73.1175,"Central Park"));
        addLocation(1009,PassengerLocation(1009,"REQ-2009","Vikram Patel","Kandivali",     19.2050,72.8561,"Growel Mall"));
        addLocation(1010,PassengerLocation(1010,"REQ-2010","Pooja Rao",   "Sion",          19.0437,72.8612,"Sion Circle"));
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n";
            printLine(CYAN);
            cout << "  " << BOLD << BG_CYAN << BLACK
                 << "  LOCATION FINDER  " << RESET
                 << BOLD << CYAN << "  Hash Table  O(1) by ID" << RESET << "\n";
            printThinLine(CYAN);
            cout << "  " << BOLD << "  Stored : " << RESET
                 << CYAN << BOLD << locationMap.size() << " locations" << RESET << "\n";
            printLine(CYAN);
            cout << "  " << CYAN << "  1" << RESET << "  Add Location\n";
            cout << "  " << CYAN << "  2" << RESET << "  Search by User ID      " << DIM << "(O(1) hash)" << RESET << "\n";
            cout << "  " << CYAN << "  3" << RESET << "  Search by Request Token " << DIM << "(O(n) scan)" << RESET << "\n";
            cout << "  " << CYAN << "  4" << RESET << "  Remove Location\n";
            cout << "  " << CYAN << "  5" << RESET << "  Display All\n";
            cout << "  " << CYAN << "  6" << RESET << "  Back\n";
            printThinLine(CYAN);
            cout << "  " << BOLD << CYAN << "  ➤  Choice: " << RESET;
            cin >> choice;

            if (choice == 1) {
                int id; string tok, name, area, land; double lat, lon;
                printThinLine(CYAN);
                cout << "  " << YELLOW << "  User ID        : " << RESET; cin >> id; cin.ignore();
                cout << "  " << YELLOW << "  Request Token  : " << RESET; getline(cin, tok);
                cout << "  " << YELLOW << "  Passenger Name : " << RESET; getline(cin, name);
                cout << "  " << YELLOW << "  Area           : " << RESET; getline(cin, area);
                cout << "  " << YELLOW << "  Latitude       : " << RESET; cin >> lat;
                cout << "  " << YELLOW << "  Longitude      : " << RESET; cin >> lon; cin.ignore();
                cout << "  " << YELLOW << "  Landmark       : " << RESET; getline(cin, land);
                addLocation(id, PassengerLocation(id,tok,name,area,lat,lon,land));
            }
            else if (choice == 2) {
                int id;
                cout << "\n  " << YELLOW << "  Enter User ID: " << RESET; cin >> id;
                PassengerLocation* loc = searchById(id);
                if (loc) printCard(loc);
                else     printError("No record for ID: " + to_string(id));
            }
            else if (choice == 3) {
                string tok; cin.ignore();
                cout << "\n  " << YELLOW << "  Enter Token (e.g. REQ-2001): " << RESET;
                getline(cin, tok);
                PassengerLocation* loc = searchByToken(tok);
                if (loc) printCard(loc);
                else     printError("No record for token: " + tok);
            }
            else if (choice == 4) {
                int id;
                cout << "\n  " << YELLOW << "  User ID to remove: " << RESET; cin >> id;
                removeLocation(id);
            }
            else if (choice == 5) { displayAllLocations(); }
            else if (choice != 6) { printError("Invalid choice."); }

        } while (choice != 6);
    }
};
