#include <stdio.h>

#include <GridDesigner/ZigZagGrid.h>

void handleProgressChanged(int progress)
{
    printf("%3.d%%\n", progress);
}


int main(int argc, char *argv[])
{
    ZigZagGrid * g = new_ZigZagGrid();
//    g->progressCallBack = &handleProgressChanged;
    g->Pt = 2;
    g->N = 3;
    g->Gw = 40;
    g->Gh = 30;
    g->solve(g);
    printf("Done\n");
    printf("A solved to %f\n", g->a);
    return 0;
}
