
//
// This source file is part of appleseed.
// Visit https://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014-2018 Francois Beaune, The appleseedhq Organization
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

// Interface header.
#include "sppmphotonmap.h"

// appleseed.renderer headers.
#include "renderer/global/globallogger.h"
#include "renderer/kernel/lighting/sppm/sppmphoton.h"

// appleseed.foundation headers.
#include "foundation/platform/defaulttimers.h"
#include "foundation/utility/statistics.h"
#include "foundation/utility/string.h"

// Standard headers.
#include <cstddef>
#include <string>

using namespace foundation;

namespace renderer
{

SPPMPhotonMap::SPPMPhotonMap(SPPMPhotonVector& photons)
{
    const size_t photon_count = photons.size();

    if (photon_count > 0)
    {
        RENDERER_LOG_INFO(
            "building sppm photon map from %s %s...",
            pretty_uint(photon_count).c_str(),
            photon_count > 1 ? "photons" : "photon");

        knn::Builder3f builder(*this);
        builder.build_move_points<DefaultWallclockTimer>(photons.m_positions);

        Statistics statistics;
        statistics.insert_time("build time", builder.get_build_time());
        statistics.insert_size("size", photons.get_memory_size());
        statistics.merge(knn::TreeStatistics<knn::Tree3f>(*this));

        RENDERER_LOG_DEBUG("%s",
            StatisticsVector::make(
                "sppm photon map statistics",
                statistics).to_string().c_str());
    }
    else
    {
        RENDERER_LOG_WARNING(
            "cannot build sppm photon map because no photon were stored by the photon tracing pass.");
    }
}

}   // namespace renderer
