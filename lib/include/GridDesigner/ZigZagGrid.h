#ifndef ZIG_ZAG_GRID_H
#define ZIG_ZAG_GRID_H

typedef struct ZigZagGrid
{
    /* "Public" methods */

    /* Returns 1 if the constraings could be met within the allowed seach time. 0 if not. */
    int(*solve)(struct ZigZagGrid *this);
    void(*destroy)(struct ZigZagGrid *this);
    void(*printToStdOut)(struct ZigZagGrid *this);
    // Member variables
    double a;
    double N;
    double Pt;
    double Gh;
    double Gw;
    double T;
    void(*progressCallBack)(int percentageCompletedSoFar);

    double Tw;   //Used for rendering
    double Tww;  //Used for rendering
    double Tiw;  //Used for rendering
    double Tih;  //Used for rendering


} ZigZagGrid;

ZigZagGrid *new_ZigZagGrid();

#endif /* ZIG_ZAG_GRID_H */
