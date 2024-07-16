/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2024 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */
#include "scene/loader/model/obj.hpp"
#include "log.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>

enum class ObjLineType {
  Name,
  Vertex,
  Face,
  Unknown
};

static ObjLineType getLineType(const std::string &line) {
  std::string token;
  if (auto pos = line.find(' '); pos != line.npos) {
    token = line.substr(0, pos);
  } else {
    return ObjLineType::Unknown;
  }
  // Return the token's type
  if (token == "o") {
    return ObjLineType::Name;
  } else if (token == "v") {
    return ObjLineType::Vertex;
  } else if (token == "f") {
    return ObjLineType::Face;
  }
  return ObjLineType::Unknown;
}

static bool getVertex(const std::string &line, float *vtx) {
  char v;
  float w;
  std::istringstream str{line};

  str >> v >> vtx[0] >> vtx[1] >> vtx[2] >> w;
  return true;
}

static int getFace(const std::string &line, int *faces) {
  std::string face;
  std::istringstream str{line};
  unsigned nfaces {0};

  while (std::getline(str, face, ' ')) {
    auto pos = face.find('/');
    if (pos != face.npos) {
      faces[nfaces++] = std::atoi(face.substr(0, pos).c_str());
    }
  }

  return nfaces;
}

bool loader::model::obj(const std::string &path, Entity3 &entity) {
  // Read the file
  std::ifstream file(path);
  if (!file.is_open()) {
    LOG("Can't open a file with obj model: " << path);
    return false;
  }
  std::stringstream objContent;
  objContent << file.rdbuf();
  // Calculate counters and allocate data
  int nV{0}, nF{0}, nIdx{0};
  for (std::string line{}; std::getline(objContent, line);) {
    switch (getLineType(line)) {
      case ObjLineType::Vertex:
        ++nV;
        break;
      case ObjLineType::Face:
        ++nF;
        for (char ch: line) {
          if (ch == ' ') ++nIdx; // We assume that numbers separated only by 1 white-space
        }
        break;
    }
  }

  float *vtx = new(std::nothrow) float[nV*3]; // We will not use 4-th coord (w)
  int *faces = new(std::nothrow) int[nIdx];
  float *model = new(std::nothrow) float[nIdx*3];
  if (!model || !faces || !vtx) {
    LOG("Can't allocate memory for the model");
    delete[] vtx; delete[] faces; delete[] model;
    return false;
  }

  // Read the vertices and faces
  file.seekg(0);
  objContent.clear();
  objContent << file.rdbuf();

  unsigned vtxRead {0};
  unsigned facesRead {0};
  for (std::string line{}; std::getline(objContent, line);) {
    switch (getLineType(line)) {
      case ObjLineType::Vertex:
        getVertex(line, vtx + vtxRead*3); // TODO: return value
        vtxRead++;
        break;
      case ObjLineType::Face:
        facesRead += getFace(line, faces + facesRead);
        break;
    }
  }

  // Construct a model using faces and vertices
  for (unsigned iVtx {0}; iVtx < facesRead; ++iVtx) {
    model[iVtx*3] = vtx[(faces[iVtx] - 1)*3];
    model[iVtx*3 + 1] = vtx[(faces[iVtx] - 1)*3 + 1];
    model[iVtx*3 + 2] = vtx[(faces[iVtx] - 1)*3 + 2];
  }

  entity.setVtx(model, nIdx*3);
  delete[] vtx; delete[] faces;
  return true;
}
