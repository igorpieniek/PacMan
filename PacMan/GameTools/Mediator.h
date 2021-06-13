#pragma once

#ifndef __MEDIATOR_H__
#define __MEDIATOR_H__

#include "Position.h"

enum class Event {
	SPECIAL_POINT_REACHED,
	ALL_POINTS_COLLECTED,
	DISABLE_ALL_OPONENTS,
	ENABLE_ALL_OPONENTS,
	PLAYER_CATCHED,
	END_OF_LIVES,
	LIFE_LOST,
};




class Mediator {
public:
	virtual void notify( Event evt) = 0;
};


class MediatorComponent {
public:
	MediatorComponent(Mediator* med = nullptr) : mediator(med) {};
	void setMediator(Mediator* med) { mediator = med; };
	virtual void notify(Event evt) = 0;

protected:
	Mediator* mediator;
};



class PlayerPositionPropagator {
public:
	virtual void notifyPlayerPosition(Position& pos) = 0;
};

class GameMediator : public Mediator, 
				     public PlayerPositionPropagator {};

class GameMediatorComponent : public MediatorComponent, 
							  public PlayerPositionPropagator {};



#endif //__MEDIATOR_H__
