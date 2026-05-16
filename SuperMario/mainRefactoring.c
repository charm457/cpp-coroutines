#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 40

typedef struct GameObject {
    float x, y;
    float width, height;
    float vertSpeed;
    bool isFly;
    char type;
    float horizonSpeed;
} GameObject;

char map[MAP_HEIGHT][MAP_WIDTH + 1];
GameObject mario;

GameObject *bricks = NULL;
int bricksCount;

GameObject *enemies = NULL;
int enemiesCount;
int currentLevel = 1;
int gameScore;
int maxLevel;

// Объявления функций
void clearMap(void);
void displayMap(void);
void setObjectPosition(GameObject* obj, float xPos, float yPos);
void initObject(GameObject* obj, float xPos, float yPos, float oWidth, float oHeight, char objType);
bool checkCollision(GameObject o1, GameObject o2);
GameObject* addNewEnemy(void);
void createLevel(int lvl);
void playerDeath(void);
void moveVertical(GameObject* obj);
void removeEnemy(int index);
void handleMarioCollision(void);
void moveHorizontal(GameObject* obj);
bool isPositionValid(int x, int y);
void placeObjectOnMap(GameObject obj);
void setCursorPosition(int x, int y);
void scrollMap(float dx);
GameObject* addNewBrick(void);
void updateScoreOnMap(void);


int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    createLevel(currentLevel);

    int ch;
    float current_dx = 0;
    bool running = true;

    while (running) {
        clearMap();
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
            scrollMap(current_dx);
        }

        if (mario.y > MAP_HEIGHT) {
            playerDeath();
        }

        moveVertical(&mario);
        handleMarioCollision();

        for (int i = 0; i < bricksCount; i++) {
            placeObjectOnMap(bricks[i]);        
        }

        for (int i = 0; i < enemiesCount; i++) {
            moveVertical(enemies + i);
            moveHorizontal(enemies + i);
            if (enemies[i].y > MAP_HEIGHT) {
                removeEnemy(i);
                i--;
                continue;
            }
            placeObjectOnMap(enemies[i]);
        }

        placeObjectOnMap(mario);
        updateScoreOnMap();

        clear();
        setCursorPosition(0, 0);
        displayMap();
        mvprintw(0, 0, "Score: %d  Level: %d  A/D + Space | ESC to exit", gameScore, currentLevel);

        refresh();
        napms(10);
    }

    endwin();
    return 0;
}


void clearMap(void) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        map[0][i] = ' ';
    }
    map[0][MAP_WIDTH] = '\0';
    for (int j = 0; j < MAP_HEIGHT; j++) {
        sprintf(map[j], "%s", map[0]);
    }
}

void displayMap(void) {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        mvprintw(j, 0, "%s", map[j]);
    }
}

void setObjectPosition(GameObject* obj, float xPos, float yPos) {
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void initObject(GameObject* obj, float xPos, float yPos, float oWidth, float oHeight, char objType) {
    setObjectPosition(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).height = oHeight;
    (*obj).vertSpeed = 0;
    (*obj).type = objType;
    (*obj).horizonSpeed = 0.2;
}

bool checkCollision(GameObject o1, GameObject o2) {
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
        ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

GameObject* addNewEnemy(void) {
    enemiesCount++;
    enemies = (GameObject*)realloc(enemies, sizeof(*enemies) * enemiesCount);
    return enemies + enemiesCount - 1;
}

void createLevel(int lvl) {
    bricksCount = 0;
    bricks = (GameObject*)realloc(bricks, 0);
    enemiesCount = 0;
    enemies = (GameObject*)realloc(enemies, 0);
    initObject(&mario, 39, 10, 3, 3, '@');
    gameScore = 0;

    if (lvl == 1) {
        initObject(addNewBrick(), 20, 20, 40, 5, '#');
        initObject(addNewBrick(), 30, 10, 5, 3, '?');
        initObject(addNewBrick(), 50, 10, 5, 3, '?');        
        initObject(addNewBrick(), 60, 15, 40, 10, '#');
        initObject(addNewBrick(), 60, 5, 10, 3, '-');
        initObject(addNewBrick(), 70, 5, 5, 3, '?');
        initObject(addNewBrick(), 75, 5, 5, 3, '-');
        initObject(addNewBrick(), 80, 5, 5, 3, '?');
        initObject(addNewBrick(), 85, 5, 10, 3, '-');
        initObject(addNewBrick(), 100, 20, 20, 5, '#');
        initObject(addNewBrick(), 120, 15, 10, 10, '#');
        initObject(addNewBrick(), 150, 20, 40, 5, '#');
        initObject(addNewBrick(), 210, 15, 10, 10, '+');
        initObject(addNewEnemy(), 25, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 80, 10, 3, 2, 'o');        
    }
    if (lvl == 2) {
        initObject(addNewBrick(), 20, 20, 40, 5, '#');
        initObject(addNewBrick(), 60, 15, 10, 10, '#');
        initObject(addNewBrick(), 80, 20, 20, 5, '#');
        initObject(addNewBrick(), 120, 15, 10, 10, '#');
        initObject(addNewBrick(), 150, 20, 40, 5, '#');
        initObject(addNewBrick(), 210, 15, 10, 10, '+');
        initObject(addNewEnemy(), 25, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 80, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 65, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 120, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 160, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 175, 10, 3, 2, 'o');
    }
    if (lvl == 3) {
        initObject(addNewBrick(), 20, 20, 40, 5, '#');
        initObject(addNewBrick(), 80, 20, 15, 5, '#');
        initObject(addNewBrick(), 120, 15, 15, 10, '#');
        initObject(addNewBrick(), 160, 10, 15, 15, '+');
        initObject(addNewEnemy(), 25, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 50, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 80, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 90, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 120, 10, 3, 2, 'o');
        initObject(addNewEnemy(), 130, 10, 3, 2, 'o');
    }
    maxLevel = 3;
}

void playerDeath(void) {
    mvprintw(MAP_HEIGHT/2, MAP_WIDTH/2 - 5, "GAME OVER");
    refresh();
    napms(500);
    createLevel(currentLevel);
}

void moveVertical(GameObject* obj) {
    (*obj).vertSpeed += 0.05;
    (*obj).isFly = true;
    setObjectPosition(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);

    for (int i = 0; i < bricksCount; i++) {
        if (checkCollision(*obj, bricks[i])) {
            if ((*obj).vertSpeed > 0) {
                (*obj).isFly = false;
            }

            if ((bricks[i].type == '?') && ((*obj).vertSpeed < 0) && (obj == &mario)) {
                bricks[i].type = '-';
                initObject(addNewEnemy(), bricks[i].x, bricks[i].y - 3, 3, 2, '$');
                enemies[enemiesCount - 1].vertSpeed = -0.7;
            }

            (*obj).y -= (*obj).vertSpeed;
            (*obj).vertSpeed = 0;

            if (bricks[i].type == '+') {
                currentLevel++;
                if (currentLevel > maxLevel) currentLevel = 1;
                mvprintw(MAP_HEIGHT/2, MAP_WIDTH/2 - 4, "LEVEL UP!");
                refresh();
                napms(500);
                createLevel(currentLevel);
            }
            break;
        }
    }
}

void removeEnemy(int index) {
    enemiesCount--;
    enemies[index] = enemies[enemiesCount];
    enemies = (GameObject*)realloc(enemies, sizeof(*enemies) * enemiesCount);
}

void handleMarioCollision(void) {
    for (int i = 0; i < enemiesCount; i++) {
        if (checkCollision(mario, enemies[i])) {
            if (enemies[i].type == 'o') {
                if ((mario.isFly == true) && (mario.vertSpeed > 0) && (mario.y + mario.height < enemies[i].y + enemies[i].height) * 0.5) {
                    gameScore += 50;
                    removeEnemy(i);
                    i--;
                    continue;
                } else {
                    playerDeath();
                }
            }

            if (enemies[i].type == '$') {
                gameScore += 100;
                removeEnemy(i);
                i--;
                continue;
            }
        }
    }
}

void moveHorizontal(GameObject *obj) {
    (*obj).x += (*obj).horizonSpeed;

    for (int i = 0; i < bricksCount; i++) {
        if (checkCollision((*obj), bricks[i])) {
            (*obj).x -= (*obj).horizonSpeed;
            (*obj).horizonSpeed = -(*obj).horizonSpeed;
            return;
        }
    }

    if ((*obj).type == 'o') {
        GameObject tmp = *obj;
        moveVertical(&tmp);
        if (tmp.isFly == true) {
            (*obj).x -= (*obj).horizonSpeed;
            (*obj).horizonSpeed = -(*obj).horizonSpeed;    
        }
    }
}

bool isPositionValid(int x, int y) {
    return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
}

void placeObjectOnMap(GameObject obj) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++) {
        for (int j = iy; j < (iy + iHeight); j++) {
            if (isPositionValid(i, j)) {
                map[j][i] = obj.type;
            }
        }
    }
}

void setCursorPosition(int x, int y) {
    move(y, x);
}

void scrollMap(float dx) {
    mario.x -= dx;
    for (int i = 0; i < bricksCount; i++) {
        if (checkCollision(mario, bricks[i])) {
            mario.x += dx;
            return;
        }
    }
    mario.x += dx;

    for (int i = 0; i < bricksCount; i++) {
        bricks[i].x += dx;
    }
    for (int i = 0; i < enemiesCount; i++) {
        enemies[i].x += dx;
    }
}

GameObject* addNewBrick(void) {
    bricksCount++;
    bricks = (GameObject*)realloc(bricks, sizeof(*bricks) * bricksCount);
    return bricks + bricksCount - 1;
}

void updateScoreOnMap(void) {
    char buffer[30];
    sprintf(buffer, "Score: %d", gameScore);
    int len = strlen(buffer);
    for (int i = 0; i < len; i++) {
        map[1][i + 5] = buffer[i];
    }
}
