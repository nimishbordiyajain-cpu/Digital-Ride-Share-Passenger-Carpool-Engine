/*
    UserDirectory.cpp  —  Feature 1 : B-Tree (degree t = 3)
    Helpers (printLine, printError etc.) are defined in main.cpp
*/

// ── Data ──────────────────────────────────────────────────────────
struct User {
    int    userId;
    string name;
    string phone;
    string frequentRoute;

    User() : userId(0), name(""), phone(""), frequentRoute("") {}
    User(int id, string n, string p, string r)
        : userId(id), name(n), phone(p), frequentRoute(r) {}
};

// ── B-Tree Node ───────────────────────────────────────────────────
struct BTreeNode {
    User*       keys;
    int         t;
    BTreeNode** children;
    int         n;
    bool        isLeaf;

    BTreeNode(int degree, bool leaf) {
        t = degree; isLeaf = leaf; n = 0;
        keys     = new User[2 * t - 1];
        children = new BTreeNode*[2 * t];
        for (int i = 0; i < 2 * t; i++) children[i] = nullptr;
    }
    ~BTreeNode() { delete[] keys; delete[] children; }

    // In-order traversal — prints sorted by userId
    void traverse() {
        int i;
        for (i = 0; i < n; i++) {
            if (!isLeaf) children[i]->traverse();
            cout << "  " << tV << " "
                 << BOLD << CYAN   << " " << keys[i].userId << RESET
                 << "  " << BOLD << WHITE << keys[i].name   << RESET
                 << DIM  << "  "   << keys[i].phone         << RESET
                 << "  " << GREEN  << keys[i].frequentRoute << RESET << "\n";
        }
        if (!isLeaf) children[i]->traverse();
    }

    BTreeNode* search(int id) {
        int i = 0;
        while (i < n && id > keys[i].userId) i++;
        if (i < n && keys[i].userId == id) return this;
        if (isLeaf) return nullptr;
        return children[i]->search(id);
    }

    void splitChild(int i, BTreeNode* y) {
        BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
        z->n = t - 1;
        for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];
        if (!y->isLeaf)
            for (int j = 0; j < t; j++) z->children[j] = y->children[j + t];
        y->n = t - 1;
        for (int j = n; j >= i + 1; j--) children[j + 1] = children[j];
        children[i + 1] = z;
        for (int j = n - 1; j >= i; j--) keys[j + 1] = keys[j];
        keys[i] = y->keys[t - 1];
        n++;
    }

    void insertNonFull(User user) {
        int i = n - 1;
        if (isLeaf) {
            while (i >= 0 && keys[i].userId > user.userId) {
                keys[i + 1] = keys[i]; i--;
            }
            keys[i + 1] = user; n++;
        } else {
            while (i >= 0 && keys[i].userId > user.userId) i--;
            i++;
            if (children[i]->n == 2 * t - 1) {
                splitChild(i, children[i]);
                if (keys[i].userId < user.userId) i++;
            }
            children[i]->insertNonFull(user);
        }
    }
};

// ── UserDirectory class ───────────────────────────────────────────
class UserDirectory {
private:
    BTreeNode* root;
    int        t;

public:
    UserDirectory(int degree = 3) { t = degree; root = nullptr; }

    void insertUser(User user) {
        if (!root) {
            root = new BTreeNode(t, true);
            root->keys[0] = user; root->n = 1;
        } else {
            if (root->n == 2 * t - 1) {
                BTreeNode* s = new BTreeNode(t, false);
                s->children[0] = root;
                s->splitChild(0, root);
                int i = (s->keys[0].userId < user.userId) ? 1 : 0;
                s->children[i]->insertNonFull(user);
                root = s;
            } else {
                root->insertNonFull(user);
            }
        }
    }

    User* searchUser(int id) {
        if (!root) return nullptr;
        BTreeNode* node = root->search(id);
        if (!node) return nullptr;
        for (int i = 0; i < node->n; i++)
            if (node->keys[i].userId == id) return &node->keys[i];
        return nullptr;
    }

    void displayAllUsers() {
        if (!root) { printError("No users in directory."); return; }
        cout << "\n";
        printLine(CYAN);
        cout << "  " << BOLD << BG_CYAN << BLACK
             << "  USER DIRECTORY  " << RESET
             << BOLD << CYAN << "  B-Tree In-Order  (sorted by ID)" << RESET << "\n";
        printLine(CYAN);
        cout << "  " << tTL;
        for (int i = 0; i < 48; i++) cout << tH;
        cout << tTR << "\n";
        root->traverse();
        cout << "  " << tBL;
        for (int i = 0; i < 48; i++) cout << tH;
        cout << tBR << "\n\n";
    }

    void loadSampleData() {
        insertUser(User(1001,"Arjun Sharma", "9821001001","Andheri -> BKC"));
        insertUser(User(1002,"Priya Mehta",  "9821001002","Thane -> CST"));
        insertUser(User(1003,"Ravi Kumar",   "9821001003","Borivali -> Dadar"));
        insertUser(User(1004,"Sneha Patil",  "9821001004","Vashi -> Kurla"));
        insertUser(User(1005,"Amit Joshi",   "9821001005","Powai -> Lower Parel"));
        insertUser(User(1006,"Neha Desai",   "9821001006","Mulund -> Fort"));
        insertUser(User(1007,"Rahul Nair",   "9821001007","Kalyan -> Bandra"));
        insertUser(User(1008,"Kavya Singh",  "9821001008","Panvel -> Belapur"));
        insertUser(User(1009,"Vikram Patel", "9821001009","Kandivali -> Churchgate"));
        insertUser(User(1010,"Pooja Rao",    "9821001010","Sion -> Worli"));
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n";
            printLine(CYAN);
            cout << "  " << BOLD << BG_CYAN << BLACK
                 << "  USER DIRECTORY  " << RESET
                 << BOLD << CYAN << "  B-Tree  degree t=3  O(log n)" << RESET << "\n";
            printLine(CYAN);
            cout << "  " << CYAN << "  1" << RESET << "  Add New User\n";
            cout << "  " << CYAN << "  2" << RESET << "  Search User by ID\n";
            cout << "  " << CYAN << "  3" << RESET << "  Display All Users\n";
            cout << "  " << CYAN << "  4" << RESET << "  Back\n";
            printThinLine(CYAN);
            cout << "  " << BOLD << CYAN << "  ➤  Choice: " << RESET;
            cin >> choice;

            if (choice == 1) {
                User u;
                cout << "\n";
                printThinLine(CYAN);
                cout << "  " << BOLD << CYAN << "  ADD NEW USER" << RESET << "\n";
                printThinLine(CYAN);
                cout << "  " << YELLOW << "  User ID        : " << RESET;
                cin >> u.userId; cin.ignore();
                cout << "  " << YELLOW << "  Name           : " << RESET;
                getline(cin, u.name);
                cout << "  " << YELLOW << "  Phone          : " << RESET;
                getline(cin, u.phone);
                cout << "  " << YELLOW << "  Frequent Route : " << RESET;
                getline(cin, u.frequentRoute);
                insertUser(u);
                printSuccess("User added to B-Tree.");
            }
            else if (choice == 2) {
                int id;
                cout << "\n  " << YELLOW << "  User ID to search: " << RESET;
                cin >> id;
                User* f = searchUser(id);
                if (f) {
                    cout << "\n";
                    printThinLine(GREEN);
                    cout << "  " << BOLD << GREEN << "  USER FOUND" << RESET << "\n";
                    printThinLine(GREEN);
                    printLabel("  ID    :", to_string(f->userId));
                    printLabel("  Name  :", f->name);
                    printLabel("  Phone :", f->phone);
                    printLabel("  Route :", f->frequentRoute);
                    printThinLine(GREEN);
                } else {
                    printError("User ID " + to_string(id) + " not found.");
                }
            }
            else if (choice == 3) { displayAllUsers(); }
            else if (choice != 4) { printError("Invalid choice."); }

        } while (choice != 4);
    }
};
