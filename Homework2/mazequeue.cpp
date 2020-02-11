#include<iostream>
#include<queue>
using namespace std;

class Coord
{
  public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr,sc)); //Push starting coord (sr,sc) onto stack
    maze[sr][sc] = 'S'; //Indicates (S)tarting position
    while (coordQueue.empty()==false) //While the stack is not empty
    {
        Coord currentPoint = coordQueue.front();
        coordQueue.pop();
        if (currentPoint.r() == er && currentPoint.c() == ec) //If the current coordinate is equal to the ending coordinate
        {
            return true; //Then we solved the maze so return true!
        }
        else
        {
            if (currentPoint.c()+1 < nCols && maze[currentPoint.r()][currentPoint.c()+1] == '.') //If we can move east and haven't encountered it yet
            {
                coordQueue.push(Coord(currentPoint.r(), currentPoint.c()+1)); //Push (r,c+1) onto stack
                maze[currentPoint.r()][currentPoint.c()+1] = 'D'; //Update map to indicate that we (D)iscovered it
            }
            if (currentPoint.r()+1 < nRows && maze[currentPoint.r()+1][currentPoint.c()] == '.') //If we can move south and haven't encountered it yet
            {
                coordQueue.push(Coord(currentPoint.r()+1, currentPoint.c())); //Push (r+1,c) onto stack
                maze[currentPoint.r()+1][currentPoint.c()] = 'D'; //Update map to indicate that we (D)iscovered it
            }
            if (currentPoint.c()-1 > 0 && maze[currentPoint.r()][currentPoint.c()-1] == '.') //If we can move west and haven't encountered it yet
            {
                coordQueue.push(Coord(currentPoint.r(), currentPoint.c()-1)); //Push (r,c-1) onto stack
                maze[currentPoint.r()][currentPoint.c()-1] = 'D'; //Update map to indicate that we (D)iscovered it
            }
            if (currentPoint.r()-1 > 0 && maze[currentPoint.r()-1][currentPoint.c()] == '.') //If we can move north and haven't encountered it yet
            {
                coordQueue.push(Coord(currentPoint.r()-1, currentPoint.c())); //Push (r-1,c) onto stack
                maze[currentPoint.r()-1][currentPoint.c()] = 'D'; //Update map to indicate that we (D)iscovered it
            }
        }
    }
    return false; //There was no solution, so return false
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X.XXX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 4,3, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

