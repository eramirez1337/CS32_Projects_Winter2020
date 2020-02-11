#include "Map.h"

#include<iostream>
using namespace std;

Map::Map()
{
    head = nullptr; //This program will not be using dummy nodes, so I will simply have head be nullptr
    m_listSize = 0; //Nothing in the list yet, so set list size to 0
}

Map::~Map()
{
    Node *p = head; //Have a pointer point to the start of the list
    while (p != nullptr)
    {
        Node *n = p->next; //Circumvent the target node
        delete p; //Delete target
        p = n; //Target the next node (or nullptr if we reach the end)
    }
}

Map::Map(const Map &other)
{
    m_listSize = other.m_listSize; //Set the list size equal to the source's list size
    head = nullptr; //Initialize a head pointer to null
    for (int i = 0; i < m_listSize; i++)
    {
        KeyType keyGetter;
        ValueType valueObtainer;
        other.get(i, keyGetter, valueObtainer);
        insert(keyGetter, valueObtainer); //This section will essentially copy and paste each source node into the current node using the get and insert functions
    }
}

Map& Map::operator=(const Map &other)
{
    if (this == &other) //Check yourself before you wreck yourself
        return *this;
    Map holder(other); //Copy construct a temporary list holder from the source
    swap(holder); //Take our current list and swap values with the holder
    return *this; //After this is executed, holder will be deconstructed, and we will end up with our desired results (thank god for variable scopes)
}

bool Map::empty() const
{
    return m_listSize==0; //If there is nothing in the list, this should result true
}

int Map::size() const
{
    return m_listSize; //Simply return the size of the list after incrementations from other functions
}

bool Map::insert(const KeyType &key, const ValueType &value)
{
    if (contains(key)) //If our list already has the value, then why would you want to insert it again? Wrong function, buddy. Use update. Geez, did you even read the specs, user?! It's people like you who mess up OUR programs and give us headaches for days trying to fix YOUR mistakes!
        return false; //Ughhh... anyway
    Node *p = new Node; //Allocate a new node
    p -> key = key;
    p -> value = value; //Set the values in place
    p -> next = head; //Link the new node to the current top node
    p -> previous = nullptr; //For now, set previous to nullptr. We will use it in the erase function to look at the addresses of other nodes
    head = p; //Now set the head pointer to the new top, our new node
    m_listSize++; //We have added a new node, so increase the size
    return true; //Huzzah, we made it!
}

bool Map::update(const KeyType &key, const ValueType &value)
{
    Node *p = head;
    while (p != nullptr) //Begin traversal
    {
        if (p -> key == key) //Let's find the key, much like real life
        {
            p -> value = value;
            return true; //If we find it, update the value and return true
        }
        p = p -> next; //Continue through the list if we haven't found our key
    }
    return false; //At this point, you're probably wondering "Where the hell are my keys?" Well, user, it would appear that you never even inserted it in the first place, so we returned false
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (update(key, value)) //Use the preexisting update function and check if the key exists; update the value if it does
        return true;
    else
        insert(key, value); //In the case that the key was not found, insert a new node to the list
    return true;
}

bool Map::erase(const KeyType& key)
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->key == key) //Locate the key in our list
        {
            if (p->previous == nullptr) //If we are at the start of our list...
            {
                head = p -> next; //Have the head of the list be whatever the target node's next is pointing to
            }
            else if (p -> next == nullptr) //If we are at the end of the list...
            {
                Node *n = p -> previous; //Create a node pointer that points to the previous node
                n -> next = nullptr; //The previous node's next pointer now points to null, skipping over the target node
            }
            else
            {
                Node *n = p -> previous;
                n -> next = p -> next; //Otherwise, skip over the target node like in the previous case
            }
            delete p;
            m_listSize--;
            return true; //Delete the target node, decrease the size
        }
        else
        {
            Node *holder = p;
            p = p -> next;
            p -> previous = holder; //If the key has not been found, then remember the previous node and move on
        }
    }
    return false; //Key was not found, we can't erase what doesn't exist
}

bool Map::contains(const KeyType& key) const
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p -> key == key)
            return true; //If we found the key, then we found the key
        p = p -> next; //Otherwise, keep searching
    }
    return false; //The list does not have that value
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    if (contains(key)) //If the list has the key...
    {
        Node *p = head;
        while (p -> key != key) //Traverse through the list until you found the key
        {
            p = p -> next;
        }
        value = p -> value;
        return true; //Get the value that the key contains
    }
    return false; //Value could not be retrieved because it doesn't exist
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i >= 0 && i < size()) //When this function is implemented in a loop for another function, if the current iteration count is within bounds, then we can get the key AND value at that position
    {
        Node *p = head;
        for (int j = 0; j < i; j++) //We have already determined where we need to stop, so no need to check if the key argument exists within the list
            p = p -> next;
        key = p -> key;
        value = p -> value; //Set the arguments equal to the values at the current list's position
        return true;
    }
    return false; //The iteration counter is out of bounds. Therefore, we can't get a key or value
}

void Map::swap(Map& other)
{
    Node *n = head; //Allocate a  temporary pointer that points to the head of our list
    int temp = m_listSize; //Hold our map size
    head = other.head; //Have our head pointer point to the other list
    other.head = n; //Have the other map head pointer point to our list using the temporary pointer
    m_listSize = other.m_listSize;
    other.m_listSize = temp; //Swap size values
}

//Non-class functions
bool combine(const Map& m1, const Map& m2, Map& result)
{
    Map temp = m1;
    result.swap(temp); //Initialize result with the first group we need to combine
    bool repeatNotDetected = true; //Initialize a flag that will detect if a key has been repeated
    for (int i = 0; i < m2.size(); i++) //Traverse through the other map's list
    {
        KeyType key2;
        ValueType value2;
        m2.get(i, key2, value2); //Obtain the values at each node of the list
        if (result.contains(key2)) //If our resultant map has the key already...
        {
            ValueType value1;
            result.get(key2, value1); //Get the value of the resultant map's key
            if (value1 != value2) //If either key's value does not match the other...
            {
                repeatNotDetected = false; //A repeat was detected, set flag to false
                result.erase(key2); //We will delete the key and value from our resultant map
            }
        }
        result.insert(key2, value2); //Insert the key and value into the resultant map
    }
    return (repeatNotDetected); //This function will still return the resultant map, this return value just states if we had to delete a node in the process
}

void reassign(const Map& m, Map& result)
{
    Map eraseResult; //So what if result references the same map as m? Well, no other choice but to erase it
    result = eraseResult; //Insurance policy secured, as eraseResult is constructed to be empty!
    if (m.size() <= 1) {
        result = m;
        return; //If the map is empty or only has one node, then there is no reassigning to do; we are done
    }
    Map group1;
    Map group2; //Create two lists that will separate the map list into two
    if (m.size()%2 == 0)
    {
        for (int i = 0; i < (m.size()/2); i++)  //Ex: size 2, group1 is 0, group 2 is 1 (if we think like arrays)
        {
            KeyType key;
            ValueType value;
            m.get(i, key, value);
            group1.insert(key, value); //Get the values of the map up until we reach the midpoint for the first half and insert it into our first group
        }
        for (int i = m.size()/2; i < m.size(); i++)
        {
            KeyType key;
            ValueType value;
            m.get(i, key, value);
            group2.insert(key, value); //Like above, except we start at the midpoint and end at the end of the map list, and allocate the values into the second group
        }
        for (int i = 0; i < group1.size(); i++)
        {
            KeyType key1, key2;
            ValueType value1, value2;
            group1.get(i, key1, value1);
            group2.get(i, key2, value2);
            group1.update(key1, value2);
            group2.update(key2, value1); //Swap the first values of the first nodes in both groups, then the second, then the third, etc.
        }
        combine(group1, group2, result);
        return; //Combine groups and return the result
    }
    else
    {
        for (int i = 0; i < (m.size()/2); i++) //Ex: size is 3 -> group1 is 0, group2 is 1, group3 (our lonely third wheel in this party) is 3. 3/2 is 1.5, but we drop the .5 since we divide ints, so it becomes 1
        {
            KeyType key;
            ValueType value;
            m.get(i, key, value);
            group1.insert(key, value);
        }
        for (int i = m.size()/2; i < m.size()-1; i++) //Save the last element for group3
        {
            KeyType key;
            ValueType value;
            m.get(i, key, value);
            group2.insert(key, value);
        }
        for (int i = 0; i < group1.size(); i++) {
            KeyType key1, key2;
            ValueType value1, value2;
            group1.get(i, key1, value1);
            group2.get(i, key2, value2);
            group1.update(key1, value2);
            group2.update(key2, value1);
        }
        Map tempMap;
        combine(group1, group2, tempMap); //Combine our first two groups into a temporary map
        
        Map group3;
        KeyType keyThirdWheel;
        ValueType valueThirdWheel;
        m.get(m.size()-1, keyThirdWheel, valueThirdWheel); //The key and value of the third group have been updated, so we can use these variables for later purposes
        group3.insert(keyThirdWheel, valueThirdWheel); //Here, we get the key and value of the last element of the original map and put it into the third group since we have an odd number of nodes
        
        KeyType keyPair;
        ValueType valuePair;
        tempMap.get(0, keyPair, valuePair); //Obtain the first node's key and values of the temp map
        tempMap.update(keyPair, valueThirdWheel);
        group3.update(keyThirdWheel, valuePair); //Swap the values between the first and last nodes of the original map m; now all values are reassigned!
        combine(tempMap, group3, result);
        return; //Combine and return
    }
}
