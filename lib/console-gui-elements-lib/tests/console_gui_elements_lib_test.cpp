//#include <gtest/gtest.h>
/*
std::optional<std::string> GetWorkDir()
{
    auto filesystem_api = filesystemlib::FilesystemFabric::GetFilesystemFabric();
    return filesystem_api->GetWorkDir();
}

TEST(FilesystemLibTest, GetWorkDir)
{
    auto work_dir = GetWorkDir();
    std::cout << "Work dir: " << *work_dir;
    ASSERT_TRUE(work_dir);
}*/

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
