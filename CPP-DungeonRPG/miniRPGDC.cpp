#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <limits>
#include <cstdlib>
#include <fstream>
#include <string> 
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cctype>
#include "ASSETS.h"

// Gonçalo Fonseca PI06 

using namespace std; 

/*

This project is a small dungeon RPG exercise made for class focusing on OOP programming.

Player objective: defeat the final boss to escape the dungeon.

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

    if (cin.peek() == '\n' || cin.peek() == ' ') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.get();
}

class Item {
private:
    string name;
    int atk;
    int def;
    int hp;
    bool consume; 

public:
    Item(string iname, int iatk = 0, int idef = 0, int iHp = 0, bool iconsume = false)
        : name(iname), atk(iatk), def(idef), hp(iHp), consume(iconsume) {}

    string getItemName() const { return name; }
    int getItemATK() const { return atk; }
    int getItemDEF() const { return def; }
    int getItemHP() const { return hp; }
    bool checkIfConsumable() const { return consume; }

    bool operator==(const Item& other) const {
        return name == other.name;
    }
};

Item sword_basic("Wood Plank", 10, 0, 0); 
Item sword_advanced("Moonsword", 40, 0, 0);

Item shield_basic("Cauldron Lid", 0, 10, 100); 
Item shield_advanced("Mithril Shield", 0, 40, 700);

Item potion_lesser("Lesser Health Potion", 0, 0, 100, true); 
Item potion_medium("Medium Health Potion", 0, 0, 200, true);
Item potion_greater("Greater Health Potion", 0, 0, 400, true);

vector<Item> weapons_loot = {sword_basic, sword_advanced};
vector<Item> shield_loot = {shield_basic,shield_advanced};
vector<Item> potions_loot = {potion_lesser, potion_medium, potion_greater};


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
        cout << ASCII << "\n";
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


//Enemies
Mob zombie("Zombie", 1, 110, 11, 8, 300, zombieART); 
Mob skeleton("Skeleton", 4, 150, 20, 15, 600, skeletonART);
Mob ghost("Ghost", 8, 120, 13, 35, 900, ghostART);
Mob homunculus("Mindless Homunculus", 12, 320 , 20, 45, 1500, humonculousART);
Mob stalker("Crypt Stalker", 18, 200, 35, 25, 2400, stalkerART);
Mob knight ("Death knight", 25, 400, 30, 50, 3800, death_knightART);

// Boss
Mob boss("Gargoyle", 40 , 1500, 70, 88, 5000, gargoyleART);  

vector<Mob> mobs_first_floor = {zombie, skeleton, ghost, homunculus, stalker, knight};

class Character{

private:
    string nome;
    int Lv,HP,MaxHP,ATK,DEF,XP;
    vector<Item> player_inventory;
    int equipped_weapon;
    int equipped_shield;
 

public:

Character(const string& nome)
    : nome(nome), Lv(0), HP(0), MaxHP(0), ATK(0), DEF(0), XP(0),
      player_inventory{}, equipped_weapon(-1), equipped_shield(-1)
{
    // Adds starter items
    player_inventory.push_back(sword_basic);   
    player_inventory.push_back(shield_basic);  
   
    setHP(getMaxHP());
}
    
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


    void equipWeapon(int index){

    if (equipped_weapon != -1) {
        addATK(-player_inventory[equipped_weapon].getItemATK());
    }

    equipped_weapon = index;

    addATK(player_inventory[index].getItemATK());
    }
    
   void equipShield(int index){

    if (equipped_shield != -1) {
        addDEF(-player_inventory[equipped_shield].getItemDEF());
        addMaxHP(-player_inventory[equipped_shield].getItemHP());
    }

    equipped_shield = index;

    addDEF(player_inventory[index].getItemDEF());
    addMaxHP(player_inventory[index].getItemHP());
}
    
    // inventory logic here
    const vector<Item>& getInventory() const { return player_inventory; }
    
    void addItem(const Item& item) { player_inventory.push_back(item);}

    bool hasItem(const Item& itemToFind) const {
        for (const auto& item : player_inventory) {
            if (item == itemToFind) { 
                return true; 
            }
        }
        return false; 
    }
    
    int countItem(const Item& itemToFind) const {
        int total = 0;
        for (const auto& item : player_inventory) {
            if (item == itemToFind) {
            total++;
            }
        }
        return total;
    }
    
    void UseConsumable(const Item& consumable){   

        auto pot = find(player_inventory.begin(), player_inventory.end(), consumable); 
        
        if(HP == MaxHP){cout << "\nYou're already full health!" << endl;PauseEnter(); return;}
        

        if(pot == player_inventory.end()){ 
        
            cout <<"\nYou don't have any "<< consumable.getItemName()<<" left."<< endl;
            PauseEnter();
            return;
            
        };

        
        if(pot != player_inventory.end()){
        
            addHP(consumable.getItemHP());
            if(HP > MaxHP) setHP(MaxHP);

            cout << "\nYou used your " << pot -> getItemName() <<". It heals for "<< pot -> getItemHP() <<" HP!" <<endl;
            player_inventory.erase(pot);
            
            PauseEnter();
        }
    };

    // save load logic
    void saveGame() const {
        string nomeFile = nome + ".sav";
        ofstream out(nomeFile);
            
        out << nome << "\n" << Lv << "\n" << HP << "\n" 
            << MaxHP << "\n" << ATK << "\n" << DEF << "\n" << XP << endl;
        
        out << player_inventory.size() << endl;
        for (const auto& item : player_inventory) {
            out << item.getItemName() << endl;
            out << item.getItemATK() << " "
                << item.getItemDEF() << " "
                << item.getItemHP() << " "
                << item.checkIfConsumable() << endl; 
        }
    }

   bool loadGame() {
    string nomeFile = nome + ".sav";
    ifstream in(nomeFile);
    if(!in) return false;

    getline(in >> ws, nome);
    in >> Lv >> HP >> MaxHP >> ATK >> DEF >> XP;

    size_t inventorySize;
    if (in >> inventorySize) {
        player_inventory.clear();
        for (size_t i = 0; i < inventorySize; i++) {
            string iname;
            int iatk, idef, ihp;
            bool iconsume;
            getline(in >> ws, iname);
            in >> iatk >> idef >> ihp >> iconsume;
            player_inventory.push_back(Item(iname, iatk, idef, ihp, iconsume));
        }
    }


    if (equipped_weapon < 0 || equipped_weapon >= player_inventory.size())
        equipped_weapon = -1;
    if (equipped_shield < 0 || equipped_shield >= player_inventory.size())
        equipped_shield = -1;

    return true;
}
};


struct Room {

    int room_id;
    string room_name; 
    string map_art;    
    vector<Mob> mobs;
    vector<Item> loot;
};

Room hallway_First_Floor{ 0 ,"Stone corridor", dungeonHallArt, mobs_first_floor,{}};
Room cell{ 1, "Cell", CellRoomArt, mobs_first_floor, weapons_loot};
Room laboratory{ 2, "Laboratory", LaboratoryRoomArt,mobs_first_floor, shield_loot};
Room inner_gates{ 3, "Inner Gates", arenaART, mobs_first_floor, {} };
Room safe_room{ 4, "Abandoned Chapel", chapelArt, {}, potions_loot };

struct Floor{
    
    string floor_at_name;
    vector<Room> rooms;
};

Floor dungeon_floor{"First Floor", { hallway_First_Floor, cell, laboratory, inner_gates, safe_room} };
         
        //      \\        HELPERS GO HERE      \\        //
void LevelUp(Character &player){    

    while(player.getLv() < 45 && player.getXP() >= player.getLv() * 60 )
    {
        cls(1);
        
        int xp_needed = player.getLv() * 60;
        player.addLv(1);
        
        cout << "===========================" << endl;

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
    
        if(player.getATK() > 99) player.setATK(99);
        if(player.getDEF() > 99) player.setDEF(99);

        cout << "\nCongratulations! You're now level " << player.getLv() << "!\n";
        cout << "\nYou now have " << player.getATK() << "ATK!\n";
        cout << "You now have " << player.getDEF() << "DEF!\n";
        cout << "You now have " << player.getMaxHP() << "HP!\n";

        cout << "===========================" << endl;

       
        player.setXP(player.getXP() - xp_needed);
        
        player.setHP(player.getMaxHP());
        player.saveGame();
        cout << "\nPress enter to continue..." << endl;
        PauseEnter();
    };
};

void savePosition(Character &player, Floor &current_floor, Room &current_room) {
    string nomeFile = player.getNome() + "_pos.sav";
    ofstream out(nomeFile);
    if(out.is_open()){
        out << current_floor.floor_at_name << "\n";
        out << current_room.room_name << endl;
    }
}

bool loadPosition(Character &player, Floor &current_floor, Room &current_room) {
    string nomeFile = player.getNome() + "_pos.sav";
    ifstream in(nomeFile);
    if(!in) return false;

    string fName, rName;
    getline(in >> ws, fName);
    getline(in >> ws, rName);

    for (const auto& r : current_floor.rooms) {
        if (r.room_name == rName) {
            current_room = r;
            current_floor.floor_at_name = fName;
            return true;
        }
    }
    return false;
}

void CombatAttackLogic(Character &player, Mob &rival){
    
    int damage_player;
    int damage_rival;

    damage_player = ceil((rand() % (player.getATK() + 1) * (1 - (double)rival.getDEF()/100)));           
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
            
    if (rival.getHP() > 0){
        cout<< rival.getName() <<" attacked back! You lost " << damage_rival <<"HP.";
        player.addHP(-damage_rival);
        PauseEnter(); 
    }; 
};

void CombatBlockLogic(Character &player, Mob &rival){

    int damage_rival;

    damage_rival = ceil((rand() % (rival.getATK()+ 1) * (1 - (double)player.getDEF()/100))); 
    if(damage_rival < 0) damage_rival = 0;

    int block_chance = max(player.getDEF() - rival.getATK(), 35);
    if(damage_rival < 0) damage_rival = 0;

    if(damage_rival == 0){

        cout << "You managed to deflect the enemies' attack!"<< endl;
        cout << "You reflected "<< player.getATK() / 2 << " HP damage to " << rival.getName() <<"!"<<endl;
        rival.addHP(-player.getATK() / 2);
        PauseEnter();

    }else if(rand() % 100 < block_chance){
        
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

bool CombatEscapeLogic(Character &player, Mob &rival, Floor &current_floor, Room &current_room){

    int damage_rival;

    damage_rival = ceil((rand() % (rival.getATK()+ 1) * (1 - (double)player.getDEF()/100))); 
    if(damage_rival < 0) damage_rival = 0;

    if(rand() % 100 < max(player.getDEF()-rival.getATK(), 5)){
        cout << "You managed to escape from " << rival.getName() <<"..." << endl;
        sleep(3);
        player.saveGame();
        savePosition(player,current_floor, current_room);
        return true;
    }else{ 
        damage_rival = ceil((rand() % (rival.getATK()+ 1) * (1 - (double)player.getDEF()/100))); 
        if(damage_rival < 0) damage_rival = 0;
        
        cout<< rival.getName() <<" managed to catch you!" << endl;
        cout<< rival.getName() <<" attacked you! You lost " << damage_rival <<"HP.";
        player.addHP(-damage_rival);
        PauseEnter();
        return false;
    };
};

void PlayerInfoBar(Character &player){

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

bool combateInstance(Character &player, Mob &rival, Floor &current_floor, Room &current_room, bool &isAlive, bool &player_victory){
    
    player.saveGame();
    savePosition(player,current_floor, current_room);
    
    int player_action;
    

    while(player.getHP() > 0 && rival.getHP() > 0){
        
        vector<string> item_slot(7, "Empty");
        auto& show_inv = player.getInventory();

        int ui_idx = 0;
        for (int i = 0; i < show_inv.size() && ui_idx < 7; i++) {
            
            string current_item_name = show_inv[i].getItemName();
            bool exists = false;

            for (int j = 0; j < ui_idx; j++) {
                if(item_slot[j] == current_item_name) {
                    exists = true;
                    break;
                }
            }
            if(!exists) {
                item_slot[ui_idx] = current_item_name;
                ui_idx++; 
            }
        }

        cls(0.5);
        rival.printASCII();
        rival.MobInfoBar();
        PlayerInfoBar(player);
        cout << "\n"
             <<"+-----------------------+" <<"----------------------------------+" <<"\n" 
             <<"|        ACTIONS        |" <<"           INVENTORY              |" <<"\n" 
             <<"+-----------------------+" <<"----------------------------------+" <<"\n" 
             <<"|        1.Attack       |" << setw(22)<<item_slot[0] <<" "<< player.countItem(item_slot[0]) <<"\n"  
             <<"+-----------------------+" << setw(22)<<item_slot[1] <<" "<< player.countItem(item_slot[1]) <<"\n"
             <<"|        2.Block        |" << setw(22)<<item_slot[2] <<" "<< player.countItem(item_slot[2]) <<"\n"
             <<"+-----------------------+" << setw(22)<<item_slot[3] <<" "<< player.countItem(item_slot[3]) <<"\n"  
             <<"|        3.Escape       |" << setw(22)<<item_slot[4] <<" "<< player.countItem(item_slot[4]) <<"\n"  
             <<"+-----------------------+" << setw(22)<<item_slot[5] <<" "<< player.countItem(item_slot[5]) <<"\n"   
             <<"|        4.Heal         |" << setw(22)<<item_slot[6] <<" "<< player.countItem(item_slot[6]) <<"\n"   
             <<"+-----------------------+" <<"----------------------------------+" << endl;   

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
            case 3: if(CombatEscapeLogic(player,rival, current_floor, current_room)) return true;
                    break;
            case 4:{
                    int potion_choice;
                    cout <<"Pick your potion: \n";
                    cout << "1.Lesser Potion. \n 2.Medium Potion. \n 3.Greater Potion.\n Choice:";
                    if(!(cin >> potion_choice)){
                        cin.clear(); 
                        cout << "Choose a valid option.\n";
                        cls(1);
                        continue;
                    }switch (potion_choice){
                        case 1: player.UseConsumable(potion_lesser);break;
                        case 2: player.UseConsumable(potion_medium);break;
                        case 3: player.UseConsumable(potion_greater);break;
                    }
            break;
                } 
            default:
                cout << "Choose a valid option\n.";
                sleep(1);
                continue;
        };

        if(rival.getHP() <= 0){
            
            cls(1);
            cout << "You defeated "<< rival.getName() <<"."<< endl;
            
            if (rival.getName() == boss.getName()) {return player_victory = true;}
            
            if(player.getLv() < 45){
                    
                player.addXP(rival.getXP());
                cout << "You got " << rival.getXP() <<"XP!"<< endl;
                LevelUp(player);
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
                player.loadGame();
                loadPosition(player, current_floor, current_room);
            }else if(player_exit_game != 1){
                cout << "Until next time!";
                PauseEnter();
                isAlive = false;
                return isAlive;
            };
        };    
    };
}

void MonsterSpawn(Character &player, Mob &rival, Room &current_room){

    vector<Mob> eligible; 

    for (auto& enemy : current_room.mobs) 
    {
        if(enemy.getLv() <= player.getLv() || player.getLv() == 45)
        {   
            int higher_dificulty_enemies = max(1, enemy.getLv() - player.getLv() / 2 + 1);
            for (int i = 0; i < higher_dificulty_enemies; i++){
                eligible.push_back(enemy);
            }
        }; 
    };

    if (!eligible.empty()) {
        int index = rand() % eligible.size();
        rival = eligible[index];
    }
};

bool recoveryPlayer(Character &player, bool &is_rested){
    cout << "You sit down to rest a while..\n"
         << "Would you like to use any items, or simply sit down?" << endl;

    cout << R"(
    |.................|
    |1. Lesser Potion |
    |-----------------|
    |2. Medium Potion |
    |-----------------|
    |3. Greater Potion|
    |-----------------|
    |4. Sit down      |
    |.................|

    Choice: )";

    int rest_choice;
    if(!(cin >> rest_choice)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Choose a valid option.\n";
        cls(1);
        return false; 
    }

    switch(rest_choice){
        case 1: player.UseConsumable(potion_lesser);
            return false; 
        case 2: player.UseConsumable(potion_medium);
            return false;
        case 3: player.UseConsumable(potion_greater);
            return false;
        case 4:
            if (!is_rested){
                cout << "You catch your breath." << endl;

                player.addHP(player.getMaxHP() / 4);
                
                if(player.getHP() > player.getMaxHP()) player.setHP(player.getMaxHP());
                
                PauseEnter();
                
                is_rested = true;
                
                return true; 
            } else {

                cout << "You've already taken a rest." << endl;
                PauseEnter();
                
                return false;
            }
        default:
            cout << "Choose a valid option.\n";
            return false;
    }
}

// Exploration, searching rooms logic and functions here
void enconterRate(int enconter_chance, Character &player, Mob &rival, Floor &current_floor, Room &current_room, bool &isAlive, bool &player_victory){


    int combat_chance = rand() % 100;
    if (combat_chance < enconter_chance){

        MonsterSpawn(player,rival,current_room);
        cout << "A " << rival.getName() <<" has appeared. It seems hostile!"<< endl;
        rival.printASCII();
        
        PauseEnter();
        combateInstance(player, rival, current_floor, current_room, isAlive, player_victory);
    };
     
}

void PlayerExplore(Character &player, Mob &rival, Floor &current_floor, Room &current_room, bool &isAlive, bool &player_victory){
    
    
    enconterRate(35, player, rival, current_floor, current_room, isAlive, player_victory);

    cls(1);
    current_room = dungeon_floor.rooms[0];
    cout << current_room.map_art << endl;
    cout << "\nYou navigate through the "<< current_room.room_name <<".\n" << endl;
    
    
    char player_movement;
   
    cout << "Where are you turning to? (N, S, W, E)"<< endl;
    if (!(cin >> player_movement)) {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout <<"Choose a valid option." << endl;
    cls(1);
    };
    
    player_movement = toupper(player_movement);
    
    switch (player_movement)
    {

    case 'N':
        current_room = dungeon_floor.rooms[2];
        cout << "You arrived at the "<< current_room.room_name << endl;
        enconterRate(20, player, rival, current_floor, current_room, isAlive,player_victory);
        PauseEnter();
        break;

    case 'S':
        current_room = dungeon_floor.rooms[1];
        cout << "You returned back to your "<< current_room.room_name << endl;
        enconterRate(20, player, rival, current_floor, current_room, isAlive,player_victory);
        PauseEnter();
        break;

    case 'E':
        if(player.getLv() < 30){
            enconterRate(100,player, rival, current_floor, current_room, isAlive,player_victory);// enconter is set to 100 so the player can grind levels until he can enter.
            cls(1);
            cout << dungeon_floor.rooms[3].map_art << endl;
            cout << "You're not strong enough to open the door to the Arena...\n"
                 << "Return when you're stronger." << endl;
                PauseEnter();
            break;
        }else{
            current_room = dungeon_floor.rooms[3];
            cout << "You arrived at the "<< current_room.room_name << endl;
            PauseEnter();

            cout << "\nThe doors open slowly, revealing a menacing figure inside." << endl;
            PauseEnter();
            combateInstance(player, boss, current_floor, current_room, isAlive,player_victory);

        }
        break;

    case 'W':
        current_room = dungeon_floor.rooms[4];
        cout << "You arrived at the "<< current_room.room_name 
             << "\nYou feel oddly at peace here." << endl;
            PauseEnter();
        break;

    default:
        cout << "You see nothing of interest." << endl;
        break;
    }    
    PauseEnter();
}

void LookAround(Character &player, Room &current_room){

    if(current_room.room_id == 0){ //hallway
        cout << "You see nothing but a cold, empty corridor." << endl;

    }else if(current_room.room_id == 1){ // cell
        
        cout << "\nYou see chains hanging on the wall and a single barred window.\n" << endl;
        
        if(!player.hasItem(sword_advanced)){
       
            player.addItem(sword_advanced);
            cout << "\nYou found a "<< sword_advanced.getItemName()<< " on the floor.\nYou take it with you." << endl;
           

        }else{
            
            cout << "\nThere is nothing of value left." << endl;

        };
        PauseEnter();
    }else if(current_room.room_id == 2){ // lab

        cout << "\nTheres shelfs with vials filled with strange liquids, a large couch sits in the middle of the room.\n"
             << "A filing cabinet sits in the corner by itself, empty.\n" << endl;
        
            if(!player.hasItem(shield_advanced)){
                
                player.addItem(shield_advanced);

                cout << "\nYou found a "<< shield_advanced.getItemName()<< " on the floor.\nYou take it with you." << endl;
            
            }else{
            
                cout << "\nThere is nothing of value left to take." << endl;
                
            };  
            PauseEnter();  
    }else if(current_room.room_id == 3){ // arena

        cout << "\nYou stare at the giant double doors in front of you.\n"
             << "Nothing else stands out in this room.\n" << endl;
            PauseEnter();

    }else if(current_room.room_id == 4){ // chapel
        
        int potion_find_chance = rand() % 100;
        
        if(potion_find_chance <= 4){ 
            
            if(player.countItem(potion_greater) > 1)
            { 
                cout <<"You cannot carry any more Greater potions";
            
            }else{
            player.addItem(potion_greater);
            
            cout << "\nLucky find!\nA greater potion appeared on the altar. \nYou take it with you." <<endl;
            
            }
            PauseEnter();
        }else if(potion_find_chance <= 14){
        
            if(player.countItem(potion_medium) > 2)
            { 
                cout <<"You cannot carry any more Medium potions";
            }else{

            player.addItem(potion_medium);
            cout << "\nDecent fortune.\nA medium potion appeared on the altar. \nYou take it with you." <<endl;
            
            }
        }else if(potion_find_chance <= 50){
        
            if(player.countItem(potion_lesser) > 3){ 
                cout <<"You cannot carry any more Lesser potions";
            }else{
            player.addItem(potion_lesser);
            cout << "\nSmall luck.\nYou found a lesser potion on the altar. \nYou take it with you." <<endl;
            
            }   
        }else{

            cout<<"It seems you are unfortunate.\nYou found nothing.";
            
        }   
        PauseEnter();
    };
}

// Main game loop and intro here, everything before is foundation
void gameLoop(Character &player, Mob &rival, Floor &current_floor, Room &current_room){
    
    cls(0.5);

    bool player_victory = false;
    bool is_rested = false;
    bool isAlive = true;
    bool game_active = true;

    while(game_active && isAlive){
        
        cls(1);
    
        int player_interaction;
        cout << current_room.map_art << endl;
        cout
        << "+-----------------------+ +---------------------------------------+\n"
        << "|   1.Explore           | |                   STATUS              |\n"
        << "+-----------------------+ +---------------------------------------+\n"
        << "|   2.Search around     | |    LEVEL:         "<<player.getLv()<< setw(21) <<"|\n" 
        << "+-----------------------+ |    HEALTH:        "<<player.getHP()<<" / "<<player.getMaxHP()<< setw(13) <<"|\n"
        << "|   3.Rest              | |    ATTACK:        "<<player.getATK()<< setw(20) <<"|\n"
        << "+-----------------------+ |    DEFENCE:       "<<player.getDEF()<< setw(20) <<"|\n"
        << "|   4.Save              | |    CURRENT XP:    "<<player.getXP()<< setw(21) <<"|\n"
        << "+-----------------------+ |    NEXT LEVEL XP: "<<player.getLv() * 60<< setw(20) <<"|\n"
        << "|   5.Save and Exit     | |                                       |\n"
        << "+-----------------------+ |                                       |\n"
        << "|   6.Equip Item        | |                                       |\n" 
        << "+-----------------------+ +---------------------------------------+\n"
        << "What would you like to do now?\nR: ";

        if (!(cin >> player_interaction)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout <<"Choose a valid option." << endl;
            cls(1);
            continue;
        }

        switch (player_interaction)
        { 
            case 1:
                PlayerExplore(player, rival, current_floor ,current_room, isAlive, player_victory);
                break;
        
            case 2:
                LookAround(player, current_room);
                break;
        
            case 3:
                if(current_room.room_id == 4){ 

                    recoveryPlayer(player, is_rested);
                
                }else{
                
                    cout << "You feel too uneasy to rest here. You should seek sanctuary.";
                    PauseEnter();
                }
                break;
        
            case 4:

                player.saveGame();
                savePosition(player,current_floor,current_room);
                cout << "\n";
                cout << "Your progress been saved.\n" << endl;
                cout << "Press enter to continue..." << endl;
                PauseEnter();
                break;
        
            case 5:

                cout << "\n";
                cout << "Your progress has been saved.\n" << endl;
                cout << "Press enter to exit the game..." << endl;
                player.saveGame();
                savePosition(player,current_floor,current_room);
                PauseEnter();
                game_active = false;
                break;
            
            case 6:

                const auto& temp_invent = player.getInventory();
                
           
                bool hasEquipable = false;

                for (const auto& item : temp_invent)
                {
                    if (!item.checkIfConsumable()) 
                    {
                        hasEquipable = true;
                        break;
                    }
                }

                if (!hasEquipable)
                {
                    cout << "You have no equipable items.\n";
                    PauseEnter();
                    break;
                }

                cout << "Choose an item to equip:\n";

                for (size_t item_index = 0; item_index < temp_invent.size(); item_index++)
                {
                    if (!temp_invent[item_index].checkIfConsumable()) 
                    {
                        cout << item_index  << ": " << temp_invent[item_index].getItemName() << endl;
                    }
                }

                int item_choice_player;

                if (!(cin >> item_choice_player))
                    {
                    cout << "Invalid choice.\n";
                    PauseEnter();
                    break;
                    }

                if (temp_invent[item_choice_player].getItemATK() > 0) 
                {
                
                    player.equipWeapon(item_choice_player);

                } else if (temp_invent[item_choice_player].getItemDEF() > 0){
                    
                    player.equipShield(item_choice_player);
                
                } else {
                
                    cout << "This item cannot be equipped.\n";
                
                    break;
                }

                cout << "You equipped the " << temp_invent[item_choice_player].getItemName() << endl;
                PauseEnter();
                break;
        
            
        }
            
        if(!isAlive) {

            cout << defeatScreen << endl;
            game_active = false;
            
            
        }
        if(isAlive && player_victory){
            cout << victoryScreen <<endl;
            game_active = false;
        }
    }
}


void intro(Mob &rival, Floor &current_floor, Room &current_room){
    
    cls(0);

    bool new_player = true;
    char nome[22];

    cout << coverArt << endl;
         cout << "\nWelcome to my small dungeon crawler!\n\n"
            << "You can beat up enemies to level up to level 45, \n"
            << "finding items to help you in fights while exploring by searching the rooms.\n"
            << "Mostly you roam around, grind for a bit and then there's a boss fight at the end.\n\n";
            
    
    cout << "What are you called?:\n";
    cin.getline(nome, 22);

    Character player(nome);
    string saved_floor, saved_room;

    if(!player.loadGame()){
        player.setLv(1);
        player.setHP(150);
        player.setMaxHP(150);
        player.setATK(15);
        player.setDEF(15);
        player.setXP(0);
        new_player = true;
    } else {
        cout << "Welcome back! Press enter to continue your adventure..." << endl;
            player.loadGame();
            loadPosition(player,current_floor, current_room);
            new_player = false;
            PauseEnter();
        
        }
    
    if(new_player == true){

        player.saveGame();
        savePosition(player,current_floor,current_room);
        cout << "Press enter to start and have fun! " << endl;
            
        PauseEnter();
    };

    gameLoop(player, rival, current_floor, current_room);
};

int main(){
srand(time(NULL));
Room starting_room = dungeon_floor.rooms[1];
Mob zombie("Zombie", 1, 110, 11, 8, 100, zombieART); 
intro(zombie, dungeon_floor, starting_room);
return 0;
};

