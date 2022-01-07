#include <stdio.h>

#include <GridDesigner/ZigZagGrid.h>
#include <GridDesigner/SvgRenderer.h>
#include <stdlib.h>

void handleProgressChanged(int progress)
{
    printf("%3.d%%\n", progress);
}


int main(int argc, char *argv[])
{
    double scale = 6    ;
    ZigZagGrid * g = new_ZigZagGrid();
//    g->progressCallBack = &handleProgressChanged;
    g->Pt = 2*scale;
    g->N = 3;
    g->Gw = 40*scale;
    g->Gh = 8*scale;
    g->T = 0.01;
    g->solve(g);

    char *svg = NULL;
    renderAsSVG(g, &svg);
    FILE *f = fopen("/tmp/grid.svg", "w");
    fprintf(f, "%s", svg);
    fclose(f);

    free(svg);
    g->destroy(g);
    return 0;
}
