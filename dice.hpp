#ifndef DICE_HPP
#define DICE_HPP

#include <vector>
#include <string>
#include "raylib.h"

class DieSide{
    public:
        DieSide(int);
        int getNumber();
        void setNumber(int);
        void addToNumber(int);
    private:
        int number;
};

class Die{
    public:
        Die(std::string);
        Die(std::vector<DieSide>);
        DieSide* getSide(int);
        std::vector<DieSide> getSides();
        std::string getString();
        void setSide(int,DieSide);
        void roll();
        int getLastRoll();
    private:
        std::vector<DieSide> sides;
        int lastRoll = 0;
};

#define standardDie Die({DieSide(1),DieSide(2),DieSide(3),DieSide(4),DieSide(5),DieSide(6)})

#endif