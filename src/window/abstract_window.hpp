/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_ABSTRACT_WINDOW_HPP_
#define KAON_ABSTRACT_WINDOW_HPP_

#include "log.hpp"
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>

enum class WindowEvent {
  keyPress,
  lastEvent
};
using WindowEventCB = std::function<void(WindowEvent, void *)>;
using WindowEventId = int;

class AbstractWindow {
  public:
    virtual ~AbstractWindow() = default;
    virtual bool createWindow(int width = 640, int height = 480, const std::string &name = "K engine") {
      mWidth = width;
      mHeight = height;
      mName = name;
      return true;
    }
    virtual bool destroyWindow() = 0;
    virtual void draw() = 0;

    WindowEventId addEventCB(WindowEvent event, WindowEventCB func) {
      auto itEvent = mEvents.find(event);
      if (itEvent != mEvents.end()) {
        itEvent->second.push_back(func);
        return itEvent->second.size() - 1;
      }
      mEvents.insert({event, {func}});
      return 0;
    }

    void deleteEventCB(WindowEvent event, WindowEventId id) {
      auto itEvent = mEvents.find(event);
      if (itEvent == mEvents.end()) return;
      if (itEvent->second.size() <= id) return;
      auto itCB = itEvent->second.begin() + id;
      itEvent->second.erase(itCB);
    }

    static std::shared_ptr<AbstractWindow> factory(); // Every derived class should define this function

  protected:
    int mWidth, mHeight;
    std::string mName;
    std::unordered_map<WindowEvent, std::vector<WindowEventCB>> mEvents;
};

#endif // #define KAON_ABSTRACT_WINDOW_HPP_
