#pragma once

#include "util/Surface.hpp";

class Sun : public Surface {

private:
	glm::vec3 light_position;
	float radius;

public:
	Sun(unsigned int N, unsigned int M, glm::vec3 _center);
	inline void setRadius(float value) { radius = value; }

	void translateX(float speed) override;
	void translateY(float speed) override;
	void translateZ(float speed) override;

	void rotate(float degrees) override;
	void eval(float u, float v, glm::vec3& pos, glm::vec3& norm) override;

	void setUniformLight(const GpuProgram& progarm) const;
};