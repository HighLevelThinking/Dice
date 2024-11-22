#include "dice.hpp"

Die::Die(std::vector<DieSide> setupSides){
    for (auto side :setupSides){
        sides.push_back(side);
    }
}
DieSide* Die::getSide(int idx){
    return &sides[idx];
}
std::vector<DieSide> Die::getSides(){
    return sides;
}
void Die::setSide(int idx,DieSide side){
    sides[idx] = side;
}
void Die::roll(){
    lastRoll = sides[GetRandomValue(0,5)].getNumber();
}
int Die::getLastRoll(){
    return lastRoll;
}

DieSide::DieSide(int initalNumber){
    number = initalNumber;
}
int DieSide::getNumber(){
    return number;
}
void DieSide::setNumber(int newNumber){
    number = newNumber;
}
void DieSide::addToNumber(int addingValue){
    number += addingValue;
}