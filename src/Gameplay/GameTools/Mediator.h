#pragma once

#include "Position.h"

enum class Event {
	START_GAME,
	RESET_GAME,
	SPECIAL_POINT_REACHED,
	ALL_POINTS_COLLECTED,
	DISABLE_ALL_OPPONENTS,
	ENABLE_ALL_OPPONENTS,
	WARNING_NEAR_ENABLE_ALL_OPPONENTS,
	RESET_OPPONENTS_STATE,
	DISABLED_GHOST_CATCHED,
	PLAYER_CATCHED,
	END_OF_LIVES,
	RESTART_POSITIONS,
	ALLOW_MOTION,
	STOP_MOTION
};




class Mediator {
public:
	virtual void notify( Event evt) = 0;
};


class MediatorComponent: public Mediator {
public:
	MediatorComponent(Mediator* med = nullptr) : mediator(med) {};
	void setMediator(Mediator* med) { mediator = med; };

protected:
	Mediator* mediator;
};



class PlayerPositionPropagator {
public:
	virtual void notifyPlayerPosition(const Position& pos) = 0;
};

class GameMediator : public Mediator, 
				     public PlayerPositionPropagator {};

class GameMediatorComponent : public MediatorComponent, 
							  public PlayerPositionPropagator {};

