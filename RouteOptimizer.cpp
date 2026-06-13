/*
    RouteOptimizer.cpp  —  Feature 7 : Dijkstra's Algorithm
    Depends on StreetNetwork (included before this in main.cpp)
*/

class RouteOptimizer {
private:
    StreetNetwork* network;
    typedef pair<int,int> pii;

    void printPath(vector<int>& path, int totalTime) {
        cout << "\n  " << DIM << "  Path : " << RESET;
        for (int i = 0; i < (int)path.size(); i++) {
            cout << BOLD << CYAN << network->getLocationName(path[i]) << RESET;
            if (i != (int)path.size() - 1)
                cout << YELLOW << "  →  " << RESET;
        }
        cout << "\n  " << BOLD << GREEN
             << "  Total Travel Time : " << totalTime << " minutes"
             << RESET << "\n";
    }

public:
    RouteOptimizer(StreetNetwork* net) { network = net; }

    // Core Dijkstra — O((V+E) log V)
    int dijkstra(int src, int dest, vector<int>& path) {
        int n = network->getNumLocations();
        vector<int>  dist(n, INT_MAX);
        vector<int>  prev(n, -1);
        vector<bool> vis(n, false);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        dist[src] = 0; pq.push({0, src});
        while (!pq.empty()) {
            int u = pq.top().second; pq.pop();
            if (vis[u]) continue; vis[u] = true;
            for (auto& e : network->getAdjList()[u]) {
                int v = e.destination, w = e.travelTime;
                if (!vis[v] && dist[u]+w < dist[v]) {
                    dist[v] = dist[u]+w; prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        path.clear();
        if (dist[dest] == INT_MAX) return -1;
        for (int c = dest; c != -1; c = prev[c]) path.push_back(c);
        reverse(path.begin(), path.end());
        return dist[dest];
    }

    void displayShortestRoute(int src, int dest) {
        int n = network->getNumLocations();
        if (src<0||src>=n||dest<0||dest>=n) { printError("Invalid index."); return; }
        vector<int> path;
        int t = dijkstra(src, dest, path);
        if (t == -1) { printError("No route found."); return; }
        cout << "\n";
        printLine(YELLOW);
        cout << "  " << BOLD << BG_YELLOW << BLACK
             << "  SHORTEST ROUTE  " << RESET
             << BOLD << YELLOW << "  Dijkstra  Min Travel Time" << RESET << "\n";
        printThinLine(YELLOW);
        printLabel("  From :", network->getLocationName(src));
        printLabel("  To   :", network->getLocationName(dest));
        printPath(path, t);
        printLine(YELLOW);
    }

    void displayMultiStop(vector<int>& stops) {
        if ((int)stops.size() < 2) { printError("Need at least 2 stops."); return; }
        int n = network->getNumLocations();
        for (int s : stops)
            if (s<0||s>=n) { printError("Invalid index: " + to_string(s)); return; }
        cout << "\n";
        printLine(YELLOW);
        cout << "  " << BOLD << BG_YELLOW << BLACK
             << "  MULTI-STOP CARPOOL ROUTE  " << RESET
             << BOLD << YELLOW << "  Dijkstra per leg" << RESET << "\n";
        printThinLine(YELLOW);
        int total = 0; vector<int> full;
        for (int i = 0; i < (int)stops.size()-1; i++) {
            vector<int> seg;
            int t = dijkstra(stops[i], stops[i+1], seg);
            if (t == -1) {
                printError("No route: " + network->getLocationName(stops[i])
                           + " → " + network->getLocationName(stops[i+1]));
                return;
            }
            cout << "  " << BOLD << CYAN << "  Leg " << i+1 << RESET
                 << "  " << WHITE << network->getLocationName(stops[i]) << RESET
                 << YELLOW << "  →  " << RESET
                 << WHITE << network->getLocationName(stops[i+1]) << RESET
                 << GREEN  << "  " << t << " min" << RESET << "\n";
            if (full.empty()) full = seg;
            else for (int j=1; j<(int)seg.size(); j++) full.push_back(seg[j]);
            total += t;
        }
        printThinLine(YELLOW);
        printPath(full, total);
        printLine(YELLOW);
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n";
            printLine(YELLOW);
            cout << "  " << BOLD << BG_YELLOW << BLACK
                 << "  ROUTE OPTIMIZER  " << RESET
                 << BOLD << YELLOW << "  Dijkstra  O((V+E) log V)" << RESET << "\n";
            printLine(YELLOW);
            cout << "  " << YELLOW << "  1" << RESET << "  Single Route          " << DIM << "(source → destination)" << RESET << "\n";
            cout << "  " << YELLOW << "  2" << RESET << "  Multi-Stop Carpool    " << DIM << "(pick up multiple passengers)" << RESET << "\n";
            cout << "  " << YELLOW << "  3" << RESET << "  View All Locations\n";
            cout << "  " << YELLOW << "  4" << RESET << "  Back\n";
            printThinLine(YELLOW);
            cout << "  " << BOLD << YELLOW << "  ➤  Choice: " << RESET;
            cin >> choice;

            if (choice == 1) {
                network->displayLocationList();
                int src, dest;
                cout << "\n  " << YELLOW << "  Source index      : " << RESET; cin >> src;
                cout << "  "   << YELLOW << "  Destination index : " << RESET; cin >> dest;
                displayShortestRoute(src, dest);
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
                    displayMultiStop(stops);
                }
            }
            else if (choice == 3) { network->displayLocationList(); }
            else if (choice != 4) { printError("Invalid choice."); }

        } while (choice != 4);
    }
};
