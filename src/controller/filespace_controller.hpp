#pragma once

#include <filesystem/filesystem.hpp>

#include "../include/i_controller.hpp"
#include "../model/filespace_model.hpp"
#include "../view/filespace_view.hpp"

namespace sup_manager
{

class FilespaceController : public IController
{
public:
   FilespaceController( filesystem::FilePath const& initial_filepath ) noexcept;

   FilespaceController( FilespaceController const& copy ) noexcept;

   IView const& GetView() noexcept override;

private:
   // TODO: Может куда то перемести эту функцию?
   static std::vector< std::string > GetCurrentDirFilesName( filesystem::FileList const& filelist ) noexcept;

   FilespaceModel mModel;
   FilespaceView mFilespaceView;
};

} // namespace sup_manager