#include "Transformation.h"

Transformation::Transformation()
	: angle(0), move(0), rotation(0,0,1), scale(1){}

void Transformation::setTranslation(float x, float y, float z){
	move = Coordinates(x, y, z);
}

void Transformation::setRotation(float degAngle){
	angle = degAngle;
}

void Transformation::setScale(float sc){
	scale = Coordinates(sc);
}

void Transformation::setScale(float scX, float scY, float scZ){
	scale = Coordinates(scX, scY, scZ);
}

void Transformation::setRotationAxis(Axis ax){
	switch (ax)
	{
	case Transformation::Axis::X:
		setRotationAxis(1, 0, 0);
		break;
	case Transformation::Axis::Y:
		setRotationAxis(0, 1, 0);
		break;
	case Transformation::Axis::Z:
		setRotationAxis(0, 0, 1);
		break;
	default:
		break;
	}
}

void Transformation::setRotationAxis(float rotX, float rotY, float rotZ){
	rotation = Coordinates(rotX, rotY, rotZ);
}

const float* Transformation::getPointer(){
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(move.x, move.y, move.z));
	trans = glm::rotate(trans, glm::radians(angle), glm::vec3(rotation.x, rotation.y, rotation.z));
	trans = glm::scale(trans, glm::vec3(scale.x, scale.y, scale.z));

	return glm::value_ptr(trans);

}
