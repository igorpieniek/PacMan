#pragma once

#ifndef __MEDIATOR_H__
#define __MEDIATOR_H__

enum class Event {
	SPECIAL_POINT_REACHED,
	ALL_POINTS_COLLECTED,
	DISABLE_ALL_OPONENTS,
	ENABLE_ALL_OPONENTS,
	PLAYER_CATCHED,
	END_OF_LIVES
};


class MediatorComponent;

class Mediator {
public:
	virtual void notify( Event evt) = 0;
};


class MediatorComponent {
public:
	MediatorComponent(Mediator* med = nullptr) : mediator(med) {};
	void setMediator(Mediator* med) { mediator = med; };

protected:
	Mediator* mediator;

};

#endif //__MEDIATOR_H__
