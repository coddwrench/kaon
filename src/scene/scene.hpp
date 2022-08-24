/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_SCENE_HPP_
#define KAON_SCENE_HPP_

#include "scene/entity.hpp"
#include "render/abstract_render.hpp"

class Scene {
  public:
    Scene(std::shared_ptr<AbstractRender> render)
      : mRender(render) {};
    bool loadScene(const std::string &path);
    void frame();
  private:
    bool loadModel(Entity3 &entity, const std::string &path);
    bool loadVtxShader(Entity3 &entity, const std::string &path);
    bool loadFrgShader(Entity3 &entity, const std::string &path);

    std::shared_ptr<AbstractRender> mRender;
    std::vector<Entity3> mEntities;
};

#endif // #define KAON_SCENE_HPP_
