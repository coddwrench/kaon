/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "kaonConfig.h"
#include "log.hpp"
#include "window/xlib_window.hpp"

int main() {
  Log logger("main");
  LOG(logger, "Starting kaon v" << kaon_VERSION_MAJOR << "." << kaon_VERSION_MINOR);
  KWindow wnd;
  bool run = true;
  wnd.createWindow();

  auto keyPress = [&run, &logger](WindowEvent event, void *) {
    run = false;
  };
  wnd.addEventCB(WindowEvent::keyPress, keyPress);

  while (run) {
    wnd.draw();
  }

  return 0;
}
