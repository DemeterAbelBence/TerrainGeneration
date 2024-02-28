#include "Sun.hpp"



Sun::Sun(unsigned int N, unsigned int M, glm::vec3 _center) : Surface (N, M) {
	light_position = _center;
	setCenter(_center);
}

void Sun::translateX(float speed) {
	translation.x += speed;
	light_position.x += speed;
}

void Sun::translateY(float speed) {
	translation.y += speed;
	light_position.y += speed;
}

void Sun::translateZ(float speed) {
	translation.z += speed;
	light_position.z += speed;
}

void Sun::rotate(float speed) {}

void Sun::eval(float x, float y, glm::vec3& pos, glm::vec3& norm) {
	float u = x * 2 * (float)3.14157;
	float v = y * (float)3.14157;

	pos.x = radius * sinf(u) * cosf(v) + center.x;
	pos.y = radius * sinf(u) * sinf(v) + center.y;
	pos.z = radius * cosf(u) + center.z;

	norm = glm::normalize(pos - center);
}

void Sun::setUniformLight(const GpuProgram& progarm) const { 
	progarm.bind();
	progarm.setVec3("light", light_position);
}
