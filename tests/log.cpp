/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include <memory>
#include <fstream>
#include <cstdio>
#include <log.hpp>
#include <gtest/gtest.h>

class LogTest : public ::testing::Test {
  protected:
    static constexpr const char *mLogFile = "LogTest.log";
    std::shared_ptr<Log> mLoggerPtr;

    LogTest() {
      mLoggerPtr.reset(new Log("LogTest", mLogFile));
    }
    ~LogTest() override {
      std::remove(mLogFile);
    }
};

TEST_F(LogTest, stdoutTest) {
  std::time_t time = std::time(nullptr);
  std::string localtime = std::asctime(std::localtime(&time));
  localtime.erase(--localtime.end(), localtime.end());
  LOG(*mLoggerPtr, "leel");

  std::ifstream logFile(mLogFile);
  std::string str = "[" + localtime + "] LogTest: leel";
  std::string logStr;
  std::getline(logFile, logStr);
  ASSERT_EQ(logStr, str);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
