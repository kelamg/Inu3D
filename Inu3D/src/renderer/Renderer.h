#pragma once

#include "Common.h"
#include "models/RawModel.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void render(RawModel *model);
};

