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

#define LOG(log, str) log << str << std::endl

class LogBase {
  protected:
    std::shared_ptr<std::ostream> mLogFile;
    std::string mPrefix;

    LogBase(const std::string &prefix, const std::string &fpath);
    LogBase(const LogBase &) = delete;
    ~LogBase() = default;
  public:
    template<typename T>
    const LogBase &operator<< (const T &rhs) const {
      *mLogFile << rhs;
      return *this;
    }

    const LogBase &operator<< (std::ostream&(*func)(std::ostream&)) const {
      (*func)(*mLogFile);
      return *this;
    }
};

class Log : public LogBase {
  public:
    Log(const std::string &prefix, const std::string &fpath = "");

    template<typename T>
    const LogBase &operator<< (const T &rhs) const {
      std::time_t time = std::time(nullptr);
      std::string localtime = std::asctime(std::localtime(&time));
      localtime.erase(--localtime.end(), localtime.end());
      *mLogFile << "[" << localtime << "] " << mPrefix << ": " << rhs;
      return *this;
    }
};

#endif // #define KAON_LOG_HPP_
