#include "../include/GridDesigner/ZigZagGrid.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define Pi 3.141592654
#define RADIANS(v) ((v)*Pi/180)

static int ZigZagGrid_solve(ZigZagGrid *this)
{
    double highestGuess, lowestGuess, guess, Tww, Tih, Tiw, Tw, calculagedGw, delta;

    highestGuess = 90;
    lowestGuess = 0;

    int step = 0;
    int maximumSteps = 50;
    int exceededMaximumSteps = 1;
    while((step < maximumSteps))
    {
        guess = (highestGuess + lowestGuess) / 2;
        Tww = this->Pt/sin(RADIANS(guess));
        Tih = this->Gh - 2 * this->Pt;
        Tiw = (this->Gh - 2 * this->Pt)/tan(RADIANS(guess))*2;
        Tw =Tiw + 2 * Tww;

        calculagedGw = this->N * Tw;
        delta = calculagedGw - this->Gw;
        step++;

        if(fabs(delta) <= this->T)
        {
            exceededMaximumSteps = 0;
            break;
        }

        if(delta < 0)
        {
            highestGuess = guess;
        }
        else
        {
            lowestGuess = guess;
        }
    }
    this->a = guess;

    return ! exceededMaximumSteps;
}

static void ZigZagGrid_destroy(ZigZagGrid *this)
{
    free(this);
    this = NULL;
}



static void ZigZagGrid_init(ZigZagGrid *zzg)
{

    zzg->solve = &ZigZagGrid_solve;
    zzg->destroy = &ZigZagGrid_destroy;

    zzg->a = 0;
    zzg->N = 0;
    zzg->Pt = 0;
    zzg->Gh = 0;
    zzg->Gw = 0;
    zzg->progressCallBack = NULL;
}

ZigZagGrid *new_ZigZagGrid()
{
    ZigZagGrid* r = (ZigZagGrid*)malloc(sizeof(ZigZagGrid));
    ZigZagGrid_init(r);
    return r;
}
