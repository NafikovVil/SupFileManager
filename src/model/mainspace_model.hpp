#pragma once

#include "../include/i_view.hpp"

#include <functional>

namespace sup_manager
{

struct MainspaceModel
{
   std::vector< std::reference_wrapper< const IView > > mFilespaceViews;
};

} // namespace sup_manager