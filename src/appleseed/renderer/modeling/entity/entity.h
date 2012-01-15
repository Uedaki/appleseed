
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2011 Francois Beaune
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_RENDERER_MODELING_ENTITY_ENTITY_H
#define APPLESEED_RENDERER_MODELING_ENTITY_ENTITY_H

// appleseed.renderer headers.
#include "renderer/utility/paramarray.h"

// appleseed.foundation headers.
#include "foundation/core/concepts/iunknown.h"
#include "foundation/utility/uid.h"
#include "foundation/utility/version.h"

// appleseed.main headers.
#include "main/dllsymbol.h"

// Standard headers.
#include <cstddef>

namespace renderer
{

//
// Base class for all entities in the scene.
//

class DLLSYMBOL Entity
  : public foundation::Identifiable
  , public foundation::Versionable
  , public foundation::IUnknown
{
  public:
    // Constructors.
    explicit Entity(
        const foundation::UniqueID      class_uid);
    Entity(
        const foundation::UniqueID      class_uid,
        const ParamArray&               params);

    // Return the unique ID of this class of entities.
    foundation::UniqueID get_class_uid() const;

    // Set/get the name of this entity.
    void set_name(const char* name);
    const char* get_name() const;

    // Return the parameters of this entity.
    ParamArray& get_parameters();
    const ParamArray& get_parameters() const;

    // Set/get the name of the render layer for this entity.
    void set_render_layer_name(const char* name);
    const char* get_render_layer_name() const;

    // Set/get the index of the render layer for this entity.
    // Use ~size_t(0) to disable render layer assignment.
    void set_render_layer_index(const size_t render_layer);
    size_t get_render_layer_index() const;

  protected:
    struct Impl;
    Impl* impl;

    const foundation::UniqueID          m_class_uid;
    ParamArray                          m_params;
    size_t                              m_render_layer;

    // Destructor.
    ~Entity();
};


//
// Entity class implementation.
//

inline foundation::UniqueID Entity::get_class_uid() const
{
    return m_class_uid;
}

inline ParamArray& Entity::get_parameters()
{
    return m_params;
}

inline const ParamArray& Entity::get_parameters() const
{
    return m_params;
}

inline void Entity::set_render_layer_name(const char* name)
{
    assert(name);
    m_params.insert("render_layer", name);
}

inline const char* Entity::get_render_layer_name() const
{
    return
        m_params.strings().exist("render_layer")
            ? m_params.strings().get("render_layer")
            : "";
}

inline void Entity::set_render_layer_index(const size_t render_layer)
{
    m_render_layer = render_layer;
}

inline size_t Entity::get_render_layer_index() const
{
    return m_render_layer;
}

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_MODELING_ENTITY_ENTITY_H
