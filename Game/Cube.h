#pragma once
#include "Object.h"

namespace Shader {
	class Program;
	class Texture;
}

class Cube : public Object {
public:
	Cube(const uint32_t id, Shader::Program* program);

	void quad(int a, int b, int c, int d);
	//void initialize(void* texturePointer) override;
	//oid draw(float interpolate) override;

	//int updateCPU(void* arg0) override;
	//void updateGPU() override;

private:
	const int numVertices = 36;

	GLuint _buffers;
	Shader::Program* _program;

	//point4 vertices[8]; // 8 vertexs del cub
	//color4 vertex_colors[8]; // 8 colors RGBA associats a cada vertex

	glm::vec2* _textureCoords;

	Shader::Texture* _texture;

	int Index;
};