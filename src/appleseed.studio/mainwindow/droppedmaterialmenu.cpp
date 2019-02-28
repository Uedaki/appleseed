
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

#include "mainwindow/droppedmaterialmenu.h"

namespace appleseed {
namespace studio {

DroppedMaterialMenu::DroppedMaterialMenu(
    const foundation::Vector2d& drop_pos,
    const std::string& material_name)
    : m_drop_pos(drop_pos)
    , m_material_name(material_name)
{
    QAction* front = addAction("Front side");
    QAction* back = addAction("Back side");
    QAction* both = addAction("Both sides");

    connect(front, SIGNAL(triggered()),
        SLOT(slot_apply_to_front()));

    connect(back, SIGNAL(triggered()),
        SLOT(slot_apply_to_back()));

    connect(both, SIGNAL(triggered()),
        SLOT(slot_apply_to_both()));
}

void DroppedMaterialMenu::slot_apply_to_front()
{
    emit signal_apply_material(m_drop_pos, m_material_name, renderer::ObjectInstance::Side::FrontSide);
}

void DroppedMaterialMenu::slot_apply_to_back()
{
    emit signal_apply_material(m_drop_pos, m_material_name, renderer::ObjectInstance::Side::BackSide);
}

void DroppedMaterialMenu::slot_apply_to_both()
{
    emit signal_apply_material(m_drop_pos, m_material_name, renderer::ObjectInstance::Side::BothSides);
}

}   // namespace studio
}   // namespace appleseed

#include "mainwindow/moc_cpp_droppedmaterialmenu.cxx"
