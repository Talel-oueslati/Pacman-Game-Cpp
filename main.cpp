#include <graphics.h>
#include <conio.h>

const int POINT_RADIUS = 3;
const int POINT_GAP_X = 50;
const int POINT_GAP_Y = 40;

bool points[13][9]; 

void inizialition_points() {
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 9; ++j) {
            points[i][j] = true;
        }
    }
}

void make_points() {
    int i, j;
    for (i = 120; i <= 480; i += POINT_GAP_X) {
        for (j = 120; j <= 360; j += POINT_GAP_Y) {
            if (points[(i - 120) / POINT_GAP_X][(j - 120) / POINT_GAP_Y]) {
                setcolor(COLOR(255, 165, 0));
                setfillstyle(SOLID_FILL, COLOR(255, 165, 0));
                circle(i, j, POINT_RADIUS);
                floodfill(i, j, COLOR(255, 165, 0));
            }
        }
    }
}

bool checkpacman_ontoppoint(int x, int y) {
    int pointPosX = (x - 120) / POINT_GAP_X;
    int pointPosY = (y - 120) / POINT_GAP_Y;

    if (pointPosX >= 0 && pointPosX < 13 && pointPosY >= 0 && pointPosY < 9) {
        return points[pointPosX][pointPosY];
    }

    return false;
}

void eatPoint(int x, int y) {
    int pointPosX = (x - 120) / POINT_GAP_X;
    int pointPosY = (y - 120) / POINT_GAP_Y;

    if (pointPosX >= 0 && pointPosX < 13 && pointPosY >= 0 && pointPosY < 9) {
        points[pointPosX][pointPosY] = false;
    }
}

void make_cadre() {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLACK);
    rectangle(80, 80, 540, 400);
    floodfill(310, 240, BLUE);
}

void make_murs() {
    setcolor(RED);

    rectangle(148, 150, 152, 200);

   
    rectangle(150, 198, 200, 202);

    rectangle(250, 150, 255, 180);
    rectangle(285, 170, 290, 200); 
    rectangle(320, 150, 325, 180); 
    rectangle(355, 170, 360, 200); 

    rectangle(370, 150, 375, 230); 
    rectangle(380, 200, 425, 205); 
    rectangle(148, 200, 152, 250); 

 
    rectangle(148, 250, 152, 295); 
    rectangle(150, 298, 195, 302); 
    rectangle(255, 270, 260, 300);
    rectangle(320, 270, 325, 300); 
    rectangle(355, 250, 360, 275); 
    rectangle(370, 280, 375, 380); 
    rectangle(380, 360, 425, 365); 

}

bool checkCollision(int x, int y) {
    int boxLeft = 100;
    int boxRight = 540;
    int boxTop = 80;
    int boxBottom = 400;


    if (x < boxLeft || x > boxRight || y < boxTop || y > boxBottom) {
        return true;
    }

    int rectangles[][4] = {
        {150, 150, 200, 200},
        {250, 150, 260, 180},
        {280, 170, 290, 200},
        {320, 150, 330, 180},
        {350, 170, 360, 200},
        {370, 150, 380, 230},
        {380, 200, 430, 210},
        {148, 250, 152, 295},
        {150, 298, 195, 302},
        {255, 270, 260, 300},
        {320, 270, 325, 300},
        {355, 250, 360, 275},
        {370, 280, 375, 380},
        {380, 360, 425, 365}};

   
    for (int i = 0; i < sizeof(rectangles) / sizeof(rectangles[0]); ++i) {
        int left = rectangles[i][0];
        int top = rectangles[i][1];
        int right = rectangles[i][2];
        int bottom = rectangles[i][3];

        if (x >= left && x <= right && y >= top && y <= bottom) {
            return true; 
        }
    }

    return false;
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    int x = 110, y = 120;
    int direction = 0;

    inizialition_points();
    make_points();
    setbkcolor(BLACK);
    cleardevice();

    make_cadre();
    make_murs();

    setfillstyle(SOLID_FILL, YELLOW);
    pieslice(x, y, 45, 315, 12);

    make_points(); 

    while (1) {
        if (kbhit()) {
            char key = getch();
            if (key == 27)
                break;
            if (key == 72) {
                direction = 1;
                if (!checkCollision(x, y - 10)) {
                    y -= 10;
                }
            } else if (key == 80) { 
                direction = 3;
                if (!checkCollision(x, y + 10)) {
                    y += 10;
                }
            } else if (key == 75) { 
                direction = 2;
                if (!checkCollision(x - 10, y)) {
                    x -= 10;
                }
            } else if (key == 77) { 
                direction = 0;
                if (!checkCollision(x + 10, y)) {
                    x += 10;
                }
            }
            if (checkpacman_ontoppoint(x, y)) {
                eatPoint(x, y);
            }
            setfillstyle(SOLID_FILL, BLACK);
            floodfill(0, 0, BLACK);

            make_cadre();
            make_murs();
            make_points();

            setfillstyle(SOLID_FILL, YELLOW);
            if (direction == 0) 
                pieslice(x, y, 45, 315, 12);
            else if (direction == 1) 
                pieslice(x, y, 135, 405, 12);
            else if (direction == 2) 
                pieslice(x, y, 225, 495, 12);
            else if (direction == 3) 
                pieslice(x, y, 315, 585, 12);

        
        }
    }

    closegraph();
    return 0;
}
