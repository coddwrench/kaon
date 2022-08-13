/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */
#ifndef KAON_XLIB_WINDOW_HPP_
#define KAON_XLIB_WINDOW_HPP_

#include "window/abstract_window.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <thread>
#include <atomic>

class KWindow : public AbstractWindow {
  public:
    ~KWindow() override;
    bool createWindow(int width, int height, const std::string &name) override;
    bool destroyWindow() override;
    void draw() override;
    void nextEvent() override;

  private:
    Display *mDisplay {nullptr};
    Window mRootWnd;
    XVisualInfo *mVisInfo;
    Colormap mCMap;
    XSetWindowAttributes mSwa;
    Window mWnd;
    GLXContext mGlc;
    XWindowAttributes mGwa;
    XEvent mXev;
    std::atomic<std::thread::id> mCurrentThread;

    WindowEvent convertEvent(const XEvent &event);
};

#endif // KAON_XLIB_WINDOW_HPP_
