#include "../include/GridDesigner/ZigZagGrid.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define Pi 3.141592654
#define RADIANS(v) ((v)*Pi/180)

static void ZigZagGrid_solve(ZigZagGrid *this)
{
    double currentLowGuess, currentHighGuess, currentGuess, Tww, Tih, Tiw, Tw, calculagedGw, delta;

    currentLowGuess = 1;
    currentHighGuess = 89;
    currentGuess = 79.2;

    Tww = this->Pt/sin(RADIANS(currentGuess));
    Tih = this->Gh - 2 * this->Pt;
    Tiw = (this->Gh - 2 * this->Pt)/tan(RADIANS(currentGuess))*2;
    Tw =Tiw + 2 * Tww;

    calculagedGw = this->N * Tw;
    delta = calculagedGw - this->Gw;

    printf(" ------------------ \n");
    printf("          Tww : %f\n", Tww);
    printf("          Tih : %f\n", Tih);
    printf("          Tiw : %f\n", Tiw);
    printf("          Tw  : %f\n", Tw);
    printf("          Tww : %f\n", Tww);
    printf("Calculated Gw : %f\n", calculagedGw);
    printf("        delta : %f\n", delta);



    this->a = currentGuess;
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
