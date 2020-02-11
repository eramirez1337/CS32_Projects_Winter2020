#include "newMap.h"
#include<iostream>

Map::Map(){ //Constructor
    m_numberElements = 0;
    m_customMaxNumberElements = DEFAULT_MAX_ITEMS;
    m_map = new mapDataMembers[DEFAULT_MAX_ITEMS];
}

Map::Map(int customMaxItems){ //Constructor when overloaded
    if (customMaxItems < 0) {
        exit(1); //Had to look this up since I had to somehow check if the user inputs a negative value
    }
    m_numberElements = 0;
    m_customMaxNumberElements = customMaxItems;
    m_map = new mapDataMembers[customMaxItems];
}

Map::~Map(){ //Destructor
    delete [] m_map;
}

Map::Map(const Map &other){ //Copy Constructor
    m_numberElements = other.m_numberElements;
    m_customMaxNumberElements = other.m_customMaxNumberElements;
    m_map = new mapDataMembers[m_customMaxNumberElements];
    for (int i = 0; i < m_customMaxNumberElements; i++) {
        m_map[i] = other.m_map[i];
    }
}

Map& Map::operator=(const Map &source){ //Assignment Operator
    if (this == &source) //Check yourself before you wreck yourself, kids!
        return *this;
    delete [] m_map; //NO MEMORY LEAK PLEASE AND THANKS
    m_numberElements = source.m_numberElements;
    m_customMaxNumberElements = source.m_customMaxNumberElements;
    m_map = new mapDataMembers[m_customMaxNumberElements];
    for (int i = 0; i < m_customMaxNumberElements; i++) {
        m_map[i] = source.m_map[i];
    }
    return *this;
}

bool Map::empty() const{
    return m_numberElements == 0;
}

int Map::size() const{
    return m_numberElements;
}

bool Map::insert(const KeyType &key, const ValueType &value){
    for (int i = 0; i < m_numberElements; i++) {
        if (m_map[i].m_key == key) {
            return false; //Iterate through the whole array to check if the key already exists
        }
    }
    if (size() == DEFAULT_MAX_ITEMS)
        return false; //If we reached the cap already...well I don't know why you keep adding more. Stop it!
    
    mapDataMembers newData;
    newData.m_key = key;
    newData.m_value = value;
    m_map[size()] = newData;
    m_numberElements++;
    return true; //Otherwise, create a new data member pair, add it to the array, and increase the counter
}

bool Map::update(const KeyType &key, const ValueType &value){
    for (int i = 0; i < m_numberElements; i++) {
        if (m_map[i].m_key == key) {
            m_map[i].m_value = value;
            return true; //Check for the key and update the value once it is found change the value
        }
    }
    return false; //ERROR 404: Your key is not found
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value){
    for (int i = 0; i < m_numberElements; i++) {
        if (m_map[i].m_key == key) {
            m_map[i].m_value = value;
            return true; //Check for the key and update the value once it is found change the value
        }
    }
    if (size() == DEFAULT_MAX_ITEMS)
        return false; //If we reached the cap already...well I don't know why you keep adding more. Stop it!
    
    mapDataMembers newData;
    newData.m_key = key;
    newData.m_value = value;
    m_map[size()] = newData;
    m_numberElements++;
    return true; //Otherwise, create a new data member pair, add it to the array, and increase the counter
    //Woah, don't you get a sense of deja vu? It's almost like this function is an amalgamation of the previous two...
}

bool Map::erase(const KeyType &key){
    for (int i = 0; i < m_numberElements; i++) {
        if (m_map[i].m_key == key) {
            for (int j = i; j < size()-i; j++) {
                m_map[j] = m_map[j+1];
            }
            m_numberElements--;
            return true; //Essentially, push all of the elements one to the left until the targeted element is pushed to the end, then set the size of the map to be one less so that the targeted element is "deleted" from the array
        }
    }
    return false; //Key doesn't exist
}

bool Map::contains(const KeyType &key) const{
    for (int i = 0; i < size(); i++) {
        if (m_map[i].m_key == key) {
            return true; //If we found the key, hooray, the map contains it
        }
    }
    return false; //Nah mate, we ain't found it
}


bool Map::get(const KeyType &key, ValueType &value) const{
    for (int i = 0; i < size(); i++) {
        if (m_map[i].m_key == key) {
            value = m_map[i].m_value;
            return true; //If we can find the key in the map, we will change the value that we put in to the value that the map contains
        }
    }
    return false; //Wrong key, dude
}

bool Map::get(int i, KeyType &key, ValueType &value) const{
    if (i >= 0 && i < size()) {
        key = m_map[i].m_key;
        value = m_map[i].m_value;
        return true; //Like the previous get function, except we are setting it up so that if the get function is used in a loop, we can set it into a temporary array and copy the data members in order
    }
    return false; //Something went wrong with i
}

void Map::swap(Map &other){
    Map cartographer = *this;
    *this = other;
    other = cartographer; //Completes the swap of maps
    int holdMyNumElements = m_numberElements;
    m_numberElements = other.m_numberElements;
    other.m_numberElements = holdMyNumElements; //Completes the swap of number of elements
    int carryOnMyMaxNumSon = m_customMaxNumberElements;
    m_customMaxNumberElements = other.m_customMaxNumberElements;
    other.m_customMaxNumberElements = carryOnMyMaxNumSon; //Completes the swap of max elements
}
