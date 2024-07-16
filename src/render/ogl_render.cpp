/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "log.hpp"
#include "render/ogl_render.hpp"
#include <memory>

Shader::Shader(GLenum type, const GLchar *code, bool &state)
  : mType(type) {
  // Create shader and compile
  mId = glCreateShader(type);
  glShaderSource(mId, 1, &code, 0);
  glCompileShader(mId);
  // Check that shader successfully compiled
  GLint status = 0;
  glGetShaderiv(mId, GL_COMPILE_STATUS, &status);
  state = status;
}

bool ShaderProgram::addShader(GLenum type, const GLchar *code) {
  bool compiled {false};
  Shader shader(type, code, compiled);
  if (!compiled) {
    shaderErrorLog(shader.getId());
    return false;
  }

  glAttachShader(mId, shader.getId());
  mShaders.push_back(std::move(shader));
  return true;
}

bool ShaderProgram::linkShader() {
  glLinkProgram(mId);

  GLint isLinked {0};
  glGetProgramiv(mId, GL_LINK_STATUS, &isLinked);
  if (isLinked == 0) shaderErrorLog(mId);
  else glUseProgram(mId);

  return isLinked;
}

void ShaderProgram::shaderErrorLog(GLuint shaderId) {
  // Get error log size
  GLint maxLength {0};
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

VertexBuffer::VertexBuffer(float *vtx, int size) {
  glCreateBuffers(1, &mBufferID);
  glNamedBufferStorage(mBufferID, size, vtx, 0);

  glCreateVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
}

bool OGLRender::createRender() {
  glewInit();
  return true;
}

void OGLRender::render(std::vector<Entity3> &entities) {
  static const float black[] = {0.f, 0.f, 0.f, 1.f};
  glClearBufferfv(GL_COLOR, 0, black);
  for (auto &entity: entities) {
    auto &shader_ptr = entity.getShader();
    auto &vertex_ptr = entity.getVertexBuffer();
    glBindVertexArray(vertex_ptr->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, entity.getVtxLen());
  }
}

bool OGLRender::addShader(Entity3 &entity, ShaderType type, const std::string &code) {
  // Check for pointer
  auto &shader_ptr = entity.getShader();
  if (shader_ptr == nullptr) {
    shader_ptr.reset(new ShaderProgram());
  }
  // Take the type
  GLenum glType;
  switch (type) {
    case ShaderType::Vertex:
      glType = GL_VERTEX_SHADER;
      break;
    case ShaderType::Fragment:
      glType = GL_FRAGMENT_SHADER;
      break;
    default:
      glType = GL_NONE;
  }
  // Add a shader
  return shader_ptr->addShader(glType, code.c_str());
}

bool OGLRender::linkShader(Entity3 &entity) {
  return entity.getShader()->linkShader();
}

bool OGLRender::loadModel(Entity3 &entity) {
  auto &vertex_ptr = entity.getVertexBuffer();
  if (vertex_ptr == nullptr) {
    vertex_ptr.reset(new VertexBuffer(entity.getVtx(), entity.getVtxLen()*sizeof(decltype(*entity.getVtx()))));
  }
  return true;
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
