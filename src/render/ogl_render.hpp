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

class OGLRender : public AbstractRender {
  public:
    bool createRender() override;
    void pushScene() override;
    void render() override;
  private:
    GLuint createShader(GLenum type, const std::string &shader);
    void shaderErrorLog(GLuint shaderId);

    GLuint mBuffer;
    GLuint mVAO;
};

#endif // KAON_OGL_RENDER_HPP_
