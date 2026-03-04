// Created by Simon N. Nganga - 2655389

#ifndef STARSHIP_H
#define STARSHIP_H

#include <vector>
using std::vector;

class Starship {
protected:
    int size;
    int hits_to_destroy;
    int laser_bursts;
    int status;
    vector<int> occupiedRows;
    vector<int> occupiedCols;

public:
  virtual void setStatus(int ) = 0;
    virtual void set_hits_to_destroy(int) = 0;
    virtual int get_hits_to_destroy() const = 0;
    virtual int get_size() const = 0;
    virtual int get_laser_bursts() const = 0;
    virtual int get_status() const = 0;
    void addCell(int , int );
    bool occupies(int , int )const;
    void registerHit();
    int getOccupiedRow(int )const;
    int getOccupiedCol(int )const;
    int getOcupiedCount()const;

};

class StarDestroyer : public Starship {

public:
    StarDestroyer();
    void setStatus(int );
    void set_hits_to_destroy(int );
    int get_hits_to_destroy() const;
    int get_size() const;
    int get_laser_bursts() const;
    int get_status() const;
};

class MonCalamariCruiser : public Starship {

public:
    MonCalamariCruiser();
    void setStatus(int );
    void set_hits_to_destroy(int );
    int get_hits_to_destroy() const;
    int get_size() const;
    int get_laser_bursts() const;
    int get_status()const;
};


class XWingSquadron : public Starship {

public:
    XWingSquadron();
    void setStatus(int );
    void set_hits_to_destroy(int );
    int get_hits_to_destroy() const;
    int get_size() const;
    int get_laser_bursts()const;
    int get_status()const;

};

class TIEFighter : public Starship {

public:
    TIEFighter();
    void setStatus(int );
    void set_hits_to_destroy(int );
    int get_hits_to_destroy() const;
    int get_size() const;
    int get_laser_bursts() const;
    int get_status() const;

};

#endif //STARSHIP_H
