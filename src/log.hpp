/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_LOG_HPP_
#define KAON_LOG_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

#define LOG(str) Logger::instance() << str << std::endl

class LoggerBase {
  protected:
    std::shared_ptr<std::ostream> mLogFile {&std::cout, [](...){}};

    LoggerBase() = default;
    ~LoggerBase() = default;
    LoggerBase(const LoggerBase &) = delete;

  public:
    template<typename T>
    LoggerBase &operator<< (const T &rhs) {
      *mLogFile << rhs;
      return *this;
    }

    LoggerBase &operator<< (std::ostream &(*func)(std::ostream &)) {
      (*func)(*mLogFile);
      return *this;
    }
};

class Logger : public LoggerBase {
  private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger &) = delete;

  public:
    static Logger &instance() {
      static Logger logger;
      return logger;
    }

    void setOutput(const std::string &fpath) {
      if (!fpath.empty()) {
        std::ofstream *file = new std::ofstream(fpath);
        if (file->is_open()) {
          mLogFile.reset(file);
          return;
        }
      }
      mLogFile.reset(&std::cout, [](...){});
    }

    template<typename T>
    LoggerBase &operator<< (const T &rhs) {
      std::time_t time = std::time(nullptr);
      std::string localtime = std::asctime(std::localtime(&time));
      localtime.erase(--localtime.end(), localtime.end());
      *mLogFile << "[" << localtime << "] " << rhs;
      return *this;
    }
};

#endif // #define KAON_LOG_HPP_
