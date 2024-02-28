#pragma once

#include <glm.hpp>

#include "gl/GpuProgram.hpp"

class Transformable {

protected:
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 translation;
	glm::vec3 scale;
	glm::vec3 rotationAxis;
	float rotationAngle;

public:
	Transformable();

	inline void setTranslation(glm::vec3 t) { translation = t; }
	inline void setScale(glm::vec3 s) { scale = s; }
	inline void setRotationAxis(glm::vec3 r) { rotationAxis = r; }
	inline void setRotationAngle(float r) { rotationAngle = r; }
	inline void setCenter(glm::vec3 value) { center = value; }
	inline glm::vec3 getCenter() const { return center; }

	virtual inline void translateX(float speed) { translation.x += speed; }
	virtual inline void translateY(float speed) { translation.y += speed; }
	virtual inline void translateZ(float speed) { translation.z += speed; }
	virtual void rotate(float angle);

	glm::mat4 makeModelMatrix() const;
	glm::mat4 makeModelInverseMatrix() const;
	void resetTransformations();

	glm::mat4 makeTranslationMatrix() const;
	glm::mat4 makeScaleMatrix() const;
	glm::mat4 makeRotationMatrix() const;

	glm::mat4 makeTranslationInverseMatrix() const;
	glm::mat4 makeScaleInverseMatrix() const;
	glm::mat4 makeRotationInverseMatrix() const;
};