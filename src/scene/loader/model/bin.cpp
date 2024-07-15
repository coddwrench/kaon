/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2024 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "scene/loader/model/bin.hpp"
#include "log.hpp"

bool loader::model::bin(const std::string &path, Entity3 &entity) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    LOG("Can't open a file with model: " << path);
    return false;
  }
  auto nsz = file.tellg();
  // This is god awful bad. Isn't it? But, it should be just a test.
  // TODO: sort tthe sortt iut if itf.
  float *model = new float[nsz/sizeof(float)];
  file.seekg(0);
  file.read((char *)model, nsz);
  entity.setVtx(model, nsz/sizeof(float));

  return true;
}
