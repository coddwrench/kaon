/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "scene/vector.hpp"
#include <cmath>
#include <gtest/gtest.h>
class VectorTest : public ::testing::Test { };

TEST_F(VectorTest, mod_list_initializer) {
  Vector2f v {1., 2.};
  auto mod = v.mod();
  constexpr float mod_true = std::sqrt(5.);
  ASSERT_EQ(mod, mod_true);
}

TEST_F(VectorTest, mod_list) {
  Vector2f v({1., 2.});
  auto mod = v.mod();
  constexpr float mod_true = std::sqrt(5.);
  ASSERT_EQ(mod, mod_true);
}

TEST_F(VectorTest, mod_default_constructor) {
  Vector2f v;
  auto mod = v.mod();
  constexpr float mod_true = 0.;
  ASSERT_EQ(mod, mod_true);
}

TEST_F(VectorTest, ptr) {
  Vector2f v {42., 24.};
  const float *x = v.ptr();
  ASSERT_EQ(*x, 42.);
  ASSERT_EQ(*++x, 24.);
}

TEST_F(VectorTest, size2) {
  Vector2f v {1., 2.};
  ASSERT_EQ(v.size(), 2);
}

TEST_F(VectorTest, size3) {
  Vector3f v {1., 2., 3.};
  ASSERT_EQ(v.size(), 3);
}

TEST_F(VectorTest, operator_sbraces_const) {
  Vector2f v {1., 2.};
  float x = v[0];
  float y = v[1];
  ASSERT_EQ(x, 1.);
  ASSERT_EQ(y, 2.);
}

TEST_F(VectorTest, operator_sbraces) {
  Vector2f v;
  v[0] = 1.;
  v[1] = 2.;
  float x = v[0];
  float y = v[1];
  ASSERT_EQ(x, 1.);
  ASSERT_EQ(y, 2.);
}

TEST_F(VectorTest, operator_sum) {
  Vector2f v1 {1., 2.};
  Vector2f v2 {2., 3.};
  auto v_sum = v1 + v2;
  float x = v_sum[0];
  float y = v_sum[1];
  ASSERT_EQ(x, 3.);
  ASSERT_EQ(y, 5.);
}

TEST_F(VectorTest, operator_sum_eq) {
  Vector2f v1 {1., 2.};
  Vector2f v2 {2., 3.};
  v1 += v2;
  float x = v1[0];
  float y = v1[1];
  ASSERT_EQ(x, 3.);
  ASSERT_EQ(y, 5.);
}

TEST_F(VectorTest, operator_scalar_prod) {
  Vector2f v1 {1., 2.};
  Vector2f v2 {2., 3.};
  float prod = v1*v2;
  ASSERT_EQ(prod, 8.);
}

TEST_F(VectorTest, operator_scale) {
  Vector2f v {1., 2.};
  auto v_scaled = v*2.;
  float x = v_scaled[0];
  float y = v_scaled[1];
  ASSERT_EQ(x, 2.);
  ASSERT_EQ(y, 4.);
}

TEST_F(VectorTest, operator_scale_eq) {
  Vector2f v {1., 2.};
  v *= 2.;
  float x = v[0];
  float y = v[1];
  ASSERT_EQ(x, 2.);
  ASSERT_EQ(y, 4.);
}

TEST_F(VectorTest, cross) {
  Vector3f v1 {1., 0., 0.};
  Vector3f v2 {0., 1., 0.};
  auto v_cross = v1.cross(v2);
  float x = v_cross[0];
  float y = v_cross[1];
  float z = v_cross[2];
  ASSERT_EQ(x, 0.);
  ASSERT_EQ(y, 0.);
  ASSERT_EQ(z, 1.);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
