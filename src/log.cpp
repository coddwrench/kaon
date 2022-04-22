/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "log.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

log::log(const std::string prefix, const std::string fpath)
: mPrefix(prefix) {

  if (!fpath.empty()) {
    std::ofstream *file = new std::ofstream(fpath);
    if (file->is_open()) {
      mLogFile.reset(file);
      return;
    }
  }
  mLogFile.reset(&std::cout, [](...){});
}

void log::operator<< (const std::string str) const {
  std::time_t time = std::time(nullptr);
  std::string localtime = std::asctime(std::localtime(&time));
  localtime.erase(--localtime.end(), localtime.end());
  *mLogFile << "[" << localtime << "] " << mPrefix << ": " << str << std::endl;
}
