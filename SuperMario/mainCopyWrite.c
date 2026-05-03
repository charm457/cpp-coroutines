#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>

#define mapHeight 25
#define mapWidth 80

typedef struct SObject{
    float x, y;
    float width, hight; 
} TObject;

char map[mapHeight][mapWidth+1];
TObject mario;

void Clearmap(){
    for (int i = 0; i < mapWidth; i++)
        map[0][i] = '.';
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++)
        sprintf(map[j], "%s", map[0]);
}

void ShowMap(){
    for (int j = 0; j < mapHeight; j++)
        mvprintw(j, 0, "%s", map[j]);
}

void SetObjectPos(TObject *obj, float xPos, float yPos){
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHight){
    SetObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).hight = oHight;
}

void PutObjectOnMap(TObject obj){
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHight = (int)round(obj.hight);

    for (int i = ix; i < (ix + iWidth); i++)
        for (int j = iy; j < (iy + iHight); j++)
            if (i >= 0 && i < mapWidth && j >= 0 && j < mapHeight)
                map[j][i] = '@';
}

int main(){
    // Инициализация ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    
    InitObject(&mario, 39, 10, 3, 3);
    
    int ch;
    do {
        Clearmap();
        PutObjectOnMap(mario);
        
        // Управление
        ch = getch();
        if (ch != ERR) {
            if (ch == 'a' || ch == KEY_LEFT) mario.x -= 1;
            if (ch == 'd' || ch == KEY_RIGHT) mario.x += 1;
            if (ch == 'w' || ch == KEY_UP) mario.y -= 1;
            if (ch == 's' || ch == KEY_DOWN) mario.y += 1;
        }
        
        clear();
        ShowMap();
        mvprintw(0, 0, "Use WASD/Arrows to move | ESC to exit");
        refresh();
        
        napms(50);
    } while(ch != 27);
    
    endwin();
    return 0;
}