#include "Terrain.hpp"

Terrain::Terrain(unsigned int n) : PatchSurface(n) {
	amplitude = 0.0f;
	phase = 0.0f;
	iterations = 0.0f;
}

void Terrain::setTesselationParameters(unsigned int min_t, unsigned int max_t, float min_d, float max_d) {
	minimal_tesselation = min_t;
	maximal_tesselation = max_t;
	minimal_distance = min_d;
	maximal_distance = max_d;
}

void Terrain::setUniformParameters(const GpuProgram& program) {
	program.bind();
	program.setFloat("amplitude_factor", amplitude);
	program.setFloat("phase_factor", phase);
	program.setInt("iterations", iterations);

	program.setFloat("MIN_DIST", minimal_distance);
	program.setFloat("MAX_DIST", maximal_distance);
	program.setInt("MIN_TESS", minimal_tesselation);
	program.setInt("MAX_TESS", maximal_tesselation);
}
