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
  public:
    LogTest() {
      Logger::instance().setOutput(mLogFile);
    }

    ~LogTest() {
      std::remove(mLogFile);
    }
  protected:
    static constexpr const char *mLogFile = "/tmp/LogTest.log";
};

TEST_F(LogTest, stdoutTest) {
  std::time_t time = std::time(nullptr);
  std::string localtime = std::asctime(std::localtime(&time));
  localtime.erase(--localtime.end(), localtime.end());
  LOG("leel");

  std::ifstream logFile(mLogFile);
  std::string str = "[" + localtime + "] leel";
  std::string logStr;
  std::getline(logFile, logStr);
  ASSERT_EQ(logStr, str);
}

TEST_F(LogTest, multipleOutput) {
  std::time_t time_foo = std::time(nullptr);
  std::string localtime_foo = std::asctime(std::localtime(&time_foo));
  localtime_foo.erase(--localtime_foo.end(), localtime_foo.end());
  LOG("foo");

  std::time_t time_bar = std::time(nullptr);
  std::string localtime_bar = std::asctime(std::localtime(&time_bar));
  localtime_bar.erase(--localtime_bar.end(), localtime_bar.end());
  LOG("bar");

  std::ifstream logFile(mLogFile);
  std::string str_foo = "[" + localtime_foo + "] foo";
  std::string str_bar = "[" + localtime_bar + "] bar";
  std::string logStr_foo, logStr_bar;
  std::getline(logFile, logStr_foo);
  std::getline(logFile, logStr_bar);
  ASSERT_EQ(logStr_foo, str_foo);
  ASSERT_EQ(logStr_bar, str_bar);
}

TEST_F(LogTest, multipleOperator) {
  std::time_t time = std::time(nullptr);
  std::string localtime = std::asctime(std::localtime(&time));
  localtime.erase(--localtime.end(), localtime.end());
  LOG("foo" << " bar");

  std::ifstream logFile(mLogFile);
  std::string str = "[" + localtime + "] foo bar";
  std::string logStr;
  std::getline(logFile, logStr);
  ASSERT_EQ(logStr, str);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
