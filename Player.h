// Created by Simon N. Nganga - 2655389


#ifndef PLAYER_H
#define PLAYER_H
#include  "Starship.h"
#include "Grid.h"
#include <vector>
using std::vector;


class Player {
private:
    const char *name;
    Grid defenseGrid;                 // Where ships are placed (opponent shoots here)
    Grid attackGrid;                  // Where this player records shots
    vector<Starship*> myFleet;
    int shipCount;
    int lastSunkShipIndex;
    int bonusShots = 0;     // Extra shots awarded this round
    int shotPenalty = 0;    // Shots to subtract this round
    int shotCap = -1;       // If set (e.g. 1), max shots allowed this turn
    bool extraTurn = false;


public:
    Player(char const *,int , char , int );
    int get_shipCount() const;

    bool deployShip(Starship *, int, int, char);   // Places a ship on the defense grid
    void addShipToGrid();

    bool canPlaceShip(int , int , int , char );//checks individual cell before placing the ship
    int maximumShots() const;


    // void takeTurn(Player& );   // Full turn: asks for shots and fires
    bool shootAt(Player& );  // Shoot a single shot at the opponent
    bool isMiss(int , int );
    bool hasLost() const;          // Returns true if all ships are sunk
    const char* getName() const;       // Returns player's name
    void display_defense_grid() const;
    void display_attack_grid() const;
    char getCell(int , int );
    void handleHitAt(int , int );
    bool checkAlreadyShotCell(int row, int col);
    bool validCoords(int , int ) const;
    void clearLastSunk();
    bool hasSunkShip() const;
    Starship* getLastSunkShip() const ;
    void receiveGiftFromRound(Player&);
    void addGiftToGrid(Starship*);

    int getBonusShots() const;

    void setBonusShots(int n);

    int getShotPenalty() const;

    void setShotPenalty(int n);

    int getShotCap() const;

    void setShotCap(int n);

    void resetShotModifiers();

    bool getExtraTurn() const;
    void setExtraTurn(bool value);

    void displayLostShips() const;

    int getLostCells() const;

    int countLostShipsOfSize(int size) const;


    int totalShots = 0;
    int totalHits = 0;
    int totalMisses = 0;
};








#endif //PLAYER_H
