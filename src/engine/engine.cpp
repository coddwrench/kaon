/*
 * vim:et:sw=2:ts=2
 *
 * Description: This is a main class that controls everything. The engine.
 *
 * Copyright (c) 2024 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "kaonConfig.h"
#include "engine/engine.hpp"
#include "log.hpp"

#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

Engine::Engine() {
  LOG("Starting kaon v" << kaon_VERSION_MAJOR << "." << kaon_VERSION_MINOR);

  mWindow = std::move(AbstractWindow::factory());
  mRender = std::move(AbstractRender::factory());

  LOG("Creating window");
  if (mWindow->createWindow(1920, 1080, "K engine")) {
    LOG("Window has been created");
  } else {
    LOG("Failed to create window");
    throw std::runtime_error("Failed to create window");
  }

  LOG("Creating render");
  mRender->createRender();

  LOG("Loading scene");
  mScene = std::make_shared<Scene>(mRender);
  mScene->loadScene("test.json");

  mWindow->addEventCB(WindowEvent::keyPress, &keyPress);
}

Engine::~Engine() {
  LOG("Bye!");
}

void Engine::run() {
  std::thread thEvents([this](){
    while (mRun) {
      mWindow->nextEvent();
    }
  });
  while (mRun) {
    mScene->frame();
    mWindow->draw();
    std::this_thread::sleep_for(1s/60);
  }
  thEvents.join();
}

void Engine::keyPress(WindowEvent event, void *) {
  static Engine &engine = Engine::instance();
  LOG("Key has been pressed");
  engine.mRun = false;
}
