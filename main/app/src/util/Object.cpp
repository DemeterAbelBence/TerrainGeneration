#include "Object.hpp"

Object::Object() { 
	program = nullptr; 
	material = nullptr;

	primitiveType = GL_TRIANGLES;
}

void Object::setNewProgram(const GpuProgram& _program) {
	if (program)
		delete program;
	program = new GpuProgram(_program);
}

void Object::setNewMaterial(const Material& _material) {
	if (material)
		delete material;
	material = new Material(_material);
}

void Object::addNewTexture(const Texture& _texture) {
	textures.push_back(new Texture(_texture));
}

void Object::setAllUniforms() const {
	if (program) {
		program->bind();

		program->setMat4("M", makeModelMatrix());
		program->setMat4("MI", makeModelInverseMatrix());

		if (material) {
			program->setVec3("material.ambient", material->ambient);
			program->setVec3("material.diffuse", material->diffuse);
			program->setVec3("material.specular", material->specular);
			program->setFloat("material.shininess", material->shininess);
		}

		GLenum glParam = GL_TEXTURE0;
		for (const auto& t : textures) {
			glActiveTexture(glParam++);
			t->bind();
		}

		glUniform1i(glGetUniformLocation(program->getProgramId(), "grass_texture"), 0);
		glUniform1i(glGetUniformLocation(program->getProgramId(), "dirt_texture"), 1);
		glUniform1i(glGetUniformLocation(program->getProgramId(), "rock_texture"), 2);
		glUniform1i(glGetUniformLocation(program->getProgramId(), "snow_texture"), 3);
	}
}

Object::~Object() {
	delete program;
	delete material;
}
