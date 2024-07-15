/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#include "scene/scene.hpp"
#include "scene/loader/model/bin.hpp"
#include "log.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

bool Scene::loadScene(const std::string &path) {
  std::ifstream jsonFile(path);
  json data = json::parse(jsonFile, nullptr, false /* turn off exceptions */);
  if (data.is_discarded()) {
    LOG("The file " << path << " doesn't look like JSON");
    return false;
  }

  for (const auto &node: data.items()) {
    // Parse 'type' node
    if (!node.value().contains("type")) { // 'type' is a mandatory node
      LOG("Entity " << node.key() << " doesn't contain 'type' node. Skipping");
      continue;
    }
    if (!node.value()["type"].is_string()) {
      LOG("Entitiy's 'type' value " << node.key() << " has type different from string. Skipping");
      continue;
    }
    // Create an entity
    EntityType type {Entity3::typeByString(node.value()["type"])};
    Entity3 entity(node.key(), type);
    // Load entity according to its type
    bool isLoaded {false};
    LOG("Loading entity '" << node.key() << "' [" << node.value()["type"] << "]");
    switch (type) {
      case EntityType::Object:
        {
          // Load model
          if (!node.value().contains("model")) {
            LOG("Entity " << node.key() << " with type Object doesn't have model node");
            break;
          }
          if (!node.value()["model"].is_string()) {
            LOG("Entity's 'model' " << node.key() << " has type different from string");
            break;
          }
          loadModel(entity, node.value()["model"]); // TODO: check for return
          LOG("Model " << node.value()["model"] << " has been loaded");
          // Load vertex shader
          if (!node.value().contains("vtx_shader")) {
            LOG("Entity " << node.key() << " with type Object doesn't have vtx_shader node");
            break;
          }
          if (!node.value()["vtx_shader"].is_string()) {
            LOG("Entity's 'vtx_shader' " << node.key() << " has type different from string");
            break;
          }
          loadVtxShader(entity, node.value()["vtx_shader"]); // TODO: check for return
          LOG("Vertex shader " << node.value()["model"] << " has been loaded");
          // Load fragment shader
          if (!node.value().contains("frg_shader")) {
            LOG("Entity " << node.key() << " with type Object doesn't have frg_shader node");
            break;
          }
          if (!node.value()["frg_shader"].is_string()) {
            LOG("Entity's 'frg_shader' " << node.key() << " has type different from string");
            break;
          }
          loadFrgShader(entity, node.value()["frg_shader"]); // TODO: check for return
          LOG("Fragment shader " << node.value()["model"] << " has been loaded");
          isLoaded = true;
          mRender->linkShader(entity);
        }
        break;
    }
    if (isLoaded) {
      LOG("Entity '" << node.key() << "' has been loaded");
      mEntities.push_back(std::move(entity));
    } else {
      LOG("Entity '" << node.key() << "' failed to load");
    }
  }

  return true;
}

void Scene::frame() {
  mRender->render(mEntities);
}

bool Scene::loadModel(Entity3 &entity, const std::string &path) {
  if (loader::model::bin(path, entity)) {
    return mRender->loadModel(entity);
  }
  return false;
}

bool Scene::loadVtxShader(Entity3 &entity, const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    LOG("Can't open a file with model: " << path);
    return false;
  }
  std::string code(std::istreambuf_iterator<char>(file), {});
  return mRender->addShader(entity, ShaderType::Vertex, code.c_str());
}

bool Scene::loadFrgShader(Entity3 &entity, const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    LOG("Can't open a file with model: " << path);
    return false;
  }
  std::string code(std::istreambuf_iterator<char>(file), {});
  return mRender->addShader(entity, ShaderType::Fragment, code.c_str());
}
