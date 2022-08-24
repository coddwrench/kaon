/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_ABSTRACT_RENDER_HPP_
#define KAON_ABSTRACT_RENDER_HPP_

#include "scene/entity.hpp"
#include <memory>

enum class ShaderType {
  Vertex,
  Fragment
};

class AbstractRender {
  public:
    virtual bool createRender() = 0;
    virtual void render(std::vector<Entity3> &entities) = 0;
    virtual bool addShader(Entity3 &entity, ShaderType type, const std::string &code) = 0;
    virtual bool linkShader(Entity3 &entity) = 0;
    virtual bool loadModel(Entity3 &entity) = 0;

    static std::shared_ptr<AbstractRender> factory(); // Every derived class should define this function
};

#endif // #ifndef KAON_ABSTRACT_RENDER_HPP_
