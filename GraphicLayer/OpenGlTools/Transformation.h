#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Transformation {
public:

	enum class Axis {
		X,Y,Z
	};

	Transformation();
	void setTranslation(float x, float y, float z = {});
	void setRotation(float degAngle);
	void setScale(float sc);
	void setScale(float scX, float scY, float scZ);
	void setRotationAxis(Axis ax);
	void setRotationAxis(float rotX, float rotY, float rotZ);
	const float* getPointer();

private:
	struct Coordinates {
		float x, y, z;
		Coordinates(float val) : x(val), y(val), z(val) {};
		Coordinates(float X, float Y, float Z) : x(X), y(Y), z(Z) {};
	};

	float angle;
	Coordinates scale;
	Coordinates move;
	Coordinates rotation;

	glm::mat4 trans;
	
};

