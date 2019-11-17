#include "StaticShader.h"

const string VERTEX_FILE   = "res/shaders/vertexshader.glsl";
const string FRAGMENT_FILE = "res/shaders/fragmentshader.glsl";

StaticShader::StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	link_program();
}


StaticShader::~StaticShader()
{
}

void StaticShader::bind_attributes()
{
	bind_attribute(0, "position");
}
