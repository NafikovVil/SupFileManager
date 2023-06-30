#pragma once

#include <ftxui/component/component_base.hpp>

namespace console::gui::elements
{
    class IRenderedElement
    {
    public:
        ftxui::Component GetRendered();
    };
}