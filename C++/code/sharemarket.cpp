// sharemarket.cpp
// Object-oriented Stock Market Simulation (fixed for portability with MinGW/Dev-C++)
// Compile with: g++ -std=c++11 sharemarket.cpp -o sharemarket

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <limits>  // Added for numeric_limits

using namespace std;

// --------------------------- Utility functions ---------------------------
string now_str() {
    // Portable way to format current time as YYYY-MM-DD HH:MM:SS
    auto t = chrono::system_clock::now();
    time_t tt = chrono::system_clock::to_time_t(t);
    tm* lt = localtime(&tt); // note: localtime is fine for single-threaded console apps
    char buf[64];
    if (lt) {
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt);
        return string(buf);
    } else {
        return string("unknown-time");
    }
}

double clamp_double(double v, double lo, double hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

// Generate random double in [a,b]
double rand_double(double a, double b) {
    static std::mt19937_64 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}

// --------------------------- Base: Investment ---------------------------
class Investment {
protected:
    string name;
    string symbol;
public:
    Investment() {}
    Investment(const string& n, const string& s) : name(n), symbol(s) {}
    virtual ~Investment() {}
    string getName() const { return name; }
    string getSymbol() const { return symbol; }

    virtual void displayDetails() const = 0;
    virtual double currentPrice() const = 0;
    virtual string typeName() const = 0;
};

// --------------------------- Stock ---------------------------
class Stock : public Investment {
private:
    double price;    // current market price per share
    int available;   // number of shares available in market
public:
    Stock() : price(0.0), available(0) {}
    Stock(const string& n, const string& s, double p, int avail)
        : Investment(n, s), price(p), available(avail) {}

    void displayDetails() const override {
        cout << left << setw(6) << symbol << " | "
             << setw(20) << name << " | "
             << "Price: " << setw(9) << fixed << setprecision(2) << price
             << " | Available: " << available;
    }

    double currentPrice() const override { return price; }
    string typeName() const override { return "Stock"; }

    void setPrice(double p) { price = p; }
    void changeAvailable(int delta) { available += delta; if (available < 0) available = 0; }
    int getAvailable() const { return available; }
};

// --------------------------- MutualFund ---------------------------
class MutualFund : public Investment {
private:
    double nav;    // net asset value per unit
    double totalUnits; // units available in "market"
public:
    MutualFund() : nav(0.0), totalUnits(0.0) {}
    MutualFund(const string& n, const string& s, double nav_, double units)
        : Investment(n, s), nav(nav_), totalUnits(units) {}

    void displayDetails() const override {
        cout << left << setw(6) << symbol << " | "
             << setw(20) << name << " | "
             << "NAV: " << setw(9) << fixed << setprecision(2) << nav
             << " | UnitsAvail: " << setw(8) << fixed << setprecision(2) << totalUnits;
    }

    double currentPrice() const override { return nav; }
    string typeName() const override { return "MutualFund"; }

    void setNAV(double n) { nav = n; }
    void changeUnits(double d) { totalUnits += d; if (totalUnits < 0) totalUnits = 0; }
    double getUnits() const { return totalUnits; }
};

// --------------------------- Holding ---------------------------
// Represents investor's holding (for a stock or mutual fund)
struct Holding {
    string symbol;
    string name;
    string type; // "Stock" or "MutualFund"
    double quantity; // for stocks use int-like quantity, but stored as double to unify mutual funds
    double avgPrice; // average buy price per unit
    Holding() : quantity(0.0), avgPrice(0.0) {}
    Holding(const string& sym, const string& nm, const string& tp, double qty, double avg)
        : symbol(sym), name(nm), type(tp), quantity(qty), avgPrice(avg) {}
};

// --------------------------- TransactionLog ---------------------------
class TransactionLog {
private:
    struct Entry {
        string time;
        string action; // BUY / SELL / DEPOSIT / WITHDRAW
        string symbol;
        string name;
        string type;
        double qty;
        double price;
        double balanceAfter;
    };
    vector<Entry> entries;
public:
    void add(const string& action, const string& symbol, const string& name,
             const string& type, double qty, double price, double balanceAfter) {
        Entry e;
        e.time = now_str();
        e.action = action;
        e.symbol = symbol;
        e.name = name;
        e.type = type;
        e.qty = qty;
        e.price = price;
        e.balanceAfter = balanceAfter;
        entries.push_back(e);
    }
    void showAll() const {
        if (entries.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        cout << left << setw(20) << "Time" << setw(8) << "Act" << setw(8) << "Type"
             << setw(8) << "Symbol" << setw(20) << "Name" << setw(10) << "Qty"
             << setw(12) << "Price" << setw(12) << "BalAfter" << "\n";
        cout << string(100, '-') << "\n";
        for (const auto& e : entries) {
            cout << setw(20) << e.time << setw(8) << e.action << setw(8) << e.type
                 << setw(8) << e.symbol << setw(20) << e.name
                 << setw(10) << fixed << setprecision(2) << e.qty
                 << setw(12) << fixed << setprecision(2) << e.price
                 << setw(12) << fixed << setprecision(2) << e.balanceAfter << "\n";
        }
    }
    // Save transaction log to file
    bool saveToFile(const string& fname) const {
        ofstream ofs(fname);
        if (!ofs) return false;
        for (const auto& e : entries) {
            ofs << e.time << '|' << e.action << '|' << e.type << '|' << e.symbol << '|'
                << e.name << '|' << e.qty << '|' << e.price << '|' << e.balanceAfter << '\n';
        }
        ofs.close();
        return true;
    }
    // Load from file (appends)
    bool loadFromFile(const string& fname) {
        ifstream ifs(fname);
        if (!ifs) return false;
        string line;
        while (getline(ifs, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            Entry e;
            getline(ss, e.time, '|');
            getline(ss, e.action, '|');
            getline(ss, e.type, '|');
            getline(ss, e.symbol, '|');
            getline(ss, e.name, '|');
            string tmp;
            getline(ss, tmp, '|'); 
            try {
                e.qty = tmp.empty() ? 0.0 : stod(tmp);
            } catch (const exception& e) {
                cout << "Error parsing quantity in transaction log.\n";
                return false;
            }
            getline(ss, tmp, '|'); 
            try {
                e.price = tmp.empty() ? 0.0 : stod(tmp);
            } catch (const exception& e) {
                cout << "Error parsing price in transaction log.\n";
                return false;
            }
            getline(ss, tmp, '\n'); 
            try {
                e.balanceAfter = tmp.empty() ? 0.0 : stod(tmp);
            } catch (const exception& e) {
                cout << "Error parsing balance in transaction log.\n";
                return false;
            }
            entries.push_back(e);
        }
        ifs.close();
        return true;
    }
};

// --------------------------- Market ---------------------------
class Market {
private:
    map<string, Stock> stocks;           // keyed by symbol
    map<string, MutualFund> funds;       // keyed by symbol
    double volatility; // a small factor to control price randomness
public:
    Market() : volatility(0.02) {} // default volatility 2%

    // Add sample data
    void addStock(const Stock& s) { stocks[s.getSymbol()] = s; }
    void addFund(const MutualFund& f) { funds[f.getSymbol()] = f; }

    // find pointers to investments (non-const)
    Investment* findInvestment(const string& symbol) {
        auto itS = stocks.find(symbol);
        if (itS != stocks.end()) return &itS->second;
        auto itF = funds.find(symbol);
        if (itF != funds.end()) return &itF->second;
        return nullptr;
    }
    Stock* findStock(const string& symbol) {
        auto it = stocks.find(symbol);
        if (it != stocks.end()) return &it->second;
        return nullptr;
    }
    MutualFund* findFund(const string& symbol) {
        auto it = funds.find(symbol);
        if (it != funds.end()) return &it->second;
        return nullptr;
    }

    // const overloads so const Market can be queried
    const Investment* findInvestment(const string& symbol) const {
        auto itS = stocks.find(symbol);
        if (itS != stocks.end()) return &itS->second;
        auto itF = funds.find(symbol);
        if (itF != funds.end()) return &itF->second;
        return nullptr;
    }
    const Stock* findStock(const string& symbol) const {
        auto it = stocks.find(symbol);
        if (it != stocks.end()) return &it->second;
        return nullptr;
    }
    const MutualFund* findFund(const string& symbol) const {
        auto it = funds.find(symbol);
        if (it != funds.end()) return &it->second;
        return nullptr;
    }

    void showMarket() const {
        cout << "\n---- AVAILABLE STOCKS ----\n";
        cout << left << setw(6) << "Sym" << " | " << setw(20) << "Name" << " | " << "Price | Available\n";
        cout << string(60, '-') << "\n";
        for (const auto& p : stocks) {
            p.second.displayDetails();
            cout << "\n";
        }
        cout << "\n---- AVAILABLE MUTUAL FUNDS ----\n";
        for (const auto& p : funds) {
            p.second.displayDetails();
            cout << "\n";
        }
    }

    // Simulate market movement using a random walk (affects stock price and NAV)
    void simulatePriceMovement() {
        for (auto& p : stocks) {
            Stock& s = p.second;
            double oldp = s.currentPrice();
            double pct = rand_double(-volatility, volatility);
            double newp = oldp * (1.0 + pct);
            newp = clamp_double(newp, 0.01, oldp * 10.0 + 10.0);
            s.setPrice(newp);
        }
        for (auto& p : funds) {
            MutualFund& f = p.second;
            double oldp = f.currentPrice();
            double pct = rand_double(-volatility*0.8, volatility*0.8);
            double newp = oldp * (1.0 + pct);
            newp = clamp_double(newp, 0.01, oldp * 5.0 + 10.0);
            f.setNAV(newp);
        }
        // occasionally vary volatility a bit
        volatility = clamp_double(volatility + rand_double(-0.002, 0.002), 0.003, 0.08);
    }

    // Save market snapshot to file
    bool saveSnapshot(const string& fname) const {
        ofstream ofs(fname);
        if (!ofs) {
            cout << "Error: Could not open file " << fname << " for writing.\n";
            return false;
        }
        // Stocks
        for (const auto& p : stocks) {
            const Stock& s = p.second;
            ofs << "STOCK|" << s.getSymbol() << '|' << s.getName() << '|' << s.currentPrice() << '|' << s.getAvailable() << '\n';
        }
        // Funds
        for (const auto& p : funds) {
            const MutualFund& f = p.second;
            ofs << "FUND|" << f.getSymbol() << '|' << f.getName() << '|' << f.currentPrice() << '|' << f.getUnits() << '\n';
        }
        ofs.close();
        return true;
    }

    // Load market snapshot (clears existing)
    bool loadSnapshot(const string& fname) {
        ifstream ifs(fname);
        if (!ifs) {
            cout << "Error: Could not open file " << fname << " for reading.\n";
            return false;
        }
        stocks.clear();
        funds.clear();
        string line;
        while (getline(ifs, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string type; getline(ss, type, '|');
            if (type == "STOCK") {
                string sym, nm, tmp;
                double price; int avail;
                getline(ss, sym, '|'); getline(ss, nm, '|'); getline(ss, tmp, '|'); 
                try {
                    price = stod(tmp);
                } catch (const exception& e) {
                    cout << "Error parsing price in market snapshot.\n";
                    return false;
                }
                getline(ss, tmp, '\n'); 
                try {
                    avail = stoi(tmp);
                } catch (const exception& e) {
                    cout << "Error parsing available in market snapshot.\n";
                    return false;
                }
                addStock(Stock(nm, sym, price, avail));
            } else if (type == "FUND") {
                string sym, nm, tmp;
                double nav, units;
                getline(ss, sym, '|'); getline(ss, nm, '|'); getline(ss, tmp, '|'); 
                try {
                    nav = stod(tmp);
                } catch (const exception& e) {
                    cout << "Error parsing NAV in market snapshot.\n";
                    return false;
                }
                getline(ss, tmp, '\n'); 
                try {
                    units = stod(tmp);
                } catch (const exception& e) {
                    cout << "Error parsing units in market snapshot.\n";
                    return false;
                }
                addFund(MutualFund(nm, sym, nav, units));
            }
        }
        ifs.close();
        return true;
    }
};

// --------------------------- Investor ---------------------------
class Investor {
private:
    string name;
    double cashBalance;
    map<string, Holding> portfolio; // keyed by symbol
    TransactionLog tlog;
public:
    Investor() : name("Unnamed"), cashBalance(0.0) {}
    Investor(const string& n, double balance) : name(n), cashBalance(balance) {}

    string getName() const { return name; }
    double getBalance() const { return cashBalance; }

    void deposit(double amt) {
        if (amt <= 0) {
            cout << "Deposit amount must be positive.\n";
            return;
        }
        cashBalance += amt;
        tlog.add("DEPOSIT", "-", "-", "-", 0.0, 0.0, cashBalance);
        cout << "Deposited " << fixed << setprecision(2) << amt << ". New balance: " << cashBalance << "\n";
    }
    bool withdraw(double amt) {
        if (amt <= 0) {
            cout << "Withdraw amount must be positive.\n";
            return false;
        }
        if (amt > cashBalance) {
            cout << "Insufficient balance.\n";
            return false;
        }
        cashBalance -= amt;
        tlog.add("WITHDRAW", "-", "-", "-", 0.0, 0.0, cashBalance);
        cout << "Withdrew " << fixed << setprecision(2) << amt << ". New balance: " << cashBalance << "\n";
        return true;
    }

    // Buy N units of an investment
    bool buy(Market& market, const string& symbol, double qty) {
        Investment* inv = market.findInvestment(symbol);
        if (!inv) {
            cout << "Investment symbol not found in market.\n";
            return false;
        }
        if (qty <= 0) {
            cout << "Quantity must be positive.\n";
            return false;
        }
        double price = inv->currentPrice();
        double cost = price * qty;

        // For stocks, check integer qty and market availability
        if (inv->typeName() == "Stock") {
            Stock* s = market.findStock(symbol);
            if (!s) { cout << "Stock not found.\n"; return false; }
            int iqty = static_cast<int>(qty);
            if (iqty != qty) {
                cout << "Stocks must be bought in whole shares only.\n";
                return false;
            }
            if (iqty > s->getAvailable()) {
                cout << "Not enough shares available in market.\n";
                return false;
            }
            if (cost > cashBalance) {
                cout << "Insufficient cash balance.\n";
                return false;
            }
            // proceed
            cashBalance -= cost;
            s->changeAvailable(-iqty);
            addOrUpdateHolding(symbol, s->getName(), s->typeName(), qty, price);
            tlog.add("BUY", symbol, s->getName(), s->typeName(), qty, price, cashBalance);
            cout << "Bought " << qty << " shares of " << symbol << " for " << cost << ".\n";
            return true;
        }
        // For mutual funds - can buy fractional units
        if (inv->typeName() == "MutualFund") {
            MutualFund* f = market.findFund(symbol);
            if (!f) { cout << "Fund not found.\n"; return false; }
            if (qty > f->getUnits()) {
                cout << "Not enough units available in fund.\n";
                return false;
            }
            if (cost > cashBalance) {
                cout << "Insufficient cash balance.\n";
                return false;
            }
            // proceed
            cashBalance -= cost;
            f->changeUnits(-qty);
            addOrUpdateHolding(symbol, f->getName(), f->typeName(), qty, price);
            tlog.add("BUY", symbol, f->getName(), f->typeName(), qty, price, cashBalance);
            cout << "Bought " << fixed << setprecision(2) << qty << " units of " << symbol << " for " << cost << ".\n";
            return true;
        }
        cout << "Unsupported investment type.\n";
        return false;
    }

    // Sell N units
    bool sell(Market& market, const string& symbol, double qty) {
        auto it = portfolio.find(symbol);
        if (it == portfolio.end()) {
            cout << "You do not hold this symbol.\n";
            return false;
        }
        Holding& h = it->second;
        if (qty <= 0) {
            cout << "Quantity must be positive.\n";
            return false;
        }
        if (qty > h.quantity + 1e-9) {
            cout << "You don't have enough quantity to sell.\n";
            return false;
        }
        Investment* inv = market.findInvestment(symbol);
        if (!inv) {
            cout << "Market no longer lists this investment; cannot sell here.\n";
            return false;
        }
        double price = inv->currentPrice();
        double proceed = price * qty;
        // For stock, qty must be integer
        if (h.type == "Stock") {
            int iqty = static_cast<int>(qty);
            if (iqty != qty) {
                cout << "You must sell whole shares for stocks.\n";
                return false;
            }
            // update market availability
            Stock* s = market.findStock(symbol);
            if (s) s->changeAvailable(iqty);
        } else if (h.type == "MutualFund") {
            MutualFund* f = market.findFund(symbol);
            if (f) f->changeUnits(qty);
        }
        // update holding
        h.quantity -= qty;
        if (h.quantity <= 1e-9) portfolio.erase(it);
        cashBalance += proceed;
        tlog.add("SELL", symbol, h.name, h.type, qty, price, cashBalance);
        cout << "Sold " << fixed << setprecision(2) << qty << " of " << symbol << " for " << proceed << ".\n";
        return true;
    }

    void addOrUpdateHolding(const string& sym, const string& nm, const string& type, double qty, double price) {
        auto it = portfolio.find(sym);
        if (it == portfolio.end()) {
            portfolio[sym] = Holding(sym, nm, type, qty, price);
        } else {
            Holding& h = it->second;
            // update average price: newAvg = (oldQty*oldAvg + qty*price) / (oldQty+qty)
            double newQty = h.quantity + qty;
            if (newQty > 0.0) {
                double newAvg = (h.quantity * h.avgPrice + qty * price) / newQty;
                h.avgPrice = newAvg;
            }
            h.quantity = newQty;
        }
    }

    void displayPortfolio(const Market& market) const {
        cout << "\n---- " << name << " PORTFOLIO ----\n";
        cout << "Cash Balance: " << fixed << setprecision(2) << cashBalance << "\n";
        if (portfolio.empty()) {
            cout << "No holdings.\n";
            return;
        }
        cout << left << setw(8) << "Sym" << setw(20) << "Name" << setw(8) << "Type"
             << setw(10) << "Qty" << setw(12) << "AvgPrice" << setw(12) << "MktPrice"
             << setw(12) << "MktValue" << setw(12) << "P/L\n";
        cout << string(90, '-') << "\n";
        double totalValue = cashBalance;
        for (const auto& p : portfolio) {
            const Holding& h = p.second;
            double mprice = 0.0;
            const Investment* inv = market.findInvestment(h.symbol);
            if (inv) mprice = inv->currentPrice();
            double mvalue = h.quantity * mprice;
            double pl = (mprice - h.avgPrice) * h.quantity;
            totalValue += mvalue;
            cout << setw(8) << h.symbol << setw(20) << h.name << setw(8) << h.type
                 << setw(10) << fixed << setprecision(2) << h.quantity << setw(12) << h.avgPrice
                 << setw(12) << mprice << setw(12) << mvalue << setw(12) << pl << "\n";
        }
        cout << string(90, '-') << "\n";
        cout << "Total Net Worth (cash + investments): " << fixed << setprecision(2) << totalValue << "\n";
    }

    void showTransactions() const {
        cout << "\n--- Transaction History ---\n";
        tlog.showAll();
    }

    // Save investor data (portfolio + cash)
    bool saveToFile(const string& fname) const {
        ofstream ofs(fname);
        if (!ofs) {
            cout << "Error: Could not open file " << fname << " for writing.\n";
            return false;
        }
        ofs << name << '\n';
        ofs << fixed << setprecision(2) << cashBalance << '\n';
        // portfolio entries
        for (const auto& p : portfolio) {
            const Holding& h = p.second;
            ofs << h.symbol << '|' << h.name << '|' << h.type << '|' << h.quantity << '|' << h.avgPrice << '\n';
        }
        ofs.close();
        // save transaction log separately
        tlog.saveToFile(fname + ".txlog");
        return true;
    }

    bool loadFromFile(const string& fname) {
        ifstream ifs(fname);
        if (!ifs) {
            cout << "Error: Could not open file " << fname << " for reading.\n";
            return false;
        }
        portfolio.clear();
        string line;
        getline(ifs, name);
        if (name.empty()) return false;
        string tmp;
        getline(ifs, tmp);
        try {
            cashBalance = tmp.empty() ? 0.0 : stod(tmp);
        } catch (const exception& e) {
            cout << "Error parsing cash balance.\n";
            return false;
        }
        while (getline(ifs, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string sym, nm, tp, qstr, avgstr;
            getline(ss, sym, '|');
            getline(ss, nm, '|');
            getline(ss, tp, '|');
            getline(ss, qstr, '|');
            getline(ss, avgstr, '\n');
            try {
                Holding h(sym, nm, tp, stod(qstr), stod(avgstr));
                portfolio[sym] = h;
            } catch (const exception& e) {
                cout << "Error parsing holding data.\n";
                return false;
            }
        }
        // load transactions if present
        tlog.loadFromFile(fname + ".txlog");
        ifs.close();
        return true;
    }
};

// --------------------------- UI & main ---------------------------
void showMainMenu() {
    cout << "\n===== STOCK MARKET SIMULATION (OOP Demo) =====\n";
    cout << "1. Show Market\n";
    cout << "2. Show My Portfolio\n";
    cout << "3. Buy\n";
    cout << "4. Sell\n";
    cout << "5. Deposit Cash\n";
    cout << "6. Withdraw Cash\n";
    cout << "7. Show Transactions\n";
    cout << "8. Simulate Market Movement\n";
    cout << "9. Save Snapshot (Market & Investor)\n";
    cout << "10. Load Snapshot (Market & Investor)\n";
    cout << "11. Quick Demo Setup (populate sample market)\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

void setupSampleMarket(Market& market) {
    // Add a bunch of stocks and funds
    market.addStock(Stock("Tata Motors Ltd", "TATAM", 490.50, 10000));
    market.addStock(Stock("Infosys Ltd", "INFY", 1830.75, 8000));
    market.addStock(Stock("Reliance Industries", "RELI", 2979.30, 9000));
    market.addStock(Stock("HDFC Bank", "HDFCB", 1435.40, 7000));
    market.addStock(Stock("ICICI Bank", "ICIC", 840.25, 6000));
    market.addStock(Stock("Wipro Ltd", "WIPR", 420.10, 6500));
    market.addFund(MutualFund("SBI Equity Fund", "SBI-EQ", 48.30, 50000.0));
    market.addFund(MutualFund("Nippon India Largecap", "NIP-LC", 34.75, 40000.0));
    market.addFund(MutualFund("HDFC Hybrid", "HDFC-HY", 20.50, 30000.0));
    cout << "Sample market populated.\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(&cout);


    Market market;
    Investor investor("Chaitanya", 10000.00); // default investor; user can load their own file
    cout << "Program started successfully.\n";
    cout << "Welcome to the OOP Stock Market Simulation!\n";
    cout << "Default user created: " << investor.getName() << " with balance " << investor.getBalance() << "\n";

    // Optionally pre-populate market
    setupSampleMarket(market);

    bool running = true;
    while (running) {
        showMainMenu();
        int choice;
        while (!(cin >> choice)) {
            cout << "Invalid input. Enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline
        try {
            switch (choice) {
                case 1: {
                    market.showMarket();
                    break;
                }
                case 2: {
                    investor.displayPortfolio(market);
                    break;
                }
                case 3: {
                    cout << "Enter symbol to buy: ";
                    string sym;
                    getline(cin, sym);
                    cout << "Enter quantity (for mutual funds you may enter fractional): ";
                    double qty;
                    while (!(cin >> qty)) {
                        cout << "Invalid quantity. Enter a number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    bool ok = investor.buy(market, sym, qty);
                    if (ok) cout << "Purchase complete.\n";
                    break;
                }
                case 4: {
                    cout << "Enter symbol to sell: ";
                    string sym;
                    getline(cin, sym);
                    cout << "Enter quantity to sell: ";
                    double qty;
                    while (!(cin >> qty)) {
                        cout << "Invalid quantity. Enter a number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    bool ok = investor.sell(market, sym, qty);
                    if (ok) cout << "Sell complete.\n";
                    break;
                }
                case 5: {
                    cout << "Enter amount to deposit: ";
                    double amt;
                    while (!(cin >> amt)) {
                        cout << "Invalid amount. Enter a number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    investor.deposit(amt);
                    break;
                }
                case 6: {
                    cout << "Enter amount to withdraw: ";
                    double amt;
                    while (!(cin >> amt)) {
                        cout << "Invalid amount. Enter a number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    investor.withdraw(amt);
                    break;
                }
                case 7: {
                    investor.showTransactions();
                    break;
                }
                case 8: {
                    cout << "Simulating market movement... (This will update prices randomly)\n";
                    market.simulatePriceMovement();
                    cout << "Simulation done.\n";
                    break;
                }
                case 9: {
                    cout << "Enter filename prefix to save snapshot (e.g. snapshot1): ";
                    string pref;
                    getline(cin, pref);
                    if (market.saveSnapshot(pref + "_market.txt") && investor.saveToFile(pref + "_investor.txt")) {
                        cout << "Saved market and investor snapshot.\n";
                    } else {
                        cout << "Error saving files.\n";
                    }
                    break;
                }
                case 10: {
                    cout << "Enter filename prefix to load snapshot (e.g. snapshot1): ";
                    string pref;
                    getline(cin, pref);
                    if (market.loadSnapshot(pref + "_market.txt") && investor.loadFromFile(pref + "_investor.txt")) {
                        cout << "Loaded snapshots for market and investor.\n";
                    } else {
                        cout << "Error loading snapshots. Make sure files exist.\n";
                    }
                    break;
                }
                case 11: {
                    cout << "This will populate sample market and reset investor data. Continue? (y/n): ";
                    char ch;
                    cin >> ch;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (ch == 'y' || ch == 'Y') {
                        market = Market();
                        setupSampleMarket(market);
                        investor = Investor("Chaitanya", 10000.0);
                        cout << "Demo setup complete.\n";
                    } else {
                        cout << "Aborted.\n";
                    }
                    break;
                }
                case 0: {
                    cout << "Exiting... Goodbye!\n";
                    running = false;
                    break;
                }
                default:
                    cout << "Unknown choice.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}