#include "Renderer.h"

#include <SOIL/SOIL2.h>

#include "Shader.h"
#include "Log.h"

#include "Sprite.h"
#include "SpriteComponent.h"

static const float rectVertices[] = {
    0.5f, 0.5f,
    0.5f, -0.5f,
    -0.5f, -0.5f,
    -0.5f, 0.5f,
};

static const float rectUVs[] = {
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f
};

static const unsigned int rectIndices[] = {
    0, 1, 3,
    1, 2, 3
};

Renderer::Renderer(Shader* rectShader, Shader* spriteShader, Shader* spriteBatchShader) :
    m_rectVao ( 0 ),
    m_rectVertexBuffer ( 0 ),
    m_rectShader( rectShader ),
    m_spriteShader ( spriteShader ),
    m_spriteBatchShader ( spriteBatchShader )
{
    glCreateVertexArrays(1, &m_rectVao);
    glBindVertexArray(m_rectVao);

    glCreateBuffers(1, &m_rectVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_rectVertexBuffer);
    glNamedBufferStorage(m_rectVertexBuffer, sizeof(float) * 8, rectVertices, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glCreateBuffers(1, &m_rectUvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_rectUvBuffer);
    glNamedBufferStorage(m_rectUvBuffer, sizeof(float) * 8, rectUVs, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glCreateBuffers(1, &m_rectIndicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rectIndicesBuffer);
    glNamedBufferStorage(m_rectIndicesBuffer, sizeof(unsigned int) * 6, rectIndices, 0);

    glCreateVertexArrays(1, &m_spriteBatchVao);
    glBindVertexArray(m_spriteBatchVao);

    glCreateBuffers(1, &m_spriteBatchVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchVertexBuffer);
    glNamedBufferStorage(m_spriteBatchVertexBuffer, sizeof(float) * 8, rectVertices, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glCreateBuffers(1, &m_spriteBatchUvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchUvBuffer);
    glNamedBufferStorage(m_spriteBatchUvBuffer, sizeof(float) * 8, rectUVs, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glCreateBuffers(1, &m_spriteBatchIndicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_spriteBatchIndicesBuffer);
    glNamedBufferStorage(m_spriteBatchIndicesBuffer, sizeof(unsigned int) * 6, rectIndices, 0);

    glCreateBuffers(1, &m_spriteBatchPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchPositionBuffer);
    glNamedBufferData(m_spriteBatchPositionBuffer, sizeof(GLfloat) * 3 * 3000, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(2, 1);

    glCreateBuffers(1, &m_spriteBatchScaleBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchScaleBuffer);
    glNamedBufferData(m_spriteBatchScaleBuffer, sizeof(GLfloat) * 2 * 3000, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(3, 1);

    glCreateBuffers(1, &m_spriteBatchRotationBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchRotationBuffer);
    glNamedBufferData(m_spriteBatchRotationBuffer, sizeof(GLfloat) * 3000, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(4, 1);

    glCreateBuffers(1, &m_spriteBatchFrameBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchFrameBuffer);
    glNamedBufferData(m_spriteBatchFrameBuffer, sizeof(GLfloat) * 3000, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(5, 1);

    glCreateBuffers(1, &m_spriteBatchDepthBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchDepthBuffer);
    glNamedBufferData(m_spriteBatchDepthBuffer, sizeof(GLfloat) * 3000, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 1, GL_FLOAT, GL_FLOAT, 0, (void*)0);
    glVertexAttribDivisor(6, 1);

    glCreateBuffers(1, &m_spriteBatchHighlightBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchHighlightBuffer);
    glNamedBufferData(m_spriteBatchHighlightBuffer, sizeof(GLfloat) * 3000, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(7, 1);
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &m_rectVertexBuffer);
    glDeleteBuffers(1, &m_rectUvBuffer);
    glDeleteVertexArrays(1, &m_rectVao);

    // need to delete other bufferss....
}

void Renderer::drawRectangle(glm::vec4 rect, glm::vec4 color, int flag) const {
    glBindVertexArray(m_rectVao);
    m_rectShader->use();

    m_rectShader->setVec4("rect", rect);
    m_rectShader->setVec4("color", color);
    m_rectShader->setBool("center", flag & RendererFlag::drawRectNonCenter ? false : true);

    ///glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// maybe add effect component for using different shaders/effects
void Renderer::drawSprite(const glm::mat4& model, SpriteComponent* sprite) const {
    if (!sprite) {
        return;
    }

    glBindVertexArray(m_rectVao);
    m_spriteShader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite->m_sprite->getTexture());

    m_spriteShader->setMat4("model", model);
    m_spriteShader->setInt("frame", sprite->m_frame.m_frame);
    m_spriteShader->setInt("width", sprite->m_sprite->getSpriteWidth());
    m_spriteShader->setInt("height", sprite->m_sprite->getSpriteHeight());
    m_spriteShader->setDouble("uvWidth", sprite->m_sprite->getSpriteUvWidth());
    m_spriteShader->setDouble("uvHeight", sprite->m_sprite->getSpriteUvHeight());
    m_spriteShader->setDouble("uvXOffset", sprite->m_sprite->getSpriteUvXOffset());
    m_spriteShader->setDouble("uvYOffset", sprite->m_sprite->getSpriteUvYOffset());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

GLuint Renderer::loadTexture(const char* file) {
    GLuint texture = SOIL_load_OGL_texture(file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (texture == 0) {
        Log::get().write(L_ERROR, "Error loading texture: ", file);
    }
    return texture;
}

void Renderer::drawSpriteData(const SpriteRenderData& p_spriteRenderData) const {
    glBindVertexArray(m_spriteBatchVao);
    m_spriteBatchShader->use();

    auto& data = p_spriteRenderData.get();
    for (auto& dataItr : data) {
        const auto& positionBuffer = dataItr.second.m_positionBuffer;
        const auto& scaleBuffer = dataItr.second.m_scaleBuffer;
        const auto& rotationBuffer = dataItr.second.m_rotationBuffer;
        const auto& frameBuffer = dataItr.second.m_frameBuffer;
        const auto& depths = dataItr.second.m_depths;
        const auto& highlights = dataItr.second.m_highlights;
        const auto& sprite = dataItr.second.m_sprite;
        const auto instances = dataItr.second.m_instances;

        glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchPositionBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, positionBuffer.size() * sizeof(GLfloat) * 3, &positionBuffer[0]);

        glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchScaleBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, scaleBuffer.size() * sizeof(GLfloat) * 2, &scaleBuffer[0]);

        glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchRotationBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, rotationBuffer.size() * sizeof(GLfloat), &rotationBuffer[0]);

        glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchFrameBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, frameBuffer.size() * sizeof(GLfloat), &frameBuffer[0]);

        glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchDepthBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, depths.size() * sizeof(GLfloat), &depths[0]);

        glBindBuffer(GL_ARRAY_BUFFER, m_spriteBatchHighlightBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, highlights.size() * sizeof(GLfloat), &highlights[0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprite->getTexture());

        m_spriteBatchShader->setInt("width", sprite->getSpriteWidth());
        m_spriteBatchShader->setInt("height", sprite->getSpriteHeight());
        m_spriteBatchShader->setDouble("uvWidth", sprite->getSpriteUvWidth());
        m_spriteBatchShader->setDouble("uvHeight", sprite->getSpriteUvHeight());
        m_spriteBatchShader->setDouble("uvXOffset", sprite->getSpriteUvXOffset());
        m_spriteBatchShader->setDouble("uvYOffset", sprite->getSpriteUvYOffset());

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instances);

        glDisable(GL_DEPTH_TEST);
    }
}