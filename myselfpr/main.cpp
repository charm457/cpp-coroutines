#include <iostream>
#include <string>

using namespace std;

class Player {
private:
    string name;
    int high;
    int damageOfDragon = 20;

protected:
    int health; 

public:
    // Конструктор по умолчанию (теперь он полезен)
    Player() : name("Unknown"), high(0), health(70) {
        cout << "PLAYER CREATED: " << name << endl;
    } 

    Player(string name_hero, int high_hero, int health_hero) 
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

class Armor : public Player {
public:
    // 1. Вызываем полный конструктор родителя
    Armor(string name, int high, int hp) : Player(name, high, hp) {
        checkArmor();
    }

    // 2. Вызываем родителя с частью данных (рост поставим 0)
    Armor(string name, int hp) : Player(name, 0, hp) {
        checkArmor();
    }

    // 3. Конструктор по умолчанию
    Armor() : Player() {
        checkArmor();
    }

private:
    void checkArmor() {
        if (health <= 100) cout << "Status: light cloth" << endl;
        else cout << "Status: heavy armor" << endl;
    }
};

int main() {
    Armor warr1("Aragorn", 200, 100);
    Armor warr2("Gilfy", 200, 150);
    Armor warr4; 

    cout << "--- BATTLE ---" << endl;
    warr1.damage();
    warr2.damage();
    warr4.damage();

    return 0;
}