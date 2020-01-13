#ifndef Game_h
#define Game_h

#include <string>

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nVampires);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
    //The next two functions were originally auxiliary functions, but will now be repurposed for use in Game.cpp
    bool recommendMove(const Arena& a, int r, int c, int& bestDir);
    int computeDanger(const Arena& a, int r, int c);
};


#endif /* Game_h */
