#ifndef History_h
#define History_h

#include "globals.h"

class History
{
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
  private:
    int hist_rows;
    int hist_cols;
    int m_grid[MAXROWS][MAXCOLS];
};

#endif /* History_h */
