/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "kaonConfig.h"
#include "log.hpp"
#include "window/abstract_window.hpp"
#include "render/abstract_render.hpp"
#include "scene/scene.hpp"
#include <atomic>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

int main() {
  LOG("Starting kaon v" << kaon_VERSION_MAJOR << "." << kaon_VERSION_MINOR);

  std::shared_ptr<AbstractWindow> wnd = std::move(AbstractWindow::factory());
  std::shared_ptr<AbstractRender> render = std::move(AbstractRender::factory());
  std::atomic<bool> run {true};

  LOG("Creating window");
  if (wnd->createWindow(800, 600, "K engine")) {
    LOG("Window has been created");
  } else {
    LOG("Failed to create window");
    return 1;
  }
  LOG("Creating render");
  render->createRender();
  LOG("Loading scene");
  Scene scene(render);
  scene.loadScene("test.json");

  auto keyPress = [&run](WindowEvent event, void *) {
    run = false;
  };
  wnd->addEventCB(WindowEvent::keyPress, keyPress);
  auto loop = [wnd, &scene, &run]() {
    while (run) {
      scene.frame();
      wnd->draw();
      std::this_thread::sleep_for(1s/60);
    }
  };

  std::thread thLoop(loop);
  while (run) {
    wnd->nextEvent();
  }
  thLoop.join();

  LOG("Bye!");
  return 0;
}
