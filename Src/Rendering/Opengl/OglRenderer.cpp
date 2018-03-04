#include "stdafx.h"
#include "OglRenderer.h"
#include "ShaderProgram.h"
#include "Common.h"


Mat4f OglRenderer::ProjectionMatrix = Mat4f(1.0f);
int OglRenderer::restoredWindowWidth = 400;
int OglRenderer::restoredWindowHeight = 400;


OglRenderer::~OglRenderer()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ubo);
	glDeleteProgram(m_programId);
	delete[] m_quadBuffer;

}



OglRenderer * OglRenderer::Create(GameContext * context, unsigned int spriteMaxCount, GLuint textureArrayId, unsigned int initialScreenWidth, unsigned int initialScreenHeight)
{
	GLuint 
		vao, 
		vbo, 
		progId;
	
	GLint
		uniformProjectionIdx,
		uniformTexSamplerIdx;

	// capture opengl messages
	
	glDebugMessageCallback(OglRenderer::DebugCallback, 0);

	// general flags ----------------------------------------------------

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glDisable(GL_ALPHA_TEST);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// compile shader ---------------------------------------------------------

	progId = ShaderProgram::Compile("vertex", "fragment");
	if (progId == 0)
	{
		PRINT("Shader compile Error");
		PRINT(ShaderProgram::GetLastError());
		return 0;
	}


	// map shader ------------------------------------------------------------

	// NOTE glsl mat4 type takes 4 shader attribute slots. one for each column of the matrix
	uniformProjectionIdx = glGetUniformLocation(progId, UNIFORM_NAME_PROJECTION_MATRIX);
	assert(uniformProjectionIdx >= 0);

	uniformTexSamplerIdx = glGetUniformLocation(progId, UNIFORM_NAME_SAMPLER_TEX_ARRAY);
	assert(uniformTexSamplerIdx >= 0);
		
	GLint posAttIdx = glGetAttribLocation(progId, ATTRIBUTE_NAME_VERTEX_POSITION);
	assert(posAttIdx >= 0);

	GLint texUvAttIdx = glGetAttribLocation(progId, ATTRIBUTE_NAME_TEXTURE_UV);
	assert(texUvAttIdx >= 0);

	GLint texIdxAttIdx = glGetAttribLocation(progId, ATTRIBUTE_NAME_TEXTURE_IDX);
	assert(texIdxAttIdx >= 0);

	GLint colorAttIdx = glGetAttribLocation(progId, ATTRIBUTE_NAME_COLOR);
	assert(colorAttIdx >= 0);




	int posOffset = 0;
	int texUvOffset = sizeof(Vec4);
	int texIdOffset = texUvOffset + sizeof(Vec2);
	int colorOffset = texIdOffset + sizeof(float);
	GLint stride = sizeof(Vertex);

	// generate buffers ----------------------------------

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	// buffer setup -----------------------------------------

	glBindVertexArray(vao);
	glUseProgram(progId);

	// vertex buffer

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// NOTE vao must be bound to setup attribute pointers!!!
	glEnableVertexAttribArray(posAttIdx);
	glVertexAttribPointer(
		posAttIdx,
		4,
		GL_FLOAT,
		GL_FALSE,
		stride,
		(void*)posOffset
	);

	glEnableVertexAttribArray(texUvAttIdx);
	glVertexAttribPointer(
		texUvAttIdx,
		2,
		GL_FLOAT,
		GL_FALSE,
		stride,
		(void*)texUvOffset
	);

	glEnableVertexAttribArray(texIdxAttIdx);
	glVertexAttribPointer(
		texIdxAttIdx,
		1,
		GL_FLOAT,
		GL_FALSE,
		stride,
		(void*)texIdOffset
	);

	glEnableVertexAttribArray(colorAttIdx);
	glVertexAttribPointer(
		colorAttIdx,
		4,
		GL_FLOAT,
		GL_FALSE,
		stride,
		(void*)colorOffset
	);

	glBufferData(GL_ARRAY_BUFFER, spriteMaxCount * sizeof(Quad), 0, GL_DYNAMIC_DRAW);


	// release ogl resources -------------------------------------------------------

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// video params initialization

	glfwSetWindowSize(context, initialScreenWidth, initialScreenHeight);
	glfwSetWindowSizeCallback(context, OglRenderer::OnWindowResize);
	OnWindowResize(context, initialScreenWidth, initialScreenHeight);


	OglRenderer* og = new OglRenderer();
	og->m_context = context;
	og->m_programId = progId;
	og->m_projMatUniIdx = uniformProjectionIdx;
	og->m_quadBuffer = new Quad[spriteMaxCount];
	og->m_samplerUniIdx = uniformTexSamplerIdx;
	og->m_spriteMaxCount = spriteMaxCount;
	og->m_textureArrayId = textureArrayId;
	og->m_vao = vao;
	og->m_vbo = vbo;
	return og;
}



void OglRenderer::DrawBuffers(size_t size)
{
	// binding

	glUseProgram(m_programId);
	glBindVertexArray(m_vao);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureArrayId);

	// upload uniforms data

	glUniformMatrix4fv(m_projMatUniIdx, 1, GL_FALSE, &ProjectionMatrix[0][0]);

	// upload vertex data

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Quad) * size, m_quadBuffer);

	// render

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, size * 6);
	glfwSwapBuffers(m_context);
	

	// unbind

	// TODO is unbind really necessary? will the ogl state ever change?
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}



void GLAPIENTRY OglRenderer::DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam)
{
	Logger::Print("0x%x: %s\n\n", id, message);
}



void OglRenderer::ToggleFullscreen()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (m_isFullscreen)
	{
		glfwSetWindowMonitor(m_context, 0, 50, 50, restoredWindowWidth, restoredWindowHeight, mode->refreshRate);
		m_isFullscreen = false;
	}
	else
	{
		glfwSetWindowMonitor(m_context, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		m_isFullscreen = true;
	}
}



void OglRenderer::OnWindowResize(GameContext * window, int width, int height)
{
	/*restoredWindowWidth = width;
	restoredWindowHeight = height;*/

	float fWidth = static_cast<float>(width);
	float fHeight = static_cast<float>(height);
	float ratio = fWidth / fHeight;
	float xSpan = 16;
	float ySpan = 16;

	/*if (ratio > 1)
	{
		fWidth *= ratio;
	}
	else
	{
		fHeight = fWidth / ratio;
	}*/

	ProjectionMatrix = glm::ortho(0.0f, fWidth, fHeight, 0.0f, 0.0f, 1000.0f);
	glViewport(0, 0, width, height);
}
