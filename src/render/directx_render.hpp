/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_DIRECTX_RENDER_HPP_
#define KAON_DIRECTX_RENDER_HPP_

#include "render/abstract_render.hpp"
#include <vector>

class DXRender : public AbstractRender {
  public:
    bool createRender() override;
    void render(std::vector<Entity3> &entities) override;
    bool addShader(Entity3 &entity, ShaderType type, const std::string &code) override;
    bool linkShader(Entity3 &entity) override;
    bool loadModel(Entity3 &entity) override;
  private:
};

#endif // KAON_DIRECTX_RENDER_HPP_
