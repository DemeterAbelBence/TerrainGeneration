#include "Transformable.hpp"

Transformable::Transformable() {
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotationAngle = 0.0f;
	rotationAxis = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Transformable::rotate(float angle) {
	rotationAngle += angle * 3.14157f;
	center = glm::vec3(glm::vec4(center, 1) * makeRotationMatrix());
}

glm::mat4 Transformable::makeModelMatrix() const {
	glm::mat4 t = makeTranslationMatrix();
	glm::mat4 s = makeScaleMatrix();
	glm::mat4 r = makeRotationMatrix();

	return r * t * s;
}

glm::mat4 Transformable::makeModelInverseMatrix() const {
	glm::mat4 t = makeTranslationInverseMatrix();
	glm::mat4 s = makeScaleInverseMatrix();
	glm::mat4 r = makeRotationInverseMatrix();

	return r * t * s;
}

void Transformable::resetTransformations() {
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotationAngle = 0.0f;
}

glm::mat4 Transformable::makeTranslationMatrix() const {
	glm::mat4 t;
	t[0] = glm::vec4(1.0f, 0.0f, 0.0f, translation.x);
	t[1] = glm::vec4(0.0f, 1.0f, 0.0f, translation.y);
	t[2] = glm::vec4(0.0f, 0.0f, 1.0f, translation.z);
	t[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return t;
}

glm::mat4 Transformable::makeScaleMatrix() const {
	glm::mat4 s;
	s[0] = glm::vec4(scale.x, 0.0f, 0.0f, 0.0f);
	s[1] = glm::vec4(0.0f, scale.y, 0.0f, 0.0f);
	s[2] = glm::vec4(0.0f, 0.0f, scale.z, 0.0f);
	s[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return s;
}

glm::mat4 Transformable::makeRotationMatrix() const {
	glm::mat4 r;
	float a = rotationAngle / 180;
	r[0] = glm::vec4(cosf(a), 0.0f, -sinf(a), 0.0f);
	r[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	r[2] = glm::vec4(sinf(a), 0.0f, cosf(a), 0.0f);
	r[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return r;
}

glm::mat4 Transformable::makeTranslationInverseMatrix() const {
	glm::mat4 t;
	t[0] = glm::vec4(1.0f, 0.0f, 0.0f, -translation.x);
	t[1] = glm::vec4(0.0f, 1.0f, 0.0f, -translation.y);
	t[2] = glm::vec4(0.0f, 0.0f, 1.0f, -translation.z);
	t[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return t;
}

glm::mat4 Transformable::makeScaleInverseMatrix() const {
	glm::mat4 s;
	s[0] = glm::vec4(1/ scale.x, 0.0f, 0.0f, 0.0f);
	s[1] = glm::vec4(0.0f, 1 / scale.y, 0.0f, 0.0f);
	s[2] = glm::vec4(0.0f, 0.0f, 1 / scale.z, 0.0f);
	s[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return s;
}

glm::mat4 Transformable::makeRotationInverseMatrix() const {
	glm::mat4 r;
	float a = -rotationAngle * 3.14152f / 180.0f;
	r[0] = glm::vec4(cosf(a), 0.0f, -sinf(a), 0.0f);
	r[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	r[2] = glm::vec4(sinf(a), 0.0f, cosf(a), 0.0f);
	r[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return r;
}
