#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>

#define mapHeight 25
#define mapWidth 80
#define GRAVITY 0.3
#define JUMP_POWER -2.5

typedef struct SObject{
    float x, y;
    float width, hight; 
    float vertSpeed;
    bool isOnGround;
} TObject;

char map[mapHeight][mapWidth+1];
TObject mario;
TObject brick[1];
float cameraX = 0;

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
    (*obj).vertSpeed = 0;
    (*obj).isOnGround = false;
}

bool IsCollision(TObject o1, TObject o2);

void VertMoveObject(TObject *obj){
    (*obj).vertSpeed += GRAVITY;
    SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
    
    (*obj).isOnGround = false;
    
    if (IsCollision(*obj, brick[0])){
        if ((*obj).vertSpeed > 0){
            (*obj).y = brick[0].y - (*obj).hight;
            (*obj).vertSpeed = 0;
            (*obj).isOnGround = true;
        } else if ((*obj).vertSpeed < 0){
            (*obj).y = brick[0].y + brick[0].hight;
            (*obj).vertSpeed = 0;
        }
    }
    
    if ((*obj).y + (*obj).hight >= mapHeight){
        (*obj).y = mapHeight - (*obj).hight;
        (*obj).vertSpeed = 0;
        (*obj).isOnGround = true;
    }
    
    if ((*obj).y < 0){
        (*obj).y = 0;
        (*obj).vertSpeed = 0;
    }
}

bool IsPosInMap(int x, int y){
    return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

void PutObjectOnMap(TObject obj, char symbol){
    int ix = (int)round(obj.x - cameraX);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHight = (int)round(obj.hight);

    for (int i = ix; i < (ix + iWidth); i++)
        for (int j = iy; j < (iy + iHight); j++)
            if (IsPosInMap(i, j))
                map[j][i] = symbol;
}

bool IsCollision(TObject o1, TObject o2){
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
            ((o1.y + o1.hight) > o2.y) && (o1.y < (o2.y + o2.hight));
}

void HorizonMoveMap(float dx){
    cameraX += dx;
}

int main(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    
    InitObject(&mario, 39, 10, 3, 3);
    InitObject(brick, 20, 18, 40, 2);
    
    int ch;
    do {
        VertMoveObject(&mario);
        Clearmap();
        
        PutObjectOnMap(mario, '@');
        PutObjectOnMap(brick[0], '#');
        
        ch = getch();
        if (ch != ERR) {
            if (ch == 'a' || ch == KEY_LEFT) {
                mario.x -= 1;
                HorizonMoveMap(-1);
            }
            if (ch == 'd' || ch == KEY_RIGHT) {
                mario.x += 1;
                HorizonMoveMap(1);
            }
            if ((ch == 'w' || ch == KEY_UP || ch == ' ') && mario.isOnGround) {
                mario.vertSpeed = JUMP_POWER;
                mario.isOnGround = false;
            }
        }
        
        cameraX = mario.x - mapWidth/2;
        
        clear();
        ShowMap();
        refresh();
        
        napms(50);
    } while(ch != 27);
    
    endwin();
    return 0;
}