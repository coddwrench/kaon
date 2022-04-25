/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "kaonConfig.h"
#include "log.hpp"

int main() {
  log logger("main");
  LOG(logger, "Starting kaon v" << kaon_VERSION_MAJOR << "." << kaon_VERSION_MINOR);
  return 0;
}
