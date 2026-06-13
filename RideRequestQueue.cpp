/*
    RideRequestQueue.cpp  —  Feature 3 : Queue (FIFO linked-list)
*/

struct RideRequest {
    int    requestId;
    string passengerName;
    string pickupLocation;
    string dropLocation;
    int    seatsNeeded;
    string requestTime;

    RideRequest()
        : requestId(0), passengerName(""), pickupLocation(""),
          dropLocation(""), seatsNeeded(1), requestTime("") {}
    RideRequest(int id, string name, string pickup,
                string drop, int seats, string time)
        : requestId(id), passengerName(name), pickupLocation(pickup),
          dropLocation(drop), seatsNeeded(seats), requestTime(time) {}
};

struct QueueNode {
    RideRequest data;
    QueueNode*  next;
    QueueNode(RideRequest r) : data(r), next(nullptr) {}
};

class RideRequestQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int        size;

    string seatDots(int seats) {
        string s = "";
        for (int i = 0; i < seats; i++) s += "●";
        for (int i = seats; i < 4; i++) s += "○";
        return s;
    }

public:
    RideRequestQueue() { front = nullptr; rear = nullptr; size = 0; }
    ~RideRequestQueue() { while (!isEmpty()) dequeue(); }

    bool isEmpty() { return front == nullptr; }
    int  getSize() { return size; }

    // Enqueue — O(1)
    void enqueue(RideRequest r) {
        QueueNode* n = new QueueNode(r);
        if (isEmpty()) { front = n; rear = n; }
        else           { rear->next = n; rear = n; }
        size++;
        cout << "  " << BOLD << GREEN << "✔ " << RESET << GREEN
             << "#" << r.requestId << "  " << r.passengerName
             << "  " << r.pickupLocation << " → " << r.dropLocation
             << RESET << "\n";
    }

    // Dequeue — O(1)
    RideRequest dequeue() {
        if (isEmpty()) { printError("Queue is empty."); return RideRequest(); }
        QueueNode*  tmp = front;
        RideRequest p   = tmp->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete tmp; size--;
        return p;
    }

    // Peek — O(1)
    RideRequest peek() {
        if (isEmpty()) { printError("Queue is empty."); return RideRequest(); }
        return front->data;
    }

    void displayPending() {
        if (isEmpty()) { printError("No pending requests."); return; }
        cout << "\n";
        printLine(MAGENTA);
        cout << "  " << BOLD << BG_MAGENTA << WHITE
             << "  PENDING RIDE REQUESTS  " << RESET
             << BOLD << MAGENTA << "  Queue  FIFO  (" << size << " total)" << RESET << "\n";
        printLine(MAGENTA);

        QueueNode* curr = front;
        int pos = 1;
        while (curr) {
            bool isNext    = (pos == 1);
            const char* rc = isNext ? CYAN : WHITE;
            cout << "  " << BOLD << MAGENTA << "  [" << pos << "]" << RESET;
            if (isNext) cout << BOLD << GREEN << "  ◄ NEXT" << RESET;
            cout << "\n";
            cout << "  " << tML << tH << tH << " "
                 << BOLD << rc << "#" << curr->data.requestId
                 << "  " << curr->data.passengerName << RESET << "\n";
            cout << "  " << tV << "    " << DIM << "From  : " << RESET
                 << WHITE << curr->data.pickupLocation << RESET << "\n";
            cout << "  " << tV << "    " << DIM << "To    : " << RESET
                 << WHITE << curr->data.dropLocation << RESET << "\n";
            cout << "  " << tV << "    " << CYAN
                 << seatDots(curr->data.seatsNeeded) << RESET
                 << DIM << "  " << curr->data.seatsNeeded << " seats"
                 << "  @ " << curr->data.requestTime << RESET << "\n";

            if (curr->next) cout << "  " << tML;
            else            cout << "  " << tBL;
            for (int i = 0; i < 46; i++) cout << tH;
            if (curr->next) cout << tMR; else cout << tBR;
            cout << "\n";

            curr = curr->next; pos++;
        }
        cout << "\n";
    }

    void loadSampleData() {
        enqueue(RideRequest(2001,"Arjun Sharma","Andheri West",  "BKC",        2,"08:05 AM"));
        enqueue(RideRequest(2002,"Priya Mehta", "Thane Station", "CST",        1,"08:12 AM"));
        enqueue(RideRequest(2003,"Ravi Kumar",  "Borivali",      "Dadar",      3,"08:18 AM"));
        enqueue(RideRequest(2004,"Sneha Patil", "Vashi",         "Kurla",      1,"08:25 AM"));
        enqueue(RideRequest(2005,"Vikram Patel","Kandivali",     "Churchgate", 2,"08:30 AM"));
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n";
            printLine(MAGENTA);
            cout << "  " << BOLD << BG_MAGENTA << WHITE
                 << "  RIDE REQUEST QUEUE  " << RESET
                 << BOLD << MAGENTA << "  Queue  O(1) enqueue/dequeue" << RESET << "\n";
            printThinLine(MAGENTA);
            cout << "  " << BOLD << "  Pending : " << RESET
                 << MAGENTA << BOLD << size << RESET;
            if (!isEmpty())
                cout << DIM << "   next → " << RESET
                     << CYAN << front->data.passengerName << RESET;
            cout << "\n";
            printLine(MAGENTA);
            cout << "  " << MAGENTA << "  1" << RESET << "  Add Ride Request    " << DIM << "(Enqueue)" << RESET << "\n";
            cout << "  " << MAGENTA << "  2" << RESET << "  Process Next        " << DIM << "(Dequeue)" << RESET << "\n";
            cout << "  " << MAGENTA << "  3" << RESET << "  View Next           " << DIM << "(Peek)" << RESET << "\n";
            cout << "  " << MAGENTA << "  4" << RESET << "  Display All Pending\n";
            cout << "  " << MAGENTA << "  5" << RESET << "  Back\n";
            printThinLine(MAGENTA);
            cout << "  " << BOLD << MAGENTA << "  ➤  Choice: " << RESET;
            cin >> choice;

            if (choice == 1) {
                RideRequest r;
                printThinLine(MAGENTA);
                cout << "  " << YELLOW << "  Request ID     : " << RESET; cin >> r.requestId; cin.ignore();
                cout << "  " << YELLOW << "  Passenger Name : " << RESET; getline(cin, r.passengerName);
                cout << "  " << YELLOW << "  Pickup         : " << RESET; getline(cin, r.pickupLocation);
                cout << "  " << YELLOW << "  Drop           : " << RESET; getline(cin, r.dropLocation);
                cout << "  " << YELLOW << "  Seats Needed   : " << RESET; cin >> r.seatsNeeded; cin.ignore();
                cout << "  " << YELLOW << "  Request Time   : " << RESET; getline(cin, r.requestTime);
                enqueue(r);
            }
            else if (choice == 2) {
                RideRequest p = dequeue();
                if (p.requestId != 0) {
                    cout << "\n";
                    printLine(GREEN);
                    cout << "  " << BOLD << BG_GREEN << BLACK
                         << "  REQUEST PROCESSED  " << RESET
                         << BOLD << GREEN << "  ASSIGNED TO DRIVER" << RESET << "\n";
                    printThinLine(GREEN);
                    printLabel("  Passenger :", p.passengerName);
                    printLabel("  From      :", p.pickupLocation);
                    printLabel("  To        :", p.dropLocation);
                    printLabel("  Seats     :", seatDots(p.seatsNeeded) + " " + to_string(p.seatsNeeded));
                    cout << "  " << BOLD << GREEN << "  Status    :  ✔ RIDE ASSIGNED" << RESET << "\n";
                    printLine(GREEN);
                }
            }
            else if (choice == 3) {
                RideRequest next = peek();
                if (next.requestId != 0) {
                    cout << "\n";
                    printThinLine(CYAN);
                    cout << "  " << BOLD << CYAN << "  NEXT IN QUEUE" << RESET << "\n";
                    printThinLine(CYAN);
                    printLabel("  Passenger :", next.passengerName);
                    printLabel("  From      :", next.pickupLocation);
                    printLabel("  To        :", next.dropLocation);
                    printLabel("  Time      :", next.requestTime);
                    printThinLine(CYAN);
                }
            }
            else if (choice == 4) { displayPending(); }
            else if (choice != 5) { printError("Invalid choice."); }

        } while (choice != 5);
    }
};
