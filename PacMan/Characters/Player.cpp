#include "Player.h"

void Player::draw(){
	std::cout << " " + symbol;
}

void Player::update(){
    int c = 0;
    if (_kbhit()) {
        switch (c = _getch()) {
        case KEY_UP:
            move(Direction::SOUTH);
            break;
        case KEY_DOWN:
            move(Direction::NORTH);
            break;
        case KEY_LEFT:
            move(Direction::WEST);
            break;
        case KEY_RIGHT:
            move(Direction::EAST);
            break;
        default:
            break;
        }
    }
}

void Player::move(Direction dir){
    Position temp = currentPostion;
    moveTool.moveInDir(temp, dir);
    if (!MapManager::instance().isOccupied(temp)) {
        currentPostion = temp;
    }
}
