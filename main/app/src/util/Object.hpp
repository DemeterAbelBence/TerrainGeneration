#pragma once

#include "gl/VertexArray.hpp"
#include "gl/GpuProgram.hpp"
#include "tex/Texture.hpp"
#include "datatypes/Material.hpp"
#include "Transformable.hpp"

#include <glm.hpp>

class Object : public Transformable {

protected:
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
	VertexBufferLayout vertexBufferLayout;

	GpuProgram* program;
	Material* material;

	std::vector<Texture*> textures;

	unsigned int primitiveType;

public:
	Object();

	void setNewProgram(const GpuProgram& _program);
	void setNewMaterial(const Material& _material);
	void addNewTexture(const Texture& _texture);

	inline GpuProgram* getProgram() const { return program; }
	inline Material* getMaterial() const { return material; }
	inline std::vector<Texture*> getTextures() const { return textures; }

	inline void setPrimitive(unsigned int type) { primitiveType = type; }

	void setAllUniforms() const;
	
	virtual void create() = 0;
	virtual void draw() const = 0;

	virtual ~Object();
};