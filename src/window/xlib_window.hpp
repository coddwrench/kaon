/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */
#define KAON_XLIB_WINDOW_HPP_
#define KAON_XLIB_WINDOW_HPP_

#include "window/abstract_window.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

class KWindow : public AbstractWindow<const XEvent &> {
  public:
    bool createWindow(int width = 640, int height = 480, const std::string &name = "K engine") override;
    bool destroyWindow() override;
    void draw() override;
    WindowEvent convertEvent(const XEvent &event) override;

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
};

#endif // KAON_XLIB_WINDOW_HPP_
