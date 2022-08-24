/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_ENTITY_HPP_
#define KAON_ENTITY_HPP_

#include "scene/vector.hpp"
#include <vector>
#include <memory>
#include <string>

class ShaderProgram;
class VertexBuffer;

enum class EntityType {
  None,
  Object,
  Trigger,
  Sound
};

template<typename T>
class Entity {
  public:
    Entity() = default;
    Entity(const std::string &name, EntityType type)
      : mName(name), mType(type) {}
    void setVtx(float *ptr, int len) {
      mVtx.reset(ptr);
      mVtxLen = len;
    }
    void setPos(T &&pos) {
      mPos = std::move(pos);
    }
    void setShader(std::shared_ptr<ShaderProgram> shader) {
      mShaderProgram = shader;
    }

    float *getVtx() {
      return mVtx.get();
    }
    int getVtxLen() {
      return mVtxLen;
    }
    std::shared_ptr<ShaderProgram> &getShader() {
      return mShaderProgram;
    }
    std::shared_ptr<VertexBuffer> &getVertexBuffer() {
      return mVertexBuffer;
    }

    static EntityType typeByString(const std::string &type) {
      if (type == "object")
        return EntityType::Object;
      else if (type == "trigger")
        return EntityType::Trigger;
      else if (type == "sound")
        return EntityType::Sound;

      return EntityType::None;
    }
  private:
    EntityType mType;
    std::string mName;
    T mPos;
    std::unique_ptr<float[]> mVtx;
    int mVtxLen;
    std::shared_ptr<ShaderProgram> mShaderProgram;
    std::shared_ptr<VertexBuffer> mVertexBuffer;
};

using Entity2 = Entity<Vector2f>;
using Entity3 = Entity<Vector3f>;

#endif // #define KAON_ENTITY_HPP_
