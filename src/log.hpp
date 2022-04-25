/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

#define LOG(log, str) log << str << std::endl

class logBase {
  protected:
    std::shared_ptr<std::ostream> mLogFile;
    std::string mPrefix;

    logBase(const std::string &prefix, const std::string &fpath);
    logBase(const logBase &) = delete;
    ~logBase() = default;
  public:
    template<typename T>
    const logBase &operator<< (const T &rhs) const {
      *mLogFile << rhs;
      return *this;
    }

    const logBase &operator<< (std::ostream&(*func)(std::ostream&)) const {
      (*func)(*mLogFile);
      return *this;
    }
};

class log : public logBase {
  public:
    log(const std::string &prefix, const std::string &fpath = "");

    template<typename T>
    const logBase &operator<< (const T &rhs) const {
      std::time_t time = std::time(nullptr);
      std::string localtime = std::asctime(std::localtime(&time));
      localtime.erase(--localtime.end(), localtime.end());
      *mLogFile << "[" << localtime << "] " << mPrefix << ": " << rhs;
      return *this;
    }
};
