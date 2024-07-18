#ifndef KAON_WIN_WINDOW_HPP_
#define KAON_WIN_WINDOW_HPP_

#include "window/abstract_window.hpp"
#include <thread>
#include <atomic>

class WWindow : public AbstractWindow {
  public:
    ~WWindow() override;
    bool createWindow(int width, int height, const std::string &name) override;
    bool destroyWindow() override;
    void draw() override;
    void nextEvent() override;

  private:
    std::atomic<std::thread::id> mCurrentThread;
};

#endif // KAON_WIN_WINDOW_HPP_
