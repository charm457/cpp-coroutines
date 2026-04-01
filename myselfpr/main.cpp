#include <iostream>
#include <string>

using namespace std;

// 1. Родительский класс-шаблон
template<typename T>
class Player {
private:
    string name;
    int high;
    int damageOfDragon = 20;

protected:
    T health; 

public:
    Player() : name("Unknown"), high(0), health(70) {
        cout << "PLAYER CREATED: " << name << endl;
    } 

    Player(string name_hero, int high_hero, T health_hero) 
        : name(name_hero), high(high_hero), health(health_hero) {
        cout << "PLAYER CREATED: " << name << endl;
    }

    void damage() {
        health -= damageOfDragon;
        cout << name << " health: " << health << endl;
    }

    virtual ~Player() { 
        cout << "DELETE " << name << endl;
    }
};


template<typename T>
class Armor : public Player<T> {
public: 
    using Player<T>::health; 

    Armor(string name, int high, T hp) : Player<T>(name, high, hp) {
        checkArmor();
    }

    Armor(string name, T hp) : Player<T>(name, 0, hp) {
        checkArmor();
    }

    Armor() : Player<T>() {
        checkArmor();
    }

private:
    void checkArmor() {
        
        if (health <= 100) cout << "Status: light cloth" << endl;
        else cout << "Status: heavy armor" << endl;
    }
};

int main() {
    Armor<int> warr1("Aragorn", 200, 100);
    Armor<double> warr2("Gilfy", 200, 150.5); 
    Armor<int> warr4; 

    cout << "--- BATTLE ---" << endl;
    warr1.damage();
    warr2.damage();
    warr4.damage();

    return 0;
}