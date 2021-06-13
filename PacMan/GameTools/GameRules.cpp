#include "GameRules.h"

void GameRules::notify(Event evt){
	switch (evt){
	case Event::SPECIAL_POINT_REACHED:
		//disable all opponents
		//start timer of special state - oponents disable
		std::cout << "GameRules: SPECIAL_POINT_REACHED:\n";
		notifyAll(evt);
		break;
	case Event::ALL_POINTS_COLLECTED:
		//exit - win
		std::cout << "GameRules: ALL_POINTS_COLLECTED:\n";
		break;
	case Event::PLAYER_CATCHED:
		//decrement live
		std::cout << "GameRules: PLAYER_CATCHED\n";
		notifyAll(evt);
		break;
	case Event::END_OF_LIVES:
		//exit - lose
		std::cout << "GameRules: END_OF_LIVES:\n";
		break;
	case Event::LIFE_LOST:
		std::cout << "GameRules: LIFE_LOST:\n";
		notifyAll(evt);
		break;
	default:
		//usused events
		break;
	}
}

void GameRules::notifyPlayerPosition(Position& playerPos){
	for (auto& comp : components) {
		comp->notifyPlayerPosition(playerPos);
	}
}

void GameRules::notifyAll(Event evt) {
	for (auto& comp : components) {
		comp->notify(evt);
	}
}
