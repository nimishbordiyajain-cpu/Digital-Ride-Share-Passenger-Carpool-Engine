/*
    TollOptimizer.cpp  —  Feature 8 : Modified Dijkstra (min toll)
    Depends on StreetNetwork (included before this in main.cpp)
*/

class TollOptimizer {
private:
    StreetNetwork* network;
    typedef pair<double,int> pdi;

    void printPath(vector<int>& path, double toll) {
        cout << "\n  " << DIM << "  Path : " << RESET;
        for (int i = 0; i < (int)path.size(); i++) {
            cout << BOLD << CYAN << network->getLocationName(path[i]) << RESET;
            if (i != (int)path.size() - 1)
                cout << YELLOW << "  →  " << RESET;
        }
        cout << "\n";
        if (toll == 0.0)
            cout << "  " << BOLD << GREEN << "  ✔  TOLL-FREE ROUTE  Rs.0" << RESET << "\n";
        else
            cout << "  " << BOLD << RED << "  Total Toll : Rs." << (int)toll << RESET << "\n";
    }

public:
    TollOptimizer(StreetNetwork* net) { network = net; }

    // Modified Dijkstra — weight = tollCost — O((V+E) log V)
    double dijkstraToll(int src, int dest, vector<int>& path) {
        int n = network->getNumLocations();
        vector<double> toll(n, 1e9);
        vector<int>    prev(n, -1);
        vector<bool>   vis(n, false);
        priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
        toll[src] = 0.0; pq.push({0.0, src});
        while (!pq.empty()) {
            int u = pq.top().second; pq.pop();
            if (vis[u]) continue; vis[u] = true;
            for (auto& e : network->getAdjList()[u]) {
                int v = e.destination; double w = e.tollCost;
                if (!vis[v] && toll[u]+w < toll[v]) {
                    toll[v] = toll[u]+w; prev[v] = u;
                    pq.push({toll[v], v});
                }
            }
        }
        path.clear();
        if (toll[dest] >= 1e9) return -1.0;
        for (int c = dest; c != -1; c = prev[c]) path.push_back(c);
        reverse(path.begin(), path.end());
        return toll[dest];
    }

    void displayCheapestRoute(int src, int dest) {
        int n = network->getNumLocations();
        if (src<0||src>=n||dest<0||dest>=n) { printError("Invalid index."); return; }
        vector<int> path;
        double t = dijkstraToll(src, dest, path);
        if (t < 0) { printError("No route found."); return; }
        cout << "\n";
        printLine(RED);
        cout << "  " << BOLD << "\033[41m" << WHITE
             << "  CHEAPEST TOLL ROUTE  " << RESET
             << BOLD << RED << "  Modified Dijkstra  min toll" << RESET << "\n";
        printThinLine(RED);
        printLabel("  From :", network->getLocationName(src));
        printLabel("  To   :", network->getLocationName(dest));
        printPath(path, t);
        printLine(RED);
    }

    void displayMultiStopToll(vector<int>& stops) {
        if ((int)stops.size() < 2) { printError("Need at least 2 stops."); return; }
        int n = network->getNumLocations();
        for (int s : stops)
            if (s<0||s>=n) { printError("Invalid index: " + to_string(s)); return; }
        cout << "\n";
        printLine(RED);
        cout << "  " << BOLD << "\033[41m" << WHITE
             << "  MULTI-STOP TOLL ROUTE  " << RESET
             << BOLD << RED << "  Min toll per leg" << RESET << "\n";
        printThinLine(RED);
        double total = 0.0; vector<int> full;
        for (int i = 0; i < (int)stops.size()-1; i++) {
            vector<int> seg;
            double t = dijkstraToll(stops[i], stops[i+1], seg);
            if (t < 0) {
                printError("No route: " + network->getLocationName(stops[i])
                           + " → " + network->getLocationName(stops[i+1]));
                return;
            }
            cout << "  " << BOLD << RED << "  Leg " << i+1 << RESET
                 << "  " << WHITE << network->getLocationName(stops[i]) << RESET
                 << YELLOW << "  →  " << RESET
                 << WHITE << network->getLocationName(stops[i+1]) << RESET << "   ";
            if (t == 0.0) cout << GREEN << "toll-free" << RESET;
            else          cout << RED   << "Rs." << (int)t << RESET;
            cout << "\n";
            if (full.empty()) full = seg;
            else for (int j=1; j<(int)seg.size(); j++) full.push_back(seg[j]);
            total += t;
        }
        printThinLine(RED);
        printPath(full, total);
        printLine(RED);
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n";
            printLine(RED);
            cout << "  " << BOLD << "\033[41m" << WHITE
                 << "  TOLL OPTIMIZER  " << RESET
                 << BOLD << RED << "  Modified Dijkstra  O((V+E) log V)" << RESET << "\n";
            printLine(RED);
            cout << "  " << RED << "  1" << RESET << "  Cheapest Toll Route       " << DIM << "(single)" << RESET << "\n";
            cout << "  " << RED << "  2" << RESET << "  Multi-Stop Cheapest Toll  " << DIM << "(carpool)" << RESET << "\n";
            cout << "  " << RED << "  3" << RESET << "  View All Locations\n";
            cout << "  " << RED << "  4" << RESET << "  Back\n";
            printThinLine(RED);
            cout << "  " << BOLD << RED << "  ➤  Choice: " << RESET;
            cin >> choice;

            if (choice == 1) {
                network->displayLocationList();
                int src, dest;
                cout << "\n  " << YELLOW << "  Source index      : " << RESET; cin >> src;
                cout << "  "   << YELLOW << "  Destination index : " << RESET; cin >> dest;
                displayCheapestRoute(src, dest);
            }
            else if (choice == 2) {
                network->displayLocationList();
                int ns;
                cout << "\n  " << YELLOW << "  How many stops? (min 2): " << RESET; cin >> ns;
                if (ns < 2) { printError("Need at least 2."); }
                else {
                    vector<int> stops(ns);
                    for (int i=0; i<ns; i++) {
                        cout << "  " << YELLOW << "  Stop " << i+1 << " index: " << RESET;
                        cin >> stops[i];
                    }
                    displayMultiStopToll(stops);
                }
            }
            else if (choice == 3) { network->displayLocationList(); }
            else if (choice != 4) { printError("Invalid choice."); }

        } while (choice != 4);
    }
};
