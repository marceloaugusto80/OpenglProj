#pragma once

#include "OpenGl.h"
#include "Utils\Utils.h"
#include "GameContext.h"

struct Vertex
{
	Vec4 Coord;
	Vec2 UV;
	float TexIndex; // float because glsl texture() functions has a float as parameter for texture index
	Vec4 Color;
};


struct Quad
{
	Vertex V1, V2, V3, V4, V5, V6;
};



class OglRenderer : NonCopyable
{
	#define UNIFORM_BLOCK_BINDING_POINT 1
	#define ATTRIBUTE_NAME_VERTEX_POSITION "position"
	#define ATTRIBUTE_NAME_TEXTURE_UV "uv"
	#define ATTRIBUTE_NAME_TEXTURE_IDX "texIndex"
	#define ATTRIBUTE_NAME_COLOR "color"
	#define UNIFORM_BLOCK_MODEL_INFO "ModelInfo"
	#define UNIFORM_NAME_PROJECTION_MATRIX "projection"
	#define UNIFORM_NAME_SAMPLER_TEX_ARRAY "texArray"

	GLuint m_vao, 
		   m_vbo, 
		   m_ubo,
		   m_textureArrayId,
		   m_programId;
	
	GLint m_projMatUniIdx,
		  m_samplerUniIdx;

	unsigned int m_spriteMaxCount;
	
	SystemContext* m_context;

	Quad* m_quadBuffer;

	static Mat4f ProjectionMatrix;

	bool m_isFullscreen;

	static int restoredWindowWidth, restoredWindowHeight;
	
	//

	OglRenderer() :
		m_vao(0),
		m_vbo(0),
		m_ubo(0),
		m_textureArrayId(0),
		m_projMatUniIdx(-1),
		m_samplerUniIdx(-1),
		m_context(0),
		m_quadBuffer(0),
		m_spriteMaxCount(0),
		m_isFullscreen(false)
	{}

public:

	~OglRenderer();

	static OglRenderer* Create(GameContext* context, unsigned int spriteMaxCount, GLuint textureArrayId,
		unsigned int initialScreenWidth, unsigned int initialScreenHeight);
		
	//
	
	void DrawBuffers(size_t size);


	Quad* GetQuadBuffer()
	{
		return m_quadBuffer;
	}

	static void OnWindowResize(GameContext* window, int width, int height);

	static void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam);

	void ToggleFullscreen();

};
