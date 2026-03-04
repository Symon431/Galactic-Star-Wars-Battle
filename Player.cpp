// Created by Simon N. Nganga - 2655389

#include "Player.h"
#include <iostream>
using namespace std;
#include "Grid.h"

Player::Player(char const *name,int level, char col, int row) :name(name), defenseGrid(col,row),attackGrid(col,row){



    switch (level) {
        case 1: {

            myFleet.push_back(new StarDestroyer());
            myFleet.push_back(new MonCalamariCruiser());
            myFleet.push_back(new XWingSquadron());
            myFleet.push_back(new TIEFighter());
            myFleet.push_back(new TIEFighter());
            shipCount = 5;
            break;
        }

        case 2: {

            for (int i = 0; i < 2; i++) {
                myFleet.push_back(new StarDestroyer());
            }

            for (int i = 0; i < 2; i++) {
                myFleet.push_back(new MonCalamariCruiser());
            }

            for (int i = 0; i < 2; i++) {
                myFleet.push_back(new XWingSquadron());
            }

            for (int i = 0; i < 4; i++) {
                myFleet.push_back(new TIEFighter());
            }

            shipCount = 10;
            break;
        }

        case 3: {
            for (int i = 0; i < 4; i++)
                myFleet.push_back(new StarDestroyer());
            for (int i = 4; i < 7; i++)
                myFleet.push_back(new MonCalamariCruiser());
            for (int i = 7; i < 9; i++)
                myFleet.push_back(new XWingSquadron());
            for (int i = 9; i < 13; i++)
                myFleet.push_back(new TIEFighter());

            shipCount = 13;
            break;
        }

    }

    for (int i = 0; i < shipCount; i++) {
        myFleet[i]->setStatus(1);//1 is active ship, 0 is sunk ship
    }

}

int Player::get_shipCount() const {
    return shipCount;
}

bool Player::deployShip(Starship *ship, int startRow, int startCol, char pattern) {
    int size = ship->get_size();

    // Convert to directionally valid second row/col (just to pass to placement loop)
    if (!canPlaceShip(startRow, startCol, size, pattern)) {
        std::cout << "Invalid placement. Ship would go out of bounds or overlap.\n";
        return false;
    }

    for (int i = 0; i < size; ++i) {
        int row = startRow;
        int col = startCol;

        if (pattern == 'H')
            col += i;
        else if (pattern == 'V')
            row += i;
        else if (pattern == 'D') {
            row += i;
            col += i;
        }

        defenseGrid.placeShip(row, col, size);
        ship->addCell(row, col);

    }
    std::cout << "Ship placed successfully.\n";
    return true;
}

//returns the maximum number of shots based on the ship with the highest number of lasers that is unsunk
int Player::maximumShots() const {
    int maxShots = 0;
    for (int i = 0; i < shipCount; ++i) {
      if (myFleet[i]->get_size() > maxShots && myFleet[i]->get_status() == 1) {
          maxShots = myFleet[i]->get_size();
      }
    }
    return maxShots;
}

void Player::addShipToGrid() {
    int count = 0;
   do {
       char startRowChar, pattern;
       int startCol;

       cout << "Enter the pattern of your ships: 'H' for horizontal, 'V' for Vertical and 'D' for Diagonal: " << endl;
       cin >> pattern;
       while (pattern != 'H' && pattern != 'V' && pattern != 'D') {
           cout << "Invalid pattern!!" << endl;
           cout << "Enter the pattern of your ships: 'H' for horizontal, 'V' for Vertical and 'D' for Diagonal: " << endl;
           cin >> pattern;
       }

       cout << "Enter the start row[character] and column[int] separated by a space to place ship " << count + 1 <<" :" << endl;
       cin >> startRowChar;
       cin >> startCol;

       int startRow = tolower(startRowChar) - 'a' + 1;


           if (deployShip(myFleet[count], startRow, startCol, pattern)) {
               count++;
           }



   }while (count != shipCount);

    cout << "A total of "<< count << "ships have placed successfully on the grid." << endl;
}

// Checks if the ship can be placed on the grid without going out of bounds or overlapping with other ships.
bool Player::canPlaceShip(int startRow, int startCol, int size, char pattern) {
    for (int i = 0; i < size; ++i) {
        int row = startRow;
        int col = startCol;

        if (pattern == 'H')
            col += i;
        else if (pattern == 'V')
            row += i;
        else if (pattern == 'D') {
            row += i;
            col += i;
        }

        // Check if cell is inside the bound of our grid
        if (!defenseGrid.checkValidity(row, col))
            return false;

        // Check if cell is empty
        if (!defenseGrid.checkAvailability(row, col))
            return false;
    }
    return true; // All checks passed
}

void Player::display_defense_grid() const {
    defenseGrid.display();
}

void Player::display_attack_grid() const {
    attackGrid.display();
}

const char* Player::getName() const {
    return name;
}

bool Player::hasLost() const {
    for (int i = 0; i < shipCount; ++i) {
        if (myFleet[i]->get_status() == 1)
            return false;
    }
    return true;//all ships are sunk, player loses the game
}

bool Player::shootAt(Player& opponent) {
    int col, row;
    char rowChar;

    // Loop until the player enters a new, unshot cell
    while (true) {
        cout << "Enter row and column of the shot: ";
        cin >> rowChar >> col;
        row = tolower(rowChar) - 'a' + 1;

        if (!opponent.validCoords(row, col)) {
            cout << "Invalid coordinates. Try again." << endl;
            continue;
        }

        if (attackGrid.getCell(row, col) != '*') {
            cout << "You have already shot at this cell. Choose a different one." << endl;
            continue;
        }

        break;
    }

    // Check if the shot is a miss
    if (opponent.isMiss(row, col)) {
        attackGrid.markCell('0', row, col);  // mark miss
        return false;
    }

    opponent.clearLastSunk();
    opponent.handleHitAt(row, col);

    // Mark initial hit
    attackGrid.markCell('*', row, col);

    // Show full ship position if it is sunk
    if (opponent.hasSunkShip()) {
        Starship* sunk = opponent.getLastSunkShip();
        int count = sunk->getOcupiedCount();
        char displayChar = sunk->get_size() + '0';

        for (int i = 0; i < count; ++i) {
            int r = sunk->getOccupiedRow(i);
            int c = sunk->getOccupiedCol(i);
            attackGrid.markCell(displayChar, r, c);
        }
    }

    return true;
}

char Player::getCell(int row, int col) {return defenseGrid.getCell(row ,col );}

bool Player::isMiss(int row, int col) {
    if (defenseGrid.getCell(row,col) == '*')
        return true;
    return false;
}


bool Player::validCoords(int row, int col) const {
    return row >= 1 && row <= defenseGrid.getRows() &&
           col >= 1 && col <= defenseGrid.getCols();
}

void Player::handleHitAt(int row, int col) {
    for (int i = 0; i < shipCount; ++i) {
        if (myFleet[i]->occupies(row, col)) {
            int wasAlive = myFleet[i]->get_status();
            myFleet[i]->registerHit();

            if (wasAlive == 1 && myFleet[i]->get_status() == 0) {
                cout << "SUNK SHIP of size " << myFleet[i]->get_size() << " (will mark it):" << endl;
                lastSunkShipIndex = i;
            }
            break;
        }
    }
}

void Player::clearLastSunk() { lastSunkShipIndex = -1; }

bool Player::hasSunkShip() const { return lastSunkShipIndex != -1; }

// Returns a pointer to the last ship sunk in the round, or nullptr if none
Starship* Player::getLastSunkShip() const {
    if (lastSunkShipIndex != -1)
        return myFleet[lastSunkShipIndex];
    return nullptr;
}

void Player::receiveGiftFromRound(Player& opponent) {
    int giftRoll = rand() % 100 + 1;
    int giftType;

    if (giftRoll <= 10)
        giftType = 1;
    else if (giftRoll <= 40)
        giftType = 2;
    else if (giftRoll <= 60)
        giftType = 3;
    else if (giftRoll <= 80)
        giftType = 4;
    else
        giftType = 5;

    switch (giftType) {
        case 1: {
            cout << "Gift: You can add a secret battleship!\n";
            int shipRoll = rand() % 100 + 1;
            Starship* giftShip;

            if (shipRoll <= 10)
                giftShip = new StarDestroyer();
            else if (shipRoll <= 30)
                giftShip = new MonCalamariCruiser();
            else if (shipRoll <= 60)
                giftShip = new XWingSquadron();
            else
                giftShip = new TIEFighter();

            cout << "Random gift ship is of size " << giftShip->get_size() << ".\n";

            // Try to place it, giving option to skip if the grid is full
            char choice;
            cout << "Do you want to try placing it? (y/n): ";
            cin >> choice;

            if (tolower(choice) == 'y') {
                addGiftToGrid(giftShip);  // uses your clean helper
            } else {
                delete giftShip;
                cout << "Gift ship skipped.\n";
            }
            break;
        }

        case 2:
            cout << "Gift: Bonus Shot Next Round!\n";
            bonusShots += 1;
            break;

        case 3:
            cout << "Gift: Opponent loses one shot next round.\n";
            opponent.setShotPenalty(opponent.getShotPenalty() + 1);
            break;

        case 4:
            cout << "Gift: Opponent limited to 1 shot next round.\n";
            opponent.setShotCap(1);
            break;

        case 5:
            cout << "Gift: You get a full bonus round!\n";
            setExtraTurn(true);
            break;
    }
}


void Player::addGiftToGrid(Starship* ship) {
    char startRowChar, pattern;
    int startCol;

    bool placed = false;

    while (!placed) {
        cout << "GIFT SHIP: Enter pattern (H, V, D): ";
        cin >> pattern;

        cout << "GIFT SHIP: Enter start row[char] and column[int]: ";
        cin >> startRowChar >> startCol;

        int startRow = tolower(startRowChar) - 'a' + 1;

        if (!validCoords(startRow, startCol)) {
            cout << "Invalid coordinates. Try again.\n";
            continue;
        }

        if (deployShip(ship, startRow, startCol, pattern)) {
            placed = true;
            ship->setStatus(1);               // Now active
            myFleet.push_back(ship);          // Add to fleet
            shipCount++;
            cout << "Gift ship placed successfully!\n";
        } else {
            cout << "Could not place ship. Try again.\n";
        }
    }
}

int Player::getBonusShots() const {return bonusShots;}

void Player::setBonusShots(int n) {bonusShots = n;}

int Player::getShotPenalty() const {return shotPenalty;}

void Player::setShotPenalty(int n) {shotPenalty = n;}

int Player::getShotCap() const {return shotCap;}

void Player::setShotCap(int n) {shotCap = n;}

void Player::resetShotModifiers() {
    bonusShots = 0;
    shotPenalty = 0;
    shotCap = -1;
}

bool Player::getExtraTurn() const {
    return extraTurn;
}

void Player::setExtraTurn(bool value) {
    extraTurn = value;
}

void Player::displayLostShips() const {
    int lostDestroyers = 0, lostCruisers = 0, lostXWings = 0, lostTIEs = 0;

    for (int i = 0; i < shipCount; ++i) {
        if (myFleet[i]->get_status() == 0) {
            switch (myFleet[i]->get_size()) {
                case 5: lostDestroyers++; break;
                case 4: lostCruisers++; break;
                case 3: lostXWings++; break;
                case 1: lostTIEs++; break;
            }
        }
    }

    cout << "Lost Star Destroyer: " << lostDestroyers << "\t";
    cout << "Lost Mon Calamari Cruiser: " << lostCruisers << "\t";
    cout << "Lost X-Wing Squadron: " << lostXWings << "\t";
    cout << "Lost TIE Fighter: " << lostTIEs << endl;
}

int Player::getLostCells() const {
    int lost = 0;
    for (int i = 0; i < shipCount; ++i) {
        if (myFleet[i]->get_status() == 0) {
            lost += myFleet[i]->getOcupiedCount();
        }
    }
    return lost;
}

int Player::countLostShipsOfSize(int size) const {
    int count = 0;
    for (int i = 0; i < shipCount; ++i) {
        if (myFleet[i]->get_status() == 0 && myFleet[i]->get_size() == size) {
            count++;
        }
    }
    return count;
}
