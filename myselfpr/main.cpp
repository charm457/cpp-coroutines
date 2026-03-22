#include <iostream>

using namespace std;

class player{
    private:
        string name;
        int high;
        int health;
        int damageOfDragon = 20;
    
    public:
        //Конструктор по умолчанию
        player(string name_hero, int high_hero, int health_hero) : name(name_hero), high(high_hero), health(health_hero){
            cout << endl;
            cout <<"NAME: " << name << " HIGH: " << high;
        }
        //object
        void damage(){
            cout << endl;
            health -= damageOfDragon;
            cout <<"NAME: " << name << " health: " << health;
        }

        //Деструктор
        ~player (){
            cout << endl << "DELETE MEMORIES";
        }

    protected:
        //todo

};


int main(){
    player warrior1("Aragorn", 200, 100);
    player warrior2("Gilfy", 200, 150);

    warrior1.damage();
    warrior2.damage();


}