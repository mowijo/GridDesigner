#include <stdio.h>

#include <GridDesigner/ZigZagGrid.h>
#include <GridDesigner/SvgRenderer.h>
#include <stdlib.h>
#include <string.h>

char *expected =
"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"240.00mm\" height=\"48.00mm\" viewBox=\"0 0 240.00 48.00\" version=\"1.1\">\n"
"   <style>\n"
"       path { fill: none; stroke: black; stroke-width: 0.1mm; }\n"
"   </style>\n"
"   <path id=\"outerPath\" d=\"M 0.00, 0.00 L 240.00, 0.00 L 240.00, 12.00 L 216.72, 12.00 L 240.00, 36.00 L 240.00, 48.00 L 0.00, 48.00 L 0.00, 36.00 L 23.28, 12.00 L 0.00, 12.00 Z\"/>\n"
"   <path id=\"upwardsPointingTriangle1\" d=\"M 16.72, 36.00 l 46.56, 0.00 l -23.28, -24.00 Z\"/>\n"
"   <path id=\"upwardsPointingTriangle2\" d=\"M 96.72, 36.00 l 46.56, 0.00 l -23.28, -24.00 Z\"/>\n"
"   <path id=\"upwardsPointingTriangle3\" d=\"M 176.72, 36.00 l 46.56, 0.00 l -23.28, -24.00 Z\"/>\n"
"   <path id=\"downwardsPointingTriangle1\" d=\"M 56.72, 12.00 l 46.56, 0.00 l -23.28, 24.00 Z\"/>\n"
"   <path id=\"downwardsPointingTriangle2\" d=\"M 136.72, 12.00 l 46.56, 0.00 l -23.28, 24.00 Z\"/>\n"
"</svg>";

int main(int argc, char *argv[])
{
    double scale = 6;
    ZigZagGrid * g = new_ZigZagGrid();
    g->Pt = 2*scale;
    g->N = 3;
    g->Gw = 40*scale;
    g->Gh = 8*scale;
    g->T = 0.01;
    g->solve(g);

    char *svg = NULL;
    renderAsSVG(g, &svg);

    int result = strcmp(svg, expected);

    free(svg);
    g->destroy(g);

    if(result == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
