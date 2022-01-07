#include "../include/GridDesigner/ZigZagGrid.h"
#include "../include/GridDesigner/SvgRenderer.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

typedef struct Point2D
{
    float x;
    float y;
} Point2D;
#define printP2D(p) p.x,p.y


int maxOf(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    return b;
}

int charactersNeededFor(float value, int decimals)
{
    return (int)log10(value)+1+decimals;
}

int characterCountNeededForFloat(ZigZagGrid *zzg)
{
    int decimals = 2;
    int charatersNeeded = 0;
    charatersNeeded = maxOf(charatersNeeded, charactersNeededFor(zzg->a, decimals));
    charatersNeeded = maxOf(charatersNeeded, charactersNeededFor(zzg->N, decimals));
    charatersNeeded = maxOf(charatersNeeded, charactersNeededFor(zzg->Pt, decimals));
    charatersNeeded = maxOf(charatersNeeded, charactersNeededFor(zzg->Gh, decimals));
    charatersNeeded = maxOf(charatersNeeded, charactersNeededFor(zzg->Gw, decimals));
    charatersNeeded = maxOf(charatersNeeded, charactersNeededFor(zzg->T, decimals));
    charatersNeeded = maxOf(charatersNeeded, charactersNeededFor(zzg->Tw, decimals));
    charatersNeeded = maxOf(charatersNeeded, charactersNeededFor(zzg->Tww, decimals));
    charatersNeeded = maxOf(charatersNeeded, charactersNeededFor(zzg->Tiw, decimals));

    charatersNeeded = charatersNeeded + 1; /* For the decimal comma */
    charatersNeeded = decimals; /* For the decimals*/

    return charatersNeeded;
}


void renderAsSVG(ZigZagGrid *zzg, char **dest)
{
    float width = zzg->Gw;
    float height = zzg->Gh;

    int decimals = 2;


    const char *headerTemplate =
            "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
                "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%.2fmm\" height=\"%.2fmm\" viewBox=\"0 0 %.2f %.2f\" version=\"1.1\">\n"
                "   <style>\n"
                "       path { fill: none; stroke: black; stroke-width: 0.1mm; }\n"
                "   </style>\n";

    char *svgHeader = malloc((strlen(headerTemplate)+charactersNeededFor(width, decimals)*2+charactersNeededFor(height,decimals)*2)*sizeof(char));
    sprintf(svgHeader, headerTemplate,
                width, height, width, height);

/*
    Construct the outer path consisting of the ten points below
 (1)───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────(2)     ┬       ┬
 │                                                                                                                                          │      │ Pt    │
 │                                                                                                                                          │      │       │
(10)────────────(9)            ────────────────────────────────              ─────────────────────────────────            (4)──────────────(3)     ┴       │      ┬
                /      /\      \                              /      /\      \                               /      /\      \                              │      │
               /      /  \      \                            /      /  \      \                             /      /  \      \                             │      │
              /      /    \      \                          /      /    \      \                           /      /    \      \                            │      │
             /      /      \      \                        /      /      \      \                         /      /      \      \                           │      │
            /      /        \      \                      /      /        \      \                       /      /        \      \                          │      │
           /      /          \      \                    /      /          \      \                     /      /          \      \                         │      │
          /      /            \      \                  /      /            \      \                   /      /            \      \                        │      │
         /      /              \      \                /      /              \      \                 /      /              \      \                       │      │
        /      /                \      \              /      /                \      \               /      /                \      \                      │ Gh   │ Tih (= Gh-2*Pt)
       /      /        1         \      \            /      /        2         \      \             /      /        N         \      \                     │      │
      /      /                    \      \          /      /                    \      \           /      /                    \      \                    │      │
     /      /                      \      \        /      /                      \      \         /      /                      \      \                   │      │
    /      /                        \      \      /      /                        \      \       /      /                        \      \                  │      │
   /      /                          \      \    /      /                          \      \     /      /                          \      \                 │      │
  /      /                            \      \  /      /                            \      \   /      /                            \      \                │      │
 /      /  a                        a  \      \/      /                              \      \ /      /                              \      \               │      │
(8)      ────────────────────────────────              ────────────────────────────────               ────────────────────────────────      (5)    ┬       │      ┴
 │                                                                                                                                          │      │ Pt    │
 │                                                                                                                                          │      │       │
(7)─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────(6)    ┴       ┴

*/

    Point2D p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;
    float pt = zzg->Pt;
    float tw = zzg->Tw;
    float tww = zzg->Tww;
    float tiw = zzg->Tiw;

    p1.x = 0;
    p1.y = 0;

    p2.x = width;
    p2.y = 0;

    p3.x = width;
    p3.y = pt;

    p4.x = width-tiw/2;
    p4.y = pt;

    p5.x = width;
    p5.y = height-pt;

    p6.x = width;
    p6.y = height;

    p7.x = 0;
    p7.y = height;

    p8.x = 0;
    p8.y = height-pt;

    p9.x = tiw/2;
    p9.y = pt;

    p10.x = 0;
    p10.y = pt;




    const char *outerPathTemplate = "   <path id=\"outerPath\" d=\""
                                    "M %.2f, %.2f "
                                    "L %.2f, %.2f "
                                    "L %.2f, %.2f "
                                    "L %.2f, %.2f "
                                    "L %.2f, %.2f "
                                    "L %.2f, %.2f "
                                    "L %.2f, %.2f "
                                    "L %.2f, %.2f "
                                    "L %.2f, %.2f "
                                    "L %.2f, %.2f "
                                    "Z\"/>\n";
    char *outerPath = malloc((strlen(outerPathTemplate)+20*characterCountNeededForFloat(zzg))*sizeof(char));
    sprintf(outerPath , outerPathTemplate
            ,printP2D(p1)
            ,printP2D(p2)
            ,printP2D(p3)
            ,printP2D(p4)
            ,printP2D(p5)
            ,printP2D(p6)
            ,printP2D(p7)
            ,printP2D(p8)
            ,printP2D(p9)
            ,printP2D(p10)
            );



    /*

        Construct the N triangles pointind upwards defined by the three points below.


    ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐              ┬
    │                                                                                                                                          │              │
    │                                                                                                                                          │              │
    └───────────────              ────────────────────────────────      (3)      ─────────────────────────────────             ────────────────┘              │            ┬
                   /      /\      \                              /      /\      \                               /      /\      \                              │            │
                  /      /  \      \                            /      /  \      \                             /      /  \      \                             │            │
                 /      /    \      \                          /      /    \      \                           /      /    \      \                            │            │
                /      /      \      \                        /      /      \      \                         /      /      \      \                           │            │
               /      /        \      \                      /      /        \      \                       /      /        \      \                          │            │
              /      /          \      \                    /      /          \      \                     /      /          \      \                         │            │
             /      /            \      \                  /      /            \      \                   /      /            \      \                        │            │
            /      /              \      \                /      /              \      \                 /      /              \      \                       │            │
           /      /                \      \              /      /                \      \               /      /                \      \                      │ Gh-pt      │  Th (relative)
          /      /        1         \      \            /      /        2         \      \             /      /        N         \      \                     │ (absolute) │
         /      /                    \      \          /      /                    \      \           /      /                    \      \                    │            │
        /      /                      \      \        /      /                      \      \         /      /                      \      \                   │            │
       /      /                        \      \      /      /                        \      \       /      /                        \      \                  │            │
      /      /                          \      \    /      /                          \      \     /      /                          \      \                 │            │
     /      /                            \      \  /      /                            \      \   /      /                            \      \                │            │
    /      /                              \      \/      /                              \      \ /      /                              \      \               │            │
    │      ────────────────────────────────             (1)─────────────────────────────(2)             ────────────────────────────────       │              ┴            ┴
    │                                                                                                                                          │
    │                                                                                                                                          │
    └──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘

    ├───────────────────────────────────────────────────┤
                             N*Tw (absolute)

                                                        ├────────────────────────────────┤
                                                                       Tw (relative

                                                                          ├──────────────┤
                                                                                Tw/2 (relative)

    */

        int N = 0;

        char *upwardsPointingTriangles = malloc(1);
        upwardsPointingTriangles[0] = 0;
        const char *upwardsPointingTriangleTemplate = "   <path id=\"upwardsPointingTriangle%d\" d=\""
                                        "M %.2f, %.2f "
                                        "l %.2f, %.2f "
                                        "l %.2f, %.2f "
                                        "Z\"/>\n";
        char *upwardPointingTriangle = malloc((strlen(outerPathTemplate)
                                               +1 /* for null termination */
                                               + 6 * characterCountNeededForFloat(zzg)
                                               )*sizeof(char));
        p1.y = height-pt;
        p2.x = tiw;
        p3.y = 0;
        p3.x = -tiw/2;
        p3.y = -(height-2*pt);

        while(N < zzg->N)
        {

            p1.x = N*(tw)+tww;


            sprintf(upwardPointingTriangle, upwardsPointingTriangleTemplate
                    ,N+1
                    ,printP2D(p1)
                    ,printP2D(p2)
                    ,printP2D(p3));

            upwardsPointingTriangles = realloc(upwardsPointingTriangles, strlen(upwardsPointingTriangles)+strlen(upwardPointingTriangle)+20);
            strcat(upwardsPointingTriangles, upwardPointingTriangle);

            N = N + 1;
        }







        /*

            Construct the N triangles pointind upwards defined by the three points below.







        ├──────────────────────────────────────────────────────────────────────────┤
                                 N*Tiw+Tiw/2+2*Tww (absolute)
                                                                                   ├────────────────────────────────┤
                                                                                           Tw (relative
        ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐              ┬
        │                                                                                                                                          │              │ Pt (absolute)
        │                                                                                                                                          │              │
        └───────────────              ────────────────────────────────            (1) ──────────────────────────── (2)             ────────────────┘              ┴   ┬
                       /      /\      \                              /      /\      \                               /      /\      \                                  │
                      /      /  \      \                            /      /  \      \                             /      /  \      \                                 │
                     /      /    \      \                          /      /    \      \                           /      /    \      \                                │
                    /      /      \      \                        /      /      \      \                         /      /      \      \                               │
                   /      /        \      \           0          /      /        \      \         N-1           /      /        \      \                              │
                  /      /          \      \                    /      /          \      \                     /      /          \      \                             │
                 /      /            \      \                  /      /            \      \                   /      /            \      \                            │
                /      /              \      \                /      /              \      \                 /      /              \      \                           │
               /      /                \      \              /      /                \      \               /      /                \      \                          │  Tih
              /      /                  \      \            /      /                  \      \             /      /                  \      \                         │  (relative)
             /      /                    \      \          /      /                    \      \           /      /                    \      \                        │
            /      /                      \      \        /      /                      \      \         /      /                      \      \                       │
           /      /                        \      \      /      /                        \      \       /      /                        \      \                      │
          /      /                          \      \    /      /                          \      \     /      /                          \      \                     │
         /      /                            \      \  /      /                            \      \   /      /                            \      \                    │
        /      /                              \      \/      /                              \      \ /      /                              \      \                   │
        │      ────────────────────────────────              ────────────────────────────────      (3)      ────────────────────────────────       │                  ┴
        │                                                                                                                                          │
        │                                                                                                                                          │
        └──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘


        */

            char *downwardsPointingTriangles = malloc(1);
            downwardsPointingTriangles[0] = 0;
            const char *downwardsPointingTriangleTemplate = "   <path id=\"downwardsPointingTriangle%d\" d=\""
                                            "M %.2f, %.2f "
                                            "l %.2f, %.2f "
                                            "l %.2f, %.2f "
                                            "Z\"/>\n";
            char *downwardPointingTriangle = malloc((strlen(downwardsPointingTriangleTemplate)
                                                   +1 /* for null termination */
                                                   + 6 * characterCountNeededForFloat(zzg)
                                                   )*sizeof(char));

            p1.y = pt;
            p2.x = tiw;
            p2.y = 0;
            p3.x = -tiw/2;
            p3.y = (height-2*pt);

            N=0;
            while(N < zzg->N - 1)
            {

                p1.x = N*(tiw+2*tww)+tiw/2+2*tww;


                sprintf(downwardPointingTriangle, downwardsPointingTriangleTemplate
                        ,N+1
                        ,printP2D(p1)
                        ,printP2D(p2)
                        ,printP2D(p3));

                downwardsPointingTriangles = realloc(downwardsPointingTriangles, strlen(downwardsPointingTriangles)+strlen(downwardPointingTriangle)+20);
                strcat(downwardsPointingTriangles, downwardPointingTriangle);

                N = N + 1;
            }





    char *svtCloseTag = "</svg>";

    int totalNeededSize =
            strlen(svgHeader)
            + strlen(outerPath)
            + strlen(upwardsPointingTriangles)
            + strlen(downwardsPointingTriangles)
            + strlen(svtCloseTag)
            + 1; /* For the terminating NULL */

    *dest = malloc(sizeof(char)*totalNeededSize);
    memset(*dest, 0, totalNeededSize);

    strcat(*dest, svgHeader);
    strcat(*dest, outerPath);
    strcat(*dest, upwardsPointingTriangles);
    strcat(*dest, downwardsPointingTriangles);
    strcat(*dest, svtCloseTag);

    free(svgHeader);
    free(outerPath);
    free(upwardPointingTriangle);
    free(upwardsPointingTriangles);
    free(downwardPointingTriangle);
    free(downwardsPointingTriangles);
}
