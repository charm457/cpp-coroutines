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
    char type;
} TObject;

char map[mapHeight][mapWidth+1];
TObject mario;
TObject *brick = NULL;
TObject *moving = NULL;
int brickLength;
int movingLength;
float cameraX = 0;
bool leftPressed = false;
bool rightPressed = false;
bool jumpPressed = false;
int level = 1;
int maxLvl = 3;

void CreateLevel();

void Clearmap(){
    for (int i = 0; i < mapWidth; i++)
        map[0][i] = ' ';
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

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHight, char inType){
    SetObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).hight = oHight;
    (*obj).vertSpeed = 0;
    (*obj).isOnGround = false;
    (*obj).type = inType;
}

bool IsCollision(TObject o1, TObject o2);

void VertMoveObject(TObject *obj){
    (*obj).vertSpeed += GRAVITY;
    SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
    
    (*obj).isOnGround = false;
    
    for(int i = 0; i < brickLength; i++){
        if (IsCollision(*obj, brick[i])){
            if ((*obj).vertSpeed > 0){
                (*obj).y = brick[i].y - (*obj).hight;
                (*obj).vertSpeed = 0;
                (*obj).isOnGround = true;
                
                if(brick[i].type == '+'){
                    level++;
                    if(level > maxLvl) level = 1;
                    CreateLevel();
                    return;
                }
            } else if ((*obj).vertSpeed < 0){
                (*obj).y = brick[i].y + brick[i].hight;
                (*obj).vertSpeed = 0;
            }
            break;
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

void HorizonMoveObject(TObject *obj, float dx){
    obj->x += dx;
    
    for(int i = 0; i < brickLength; i++){
        if (IsCollision(*obj, brick[i])){
            obj->x -= dx;
            break;
        }
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

TObject *GetNewBrick(){
    brickLength++;
    brick = (TObject*)realloc(brick, sizeof(*brick) * brickLength);
    return brick + brickLength - 1;
}

TObject *GetNewMoving(){
    movingLength++;
    moving = (TObject*)realloc(moving, sizeof(*moving) * movingLength);
    return moving + movingLength - 1;
}

void CreateLevel(){
    brickLength = 0;
    brick = (TObject*)realloc(brick, 0);
    movingLength = 0;
    moving = (TObject*)realloc(moving, 0);
    
    InitObject(&mario, 39, 10, 3, 3, '@');
    cameraX = 0;
    leftPressed = false;
    rightPressed = false;
    jumpPressed = false;
    
    if(level == 1){
        InitObject(GetNewBrick(), 20, 20, 40, 2, '#');
        InitObject(GetNewBrick(), 30, 15, 5, 3, '?');
        InitObject(GetNewBrick(), 60, 18, 10, 2, '#');
        InitObject(GetNewBrick(), 80, 15, 5, 3, '?');
        InitObject(GetNewBrick(), 100, 20, 30, 2, '#');
        InitObject(GetNewBrick(), 150, 18, 15, 2, '+');
    }
    else if(level == 2){
        InitObject(GetNewBrick(), 20, 20, 40, 2, '#');
        InitObject(GetNewBrick(), 70, 16, 10, 2, '#');
        InitObject(GetNewBrick(), 90, 12, 5, 3, '?');
        InitObject(GetNewBrick(), 120, 18, 20, 2, '#');
        InitObject(GetNewBrick(), 170, 18, 15, 2, '+');
    }
    else if(level == 3){
        InitObject(GetNewBrick(), 20, 20, 30, 2, '#');
        InitObject(GetNewBrick(), 60, 15, 10, 2, '#');
        InitObject(GetNewBrick(), 80, 10, 5, 3, '?');
        InitObject(GetNewBrick(), 110, 18, 20, 2, '#');
        InitObject(GetNewBrick(), 150, 22, 10, 2, '#');
        InitObject(GetNewBrick(), 180, 18, 15, 2, '+');
    }
}

int main(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    
    CreateLevel();
    
    int ch;
    do {
        VertMoveObject(&mario);
        
        ch = getch();
        if (ch != ERR) {
            if (ch == 'a' || ch == KEY_LEFT) leftPressed = true;
            if (ch == 'd' || ch == KEY_RIGHT) rightPressed = true;
            if (ch == 'w' || ch == KEY_UP || ch == ' ') jumpPressed = true;
            if (ch == 27) break;
        }
        
        if (leftPressed) {
            HorizonMoveObject(&mario, -1);
            HorizonMoveMap(-1);
        }
        if (rightPressed) {
            HorizonMoveObject(&mario, 1);
            HorizonMoveMap(1);
        }
        if (jumpPressed && mario.isOnGround) {
            mario.vertSpeed = JUMP_POWER;
            mario.isOnGround = false;
            jumpPressed = false;
        }
        
        Clearmap();
        
        PutObjectOnMap(mario, '@');
        for(int i = 0; i < brickLength; i++){
            if(brick[i].type == '#')
                PutObjectOnMap(brick[i], '#');
            else if(brick[i].type == '?')
                PutObjectOnMap(brick[i], '?');
            else if(brick[i].type == '+')
                PutObjectOnMap(brick[i], 'E');
        }
        
        cameraX = mario.x - mapWidth/2;
        
        clear();
        ShowMap();
        mvprintw(0, 0, "Level: %d", level);
        refresh();
        
        napms(16);
        
        leftPressed = false;
        rightPressed = false;
    } while(1);
    
    endwin();
    return 0;
}