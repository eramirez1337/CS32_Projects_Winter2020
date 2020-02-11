//#include<iostream>
//#include<string>
//using namespace std;
//FOR TESTING PURPOSES, INCLUDE THESE HEADERS

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = 'S'; //Marked 'S' for starting position
    if (maze[sr][sc+1] == '.') { //If east available
        if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec)) //Check path going east
            return true;
    }
    if (maze[sr+1][sc] == '.') { //If south available
        if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec)) //Check path going south
            return true;
    }
    if (maze[sr][sc-1] == '.') { //If west available
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec)) //Check path going west
            return true;
    }
    if (maze[sr-1][sc] == '.') { //If north available
        if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec)) //Check path going north
            return true;
    }
    return false;
}

//int main()
//{
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X...X..X.X",
//        "X.XXX....X",
//        "X.X.XXXX.X",
//        "XXX......X",
//        "X...X.XX.X",
//        "X.X.X..X.X",
//        "X.XXXX.X.X",
//        "X..X...X.X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10,10, 4,3, 1,8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}
