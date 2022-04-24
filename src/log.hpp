/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include <memory>
#include <string>

class log {
  std::shared_ptr<std::ostream> mLogFile;
  std::string mPrefix;

  public:
    log(const std::string prefix, const std::string fpath = "");
    void operator<< (const std::string str) const;
};
