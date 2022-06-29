/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "kaonConfig.h"
#include "log.hpp"
#include "window/abstract_window.hpp"

int main() {
  LOG("Starting kaon v" << kaon_VERSION_MAJOR << "." << kaon_VERSION_MINOR);

  std::shared_ptr<AbstractWindow> wnd = std::move(AbstractWindow::factory());
  bool run = true;

  LOG("Creating window");
  if (wnd->createWindow()) {
    LOG("Window has been created");
  } else {
    LOG("Failed to create window");
    return 1;
  }

  auto keyPress = [&run](WindowEvent event, void *) {
    run = false;
  };
  wnd->addEventCB(WindowEvent::keyPress, keyPress);

  while (run) {
    wnd->draw();
  }

  LOG("Bye!");
  return 0;
}
