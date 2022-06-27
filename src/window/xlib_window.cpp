/*
 * vim:et:sw=2:ts=2
 *
 * Description: This is a Xlib back-end for the Kaon engine. It is using for
 * communication with X11 window system. The extensive documentation about
 * Xlib is available there [0].
 *
 * Refs:
 * [0] https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#Introduction_to_Xlib
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "window/xlib_window.hpp"

KWindow::~KWindow() {
  if (mDisplay) destroyWindow();
}

bool KWindow::createWindow(int width, int height, const std::string &name) {
  AbstractWindow::createWindow(width, height, name);

  // If the window is already created then just throw an error;
  if (mDisplay) return false;

  // Connect to the X server. We're using a DISPLAY environment
  // variable here, so set the first argument to NULL.
  if (!(mDisplay = XOpenDisplay(nullptr)))
    return false;

  // Get the root window.
  mRootWnd = DefaultRootWindow(mDisplay);

  // Get visual for given attributes
  GLint visAtt[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
  mVisInfo = glXChooseVisual(mDisplay, 0, visAtt);

  // Create colormap for the window
  mCMap = XCreateColormap(mDisplay, mRootWnd, mVisInfo->visual, AllocNone);

  // Create window
  mSwa.colormap = mCMap;
  mSwa.event_mask = ExposureMask | KeyPressMask;
  mWnd = XCreateWindow(mDisplay,
                       mRootWnd,
                       0, 0,             // (x, y) position of the window
                       mWidth, mHeight,  // width and height of the window
                       0,                // border width
                       mVisInfo->depth,
                       InputOutput,
                       mVisInfo->visual,
                       CWColormap | CWEventMask, &mSwa);

  XMapWindow(mDisplay, mWnd);
  XStoreName(mDisplay, mWnd, mName.c_str());

  // OpenGL stuff
  mGlc = glXCreateContext(mDisplay, mVisInfo, nullptr, GL_TRUE);
  glXMakeCurrent(mDisplay, mWnd, mGlc);

  return true;
}

bool KWindow::destroyWindow() {
  glXMakeCurrent(mDisplay, None, nullptr);
  glXDestroyContext(mDisplay, mGlc);
  XFreeColormap(mDisplay, mCMap);
  XFree(mVisInfo);
  XDestroyWindow(mDisplay, mWnd);

  XCloseDisplay(mDisplay);
  mDisplay = nullptr;
  return true;
}

void KWindow::draw() {
  XNextEvent(mDisplay, &mXev);

  if (mXev.type == Expose) {
    XGetWindowAttributes(mDisplay, mWnd, &mGwa);
  }

  glXSwapBuffers(mDisplay, mWnd);

  auto event = convertEvent(mXev);
  if (event == WindowEvent::lastEvent) return;
  auto itEvent = mEvents.find(event);
  if (itEvent == mEvents.end()) return;
  const auto &callbacks = itEvent->second;
  for (const auto & cb: callbacks) {
    cb(event, nullptr);
  }
}

WindowEvent KWindow::convertEvent(const XEvent &event) {
  switch (event.type) {
    case KeyPress:
      return WindowEvent::keyPress;
  }
  return WindowEvent::lastEvent;
}

std::shared_ptr<AbstractWindow> AbstractWindow::factory() {
  return std::make_shared<KWindow>();
}
