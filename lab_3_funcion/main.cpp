#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>



const double STEP_X = 0.1000;
const double STEP_Y = 0.0250;
const int SKIP_X = 68;
const int SKIP_Y = 39;
const int GRAPH_WIDTH = 502;
const int GRAPH_HEIGHT = 400;

const int ZERO_X = 68;
const int ZERO_Y = 439;

const int DV_Y = 40;
const double DV_X = 31.375;

const double maxX = 44.1;
const double maxY = 7.68;




double functionResult(double x)
{
    double halfX = x / 2;
    double cosine = cos(halfX);
    double toPow3 = cosine * cosine;
    double sqroot = sqrt(x);
    return toPow3 + sqroot;
}

int main()
{
    clrscr();

    int graph_driver;
    int graph_mode;
    int graph_error_code;
    graph_driver = DETECT;
    initgraph(&graph_driver, &graph_mode, "C:\\Turboc3\\BGI");
    graph_error_code = graphresult();
    if (graph_error_code != grOk)
    {
        cputs("error while initting graphics\n\r");
        cprintf("error code is: %d\n\r", graph_error_code);
    }


    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(ZERO_X, ZERO_Y, ZERO_X + GRAPH_WIDTH, ZERO_Y);
    line(ZERO_X, ZERO_Y, ZERO_X, ZERO_Y - GRAPH_HEIGHT);

    for (int i = 0; i <= GRAPH_HEIGHT / DV_Y; i++)
    {

        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        line(ZERO_X - 5, ZERO_Y - i * DV_Y, ZERO_X + 5, ZERO_Y - i * DV_Y);

        char* numStr;
        itoa(i, numStr, 10);
        outtextxy(ZERO_X - 20, ZERO_Y - i * DV_Y - 5, numStr);
    }

    settextstyle(DEFAULT_FONT, 1, 0);
    for (int j = 0; j <= (int)(GRAPH_WIDTH / DV_X); j++)
    {

        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        line(ZERO_X + (int)(j * DV_X), ZERO_Y - 5, ZERO_X + (int)(j * DV_X), ZERO_Y + 5);
        char numStr[10] = { 0 };
        itoa(j, numStr, 10);
        char* res = strcat(numStr, "PI");
        outtextxy(ZERO_X + (int)(j * DV_X), ZERO_Y + 5, res);
    }
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    line(47 + SKIP_X, ZERO_Y, 47 + SKIP_X, ZERO_Y - GRAPH_HEIGHT);
    line(470 + SKIP_X, ZERO_Y, 470 + SKIP_X, ZERO_Y - GRAPH_HEIGHT);

    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);

    double minX = 3.0 * M_PI / 2.0;
    double maxx = 15.0 * M_PI;
    int minXPIXEL = (int)floor(minX / STEP_X);
    int maxXPIXEL = (int)floor(maxx / STEP_X);
    double x = minX;
    for (int xPix = minXPIXEL; xPix < maxXPIXEL; xPix++)
    {
        double y = functionResult(x);

        int yPix = GRAPH_HEIGHT - (int)ceil(y / STEP_Y);
        putpixel(xPix + SKIP_X, yPix + SKIP_Y, WHITE);
        x += STEP_X;
    }

    printf("Max value: %f at x: %f\n", maxY, maxX);
    getch();
    return 0;
}