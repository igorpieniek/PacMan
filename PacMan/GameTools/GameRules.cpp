#include "GameRules.h"

void GameRules::notify(Event evt){
	switch (evt){
	case Event::SPECIAL_POINT_REACHED:
		//disable all opponents
		//start timer of special state - oponents disable
		break;
	case Event::ALL_POINTS_COLLECTED:
		//exit - win
		break;
	case Event::PLAYER_CATCHED:
		//decrement live
		break;
	case Event::END_OF_LIVES:
		//exit - lose
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
