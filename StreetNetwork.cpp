/*
    StreetNetwork.cpp  —  Feature 6 : Graph (Adjacency List)
*/

struct RoadEdge {
    int    destination;
    int    travelTime;
    double tollCost;
    RoadEdge(int d, int t, double c) : destination(d), travelTime(t), tollCost(c) {}
};

struct Location {
    string name, type;
    Location() : name(""), type("") {}
    Location(string n, string t) : name(n), type(t) {}
};

class StreetNetwork {
private:
    int                    numLocations;
    vector<Location>       locations;
    vector<list<RoadEdge>> adjList;

public:
    StreetNetwork(int n) {
        numLocations = n;
        locations.resize(n);
        adjList.resize(n);
    }

    void addLocation(int i, string name, string type) {
        if (i >= 0 && i < numLocations) locations[i] = Location(name, type);
    }

    // Bidirectional road — O(1)
    void addRoad(int from, int to, int time, double toll) {
        adjList[from].push_back(RoadEdge(to,   time, toll));
        adjList[to].push_back(RoadEdge(from, time, toll));
    }

    int    getNumLocations()    { return numLocations; }
    string getLocationName(int i) {
        return (i >= 0 && i < numLocations) ? locations[i].name : "Unknown";
    }
    vector<list<RoadEdge>>& getAdjList() { return adjList; }

    void displayLocationList() {
        cout << "\n";
        printThinLine(BLUE);
        cout << "  " << BOLD << BLUE << "  CITY LOCATIONS" << RESET << "\n";
        printThinLine(BLUE);
        for (int i = 0; i < numLocations; i++) {
            cout << "  " << BOLD << BLUE << "  [" << i << "]" << RESET
                 << "  " << BOLD << WHITE << locations[i].name << RESET
                 << DIM  << "  "           << locations[i].type << RESET << "\n";
        }
        printThinLine(BLUE);
    }

    void displayNetwork() {
        cout << "\n";
        printLine(BLUE);
        cout << "  " << BOLD << BG_BLUE << WHITE
             << "  STREET NETWORK  " << RESET
             << BOLD << BLUE << "  Graph  Adjacency List  ("
             << numLocations << " nodes)" << RESET << "\n";
        printLine(BLUE);
        for (int i = 0; i < numLocations; i++) {
            cout << "\n  " << BOLD << CYAN << "  " << locations[i].name << RESET
                 << DIM << "  (" << locations[i].type << ")" << RESET << "\n";
            for (auto& e : adjList[i]) {
                cout << "  " << DIM << "    └─→ " << RESET
                     << BOLD << WHITE << locations[e.destination].name << RESET
                     << YELLOW << "  " << e.travelTime << " min" << RESET;
                if (e.tollCost > 0)
                    cout << RED << "  Rs." << (int)e.tollCost << " toll" << RESET;
                else
                    cout << GREEN << "  toll-free" << RESET;
                cout << "\n";
            }
        }
        cout << "\n";
        printLine(BLUE);
    }

    void loadSampleData() {
        addLocation(0,"Andheri",    "Residential/Commercial");
        addLocation(1,"Bandra",     "Commercial Hub");
        addLocation(2,"BKC",        "Business District");
        addLocation(3,"Kurla",      "Junction");
        addLocation(4,"Dadar",      "Junction");
        addLocation(5,"Thane",      "Residential");
        addLocation(6,"Mulund",     "Residential");
        addLocation(7,"Powai",      "Residential/IT");
        addLocation(8,"Borivali",   "Residential");
        addLocation(9,"Lower Parel","Commercial");

        addRoad(0,1, 15,  0.0);
        addRoad(0,8, 20,  0.0);
        addRoad(0,7, 25, 45.0);
        addRoad(1,2, 10, 75.0);
        addRoad(1,4, 20,  0.0);
        addRoad(1,9, 15,  0.0);
        addRoad(2,3, 12,  0.0);
        addRoad(2,9, 18,  0.0);
        addRoad(3,4, 15,  0.0);
        addRoad(3,5, 30, 55.0);
        addRoad(3,7, 20,  0.0);
        addRoad(4,9, 12,  0.0);
        addRoad(5,6, 20,  0.0);
        addRoad(6,7, 25, 30.0);
        addRoad(5,7, 35, 40.0);
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n";
            printLine(BLUE);
            cout << "  " << BOLD << BG_BLUE << WHITE
                 << "  STREET NETWORK  " << RESET
                 << BOLD << BLUE << "  Graph  Adjacency List" << RESET << "\n";
            printThinLine(BLUE);
            cout << "  " << BOLD << "  Locations : " << RESET
                 << BLUE << BOLD << numLocations << RESET
                 << DIM  << "  (Mumbai city graph)" << RESET << "\n";
            printLine(BLUE);
            cout << "  " << BLUE << "  1" << RESET << "  Display All Locations\n";
            cout << "  " << BLUE << "  2" << RESET << "  Display Full Network\n";
            cout << "  " << BLUE << "  3" << RESET << "  Add New Road\n";
            cout << "  " << BLUE << "  4" << RESET << "  Back\n";
            printThinLine(BLUE);
            cout << "  " << BOLD << BLUE << "  ➤  Choice: " << RESET;
            cin >> choice;

            if (choice == 1) { displayLocationList(); }
            else if (choice == 2) { displayNetwork(); }
            else if (choice == 3) {
                displayLocationList();
                int from, to, time; double toll;
                cout << "\n  " << YELLOW << "  Source index      : " << RESET; cin >> from;
                cout << "  "   << YELLOW << "  Destination index : " << RESET; cin >> to;
                cout << "  "   << YELLOW << "  Travel time (min) : " << RESET; cin >> time;
                cout << "  "   << YELLOW << "  Toll cost (Rs.)   : " << RESET; cin >> toll;
                if (from >= 0 && from < numLocations &&
                    to   >= 0 && to   < numLocations) {
                    addRoad(from, to, time, toll);
                    printSuccess("Road added: " + locations[from].name
                                 + " \342\206\224 " + locations[to].name);
                } else {
                    printError("Invalid location indices.");
                }
            }
            else if (choice != 4) { printError("Invalid choice."); }

        } while (choice != 4);
    }
};
