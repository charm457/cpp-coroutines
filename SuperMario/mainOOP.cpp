#include <cmath>
#include <cstring>
#include <iostream>
#include <ncurses.h>
#include <vector>

#define MAP_WIDTH 80
#define MAP_HEIGHT 40

class GameObject {
public:
    float x, y, width, height;
    char type;

    GameObject(float x = 0, float y = 0, float w = 0, float h = 0, char t = ' ')
        : x(x), y(y), width(w), height(h), type(t) {}

    bool checkCollision(const GameObject& other) const {
        return ((x + width) > other.x) && (x < (other.x + other.width)) &&
               ((y + height) > other.y) && (y < (other.y + other.height));
    }
};

class Brick : public GameObject {
public:
    Brick(float x = 0, float y = 0, float w = 0, float h = 0, char t = '#')
        : GameObject(x, y, w, h, t) {}
};

class Enemy : public GameObject {
public:
    float vertSpeed, horizonSpeed;
    bool isFly;

    Enemy(float x = 0, float y = 0, float w = 0, float h = 0, char t = 'o')
        : GameObject(x, y, w, h, t), vertSpeed(0), horizonSpeed(0.2f), isFly(true) {}
};

class Mario : public GameObject {
public:
    float vertSpeed;
    bool isFly;

    Mario(float x = 0, float y = 0, float w = 0, float h = 0, char t = '@')
        : GameObject(x, y, w, h, t), vertSpeed(0), isFly(true) {}
};

class GameMap {
private:
    char map[MAP_HEIGHT][MAP_WIDTH + 1];

    bool isPositionValid(int x, int y) const {
        return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
    }

public:
    void clear() {
        for (int i = 0; i < MAP_WIDTH; i++) map[0][i] = ' ';
        map[0][MAP_WIDTH] = '\0';
        for (int j = 0; j < MAP_HEIGHT; j++) sprintf(map[j], "%s", map[0]);
    }

    void display() const {
        for (int j = 0; j < MAP_HEIGHT; j++) mvprintw(j, 0, "%s", map[j]);
    }

    void placeObject(const GameObject& obj) {
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

    void updateScore(int score) {
        char buffer[30];
        sprintf(buffer, "Score: %d", score);
        int len = strlen(buffer);
        for (int i = 0; i < len; i++) {
            map[1][i + 5] = buffer[i];
        }
    }
};

class Game {
private:
    GameMap gameMap;
    Mario mario;
    std::vector<Brick> bricks;
    std::vector<Enemy> enemies;
    int currentLevel = 1;
    int gameScore = 0;
    int maxLevel = 3;
    bool running = true;

    void createLevel(int lvl) {
        bricks.clear();
        enemies.clear();
        mario = Mario(39, 10, 3, 3, '@');
        mario.isFly = false;
        gameScore = 0;

        switch (lvl) {
            case 1:
                bricks.emplace_back(20, 20, 40, 5, '#');
                bricks.emplace_back(30, 10, 5, 3, '?');
                bricks.emplace_back(50, 10, 5, 3, '?');
                bricks.emplace_back(60, 15, 40, 10, '#');
                bricks.emplace_back(60, 5, 10, 3, '-');
                bricks.emplace_back(70, 5, 5, 3, '?');
                bricks.emplace_back(75, 5, 5, 3, '-');
                bricks.emplace_back(80, 5, 5, 3, '?');
                bricks.emplace_back(85, 5, 10, 3, '-');
                bricks.emplace_back(100, 20, 20, 5, '#');
                bricks.emplace_back(120, 15, 10, 10, '#');
                bricks.emplace_back(150, 20, 40, 5, '#');
                bricks.emplace_back(210, 15, 10, 10, '+');
                enemies.emplace_back(25, 10, 3, 2, 'o');
                enemies.emplace_back(80, 10, 3, 2, 'o');
                break;
            case 2:
                bricks.emplace_back(20, 20, 40, 5, '#');
                bricks.emplace_back(60, 15, 10, 10, '#');
                bricks.emplace_back(80, 20, 20, 5, '#');
                bricks.emplace_back(120, 15, 10, 10, '#');
                bricks.emplace_back(150, 20, 40, 5, '#');
                bricks.emplace_back(210, 15, 10, 10, '+');
                enemies.emplace_back(25, 10, 3, 2, 'o');
                enemies.emplace_back(80, 10, 3, 2, 'o');
                enemies.emplace_back(65, 10, 3, 2, 'o');
                enemies.emplace_back(120, 10, 3, 2, 'o');
                enemies.emplace_back(160, 10, 3, 2, 'o');
                enemies.emplace_back(175, 10, 3, 2, 'o');
                break;
            case 3:
                bricks.emplace_back(20, 20, 40, 5, '#');
                bricks.emplace_back(80, 20, 15, 5, '#');
                bricks.emplace_back(120, 15, 15, 10, '#');
                bricks.emplace_back(160, 10, 15, 15, '+');
                enemies.emplace_back(25, 10, 3, 2, 'o');
                enemies.emplace_back(50, 10, 3, 2, 'o');
                enemies.emplace_back(80, 10, 3, 2, 'o');
                enemies.emplace_back(90, 10, 3, 2, 'o');
                enemies.emplace_back(120, 10, 3, 2, 'o');
                enemies.emplace_back(130, 10, 3, 2, 'o');
                break;
            default:
                break;
        }
    }

    void playerDeath() {
        mvprintw(MAP_HEIGHT / 2, MAP_WIDTH / 2 - 5, "GAME OVER");
        refresh();
        napms(500);
        createLevel(currentLevel);
    }

    void moveVerticalMario() {
        mario.vertSpeed += 0.05f;
        mario.isFly = true;
        mario.y += mario.vertSpeed;

        for (auto& brick : bricks) {
            if (mario.checkCollision(brick)) {
                if (mario.vertSpeed > 0) mario.isFly = false;

                if (brick.type == '?' && mario.vertSpeed < 0) {
                    brick.type = '-';
                    Enemy coin(brick.x, brick.y - 3, 3, 2, '$');
                    coin.vertSpeed = -0.7f;
                    enemies.push_back(coin);
                }

                mario.y -= mario.vertSpeed;
                mario.vertSpeed = 0;

                if (brick.type == '+') {
                    currentLevel++;
                    if (currentLevel > maxLevel) currentLevel = 1;
                    mvprintw(MAP_HEIGHT / 2, MAP_WIDTH / 2 - 4, "LEVEL UP!");
                    refresh();
                    napms(500);
                    createLevel(currentLevel);
                }
                break;
            }
        }
    }

    void moveVerticalEnemy(Enemy& obj) {
        obj.vertSpeed += 0.05f;
        obj.isFly = true;
        obj.y += obj.vertSpeed;

        for (auto& brick : bricks) {
            if (obj.checkCollision(brick)) {
                if (obj.vertSpeed > 0) obj.isFly = false;
                obj.y -= obj.vertSpeed;
                obj.vertSpeed = 0;
                break;
            }
        }
    }

    void handleMarioCollision() {
        for (auto it = enemies.begin(); it != enemies.end(); ) {
            if (mario.checkCollision(*it)) {
                if (it->type == 'o') {
                    if (mario.isFly && mario.vertSpeed > 0 && (mario.y + mario.height < it->y + it->height * 0.5f)) {
                        gameScore += 50;
                        it = enemies.erase(it);
                        continue;
                    } else {
                        playerDeath();
                        break;
                    }
                } else if (it->type == '$') {
                    gameScore += 100;
                    it = enemies.erase(it);
                    continue;
                }
            }
            ++it;
        }
    }

    void moveHorizontalEnemy(Enemy& obj) {
        obj.x += obj.horizonSpeed;

        for (const auto& brick : bricks) {
            if (obj.checkCollision(brick)) {
                obj.x -= obj.horizonSpeed;
                obj.horizonSpeed = -obj.horizonSpeed;
                return;
            }
        }

        if (obj.type == 'o') {
            Enemy tmp = obj;
            moveVerticalEnemy(tmp);
            if (tmp.isFly) {
                obj.x -= obj.horizonSpeed;
                obj.horizonSpeed = -obj.horizonSpeed;
            }
        }
    }

    void scrollMap(float dx) {
        mario.x -= dx;
        for (const auto& brick : bricks) {
            if (mario.checkCollision(brick)) {
                mario.x += dx;
                return;
            }
        }
        mario.x += dx;

        for (auto& brick : bricks) brick.x += dx;
        for (auto& enemy : enemies) enemy.x += dx;
    }

public:
    Game() {
        createLevel(currentLevel);
    }

    void run() {
        int ch;
        float current_dx = 0;

        while (running) {
            gameMap.clear();
            bool jump = false;
            bool moved = false;

            while ((ch = getch()) != ERR) {
                if (ch == ' ') jump = true;
                else if (ch == 'a' || ch == KEY_LEFT) { current_dx = 1.0f; moved = true; }
                else if (ch == 'd' || ch == KEY_RIGHT) { current_dx = -1.0f; moved = true; }
                else if (ch == 27) running = false;
            }

            if (jump && !mario.isFly) mario.vertSpeed = -1.2f;

            if (!moved) {
                current_dx *= 0.85f;
                if (std::fabs(current_dx) < 0.1f) current_dx = 0;
            }

            if (current_dx != 0) scrollMap(current_dx);

            if (mario.y > MAP_HEIGHT) playerDeath();

            moveVerticalMario();
            handleMarioCollision();

            for (const auto& brick : bricks) gameMap.placeObject(brick);

            for (auto it = enemies.begin(); it != enemies.end(); ) {
                moveVerticalEnemy(*it);
                moveHorizontalEnemy(*it);
                if (it->y > MAP_HEIGHT) {
                    it = enemies.erase(it);
                } else {
                    gameMap.placeObject(*it);
                    ++it;
                }
            }

            gameMap.placeObject(mario);
            gameMap.updateScore(gameScore);

            clear();
            move(0, 0);
            gameMap.display();
            mvprintw(0, 0, "Score: %d  Level: %d  A/D + Space | ESC to exit", gameScore, currentLevel);

            refresh();
            napms(10);
        }
    }
};

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    Game game;
    game.run();

    endwin();
    return 0;
}