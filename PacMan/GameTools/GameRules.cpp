#include "GameRules.h"

GameRules::GameRules(std::vector<std::shared_ptr<GameMediatorComponent>> comp) :
					components(comp), GameMediator()
{
	setComponentsMediator();
	notifyAll(Event::STOP_MOTION);
	
};


void GameRules::notify(Event evt){
	switch (evt){
	case Event::START_GAME:
		disableMotionForTime(startDelay);
		break;
	case Event::SPECIAL_POINT_REACHED:
		//disable all opponents
		//start timer of special state - oponents disable
		std::cout << "GameRules: SPECIAL_POINT_REACHED:\n";
		notifyAll(evt);
		break;
	case Event::ALL_POINTS_COLLECTED:
		//exit - win
		std::cout << "GameRules: ALL_POINTS_COLLECTED:\n";
		notifyAll(Event::STOP_MOTION);
		notifyAll(evt);
		break;
	case Event::PLAYER_CATCHED:
		//decrement live
		std::cout << "GameRules: PLAYER_CATCHED\n";
		disableMotionForTime(startDelay);
		notifyAll(Event::LIFE_LOST);
		notifyAll(Event::RESTART_POSITIONS);
		

		break;

	case Event::END_OF_LIVES:
		//exit - lose
		std::cout << "GameRules: END_OF_LIVES:\n";
		Timer::instance().reset();
		notifyAll(Event::STOP_MOTION);
		notifyAll(Event::END_OF_LIVES);

		break;
	case Event::RESET_GAME:

		notifyAll(Event::RESTART_POSITIONS);
		notifyAll(Event::RESET_GAME);
		
		
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

void GameRules::setComponentsMediator(){
	for (auto& comp : components) {
		comp->setMediator(this);
	}
}


void GameRules::disableMotionForTime(double seconds){
	notifyAll(Event::STOP_MOTION);
	Timer::instance().addPeriodElapsedCallback(std::bind(&GameRules::enableMotionCb, this), seconds);
}

void GameRules::enableMotionCb(){
	notifyAll(Event::ALLOW_MOTION);
	//std::cout << "Time elapsed and cb called successfully!\n";
}
