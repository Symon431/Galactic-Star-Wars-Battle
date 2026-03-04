// Created by Simon N. Nganga - 2655389

#include "Grid.h"

#include <iostream>
using namespace std;


Grid::Grid(int rows, int cols):rows(rows),columns(cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cells[i][j] = '*';
        }
    }

}


void Grid::display() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << cells[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Grid::placeShip(int row, int column, int sizeOfShip) {
        cells[row - 1][column - 1] = sizeOfShip + '0';
}


bool Grid::checkValidity(int row, int col) {

    if (row < 1 || row > this->rows) return false;

    if (col < 1 || col > this->columns) return false;

    return true;
}

bool Grid::checkAvailability(int row, int col) {
   return cells[row -1][col - 1] == '*';
}

void Grid::markCell(char value,int row, int col) {
    cells[row - 1][col - 1] = value;
}

char Grid::getCell(int row, int col) {
    return cells[row - 1][col - 1];
}

int Grid::getRows() const {
    return rows;
}

int Grid::getCols() const {
    return columns;
}






