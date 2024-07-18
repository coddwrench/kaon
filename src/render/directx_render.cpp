/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "log.hpp"
#include "render/directx_render.hpp"
#include <memory>


bool DXRender::createRender() {

  return true;
}

void DXRender::render(std::vector<Entity3> &entities) {

}

bool DXRender::addShader(Entity3 &entity, ShaderType type, const std::string &code) {
  return nullptr;
}

bool DXRender::linkShader(Entity3 &entity) {
  return nullptr;
}

bool DXRender::loadModel(Entity3 &entity) {
  return true;
}

std::shared_ptr<AbstractRender> AbstractRender::factory() {
  return std::make_shared<DXRender>();
}
