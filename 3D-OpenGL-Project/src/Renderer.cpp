#include "Renderer.h"

int Renderer::Init(ResourceHandler *resources) {
	_resources = resources;
	return 0;
}

void Renderer::render(const RenderObject &obj) {
	glUseProgram(obj._program_id);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj._texture);
	glUniform1i(obj._texture, 0);

	glBindBuffer(GL_ARRAY_BUFFER, obj._vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, obj._uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, obj._normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj._elementBuffer);

	_resources->_camera.applyObjectMatrix(obj._model);
	glUniformMatrix4fv(obj._model_id, 1, GL_FALSE, &obj._model[0][0]);
	_resources->_camera.uniformMatrix(obj._id);

	glDrawElements(GL_TRIANGLES, obj._indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Renderer::renderObjects() {
	for (unsigned int i = 0; i < _resources->_renderObjects.size(); i++) {
		render(_resources->_renderObjects[i]);
	}
}

void Renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}