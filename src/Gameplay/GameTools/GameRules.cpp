#include "GameRules.h"

GameRules::GameRules(std::vector<std::shared_ptr<GameMediatorComponent>> comp) :
					components(comp), GameMediator()
{
	setComponentsMediator();
	motionTimer.setCallback(std::bind(&GameRules::enableMotionCb, this));

	notifyAll(Event::STOP_MOTION);

};

void GameRules::notify(Event evt){
	switch (evt){
	case Event::START_GAME:
		reset();
		notifyAll(Event::ENABLE_ALL_OPPONENTS);
		disableMotionForTime(startDelay);
		break;

	case Event::SPECIAL_POINT_REACHED:
		// disable all opponents
		// start timer of special state - opponents disable
		std::cout << "GameRules: SPECIAL_POINT_REACHED:\n";
		notifyAll(evt);
		notifyAll(Event::DISABLE_ALL_OPPONENTS);
		break;

	case Event::ALL_POINTS_COLLECTED:
		std::cout << "GameRules: ALL_POINTS_COLLECTED:\n";
		reset();
		notifyAll(Event::STOP_MOTION);
		notifyAll(evt);
		break;
	case Event::DISABLED_GHOST_CATCHED:
		notifyAll(evt);
		break;
	case Event::PLAYER_CATCHED:
		std::cout << "GameRules: PLAYER_CATCHED\n";
		reset();
		disableMotionForTime(startDelay);
		notifyAll(evt);
		notifyAll(Event::RESTART_POSITIONS);
		break;

	case Event::END_OF_LIVES:
		std::cout << "GameRules: END_OF_LIVES:\n";
		reset();
		notifyAll(Event::STOP_MOTION);
		notifyAll(Event::END_OF_LIVES);
		break;

	case Event::RESET_GAME:
		notifyAll(Event::RESTART_POSITIONS);
		notifyAll(Event::RESET_GAME);
		break;
	case Event::WARNING_NEAR_ENABLE_ALL_OPPONENTS:
		notifyAll(evt);
		break;

	default:
		//usused events
		break;
	}
}

void GameRules::notifyPlayerPosition(const Position& playerPos){
	std::for_each(components.begin(), components.end(), 
				  [&playerPos](std::weak_ptr<GameMediatorComponent> comp) { comp.lock()->notifyPlayerPosition(playerPos); });
}

void GameRules::notifyAll(Event evt) {
	std::for_each(components.begin(), components.end(),
				  [&evt](std::weak_ptr<GameMediatorComponent> comp) { comp.lock()->notify(evt); });
}

void GameRules::setComponentsMediator(){
	std::for_each(components.begin(), components.end(),
				  [this](std::weak_ptr<GameMediatorComponent> comp) { comp.lock()->setMediator(this); });
}

void GameRules::disableMotionForTime(double seconds){
	notifyAll(Event::STOP_MOTION);
	motionTimer.startPeriodElapse(seconds);
}

void GameRules::enableMotionCb(){
	notifyAll(Event::ALLOW_MOTION);
}

void GameRules::reset(){
	notifyAll(Event::RESET_OPPONENTS_STATE);
	motionTimer.reset();
}
