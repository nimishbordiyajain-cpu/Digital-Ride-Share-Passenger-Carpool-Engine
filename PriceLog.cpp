/*
    PriceLog.cpp  —  Feature 2 : Stack (linked-list LIFO)
*/

struct PriceEntry {
    double surgeMultiplier;
    string reason;
    string timestamp;
    PriceEntry() : surgeMultiplier(1.0), reason(""), timestamp("") {}
    PriceEntry(double m, string r, string t)
        : surgeMultiplier(m), reason(r), timestamp(t) {}
};

struct StackNode {
    PriceEntry data;
    StackNode* next;
    StackNode(PriceEntry p) : data(p), next(nullptr) {}
};

class PriceLog {
private:
    StackNode* top;
    int        size;
    double     basePrice;

    // color based on surge level
    const char* surgeColor(double m) {
        if (m >= 2.0) return RED;
        if (m >= 1.5) return YELLOW;
        return GREEN;
    }

    // visual bar for surge level
    string surgeBar(double m) {
        int filled = (int)(m * 4);
        if (filled > 12) filled = 12;
        string bar = "  [";
        for (int i = 0; i < filled; i++)  bar += "█";
        for (int i = filled; i < 12; i++) bar += "░";
        bar += "]";
        return bar;
    }

public:
    PriceLog(double base = 12.0) {
        top = nullptr; size = 0; basePrice = base;
    }
    ~PriceLog() { while (!isEmpty()) popPrice(); }

    bool isEmpty() { return top == nullptr; }
    int  getSize() { return size; }

    // Push — O(1)
    void pushPrice(PriceEntry entry) {
        StackNode* n = new StackNode(entry);
        n->next = top; top = n; size++;
        cout << "  " << BOLD << GREEN << "✔ " << RESET << GREEN
             << "Surge " << BOLD << entry.surgeMultiplier << "x" << RESET
             << GREEN << " pushed  →  " << entry.reason << RESET << "\n";
    }

    // Pop / rollback — O(1)
    PriceEntry popPrice() {
        if (isEmpty()) {
            cout << "  " << BOLD << YELLOW << "⚠  " << RESET << YELLOW
                 << "No surge to roll back. Base price active." << RESET << "\n";
            return PriceEntry(1.0, "base", "");
        }
        StackNode* tmp = top;
        PriceEntry p   = tmp->data;
        top = top->next;
        delete tmp; size--;
        return p;
    }

    // Peek — O(1)
    PriceEntry peekCurrentPrice() {
        if (isEmpty()) return PriceEntry(1.0, "base price (no active surge)", "");
        return top->data;
    }

    double getCurrentFare(double km) {
        return basePrice * km * peekCurrentPrice().surgeMultiplier;
    }

    void displayHistory() {
        if (isEmpty()) {
            printInfo("Price log empty. Base: Rs." + to_string((int)basePrice) + "/km");
            return;
        }
        cout << "\n";
        printLine(YELLOW);
        cout << "  " << BOLD << BG_YELLOW << BLACK
             << "  SURGE PRICE HISTORY  " << RESET
             << BOLD << YELLOW << "  Stack  LIFO  (" << size << " entries)" << RESET << "\n";
        printLine(YELLOW);
        StackNode* curr = top;
        int pos = 1;
        while (curr) {
            const char* sc = surgeColor(curr->data.surgeMultiplier);
            cout << "  " << BOLD << sc
                 << "  [" << pos << "]  " << RESET
                 << sc << curr->data.surgeMultiplier << "x  " << RESET
                 << sc << surgeBar(curr->data.surgeMultiplier) << RESET
                 << DIM << "  " << curr->data.reason
                 << "  @" << curr->data.timestamp << RESET << "\n";
            curr = curr->next; pos++;
        }
        printThinLine(YELLOW);
        cout << "  " << DIM << "  Base : " << RESET
             << WHITE << "Rs." << basePrice << "/km" << RESET << "\n";
        printLine(YELLOW);
    }

    void loadSampleData() {
        pushPrice(PriceEntry(1.2, "Morning rush hour",     "07:30 AM"));
        pushPrice(PriceEntry(1.5, "Rain in Mumbai",         "09:00 AM"));
        pushPrice(PriceEntry(2.0, "IPL match at Wankhede", "06:00 PM"));
    }

    void showMenu() {
        int choice;
        do {
            PriceEntry curr = peekCurrentPrice();
            const char* sc = surgeColor(curr.surgeMultiplier);
            cout << "\n";
            printLine(YELLOW);
            cout << "  " << BOLD << BG_YELLOW << BLACK
                 << "  PRICE LOG  " << RESET
                 << BOLD << YELLOW << "  Stack  O(1) push/pop/peek" << RESET << "\n";
            printThinLine(YELLOW);
            cout << "  " << BOLD << "  Active : " << RESET
                 << sc << BOLD << curr.surgeMultiplier << "x" << RESET
                 << sc << "  " << curr.reason << RESET << "\n";
            cout << "  " << sc << surgeBar(curr.surgeMultiplier) << RESET
                 << DIM << "  depth: " << size << RESET << "\n";
            printLine(YELLOW);
            cout << "  " << YELLOW << "  1" << RESET << "  Push New Surge\n";
            cout << "  " << YELLOW << "  2" << RESET << "  Rollback Last Surge  " << DIM << "(Pop)" << RESET << "\n";
            cout << "  " << YELLOW << "  3" << RESET << "  View Current Price\n";
            cout << "  " << YELLOW << "  4" << RESET << "  View Full History\n";
            cout << "  " << YELLOW << "  5" << RESET << "  Calculate Fare\n";
            cout << "  " << YELLOW << "  6" << RESET << "  Back\n";
            printThinLine(YELLOW);
            cout << "  " << BOLD << YELLOW << "  ➤  Choice: " << RESET;
            cin >> choice;

            if (choice == 1) {
                double m; string reason, time;
                printThinLine(YELLOW);
                cout << "  " << YELLOW << "  Multiplier  : " << RESET; cin >> m; cin.ignore();
                cout << "  " << YELLOW << "  Reason      : " << RESET; getline(cin, reason);
                cout << "  " << YELLOW << "  Timestamp   : " << RESET; getline(cin, time);
                pushPrice(PriceEntry(m, reason, time));
            }
            else if (choice == 2) {
                PriceEntry rolled = popPrice();
                if (rolled.reason != "base") {
                    const char* sc2 = surgeColor(rolled.surgeMultiplier);
                    cout << "  " << BOLD << RED << "✘ " << RESET << RED
                         << "Rolled back: " << rolled.surgeMultiplier
                         << "x (" << rolled.reason << ")" << RESET << "\n";
                    PriceEntry now = peekCurrentPrice();
                    const char* sc3 = surgeColor(now.surgeMultiplier);
                    cout << "  " << BOLD << GREEN << "✔ " << RESET << GREEN
                         << "Now active: " << now.surgeMultiplier
                         << "x (" << now.reason << ")" << RESET << "\n";
                }
            }
            else if (choice == 3) {
                PriceEntry p = peekCurrentPrice();
                const char* sc2 = surgeColor(p.surgeMultiplier);
                cout << "\n";
                printThinLine(YELLOW);
                cout << "  " << BOLD << YELLOW << "  CURRENT PRICE" << RESET << "\n";
                printThinLine(YELLOW);
                printLabel("  Surge    :", to_string(p.surgeMultiplier) + "x");
                printLabel("  Reason   :", p.reason);
                printLabel("  Base     :", "Rs." + to_string((int)basePrice) + "/km");
                cout << "  " << BOLD << YELLOW << "  Effective: " << RESET
                     << sc2 << BOLD << "Rs." << basePrice * p.surgeMultiplier << "/km" << RESET << "\n";
                printThinLine(YELLOW);
            }
            else if (choice == 4) { displayHistory(); }
            else if (choice == 5) {
                double km;
                cout << "\n  " << YELLOW << "  Distance in km: " << RESET; cin >> km;
                cout << "  " << BOLD << GREEN
                     << "  Fare for " << km << " km = Rs." << getCurrentFare(km)
                     << RESET << "\n";
            }
            else if (choice != 6) { printError("Invalid choice."); }

        } while (choice != 6);
    }
};
