#include "CarMap.h"

#include<iostream>

CarMap::CarMap():m_carMap(){} //All we really need to do for the constructor is include the carmap member in its initializer list since we will be dealing with its map

bool CarMap::addCar(KeyType license){
    return (m_carMap.insert(license, 0)); //If we can add a car with the license and mileage of 0, then we added it, as signified when this function returns true
}

double CarMap::miles(KeyType license) const{
    ValueType mileCounter;
    if (m_carMap.get(license, mileCounter)) {
        return mileCounter; //Get the mileage of the cars on the map and return that value
    }
    return -1; //We couldn't find your car because you gave the wrong license plate number
}

bool CarMap::drive(KeyType license, ValueType distance){
    if (m_carMap.contains(license) || distance < 0) {
        return false;
    }
    m_carMap.update(license, miles(license) + distance);
    return true;
}

int CarMap::fleetSize() const{
    return m_carMap.size();
}

void CarMap::print() const{
    for (int i = 0; i < m_carMap.size(); i++) {
        KeyType license;
        ValueType miles;
        m_carMap.get(i, license, miles);
        std::cout << license << " " << miles << std::endl;
    }
}

