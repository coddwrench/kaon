/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_OGL_RENDER_HPP_
#define KAON_OGL_RENDER_HPP_

#include "render/abstract_render.hpp"
#include <GL/glew.h>
#include <vector>

class Shader {
  public:
    Shader(GLenum type, const GLchar *code, bool &state);
    GLenum getType() {
      return mType;
    }
    GLuint getId() {
      return mId;
    }
  private:
    GLenum mType;
    GLuint mId;
};

class ShaderProgram {
  public:
    ShaderProgram()
      : mId(glCreateProgram()) {};
    bool addShader(GLenum type, const GLchar *code);
    bool linkShader();
  private:
    void shaderErrorLog(GLuint shaderId);

    std::vector<Shader> mShaders;
    GLuint mId;
};

class VertexBuffer {
  public:
    VertexBuffer(float *vtx, int size);
    GLuint getBufferID() {
      return mBufferID;
    }
    GLuint getVAO() {
      return mVAO;
    }
  private:
    GLuint mBufferID;
    GLuint mVAO;
};

class OGLRender : public AbstractRender {
  public:
    bool createRender() override;
    void render(std::vector<Entity3> &entities) override;
    bool addShader(Entity3 &entity, ShaderType type, const std::string &code) override;
    bool linkShader(Entity3 &entity) override;
    bool loadModel(Entity3 &entity) override;
  private:
    GLuint createShader(GLenum type, const std::string &shader);
    void shaderErrorLog(GLuint shaderId);

    GLuint mBuffer;
    GLuint mVAO;
    std::vector<ShaderProgram> mShaders;
};

#endif // KAON_OGL_RENDER_HPP_
