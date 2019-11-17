#pragma once

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();
	void bind_attributes();
};

