#ifndef ZIG_ZAG_GRID_H
#define ZIG_ZAG_GRID_H

typedef struct ZigZagGrid
{
    // "Public" methods
    void(*solve)(struct ZigZagGrid *this);
    void(*destroy)(struct ZigZagGrid *this);

    // Member variables
    double a;
    double N;
    double Pt;
    double Gh;
    double Gw;
    void(*progressCallBack)(int percentageCompletedSoFar);

} ZigZagGrid;

ZigZagGrid *new_ZigZagGrid();

#endif /* ZIG_ZAG_GRID_H */
