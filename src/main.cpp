/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "engine/engine.hpp"

int main() {
  Engine &engine = Engine::instance();
  engine.run();
  return 0;
}
