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
#include <X11/Xutil.h>

KWindow::~KWindow() {
  if (mDisplay) destroyWindow();
}

bool KWindow::createWindow(int width, int height, const std::string &name) {
  AbstractWindow::createWindow(width, height, name);

  // If the window is already created then just throw an error;
  if (mDisplay) {
    LOG("Window is already created");
    return false;
  }

  XInitThreads();
  // Connect to the X server. We're using a DISPLAY environment
  // variable here, so set the first argument to NULL.
  if (!(mDisplay = XOpenDisplay(nullptr))) {
    LOG("Can't open display");
    return false;
  }

  // Get the root window.
  Screen *screen = DefaultScreenOfDisplay(mDisplay);
  int screenId = DefaultScreen(mDisplay);
  mRootWnd = RootWindow(mDisplay, screenId);

  // Get visual for given attributes
  GLint visAtt[] = { GLX_RGBA,
                     GLX_DOUBLEBUFFER,
                     GLX_DEPTH_SIZE, 24,
                     GLX_STENCIL_SIZE, 8,
                     GLX_RED_SIZE, 8,
                     GLX_GREEN_SIZE, 8,
                     GLX_BLUE_SIZE, 8,
                     GLX_SAMPLE_BUFFERS, 0,
                     GLX_SAMPLES, 0,
                     None };
  mVisInfo = glXChooseVisual(mDisplay, screenId, visAtt);

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

  // OpenGL stuff
  mGlc = glXCreateContext(mDisplay, mVisInfo, nullptr, GL_TRUE);
  glXMakeCurrent(mDisplay, mWnd, mGlc);
  glViewport(0, 0, mWidth, mHeight);

  XClearWindow(mDisplay, mWnd);
  XMapRaised(mDisplay, mWnd);
  XStoreName(mDisplay, mWnd, mName.c_str());

  return true;
}

bool KWindow::destroyWindow() {
  LOG("Destroying window");
  glXMakeCurrent(mDisplay, None, nullptr);
  glXDestroyContext(mDisplay, mGlc);
  XFreeColormap(mDisplay, mCMap);
  XFree(mVisInfo);
  XDestroyWindow(mDisplay, mWnd);

  XCloseDisplay(mDisplay);
  mDisplay = nullptr;
  LOG("Window has been destroyed");
  return true;
}

void KWindow::draw() {
  XLockDisplay(mDisplay);
  if (std::this_thread::get_id() != mCurrentThread) {
    glXMakeCurrent(mDisplay, mWnd, mGlc);
    mCurrentThread = std::this_thread::get_id();
  }
  glXSwapBuffers(mDisplay, mWnd);
  XUnlockDisplay(mDisplay);
}

void KWindow::nextEvent() {
  XNextEvent(mDisplay, &mXev);
  XLockDisplay(mDisplay);
  if (mXev.type == Expose) {
    if (std::this_thread::get_id() != mCurrentThread) {
      glXMakeCurrent(mDisplay, mWnd, mGlc);
      mCurrentThread = std::this_thread::get_id();
    }
    XGetWindowAttributes(mDisplay, mWnd, &mGwa);
    glViewport(0, 0, mGwa.width, mGwa.height);
    glXSwapBuffers(mDisplay, mWnd);
  }
  XUnlockDisplay(mDisplay);

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
