// Created by Simon N. Nganga - 2655389

#ifndef GRID_H
#define GRID_H

class Grid {
private:
    char cells[12][12];
    int rows;
    int columns;

public:
    Grid(int , int );
    void display() const;
    void placeShip(int, int ,int );
    bool checkValidity(int, int);
    bool checkAvailability(int , int);
    void markCell(char , int , int );
    char getCell(int , int );
    int getRows() const;
    int getCols() const;
};



#endif //GRID_H
