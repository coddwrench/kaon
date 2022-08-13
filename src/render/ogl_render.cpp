/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "log.hpp"
#include "render/ogl_render.hpp"

bool OGLRender::createRender() {
  // SHADERS
  const std::string vertexShaderSample = R"RAW(
#version 450 core

layout (location = 0) in vec4 vPosition;

void main() {
  gl_Position = vPosition;
}
)RAW";

  const std::string fragmentShaderSample = R"RAW(
#version 450 core

layout (location = 0) out vec4 fColor;

void main() {
  fColor = vec4(0.5, 0.4, 0.8, 1.0);
}
)RAW";
  glewInit();
  GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSample);
  GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSample);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  GLint isLinked = 0;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
  if (isLinked == 0) shaderErrorLog(shaderProgram);
  else glUseProgram(shaderProgram);

  // ARRAYS
  static const GLfloat vtx[6][2] = {
    {-0.90, -0.90},
    { 0.85, -0.90},
    {-0.90,  0.85},
    { 0.90, -0.85},
    { 0.90,  0.90},
    {-0.85,  0.90}
  };

  glCreateBuffers(1, &mBuffer);
  glNamedBufferStorage(mBuffer, sizeof(vtx), vtx, 0);

  glGenVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
//  glEnable(GL_DEPTH_TEST);

  return true;
}

void OGLRender::pushScene() {
}

void OGLRender::render() {
  static const float black[] = {0.f, 0.f, 0.f, 1.f};
  glClearBufferfv(GL_COLOR, 0, black);
  glBindVertexArray(mVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

GLuint OGLRender::createShader(GLenum type, const std::string &shader) {
  // Create shader and compile
  GLuint shaderId = glCreateShader(type);
  const GLchar *str = shader.c_str();
  glShaderSource(shaderId, 1, (const GLchar**)(&str), 0);
  glCompileShader(shaderId);
  // Check that shader successfully compiled
  GLint isCompiled = 0;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == 0) {
    shaderErrorLog(shaderId);
    return 0;
  }
  return shaderId;
}

void OGLRender::shaderErrorLog(GLuint shaderId) {
  // Get error log size
  GLint maxLength = 0;
  glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
  // Allocate buffer for the error message
  GLchar *shaderErrorLog = new GLchar[maxLength + 1];
  // Get the error message
  glGetShaderInfoLog(shaderId, maxLength, &maxLength, shaderErrorLog);
  shaderErrorLog[maxLength] = '\0';
  // Print error and free
  LOG("Error: can't compile shader\n" << shaderErrorLog);
  delete[] shaderErrorLog;
}

std::shared_ptr<AbstractRender> AbstractRender::factory() {
  return std::make_shared<OGLRender>();
}
