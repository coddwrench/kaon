/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2024 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_ABSTRACT_ENGINE_HPP_
#define KAON_ABSTRACT_ENGINE_HPP_

#include "window/abstract_window.hpp"
#include "render/abstract_render.hpp"
#include "scene/scene.hpp"

#include <atomic>
#include <stdexcept>

class Engine {
  public:
    static Engine &instance() {
      static Engine engine;
      return engine;
    }

    void run();

    Engine(const Engine &) = delete;
    Engine(Engine &&) = delete;
    Engine &operator=(const Engine &) = delete;
    Engine &operator=(Engine &&) = delete;

  private:
    Engine();
    ~Engine();

    static void keyPress(WindowEvent event, void *);
    static void loop();

    std::shared_ptr<AbstractWindow> mWindow;
    std::shared_ptr<AbstractRender> mRender;
    std::shared_ptr<Scene> mScene;
    std::atomic<bool> mRun {true};
};

#endif // #ifndef KAON_ABSTRACT_ENGINE_HPP_
