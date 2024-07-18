#include "window/win_window.hpp"

WWindow::~WWindow() {
  destroyWindow();
}

bool WWindow::createWindow(int width, int height, const std::string &name) {
  AbstractWindow::createWindow(width, height, name);
  return true;
}

bool WWindow::destroyWindow() {
  LOG("Destroying window");
  LOG("Window has been destroyed");
  return true;
}

void WWindow::draw() {
}

void WWindow::nextEvent() {
}

std::shared_ptr<AbstractWindow> AbstractWindow::factory() {
  return std::make_shared<WWindow>();
}
