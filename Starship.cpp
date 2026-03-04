// Created by Simon N. Nganga - 2655389


#include "Starship.h"

StarDestroyer::StarDestroyer() {
    size = 5;
    hits_to_destroy = 4;
    laser_bursts = 3;
    status = 0;
}

int StarDestroyer::get_hits_to_destroy() const{return hits_to_destroy;}

int StarDestroyer::get_size() const{return size;}

int StarDestroyer::get_laser_bursts() const{return laser_bursts;}

int StarDestroyer::get_status() const{return status;}

void StarDestroyer::setStatus(int status) {this->status = status;}

void StarDestroyer::set_hits_to_destroy(int hits) {
    this->hits_to_destroy = hits_to_destroy - hits;
    if (hits_to_destroy < 0) {
        hits_to_destroy = 0;
    }
}

MonCalamariCruiser::MonCalamariCruiser() {
    size = 4;
    hits_to_destroy = 3;
    laser_bursts = 4;
    status = 0;
}

void MonCalamariCruiser::setStatus(int status) {this->status = status;}

void MonCalamariCruiser::set_hits_to_destroy(int hits) {
    this->hits_to_destroy = hits_to_destroy - hits;
    if (hits_to_destroy < 0) {
        hits_to_destroy = 0;
    }
}

int MonCalamariCruiser::get_hits_to_destroy() const {return hits_to_destroy;}

int MonCalamariCruiser::get_size() const {return size;}

int MonCalamariCruiser::get_laser_bursts() const {return laser_bursts;}

int MonCalamariCruiser::get_status() const {return status;}

XWingSquadron::XWingSquadron() {
    size = 3;
    hits_to_destroy = 2;
    laser_bursts = 2;
    status = 0;
}

void XWingSquadron::setStatus(int status) {this->status = status;}

void XWingSquadron::set_hits_to_destroy(int hits) {
    this->hits_to_destroy = hits_to_destroy - hits;
    if (hits_to_destroy < 0) {
        hits_to_destroy = 0;
    }
}

int XWingSquadron::get_hits_to_destroy() const {return hits_to_destroy;}

int XWingSquadron::get_size() const {return size;}

int XWingSquadron::get_laser_bursts() const {return laser_bursts;}

int XWingSquadron::get_status() const {return status;}


TIEFighter::TIEFighter() {
    size = 1;
    hits_to_destroy = 1;
    laser_bursts = 1;
    status = 0;
}

void TIEFighter::setStatus(int status) {this->status = status;}

void TIEFighter::set_hits_to_destroy(int hits) {
    this->hits_to_destroy = hits_to_destroy - hits;
    if (hits_to_destroy < 0) {
        hits_to_destroy = 0;
    }
}

int TIEFighter::get_hits_to_destroy() const {return hits_to_destroy;}

int TIEFighter::get_size() const {return size;}

int TIEFighter::get_laser_bursts() const {return laser_bursts;}

int TIEFighter::get_status() const {
    return status;
}

void Starship::addCell(int row, int col) {
    occupiedRows.push_back(row);
    occupiedCols.push_back(col);
}

bool Starship::occupies(int row, int col) const {
    for (int i = 0; i < occupiedRows.size(); ++i) {
        if (occupiedRows[i] == row && occupiedCols[i] == col)
            return true;
    }
    return false;
}


void Starship::registerHit() {
    hits_to_destroy--;
    if (hits_to_destroy <= 0) {
        hits_to_destroy = 0;
        status = 0;
    }
}

int Starship::getOccupiedCol(int i) const {
    return occupiedCols[i];
}

int Starship::getOccupiedRow(int i) const {
    return occupiedRows[i];
}

int Starship::getOcupiedCount() const {return occupiedRows.size();}



