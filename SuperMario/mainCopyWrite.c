#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#define mapWidth 80
#define mapHeight 40

typedef struct SObject {
    float x, y;
    float width, height;
    float vertSpeed;
    bool isFly;
    char cType;
    float horizonSpeed;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;

TObject *brick = NULL;
int brickLength;

TObject *moving = NULL;
int movingLength;
int level = 1;
int score;
int maxlvl;

void ClearMap() {
    for (int i = 0; i < mapWidth; i++) {
        map[0][i] = ' ';
    }
    map[0][mapWidth] = '\0';
    for (int j = 0; j < mapHeight; j++) {
        sprintf(map[j], "%s", map[0]);
    }
}

void showMap() {
    for (int j = 0; j < mapHeight; j++) {
        mvprintw(j, 0, "%s", map[j]);
    }
}

void SetObjectPos(TObject* obj, float xPos, float yPos) {
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void InitObject(TObject* obj, float xPos, float yPos, float oWidth, float oHeight, char inType) {
    SetObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).height = oHeight;
    (*obj).vertSpeed = 0;
    (*obj).cType = inType;
    (*obj).horizonSpeed = 0.2;
}

bool IsCollision(TObject o1, TObject o2) {
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
        ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

TObject *GetNewMoving() {
    movingLength++;
    moving = (TObject*)realloc(moving, sizeof(*moving) * movingLength);
    return moving + movingLength - 1;
}

void CreateLevel(int lvl);

void PlayerDead() {
    mvprintw(mapHeight/2, mapWidth/2 - 5, "GAME OVER");
    refresh();
    napms(500);
    CreateLevel(level);
}

void VertMoveObject(TObject* obj) {
    (*obj).vertSpeed += 0.05;
    (*obj).isFly = true;
    SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
    
    for (int i = 0; i < brickLength; i++) {
        if (IsCollision(*obj, brick[i])) {
            if (obj[0].vertSpeed > 0) {
                obj[0].isFly = false;
            }

            if ((brick[i].cType == '?') && (obj[0].vertSpeed < 0) && (obj == &mario)) {
                brick[i].cType = '-';
                InitObject(GetNewMoving(), brick[i].x, brick[i].y - 3, 3, 2, '$');
                moving[movingLength - 1].vertSpeed = -0.7;
            }

            (*obj).y -= (*obj).vertSpeed;
            (*obj).vertSpeed = 0;

            if (brick[i].cType == '+') {
                level++;
                if (level > maxlvl) level = 1;
                mvprintw(mapHeight/2, mapWidth/2 - 4, "LEVEL UP!");
                refresh();
                napms(500);
                CreateLevel(level);
            }
            break;
        }
    }
}

void DeleteMoving(int i) {
    movingLength--;
    moving[i] = moving[movingLength];
    moving = (TObject*)realloc(moving, sizeof(*moving) * movingLength);
}

void MarioCollision() {
    for (int i = 0; i < movingLength; i++) {
        if (IsCollision(mario, moving[i])) {
            if (moving[i].cType == 'o') {
                if ((mario.isFly == true) && (mario.vertSpeed > 0) && (mario.y + mario.height < moving[i].y + moving[i].height) * 0.5) {
                    score += 50;
                    DeleteMoving(i);
                    i--;
                    continue;
                } else {
                    PlayerDead();
                }
            }

            if (moving[i].cType == '$') {
                score += 100;
                DeleteMoving(i);
                i--;
                continue;
            }
        }
    }
}

void HorizonMoveObject(TObject *obj) {
    obj[0].x += obj[0].horizonSpeed;

    for (int i = 0; i < brickLength; i++) {
        if (IsCollision(obj[0], brick[i])) {
            obj[0].x -= obj[0].horizonSpeed;
            obj[0].horizonSpeed = -obj[0].horizonSpeed;
            return;
        }
    }

    if (obj[0].cType == 'o') {
        TObject tmp = *obj;
        VertMoveObject(&tmp);
        if (tmp.isFly == true) {
            obj[0].x -= obj[0].horizonSpeed;
            obj[0].horizonSpeed = -obj[0].horizonSpeed;    
        }
    }
}

bool IsPosInMap(int x, int y) {
    return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

void PutObjectOnMap(TObject obj) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++) {
        for (int j = iy; j < (iy + iHeight); j++) {
            if (IsPosInMap(i, j)) {
                map[j][i] = obj.cType;
            }
        }
    }
}

void setCur(int x, int y) {
    move(y, x);
}

void HorisonMoveMap(float dx) {
    mario.x -= dx;
    for (int i = 0; i < brickLength; i++) {
        if (IsCollision(mario, brick[i])) {
            mario.x += dx;
            return;
        }
    }
    mario.x += dx;

    for (int i = 0; i < brickLength; i++) {
        brick[i].x += dx;
    }
    for (int i = 0; i < movingLength; i++) {
        moving[i].x += dx;
    }
}

TObject *GetNewBrick() {
    brickLength++;
    brick = (TObject*)realloc(brick, sizeof(*brick) * brickLength);
    return brick + brickLength - 1;
}

void PutScoreOnMap() {
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len; i++) {
        map[1][i + 5] = c[i];
    }
}

void CreateLevel(int lvl) {
    brickLength = 0;
    brick = (TObject*)realloc(brick, 0);
    movingLength = 0;
    moving = (TObject*)realloc(moving, 0);
    InitObject(&mario, 39, 10, 3, 3, '@');
    score = 0;

    if (lvl == 1) {
        InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 30, 10, 5, 3, '?');
        InitObject(GetNewBrick(), 50, 10, 5, 3, '?');        
        InitObject(GetNewBrick(), 60, 15, 40, 10, '#');
        InitObject(GetNewBrick(), 60, 5, 10, 3, '-');
        InitObject(GetNewBrick(), 70, 5, 5, 3, '?');
        InitObject(GetNewBrick(), 75, 5, 5, 3, '-');
        InitObject(GetNewBrick(), 80, 5, 5, 3, '?');
        InitObject(GetNewBrick(), 85, 5, 10, 3, '-');
        InitObject(GetNewBrick(), 100, 20, 20, 5, '#');
        InitObject(GetNewBrick(), 120, 15, 10, 10, '#');
        InitObject(GetNewBrick(), 150, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 210, 15, 10, 10, '+');
        InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');        
    }
    if (lvl == 2) {
        InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 60, 15, 10, 10, '#');
        InitObject(GetNewBrick(), 80, 20, 20, 5, '#');
        InitObject(GetNewBrick(), 120, 15, 10, 10, '#');
        InitObject(GetNewBrick(), 150, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 210, 15, 10, 10, '+');
        InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 65, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 160, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 175, 10, 3, 2, 'o');
    }
    if (lvl == 3) {
        InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 80, 20, 15, 5, '#');
        InitObject(GetNewBrick(), 120, 15, 15, 10, '#');
        InitObject(GetNewBrick(), 160, 10, 15, 15, '+');
        InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 50, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 90, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 130, 10, 3, 2, 'o');
    }
    maxlvl = 3;
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    CreateLevel(level);

    int ch;
    float current_dx = 0;
    bool running = true;

    while (running) {
        ClearMap();
        bool jump = false;
        bool moved = false;

        while ((ch = getch()) != ERR) {
            if (ch == ' ') jump = true;
            else if (ch == 'a' || ch == KEY_LEFT)  { current_dx = 1.0; moved = true; } 
            else if (ch == 'd' || ch == KEY_RIGHT) { current_dx = -1.0; moved = true; }
            else if (ch == 27) running = false;
        }

        if (jump && !mario.isFly) {
            mario.vertSpeed = -1.2;
        }

        if (!moved) {
            current_dx *= 0.85; 
            if (fabs(current_dx) < 0.1) {
                current_dx = 0;
            }
        }

        if (current_dx != 0) {
            HorisonMoveMap(current_dx);
        }

        if (mario.y > mapHeight) {
            PlayerDead();
        }

        VertMoveObject(&mario);
        MarioCollision();
        
        for (int i = 0; i < brickLength; i++) {
            PutObjectOnMap(brick[i]);        
        }
        
        for (int i = 0; i < movingLength; i++) {
            VertMoveObject(moving + i);
            HorizonMoveObject(moving + i);
            if (moving[i].y > mapHeight) {
                DeleteMoving(i);
                i--;
                continue;
            }
            PutObjectOnMap(moving[i]);
        }
        
        PutObjectOnMap(mario);
        PutScoreOnMap();

        clear();
        setCur(0, 0);
        showMap();
        mvprintw(0, 0, "Score: %d  Level: %d  A/D + Space | ESC to exit", score, level);

        refresh();
        napms(10);
    }

    endwin();
    return 0;
}