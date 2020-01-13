#include <stdio.h>
#include <iostream>
using namespace std;

#include "History.h"

History::History(int nRows, int nCols)
{
    hist_rows = nRows;
    hist_cols = nCols;

    for (int i=0; i < hist_rows; i++)
    {
        for (int j=0; j < hist_cols; j++)
        {
            m_grid[i][j] = 0; //Since there would be no poisoned vampires set, there is no moves to track; therefore, set the grid values to 0's
        }
    }
}

bool History::record(int r, int c){
    if(r > hist_rows || c > hist_cols || r < 1 || c < 1)
        return false;
    m_grid[r-1][c-1]++;
    return true;
}

void History::display() const {
    char displayGrid[MAXROWS][MAXCOLS]; //Set up a new grid to display
    int r, c;

    for (r=1; r <= hist_rows; r++)
        for (c=1; c <= hist_cols; c++) {
            if (m_grid[r-1][c-1] == 0) //Set each point where the vampires haven't ingested a poison vial and draw a dot
                displayGrid[r-1][c-1] = '.';
            else if ( m_grid[r-1][c-1] >= 26 ) //If 26 or more vampires ate a vial at that position, indicate it with a Z
                displayGrid[r-1][c-1] = 'Z';
            else
                displayGrid[r-1][c-1] = 'A'-1 + m_grid[r-1][c-1]; //Otherwise, choose a letter that corresponds to the value at that grid position

        }
    //Draw the grid
    clearScreen();
    for (r=1; r <= hist_rows; r++)
    {
        for (c=1; c <= hist_cols; c++)
                cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
}
