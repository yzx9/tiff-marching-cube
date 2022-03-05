#include <chrono>
#include <iostream>
#include <filesystem>
#include "marchingCubes.hpp"
#include "voxel.hpp"
#include "obj.hpp"

int main()
{
    constexpr auto img = "../data/seg_ImgSoma_17302_00020-x_14992.3_y_21970.3_z_4344.8.tiff";
    constexpr auto obj = "../tmp/seg_ImgSoma_17302_00020-x_14992.3_y_21970.3_z_4344.8.obj";

    auto imgFilePath = std::filesystem::current_path().append(img);
    auto voxels = voxel::read_from_tiff<float>(imgFilePath);

    auto start = std::chrono::system_clock::now();
    auto mesh = marching_cubes::extract<float>(voxels, 0.5);
    auto stop = std::chrono::system_clock::now();

    std::cout << "Extract mesh complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";

    auto objFilePath = std::filesystem::current_path().append(obj);
    obj::save<float>(objFilePath, mesh);

    return 0;
}
