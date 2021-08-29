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
		// disable all opponents
		// start timer of special state - opponents disable
		std::cout << "GameRules: SPECIAL_POINT_REACHED:\n";
		notifyAll(evt);
		notifyAll(Event::DISABLE_ALL_OPONENTS);
		Timer::instance().addPeriodElapsedCallback(std::bind(&GameRules::enableOpponentCb, this), 1.5);
		break;

	case Event::ALL_POINTS_COLLECTED:
		std::cout << "GameRules: ALL_POINTS_COLLECTED:\n";
		notifyAll(Event::STOP_MOTION);
		notifyAll(evt);
		break;

	case Event::PLAYER_CATCHED:
		std::cout << "GameRules: PLAYER_CATCHED\n";
		disableMotionForTime(startDelay);
		notifyAll(evt);
		notifyAll(Event::RESTART_POSITIONS);
		break;

	case Event::END_OF_LIVES:
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
	std::for_each(components.begin(), components.end(), 
				  [&playerPos](std::shared_ptr<GameMediatorComponent>& comp) { comp->notifyPlayerPosition(playerPos); });
}

void GameRules::notifyAll(Event evt) {
	std::for_each(components.begin(), components.end(),
				  [&evt](std::shared_ptr<GameMediatorComponent>& comp) { comp->notify(evt); });
}

void GameRules::setComponentsMediator(){
	std::for_each(components.begin(), components.end(),
				  [this](std::shared_ptr<GameMediatorComponent>& comp) { comp->setMediator(this); });
}

void GameRules::disableMotionForTime(double seconds){
	notifyAll(Event::STOP_MOTION);
	Timer::instance().addPeriodElapsedCallback(std::bind(&GameRules::enableMotionCb, this), seconds);
}

void GameRules::enableMotionCb(){
	notifyAll(Event::ALLOW_MOTION);
}

void GameRules::enableOpponentCb(){
	notifyAll(Event::ENABLE_ALL_OPONENTS);
}
