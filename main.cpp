
#include <iostream>
using namespace std;
#include "Player.h"
#include <ctime>


void takeTurn(Player& attacker, Player& defender);


int main() {
    srand(time(0));

    cout << "Welcome to THE GALACTIC STAR WARS BATTLE." << endl;
    cout << "--------------------------------------------------" << endl;

    char player1Name[100], player2Name[100];
    cout << "Enter player 1 name: ";
    cin >> player1Name;
    cout << "Enter player 2 name: ";
    cin >> player2Name;

    int level, row = 0, col = 0;
    do {
        cout << "Enter level (1, 2, or 3): ";
        cin >> level;

        switch (level) {
            case 1: row = 5; col = 8; break;
            case 2: row = 8; col = 10; break;
            case 3: row = 10; col = 12; break;
            default: cout << "Invalid level. Try again." << endl;
        }
    } while (level < 1 || level > 3);

    cout << "The grid size is: " << row << "x" << col << endl;

    Player Rebel(player1Name, level, row, col);
    Player Commander(player2Name, level, row, col);

    cout << player1Name << ", place your ships:" << endl;
    Rebel.addShipToGrid();
    Rebel.display_defense_grid();

    cout << player2Name << ", place your ships:" << endl;
    Commander.addShipToGrid();
    Commander.display_defense_grid();

    cout << "--------------------------------------------------" << endl;
    cout << "Battle Begins!" << endl;

    do {
        takeTurn(Rebel, Commander);
        if (Commander.hasLost()) break;

        if (Rebel.getExtraTurn()) {
            cout << Rebel.getName() << " gets a bonus turn!" << endl;
            takeTurn(Rebel, Commander);
            Rebel.setExtraTurn(false);
            if (Commander.hasLost()) break;
        }

        takeTurn(Commander, Rebel);
        if (Rebel.hasLost()) break;

        if (Commander.getExtraTurn()) {
            cout << Commander.getName() << " gets a bonus turn!" << endl;
            takeTurn(Commander, Rebel);
            Commander.setExtraTurn(false);
        }

    } while (!Rebel.hasLost() && !Commander.hasLost());

    // Announce winner
    cout << "--------------------------------------------------" << endl;
    if (Commander.hasLost()) {
        cout << Rebel.getName() << " wins the battle! " << endl;
    } else {
        cout << Commander.getName() << " wins the battle! " << endl;
    }
    cout << "Game Over." << endl;
    cout << "--------------------------------------------------" << endl;

    return 0;
}



void displayRoundStats(const Player& p1, const Player& p2) {
    cout << "---------------- Stats ----------------" << endl;

    auto showStats = [](const Player& player) {
        cout << "Player: " << player.getName() << endl;
        cout << "Total Shots: " << player.totalShots << endl;
        cout << "Hits: " << player.totalHits << endl;
        cout << "Misses: " << player.totalMisses << endl;
        cout << "Lost Cells: " << player.getLostCells() << endl;
        cout << "Lost Star Destroyer: " << player.countLostShipsOfSize(5) << endl;
        cout << "Lost Mon Calamari Cruiser: " << player.countLostShipsOfSize(4) << endl;
        cout << "Lost X-Wing Squadron: " << player.countLostShipsOfSize(3) << endl;
        cout << "Lost TIE Fighter: " << player.countLostShipsOfSize(1) << endl;
        cout << endl;
    };

    showStats(p1);
    showStats(p2);

    cout << "--------------------------------------\n" << endl;
}



void takeTurn(Player& attacker, Player& defender) {
    cout << "===> Entering the turn for " << attacker.getName() << endl;
    cout << "Here is your attack grid:" << endl;
    attacker.display_attack_grid();

    int baseShots = attacker.maximumShots();
    int maxShots = baseShots + attacker.getBonusShots() - defender.getShotPenalty();

    if (attacker.getShotCap() != -1) {
        maxShots = attacker.getShotCap();  // Hard cap overrides
    }

    if (maxShots < 1)
        maxShots = 1;  // Minimum of 1

    int shotsRequested;
    cout << attacker.getName() << " shoots now (can shoot " << maxShots << "): ";
    cin >> shotsRequested;

    while (shotsRequested > maxShots || shotsRequested < 1) {
        cout << "Invalid number of shots. Please enter between 1 and " << maxShots << ": ";
        cin >> shotsRequested;
    }

    int hits = 0, misses = 0;
    for (int i = 0; i < shotsRequested; ++i) {
        if (attacker.shootAt(defender))
            hits++;
        else
            misses++;
    }

    // Track stats
    attacker.totalShots += shotsRequested;
    attacker.totalHits += hits;
    attacker.totalMisses += misses;

    cout << "--------------------------------------------------" << endl;
    cout << "Total Shots: " << shotsRequested << endl;
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << misses << endl;
    cout << "--------------------------------------------------" << endl;

    cout << attacker.getName() << "'s attack grid:" << endl;
    attacker.display_attack_grid();

    // Gift logic
    if (hits >= 2) {
        int roll = rand() % 100 + 1;
        if (roll <= 30) {
            cout << attacker.getName() << " has earned a GIFT!\n";
            attacker.receiveGiftFromRound(defender);
        } else {
            cout << attacker.getName() << " just missed the gift roll.\n";
        }
    }

    // Reset modifiers
    attacker.resetShotModifiers();
    defender.resetShotModifiers();

    // Show updated round stats
    displayRoundStats(attacker, defender);
}

