#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <limits>
#include <cstdlib>
#include <fstream>
#include <string> 
#include <cmath>
#include <ctime>
#include<vector>
#include <algorithm>
#include "ASSETS.h"

/* I started using this when it was a very small project,
then i got ambitous and here we are.*/ 
using namespace std; 
/*
This project is a small dungeon RPG ,4  floors total.
Player objective, for now, is to get gear, grow stronger
and defeat the final boss to escape the dungeon.
*/

                            // Timed Clear
void cls(int time) {
	cout<<endl;
	sleep(time);
    #ifdef _WIN32
	system("cls");
    #else
	system("clear");
    #endif
}
                            // Pause with enter
void PauseEnter() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "";
	cin.get();
}

class Character{
public:
    Character(const string& nome): 
        nome(nome), Lv(0), HP(0), MaxHP(0),ATK(0), DEF(0), XP(0) {}

    const string& getNome() const{return nome;}
    void setNome(const string& alt) {nome = alt;}

    int getLv() const {return Lv;}
    void setLv(int fixo) {Lv = fixo;}
    void addLv(int add) {Lv += add;} 
    void clearLv() {Lv = 1;}

    int getHP() const {return HP;}
    void setHP(int fixo) {HP = fixo;}
    void addHP(int add) {HP += add;} 
    void clearHP() {HP = 0;}

    int getMaxHP() const { return MaxHP; }
    void setMaxHP(int fixo) { MaxHP = fixo; }
    void addMaxHP(int add) { MaxHP += add; }  

    int getATK() const {return ATK;}
    void setATK(int fixo) {ATK = fixo;}
    void addATK(int add) {ATK += add;}
    void clearATK() {ATK = 0;}

    int getDEF() const {return DEF;}
    void setDEF(int fixo) {DEF = fixo;}
    void addDEF(int add) {DEF += add;}
    void clearDEF() {DEF = 0;}

    int getXP() const {return XP;}
    void setXP(int fixo) {XP = fixo;}
    void addXP(int add) {XP += add;}
    void clearXP() {XP = 0;}

    void saveGame() const {
        string nomeFile = nome + ".sav";
        ofstream out(nomeFile);
        out << nome << endl
            << Lv << endl
            << HP << endl
            << MaxHP << endl
            << ATK << endl
            << DEF << endl
            << XP << endl;
    }

    bool loadGame() {
        string nomeFile = nome + ".sav";
        ifstream in(nomeFile);
        if(!in) return false;

        getline(in, nome);
        in >> Lv >> HP >> MaxHP >> ATK >> DEF >> XP;
        return true;
    }

private:
    string nome;
    int Lv,HP,MaxHP,ATK,DEF,XP;
};

class Mob {
public:
    Mob(const string& name, int lv, int hp, int atk, int def, int xp, const string& asciiArt)
        : name(name), Lv(lv), HP(hp), ATK(atk), DEF(def), XP(xp), ASCII(asciiArt) {}

    const string& getName() const { return name; }
    int getLv() const { return Lv; }
    int getHP() const { return HP; }
    void addHP(int add) { HP += add;}
    int getATK() const { return ATK; }
    int getDEF() const { return DEF; }
    int getXP() const {return XP; }

    void printASCII() const {
        cout << ASCII << endl;
    };

    void MobInfoBar() {
        cout << "\n" << setw(30) << name << endl;
        cout << "               +-----+-------+-----+-----+" << endl;
        cout << "               | LV  |   HP  | ATK | DEF |" << endl;
        cout << "               +-----+-------+-----+-----+" << endl;
        cout << "               | " 
                                    << setw(3) << Lv << " | "
                                    << setw(5) << HP << " | "
                                    << setw(4) << ATK << "| "
                                    << setw(4) << DEF << "|" << endl;
        cout << "               +-----+-------+-----+-----+" << endl;
    }


private:
    string name;
    int Lv, HP, ATK, DEF,XP;
    string ASCII;
};

class Item {
private:
    string name;
    int atk;
    int def;
    int hp; 

public:
    Item(string iname, int iatk = 0, int idef = 0, int iHp = 0)
        : name(iname), atk(iatk), def(idef), hp(iHp) {}

    string getItemName() const { return name; }
    int getItemATK() const { return atk; }
    int getItemDEF() const { return def; }
    int getItemHP() const { return hp; }

    bool operator==(const Item& other) const {
        return name == other.name;
    }
};

// 1st floor items
Item sword_basic("Wood Plank", 22, 0, 0); // original value is 8 ATK, current for testing / demo
Item shield_basic("Cauldron Lid", 0, 16, 150); //original value is 8 DEF, and 50 HP current for testing / demo
Item potion_lesser("Lesser Potion", 0, 0, 50);

// 2nd floor items
Item sword_advanced("Steel Sword", 13, 0);
Item shield_advanced("Bronze Shield", 0, 10 , 200);
Item potion_medium("Medium Health Potion", 0, 0, 150);

// 3rd floor items
Item sword_final("Moonsword", 19, 0, 0); 
Item shield_final("Mithril Shield", 0, 19, 500);
Item potion_greater("Greater Health Potion", 0, 0, 350);

vector<Item> first_floor_loot = {sword_basic, shield_basic, potion_lesser};
vector<Item> second_floor_loot = {sword_advanced, shield_advanced, potion_medium};
vector<Item> third_floor_loot = {sword_final, shield_final, potion_greater};

Mob rival("default",0,0,0,0,0,""); // temporary placeholder mob to init the game, does nothing

// Floor 1 enemies prison/catacombs
Mob zombie("Zombie", 1, 110, 11, 8, 75, zombieART); // nome lv hp atk def xp, arte
Mob skeleton("Skeleton", 4, 150, 20, 15, 105, skeletonART);
Mob ghost("Ghost", 6, 120, 13, 35, 125, ghostART);
Mob homunculus("Mindless Homunculus", 8, 320 , 20, 45, 145,humonculousART);

// Floor 2 enemies lower floor, ground level:
Mob crypt_stalker("Crypt Stalker", 15, 275, 25, 30, 165,""); // nome lv hp atk def xp arte
Mob risen_squire ("Risen Squire", 25, 350 , 25, 25, 215,"");
Mob wraith("Wraith", 35, 200, 35, 25, 265,"");
Mob carrion_knight("Carrion Knight", 40, 400, 35, 40, 325,"");

// Floor 3 enemies coutryard / top floor:
Mob dread_acolyte("Dread Acolyte", 50, 300, 20, 20, 435,""); // nome lv hp atk def xp arte
Mob death_knight ("Death knight", 65, 400, 30, 50, 515,"");
Mob revenant("Revenant", 70, 550, 35, 45, 615,"");
Mob fallen_hero("Fallen hero", 80, 650, 45, 45, 665,"");

// Bosses
Mob gargoyle("Gargoyle",10, 500, 30, 50, 600, gargoyleART);               // boss 1st floor
Mob bone_warden("Bone Warden",50, 600, 50, 60, 1000,"");                  // boss 2nd floor
Mob pontifex_crassus("Pontifex Crassus", 90, 1500, 80, 80, 2500,"");      // boss 3rd floor
Mob Lich("Velkharis, Malka HaNefesh HaNokhrei", 99, 4000, 99 , 99, 0,""); // floor 4;  only has this final boss fight,
                                                                          // needs special mechanics to beat, TODO: everything....

vector<Mob> mobs_first_floor = {zombie,skeleton,ghost,homunculus};
vector<Mob> mobs_second_floor = {crypt_stalker,risen_squire,wraith,carrion_knight};
vector<Mob> mobs_third_floor = {dread_acolyte, death_knight, fallen_hero, revenant, pontifex_crassus};

struct Floor{
    
    int floor_numb;
    vector<Mob> mobs;
    vector<Item> loot;
    //floor characteristics if any 
};

Floor first_floor {1, mobs_first_floor, first_floor_loot};
Floor second_floor{2, mobs_second_floor, second_floor_loot};
Floor third_floor {3, mobs_third_floor, third_floor_loot};

vector<Item> Inventory = {potion_lesser};

            //      \\        HELPERS GO HERE      \\        //
void saveGearFloor(Character & player, const vector<Item>& Inventory, int current_floor) {
    ofstream out( player.getNome()+ "inventoryFloor.sav");
    out << Inventory.size() << endl;
    for (const auto& item : Inventory) {
        out << item.getItemName() << endl;
        out << item.getItemATK() << " "
            << item.getItemDEF() << " "
            << item.getItemHP() << endl;
    }
    out << current_floor << endl;
}

bool loadGearFloor(Character &player, vector<Item>& Inventory, int& current_floor) {
    ifstream in(player.getNome()+ "inventoryFloor.sav");
    if (!in) return false;

    size_t invSize;
    in >> invSize;
    Inventory.clear();
    for (size_t i = 0; i < invSize; i++) {
        string name;
        int atk, def, hp;

        getline(in >> ws, name);
        in >> atk >> def >> hp;

        Inventory.push_back(Item(name, atk, def, hp));
    }
    in >> current_floor;
    return true;
}

void saveGameWorld(Character & player, const vector<Item>& Inventory, int current_floor){
    
    saveGearFloor( player, Inventory, current_floor);
    player.saveGame();
};

bool loadGameWorld(Character & player, vector<Item>& Inventory, int current_floor){
    
    loadGearFloor(player, Inventory, current_floor);
    player.loadGame();
    return true;
};

void useItem(Character &player, vector<Item> &Inventory, Item& consumable) 
{   
    auto pot = find(Inventory.begin(), Inventory.end(), consumable);


    if(player.getHP() == player.getMaxHP()){

        cout << "You're already full health!" << endl;
        PauseEnter();

    }else if(pot != Inventory.end()){
        
        player.addHP(consumable.getItemHP());
        
        if(player.getHP() > player.getMaxHP()) 
        
        player.setHP(player.getMaxHP());

        cout << "You used your " << pot -> getItemName() <<". It heals for "
            << pot -> getItemHP() <<" HP!" <<endl;
            Inventory.erase(pot);
            PauseEnter();
    }else{

        cout << "You don't any of that potion!"<< endl;
        PauseEnter();
    };
};
// TODO: add condition to remove obsolete gear from inventory, replace with better when it's found
void checkItemGear(Character &player, vector<Item> &Inventory, Item& find_gear){
    
    auto gear = find(Inventory.begin(), Inventory.end(), find_gear);
    
    if(gear != Inventory.end()){
        
        player.addATK  (gear -> getItemATK());
        player.addDEF  (gear -> getItemDEF());
        player.addMaxHP(gear -> getItemHP());
    
    };
};

void LevelUp(Character &player, int &current_floor){    

    while(player.getLv() < 45 && player.getXP() >= player.getLv() * 60 )
    {
        cls(1);
        player.addLv(1);
        
        cout << "====================== " << endl;

        if(player.getLv() <= 15){
            player.addATK(1);
            cout << "\nYour Attack increased by 1\n";
            player.addDEF(1);
            cout << "Your Defence increased by 1\n";
            player.addMaxHP(20);
            cout << "Your Health increased by 20\n";
        }else if(player.getLv() >= 16 && player.getLv() <= 30){
            player.addATK(2);
            cout << "\nYour Attack increased by 2\n";
            player.addDEF(2);
            cout << "Your Defence increased by 2\n";
            player.addHP(30);
            cout << "Your Health increased by 30\n";
            player.setMaxHP(player.getHP());
        }else{
            player.addATK(2);
            cout << "\nYour Attack increased by 2\n";
            player.addDEF(2);
            cout << "Your Defence increased by 2\n";
            player.addHP(40);
            cout << "Your Health increased by 40\n";
            player.setMaxHP(player.getHP());
        };
    
        cout << "\nCongratulations! You're now level " << player.getLv() << "!\n";
        cout << "You now have " << player.getATK() << "ATK!\n";
        cout << "You now have " << player.getDEF() << "DEF!\n";
        cout << "You now have " << player.getMaxHP() << "HP!\n";

        player.setXP(0);
        player.setHP(player.getMaxHP());
        saveGameWorld(player, Inventory, current_floor);
    };
};

void CombatAttackLogic(Character &player, Mob &rival){
    
    int damage_player;
    int damage_rival;
    
    damage_player = ceil((rand() % (player.getATK()+ 1) * (1 - (double)rival.getDEF()/100)));           
    if(damage_player < 0) damage_player = 0;

    if(player.getATK() >= 50){
        damage_player += 25;
    }else if(player.getATK() >= 30){ 
        damage_player += 15;};

    if(player.getATK() >= 2 * rival.getDEF()) damage_player *= 2;
        
    
    damage_rival = ceil((rand() % (rival.getATK()+ 1) * (1 - (double)player.getDEF()/100))); 
    if(damage_rival < 0) damage_rival = 0;

    cout<<"You attacked " << rival.getName() <<" for " << damage_player <<"HP!.";
    rival.addHP(-damage_player);
    PauseEnter();
            
    if (rival.getHP() <= 0){
    }else{ 
        cout<< rival.getName() <<" attacked back! You lost " << damage_rival <<"HP.";
        player.addHP(-damage_rival);
        PauseEnter(); 
    } 
};

void CombatBlockLogic(Character &player, Mob &rival){

    int damage_rival;

    damage_rival = ceil((rand() % (rival.getATK()+ 1) * (1 - (double)player.getDEF()/100))); 
    if(damage_rival < 0) damage_rival = 0;

    int block_chance = max(player.getDEF() - rival.getATK(), 35);
    if(damage_rival < 0) damage_rival = 0;

    if(rand() % 100 < block_chance){
        double reduction = player.getDEF() / 100;
        
        damage_rival = ceil(damage_rival * (1 - reduction));
        cout << "You blocked some of " << rival.getName() << "'s damage!" << endl;
        cout << rival.getName() << " attacked you for " << damage_rival << "HP." << endl;
        PauseEnter();
    }else{

        player.addHP(-damage_rival);
        cout << rival.getName() <<"Crushed through your block!\n" 
             << rival.getName() << " attacked you for " << damage_rival << "HP." << endl;
        PauseEnter();
    }
};

bool CombatEscapeLogic(Character &player, Mob &rival, int &current_floor){

    int damage_rival;

    damage_rival = ceil((rand() % (rival.getATK()+ 1) * (1 - (double)player.getDEF()/100))); 
    if(damage_rival < 0) damage_rival = 0;

    if(rand() % 100 < max(player.getDEF()-rival.getATK(), 5)){
        cout << "You managed to escape from " << rival.getName() <<"..." << endl;
        PauseEnter();
        saveGameWorld(player, Inventory, current_floor);
        return true;
    }else{ 
        damage_rival = ceil((rand() % (rival.getATK()+ 1) * (1 - (double)player.getDEF()/100))); 
        if(damage_rival < 0) damage_rival = 0;
        
        cout<< rival.getName() <<" managed to catch you!" << endl;
        cout<< rival.getName() <<" attacked back! You lost " << damage_rival <<"HP.";
        player.addHP(-damage_rival);
        PauseEnter();
        return false;
    };
};

void infoBar(Character &player){

    cout << R"(
                //====================\\
                ||         ___        ||
                ||        (|||)       ||
                ||        (|||)       ||
                ||        (ò_ó)       ||
                ||    ____/ = \____   ||
                ||   (  _  _|_  _  )  ||
                ||   ( ) | _|_ | ( )  ||
                ||___\_/_\__|__/_\_/__||
                \\====================// 
    )";
    cout << "\n"<< setw(30) << player.getNome() << endl;
    cout <<  "+-----+--------------+-------+------+----------------------+" << endl;
    cout <<  "| LV  |      HP      |  ATK  | DEF  | Total XP / XP Needed |" << endl;
    cout <<  "+-----+--------------+-------+------+----------------------+" << endl;
    cout <<  "| " << setw(3) << player.getLv()
         << " | " << setw(7) << player.getHP() <<"/"<< player.getMaxHP() 
         << " | " << setw(5) << player.getATK()          
         << " | " << setw(4) << player.getDEF()          
         << " | " << setw(5) << player.getXP() << "XP /" << setw(5) <<  player.getLv() * 60<< "XP     |" << endl;
    cout << "+-----+--------------+-------+------+----------------------+";

};

bool combateInstance(Character &player, Mob &rival, int &current_floor, vector<Item> &Inventory, bool &isAlive){
    
    saveGameWorld(player, Inventory, current_floor);
    
    int player_action;

    while(player.getHP() > 0 && rival.getHP() > 0){
        
        int less;
        int med;
        int great;
        less = count(Inventory.begin(), Inventory.end(), potion_lesser);
        med = count(Inventory.begin(), Inventory.end(), potion_medium);
        great = count(Inventory.begin(), Inventory.end(), potion_greater);

        cls(0.5);
        
        rival.printASCII();
        rival.MobInfoBar();
        infoBar(player);
        cout << "\n"
             <<"+-----------------------+" <<"---------------------------+" << "\n"
             <<"|        1.Attack       |" <<" You have "<< less <<" lesser potions |" << "\n"
             <<"+-----------------------+" <<"---------------------------+" << "\n"
             <<"|        2.Block        |" <<" You have "<< med <<" medium potions |" << "\n"   
             <<"+-----------------------+" <<"---------------------------+" << "\n"
             <<"|        3.Escape       |" <<" You have "<< great <<" greater potions|" << "\n"
             <<"+-----------------------+" <<"---------------------------+" << "\n"
             <<"|        4.Heal         |" <<"    SWORD / SHIELD  (wip)  |" <<"\n"
             <<"+-----------------------+" <<"---------------------------+" <<endl;

        cout << "\nChoose an option: ";
        if (!(cin >> player_action)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Choose a valid option.\n";
            cls(1);
            continue; 
            }

        switch (player_action)
        {
            case 1: CombatAttackLogic(player, rival); break;
            case 2: CombatBlockLogic(player, rival); break;  
            case 3: if(CombatEscapeLogic(player,rival,current_floor)) return true;
                    break;
            case 4:{
                    int potion_choice;
                    cout <<"Pick your potion: \n";
                    cout << " 1.Lesser Potion. \n 2.Medium Potion. \n 3.Greater Potion.\n Choice:";
                    if(!(cin >> potion_choice)){
                        cin.clear(); 
                        cout << "Choose a valid option.\n";
                        cls(1);
                        continue;
                    }switch (potion_choice){
                        case 1: useItem(player,Inventory, potion_lesser);break;
                        case 2: useItem(player,Inventory, potion_medium); break;
                        case 3: useItem(player,Inventory, potion_greater);break;
                    }
            break;
                } 
            default:
                cout << "Choose a valid option\n.";
                PauseEnter();
                continue;
        };

        if(rival.getHP() <= 0){
            
            cls(1);
            cout << "You defeated "<< rival.getName() <<"."<< endl;
                
            if(player.getLv() < 45){
                    
                player.addXP(rival.getXP());
                cout << "You got " << rival.getXP() <<"XP!"<< endl;
                LevelUp(player, current_floor);
                PauseEnter();
            }else{
                cout << " You are at maximum level!" << endl;
            };
            isAlive = true;
            return isAlive;
        };
        if(player.getHP() <= 0){
            player.setHP(0);

            int player_exit_game;
            cout << rival.getName() << " Has defeated you..." << endl;
            cout << "Press 1 to continue or any other key to exit.\n";
            cin  >> player_exit_game;
            
            if (player_exit_game == 1){
                loadGameWorld(player, Inventory, current_floor);
            }else if(player_exit_game != 1){
                cout << "Until next time!";
                PauseEnter();
                isAlive = false;
                return isAlive;
            };
        };    
    };
};

void monster_spawn(Character &player, Mob &rival, Floor &floor){

    vector<Mob> eligible; 

    for (auto& i : floor.mobs) 
    {
        if(i.getLv() <= player.getLv() || player.getLv() == 45 ){
            eligible.push_back(i);
        } 
    };

    if (!eligible.empty()) {
        int index = rand() % eligible.size();
        rival = eligible[index];
    }
};

// MAIN GAME LOGIC HERE, EVERYTHING BEFORE IS FOUNDATION
// TODO: exploring, locations, item locations, 
// combat triggers, miniboss fight conditions
void gameLoop(Character &player, int current_floor){
    
    cls(0.5);

    bool isAlive = true;

    bool game_active = true;
    
    while(game_active && isAlive){
    
        // add loop to set get items from inventory, assign each of them to 1-5 variable, 
        // then use that to display
        int less;
        int med;
        int great;
        less = count(Inventory.begin(), Inventory.end(), potion_lesser);
        med = count(Inventory.begin(), Inventory.end(), potion_medium);
        great = count(Inventory.begin(), Inventory.end(), potion_greater);
    
        int player_interaction;
        
        cout << playerArt << endl;
        cout
        << "+-----------------------+-----------------------------+\n"
        << "|      1.Explore        |            INVENTORY        |\n"
        << "+-----------------------+-----------------------------+\n"
        << "|      2.Look around    | " << "  "<<"    sword       " << setw(12) << "|\n"
        << "+-----------------------+ " << "  "<<"    shield      " << setw(12) << "|\n"
        << "|      3.Rest           |    " << less << " Lesser Potion" << setw(12) << "|\n"
        << "+-----------------------+    " << med  << " Medium Potion" << setw(12) << "|\n"
        << "|      4.Save           |    " << great<< " Greater Potion"<< setw(11) <<"|\n"
        << "+-----------------------+-----------------------------+\n"
        << "Choose your option:";

        if (!(cin >> player_interaction)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Choose a valid option.\n";
        cls(1);
        continue; 
        }
        monster_spawn(player, rival, first_floor);
        combateInstance(player, rival, current_floor, Inventory, isAlive);
        
        if(!isAlive) {
                game_active = false;
        };
    };
    
};
void intro()
{

    int current_floor = 1;
    char nome[22];
    
    cout << "What are you called?:\n";
    cin.getline(nome, 22);

    Character player(nome);

    if(!player.loadGame()){
        player.setLv(1);
        player.setHP(150);
        player.setMaxHP(150);
        player.setATK(15);
        player.setDEF(15);
        player.setXP(0);
    } else {
        loadGameWorld(player, Inventory, current_floor);
        cout << "Welcome back! Let's continue your adventure..." << endl;
        PauseEnter();
    }
    saveGameWorld(player, Inventory, current_floor);
    gameLoop(player, 1);
};

int main(){
srand(time(NULL));
intro();
return 0;
};