/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "log.hpp"

LogBase::LogBase(const std::string &prefix, const std::string &fpath)
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

Log::Log(const std::string &prefix, const std::string &fpath)
: LogBase(prefix, fpath) { }
