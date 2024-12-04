#pragma once

#include "../include/i_controller.hpp"

namespace sup_manager
{

class RenderProcessor
{
public:
   RenderProcessor( IController& controller ) noexcept;

   void Render() noexcept;

private:
   IController& mController;

   int mCustomLoopCount = 0;
   int mFrameCount = 0;
   int mEventCount = 0;
};

} // namespace sup_manager