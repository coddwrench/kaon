/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_VECTOR_HPP_
#define KAON_VECTOR_HPP_

#include <initializer_list>
#include <cmath>
#include <utility>
#include <cstddef>

template<typename T, std::size_t N>
class Vector {
  public:
    Vector(std::initializer_list<T> list) {
      T *px = mV;
      for (auto x0: list) {
        *px++ = x0;
      }
    }

    Vector(const T (&list)[N]) {
      const T *px0 = list;
      for (T *px = mV; px < mV + N; ++px) {
        *px = *px0++;
      }
    }

    Vector() : mV{} { }

    const T *ptr() const {
      return mV;
    }

    constexpr decltype(N) size() {
      return N;
    }

    T operator[](decltype(N) i) const {
      return mV[i];
    }

    T &operator[](decltype(N) i) {
      return mV[i];
    }

    Vector<T, N> operator+(const Vector<T, N> &v) {
      Vector<T, N> tmp(*this);
      for (decltype(N) i {}; i < N; ++i) {
        tmp[i] += v[i];
      }
      return std::move(tmp);
    }

    Vector<T, N> &operator+=(const Vector<T, N> &v) {
      for (decltype(N) i {}; i < N; ++i) {
        mV[i] += v[i];
      }
      return *this;
    }

    T operator*(const Vector<T, N> &v) {
      T product {};
      for (decltype(N) i {}; i < N; ++i) {
        product += mV[i]*v[i];
      }
      return product;
    }

    Vector<T, N> operator*(const T scale) {
      Vector<T, N> tmp(*this);
      for (decltype(N) i {}; i < N; ++i) {
        tmp[i] *= scale;
      }
      return tmp;
    }

    Vector<T, N> &operator*=(const T scale) {
      for (decltype(N) i {}; i < N; ++i) {
        mV[i] *= scale;
      }
      return *this;
    }

    Vector<T, N> cross(const Vector<T, N> &v) {
      static_assert(N == 3, "Not a 3 dim vector");
      Vector<T, N> tmp;
      tmp[0] = mV[1]*v[2] - mV[2]*v[1];
      tmp[1] = mV[2]*v[0] - mV[0]*v[2];
      tmp[2] = mV[0]*v[1] - mV[1]*v[0];
      return tmp;
    }

    T mod() {
      T mod {};
      for (decltype(N) i {}; i < N; ++i) {
        mod += mV[i]*mV[i];
      }
      return std::sqrt(mod);
    }
  private:
    T mV[N];
};

using Vector2f = Vector<float, 2>;
using Vector3f = Vector<float, 3>;

#endif // #define KAON_VECTOR_HPP_
