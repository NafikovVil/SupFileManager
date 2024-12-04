#include <filesystem/filesystem.hpp>

#include <gtest/gtest.h>

using namespace filesystem;

TEST( FilesystemLibTest, GetWorkDir )
{
   auto work_dir = Filesystem::GetWorkDir();
   ASSERT_TRUE( work_dir );
}

TEST( FilesystemLibTest, GetWorkDirRigth )
{
   auto work_dir = Filesystem::GetWorkDir();
   ASSERT_TRUE( work_dir );

   auto is_directory = Filesystem::CheckPathIsDirectory( *work_dir );
   ASSERT_TRUE( is_directory );
}

/*TEST(FilesystemLibTest, GetFilesInDirectory)
{
    auto work_dir = GetWorkDir();
    if (!work_dir)
    {
        return testing::AssertionFailure();
    }
    if (; work_dir)
    {
        std::cout << "Work dir: " << *work_dir << std::endl;
        auto filename_list = filesystem_api.GetFilesInDirectory(*work_dir);
        std::cout << "Filelist: " << std::endl;
        for (auto const &file_name : filename_list)
        {
            std::cout << file_name << std::endl;
        }
    }
}*/
