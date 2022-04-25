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

class logTest : public ::testing::Test {
  protected:
    static constexpr const char *mLogFile = "logTest.log";
    std::shared_ptr<log> mLoggerPtr;

    logTest() {
      mLoggerPtr.reset(new log("logTest", mLogFile));
    }
    ~logTest() override {
      std::remove(mLogFile);
    }
};

TEST_F(logTest, stdoutTest) {
  std::time_t time = std::time(nullptr);
  std::string localtime = std::asctime(std::localtime(&time));
  localtime.erase(--localtime.end(), localtime.end());
  LOG(*mLoggerPtr, "leel");

  std::ifstream logFile(mLogFile);
  std::string str = "[" + localtime + "] logTest: leel";
  std::string logStr;
  std::getline(logFile, logStr);
  ASSERT_EQ(logStr, str);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
