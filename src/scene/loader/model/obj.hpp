/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2024 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_LOADER_MODEL_OBJ_HPP_
#define KAON_LOADER_MODEL_OBJ_HPP_

#include "scene/entity.hpp"

namespace loader {
  namespace model {
    bool obj(const std::string &file, Entity3 &entity);
  };
};

#endif // #define KAON_LOADER_MODEL_OBJ_HPP_
