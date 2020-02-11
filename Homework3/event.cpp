//#include <iostream>
//#include <string>
//using namespace std;
//FOR TESTING PURPOSES, INCLUDE HEADERS

class Event {
public:
    Event(string name): m_name(name){}
    virtual ~Event(){};
    virtual string name() const
    {
        return m_name;
    }
    virtual string need() const
    {
        return "";
    };
    virtual bool isSport() const
    {
        return true;
    }
private:
    string m_name;
    bool m_isSport;
};

class BasketballGame: public Event {
public:
    BasketballGame(string name): Event(name){}
    ~BasketballGame()
    {
        cout << "Destroying the " << name() << " basketball game." << endl;
    }
    string need() const
    {
        return "hoops";
    }
};

class HockeyGame: public Event {
public:
    HockeyGame(string name): Event(name){}
    ~HockeyGame()
    {
        cout << "Destroying the " << name() << " hockey game." << endl;
    }
    string need() const
    {
        return "ice";
    }
};

class Concert: public Event {
public:
    Concert(string name, string genre): Event(name)
    {
        m_genre = genre;
    }
    ~Concert()
    {
        cout << "Destroying the " << name() << " " << m_genre << " concert." << endl;
    }
    string need() const
    {
        return "a stage";
    }
    bool isSport() const
    {
        return false;
    }
private:
    string m_genre;
};

//void display(const Event* e)
//{
//    cout << e->name() << ": ";
//    if (e->isSport())
//    cout << "(sport) ";
//    cout << "needs " << e->need() << endl;
//}
//
//int main()
//{
//    Event* events[4];
//    events[0] = new BasketballGame("Lakers vs. Suns");
//      // Concerts have a name and a genre.
//    events[1] = new Concert("Banda MS", "banda");
//    events[2] = new Concert("KISS", "hard rock");
//    events[3] = new HockeyGame("Kings vs. Flames");
//
//    cout << "Here are the events." << endl;
//    for (int k = 0; k < 4; k++)
//    display(events[k]);
//
//      // Clean up the events before exiting
//    cout << "Cleaning up." << endl;
//    for (int k = 0; k < 4; k++)
//    delete events[k];
//}
