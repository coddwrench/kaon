/*
 * vim:et:sw=2:ts=2
 *
 * Copyright (c) 2022 Nikita (sh1r4s3) Ermakov <sh1r4s3@mail.si-head.nl>
 * SPDX-License-Identifier: MIT
 */

#ifndef KAON_ABSTRACT_RENDER_HPP_
#define KAON_ABSTRACT_RENDER_HPP_

#include <memory>

class AbstractRender {
  public:
    virtual bool createRender() = 0;
    virtual void pushScene() = 0; // TODO: load scene from object
    virtual void render() = 0;

    static std::shared_ptr<AbstractRender> factory(); // Every derived class should define this function
};

#endif // #ifndef KAON_ABSTRACT_RENDER_HPP_
