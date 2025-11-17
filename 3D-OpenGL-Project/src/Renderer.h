#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "SystemHandler.h"
#include "ResourceHandler.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
private:
	ResourceHandler *_resources;
public:
	int Init(ResourceHandler *resources);
	void render(const RenderObject &obj);
	void renderObjects();
	void clear();
};

#endif