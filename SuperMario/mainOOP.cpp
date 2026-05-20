#include <cmath>
#include <cstring>
#include <iostream>
#include <ncurses.h>
#include <vector>

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 40;

const float PHYSICS_GRAVITY = 0.05f;
const float MARIO_JUMP_SPEED = -1.2f;
const float ENEMY_START_SPEED = 0.2f;
const float COIN_VERT_SPEED = -0.7f;
const float SCROLL_FRICTION = 0.85f;
const float MIN_SCROLL_SPEED = 0.1f;

const int SCORE_ENEMY_DEATH = 50;
const int SCORE_COIN_COLLECT = 100;

const int GAME_TICK_MS = 10;
const int DEATH_SCREEN_MS = 500;

const char TYPE_MARIO = '@';
const char TYPE_BRICK_NORMAL = '#';
const char TYPE_BRICK_BONUS = '?';
const char TYPE_BRICK_EMPTY = '-';
const char TYPE_BRICK_EXIT = '+';
const char TYPE_ENEMY_GOOMBA = 'o';
const char TYPE_ENEMY_COIN = '$';

class GameObject {
public:
    float x, y, width, height;
    char type;

    GameObject(float x = 0, float y = 0, float w = 0, float h = 0, 
               char t = ' ');
    bool checkCollision(const GameObject& other) const;
};

class Brick : public GameObject {
public:
    Brick(float x = 0, float y = 0, float w = 0, float h = 0, 
          char t = TYPE_BRICK_NORMAL);
};

class Enemy : public GameObject {
public:
    float vertSpeed, horizonSpeed;
    bool isFly;

    Enemy(float x = 0, float y = 0, float w = 0, float h = 0, 
          char t = TYPE_ENEMY_GOOMBA);
};

class Mario : public GameObject {
public:
    float vertSpeed;
    bool isFly;

    Mario(float x = 0, float y = 0, float w = 0, float h = 0, 
          char t = TYPE_MARIO);
};

class GameMap {
private:
    char map[MAP_HEIGHT][MAP_WIDTH + 1];
    bool isPositionValid(int x, int y) const;

public:
    void clear();
    void display() const;
    void placeObject(const GameObject& obj);
    void updateScore(int score);
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

    void createLevel(int lvl);
    void handleMarioCollision();
    void moveHorizontalEnemy(Enemy& obj);
    void moveVerticalEnemy(Enemy& obj);
    void moveVerticalMario();
    void playerDeath();
    void scrollMap(float dx);

public:
    Game();
    void run();
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

GameObject::GameObject(float x, float y, float w, float h, char t)
    : x(x), y(y), width(w), height(h), type(t) {}

bool GameObject::checkCollision(const GameObject& other) const {
    return ((x + width) > other.x) && 
           (x < (other.x + other.width)) &&
           ((y + height) > other.y) && 
           (y < (other.y + other.height));
}

Brick::Brick(float x, float y, float w, float h, char t)
    : GameObject(x, y, w, h, t) {}

Enemy::Enemy(float x, float y, float w, float h, char t)
    : GameObject(x, y, w, h, t), vertSpeed(0), 
      horizonSpeed(ENEMY_START_SPEED), isFly(true) {}

Mario::Mario(float x, float y, float w, float h, char t)
    : GameObject(x, y, w, h, t), vertSpeed(0), isFly(true) {}

void GameMap::clear() {
    for (int i = 0; i < MAP_WIDTH; i++) map[0][i] = ' ';
    map[0][MAP_WIDTH] = '\0';
    for (int j = 0; j < MAP_HEIGHT; j++) sprintf(map[j], "%s", map[0]);
}

void GameMap::display() const {
    for (int j = 0; j < MAP_HEIGHT; j++) mvprintw(j, 0, "%s", map[j]);
}

bool GameMap::isPositionValid(int x, int y) const {
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}

void GameMap::placeObject(const GameObject& obj) {
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

void GameMap::updateScore(int score) {
    char buffer[30];
    sprintf(buffer, "Score: %d", score);
    int len = strlen(buffer);
    for (int i = 0; i < len; i++) {
        map[1][i + 5] = buffer[i];
    }
}

Game::Game() {
    createLevel(currentLevel);
}

void Game::createLevel(int lvl) {
    bricks.clear();
    enemies.clear();
    mario = Mario(39, 10, 3, 3, TYPE_MARIO);
    mario.isFly = false;
    gameScore = 0;

    switch (lvl) {
        case 1:
            bricks.emplace_back(20, 20, 40, 5, TYPE_BRICK_NORMAL);
            bricks.emplace_back(30, 10, 5, 3, TYPE_BRICK_BONUS);
            bricks.emplace_back(50, 10, 5, 3, TYPE_BRICK_BONUS);
            bricks.emplace_back(60, 15, 40, 10, TYPE_BRICK_NORMAL);
            bricks.emplace_back(60, 5, 10, 3, TYPE_BRICK_EMPTY);
            bricks.emplace_back(70, 5, 5, 3, TYPE_BRICK_BONUS);
            bricks.emplace_back(75, 5, 5, 3, TYPE_BRICK_EMPTY);
            bricks.emplace_back(80, 5, 5, 3, TYPE_BRICK_BONUS);
            bricks.emplace_back(85, 5, 10, 3, TYPE_BRICK_EMPTY);
            bricks.emplace_back(100, 20, 20, 5, TYPE_BRICK_NORMAL);
            bricks.emplace_back(120, 15, 10, 10, TYPE_BRICK_NORMAL);
            bricks.emplace_back(150, 20, 40, 5, TYPE_BRICK_NORMAL);
            bricks.emplace_back(210, 15, 10, 10, TYPE_BRICK_EXIT);
            enemies.emplace_back(25, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(80, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            break;
        case 2:
            bricks.emplace_back(20, 20, 40, 5, TYPE_BRICK_NORMAL);
            bricks.emplace_back(60, 15, 10, 10, TYPE_BRICK_NORMAL);
            bricks.emplace_back(80, 20, 20, 5, TYPE_BRICK_NORMAL);
            bricks.emplace_back(120, 15, 10, 10, TYPE_BRICK_NORMAL);
            bricks.emplace_back(150, 20, 40, 5, TYPE_BRICK_NORMAL);
            bricks.emplace_back(210, 15, 10, 10, TYPE_BRICK_EXIT);
            enemies.emplace_back(25, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(80, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(65, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(120, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(160, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(175, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            break;
        case 3:
            bricks.emplace_back(20, 20, 40, 5, TYPE_BRICK_NORMAL);
            bricks.emplace_back(80, 20, 15, 5, TYPE_BRICK_NORMAL);
            bricks.emplace_back(120, 15, 15, 10, TYPE_BRICK_NORMAL);
            bricks.emplace_back(160, 10, 15, 15, TYPE_BRICK_EXIT);
            enemies.emplace_back(25, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(50, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(80, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(90, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(120, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            enemies.emplace_back(130, 10, 3, 2, TYPE_ENEMY_GOOMBA);
            break;
        default:
            break;
    }
}

void Game::handleMarioCollision() {
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (mario.checkCollision(*it)) {
            if (it->type == TYPE_ENEMY_GOOMBA) {
                if (mario.isFly && mario.vertSpeed > 0 && 
                    (mario.y + mario.height < it->y + it->height * 0.5f)) {
                    gameScore += SCORE_ENEMY_DEATH;
                    it = enemies.erase(it);
                    continue;
                } else {
                    playerDeath();
                    break;
                }
            } else if (it->type == TYPE_ENEMY_COIN) {
                gameScore += SCORE_COIN_COLLECT;
                it = enemies.erase(it);
                continue;
            }
        }
        ++it;
    }
}

void Game::moveHorizontalEnemy(Enemy& obj) {
    obj.x += obj.horizonSpeed;

    for (const auto& brick : bricks) {
        if (obj.checkCollision(brick)) {
            obj.x -= obj.horizonSpeed;
            obj.horizonSpeed = -obj.horizonSpeed;
            return;
        }
    }

    if (obj.type == TYPE_ENEMY_GOOMBA) {
        Enemy tmp = obj;
        moveVerticalEnemy(tmp);
        if (tmp.isFly) {
            obj.x -= obj.horizonSpeed;
            obj.horizonSpeed = -obj.horizonSpeed;
        }
    }
}

void Game::moveVerticalEnemy(Enemy& obj) {
    obj.vertSpeed += PHYSICS_GRAVITY;
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

void Game::moveVerticalMario() {
    mario.vertSpeed += PHYSICS_GRAVITY;
    mario.isFly = true;
    mario.y += mario.vertSpeed;

    for (auto& brick : bricks) {
        if (mario.checkCollision(brick)) {
            if (mario.vertSpeed > 0) mario.isFly = false;

            if (brick.type == TYPE_BRICK_BONUS && mario.vertSpeed < 0) {
                brick.type = TYPE_BRICK_EMPTY;
                Enemy coin(brick.x, brick.y - 3, 3, 2, TYPE_ENEMY_COIN);
                coin.vertSpeed = COIN_VERT_SPEED;
                enemies.push_back(coin);
            }

            mario.y -= mario.vertSpeed;
            mario.vertSpeed = 0;

            if (brick.type == TYPE_BRICK_EXIT) {
                currentLevel++;
                if (currentLevel > maxLevel) currentLevel = 1;
                mvprintw(MAP_HEIGHT / 2, MAP_WIDTH / 2 - 4, "LEVEL UP!");
                refresh();
                napms(DEATH_SCREEN_MS);
                createLevel(currentLevel);
            }
            break;
        }
    }
}

void Game::playerDeath() {
    mvprintw(MAP_HEIGHT / 2, MAP_WIDTH / 2 - 5, "GAME OVER");
    refresh();
    napms(DEATH_SCREEN_MS);
    createLevel(currentLevel);
}

void Game::run() {
    int ch;
    float current_dx = 0;

    while (running) {
        gameMap.clear();
        bool jump = false;
        bool moved = false;

        while ((ch = getch()) != ERR) {
            if (ch == ' ') jump = true;
            else if (ch == 'a' || ch == KEY_LEFT)  
                { current_dx = 1.0f; moved = true; } 
            else if (ch == 'd' || ch == KEY_RIGHT) 
                { current_dx = -1.0f; moved = true; }
            else if (ch == 27) running = false;
        }

        if (jump && !mario.isFly) mario.vertSpeed = MARIO_JUMP_SPEED;

        if (!moved) {
            current_dx *= SCROLL_FRICTION;
            if (std::fabs(current_dx) < MIN_SCROLL_SPEED) current_dx = 0;
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
        mvprintw(0, 0, 
                 "Score: %d  Level: %d  A/D + Space | ESC to exit", 
                 gameScore, currentLevel);

        refresh();
        napms(GAME_TICK_MS);
    }
}

void Game::scrollMap(float dx) {
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