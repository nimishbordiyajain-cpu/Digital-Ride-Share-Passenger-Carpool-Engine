/*
============================================================
    main.cpp  —  PoolRide Carpool Engine
    DSA-I End Semester Project  |  C++ Console Application

    Compile : g++ main.cpp -o PoolRide
    Run     : ./PoolRide
============================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

// =============================================================
//  ANSI COLOR CODES  (defined once here, used in all modules)
// =============================================================
#define RESET     "\033[0m"
#define BOLD      "\033[1m"
#define DIM       "\033[2m"
#define RED       "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"
#define MAGENTA   "\033[35m"
#define CYAN      "\033[36m"
#define WHITE     "\033[37m"
#define BG_CYAN   "\033[46m"
#define BG_GREEN  "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_MAGENTA "\033[45m"
#define BG_BLUE   "\033[44m"
#define BLACK     "\033[30m"

// Box-drawing characters
#define tTL "┌"
#define tTR "┐"
#define tBL "└"
#define tBR "┘"
#define tH  "─"
#define tV  "│"
#define tML "├"
#define tMR "┤"

// =============================================================
//  SHARED HELPER FUNCTIONS  (available to every module)
// =============================================================
void printLine(const char* color = CYAN) {
    cout << color
         << "  ══════════════════════════════════════════════════"
         << RESET << "\n";
}

void printThinLine(const char* color = DIM) {
    cout << color
         << "  ──────────────────────────────────────────────────"
         << RESET << "\n";
}

void printSuccess(string msg) {
    cout << "  " << BOLD << GREEN << "✔ " << RESET << GREEN << msg << RESET << "\n";
}

void printError(string msg) {
    cout << "  " << BOLD << RED << "✘ " << RESET << RED << msg << RESET << "\n";
}

void printInfo(string msg) {
    cout << "  " << CYAN << "➤  " << RESET << msg << "\n";
}

void printLabel(const char* label, string value) {
    cout << "  " << BOLD << YELLOW << label << RESET << " " << WHITE << value << RESET << "\n";
}

// =============================================================
//  INCLUDE ALL MODULES (in dependency order)
// =============================================================
#include "UserDirectory.cpp"
#include "PriceLog.cpp"
#include "RideRequestQueue.cpp"
#include "LocationFinder.cpp"
#include "CapacitySorter.cpp"
#include "StreetNetwork.cpp"
#include "RouteOptimizer.cpp"
#include "TollOptimizer.cpp"

// =============================================================
//  BANNER
// =============================================================
void printBanner() {
    cout << "\033[2J\033[H";   // clear screen
    cout << "\n";
    cout << BOLD << CYAN
         << "  ╔══════════════════════════════════════════════════╗\n"
         << "  ║                                                  ║\n"
         << "  ║   " << RESET << BG_CYAN << BLACK << BOLD
         << "   🚗  POOLRIDE CARPOOL ENGINE  🚗   "
         << RESET << BOLD << CYAN << "        ║\n"
         << "  ║                                                  ║\n"
         << "  ╠══════════════════════════════════════════════════╣\n"
         << "  ║  " << RESET << WHITE
         << "  Digital Ride-Share Passenger System          "
         << BOLD << CYAN << "║\n"
         << "  ║  " << RESET << DIM
         << "  DSA-I End Semester Project  |  C++ Console   "
         << BOLD << CYAN << "║\n"
         << "  ╚══════════════════════════════════════════════════╝\n"
         << RESET << "\n";
}

// =============================================================
//  LOADING LINE
// =============================================================
void printLoading(const char* module, const char* detail) {
    cout << "  " << BOLD << GREEN << "✔  " << RESET
         << BOLD << WHITE << module << RESET
         << DIM   << "  " << detail << RESET << "\n";
}

// =============================================================
//  MAIN MENU
// =============================================================
void printMenu() {
    cout << "\n" << BOLD << CYAN
         << "  ╔══════════════════════════════════════════════════╗\n"
         << "  ║           " << RESET << BG_CYAN << BLACK << BOLD
         << "       MAIN MENU       "
         << RESET << BOLD << CYAN << "                ║\n"
         << "  ╠══════════════════════════════════════════════════╣\n"
         << "  ║                                                  ║\n"

         << "  ║  " << RESET << BOLD << CYAN   << " 1 " << RESET
         << "  User Directory      " << DIM << "B-Tree           "
         << BOLD << CYAN << "║\n"

         << "  ║  " << RESET << BOLD << YELLOW << " 2 " << RESET
         << "  Price Log           " << DIM << "Stack            "
         << BOLD << CYAN << "║\n"

         << "  ║  " << RESET << BOLD << MAGENTA<< " 3 " << RESET
         << "  Ride Request Queue  " << DIM << "Queue            "
         << BOLD << CYAN << "║\n"

         << "  ║  " << RESET << BOLD << CYAN   << " 4 " << RESET
         << "  Location Finder     " << DIM << "Hash Table       "
         << BOLD << CYAN << "║\n"

         << "  ║  " << RESET << BOLD << GREEN  << " 5 " << RESET
         << "  Capacity Sorter     " << DIM << "Max Heap         "
         << BOLD << CYAN << "║\n"

         << "  ║  " << RESET << BOLD << BLUE   << " 6 " << RESET
         << "  Street Network      " << DIM << "Graph            "
         << BOLD << CYAN << "║\n"

         << "  ║  " << RESET << BOLD << YELLOW << " 7 " << RESET
         << "  Route Optimizer     " << DIM << "Dijkstra         "
         << BOLD << CYAN << "║\n"

         << "  ║  " << RESET << BOLD << RED    << " 8 " << RESET
         << "  Toll Optimizer      " << DIM << "Mod. Dijkstra    "
         << BOLD << CYAN << "║\n"

         << "  ║                                                  ║\n"
         << "  ║  " << RESET << DIM  << " 9 " << RESET
         << "  Exit                                     "
         << BOLD << CYAN << "║\n"

         << "  ║                                                  ║\n"
         << "  ╚══════════════════════════════════════════════════╝\n"
         << RESET
         << "\n  " << BOLD << CYAN << "  ➤  Choice (1-9): " << RESET;
}

// =============================================================
//  MAIN
// =============================================================
int main() {
    printBanner();
    cout << DIM << "  Initializing modules...\n\n" << RESET;

    UserDirectory    userDir(3);
    PriceLog         priceLog(12.0);
    RideRequestQueue requestQueue;
    LocationFinder   locationFinder;
    CapacitySorter   capacitySorter;
    StreetNetwork    streetNetwork(10);
    RouteOptimizer   routeOptimizer(&streetNetwork);
    TollOptimizer    tollOptimizer(&streetNetwork);

    userDir.loadSampleData();
    printLoading("User Directory     ", "10 users  →  B-Tree");

    priceLog.loadSampleData();
    printLoading("Price Log          ", "3 surge entries  →  Stack");

    requestQueue.loadSampleData();
    printLoading("Ride Request Queue ", "5 requests  →  Queue (FIFO)");

    locationFinder.loadSampleData();
    printLoading("Location Finder    ", "10 locations  →  Hash Table");

    capacitySorter.loadSampleData();
    printLoading("Capacity Sorter    ", "8 vehicles  →  Max Heap");

    streetNetwork.loadSampleData();
    printLoading("Street Network     ", "10 nodes, 15 roads  →  Graph");

    printLoading("Route Optimizer    ", "Dijkstra ready");
    printLoading("Toll Optimizer     ", "Modified Dijkstra ready");

    cout << "\n";
    printLine(GREEN);
    cout << "  " << BOLD << GREEN
         << "  ✔  All systems ready.  Welcome to PoolRide!"
         << RESET << "\n";
    printLine(GREEN);

    int choice;
    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: userDir.showMenu();        break;
            case 2: priceLog.showMenu();       break;
            case 3: requestQueue.showMenu();   break;
            case 4: locationFinder.showMenu(); break;
            case 5: capacitySorter.showMenu(); break;
            case 6: streetNetwork.showMenu();  break;
            case 7: routeOptimizer.showMenu(); break;
            case 8: tollOptimizer.showMenu();  break;
            case 9:
                cout << "\n";
                printLine(CYAN);
                cout << "  " << BOLD << CYAN
                     << "  Thank you for using PoolRide.  Goodbye! 🚗"
                     << RESET << "\n";
                printLine(CYAN);
                cout << "\n";
                break;
            default:
                printError("Invalid choice. Enter 1-9.");
        }
    } while (choice != 9);

    return 0;
}
