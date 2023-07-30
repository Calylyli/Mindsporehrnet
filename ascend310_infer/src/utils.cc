#include <fstream>
#include <algorithm>
#include <iostream>
#include "inc/utils.h"

using mindspore::MSTensor;
using mindspore::DataType;

std::vector<std::string> get_all_files(std::string dirName) {
    struct dirent *filename;
    DIR *dir = open_dir(dirName);
    if (dir == nullptr) {
        return {};
    }
    std::vector<std::string> gdirs;
    std::vector<std::string> gfiles;
    while ((filename = readdir(dir)) != nullptr) {
        std::string dName = std::string(filename->d_name);
        if (dName == "." || dName == "..") {
            continue;
        } else if (filename->d_type == DT_DIR) {
            gdirs.emplace_back(std::string(dirName) + "/" + filename->d_name);
        } else if (filename->d_type == DT_REG) {
            gfiles.emplace_back(std::string(dirName) + "/" + filename->d_name);
        } else {
            continue;
        }
    }

    for (auto d : gdirs) {
        dir = open_dir(d);
        while ((filename = readdir(dir)) != nullptr) {
            std::string dName = std::string(filename->d_name);
            if (dName == "." || dName == ".." || filename->d_type != DT_REG) {
                continue;
            }
            gfiles.emplace_back(std::string(d) + "/" + filename->d_name);
        }
    }
    std::sort(gfiles.begin(), gfiles.end());
    for (auto &f : gfiles) {
        std::cout << "image file: " << f << std::endl;
    }
    return gfiles;
}

int write_result(const std::string& imageFile, const std::vector<MSTensor> &outputs) {
    std::string homePath = "./result_Files";
    for (size_t i = 0; i < outputs.size(); ++i) {
        size_t outputSize = outputs[i].DataSize();
        std::shared_ptr<const void> netOutput = outputs[i].Data();
        int pos = imageFile.rfind('/');
        std::string fileName(imageFile, pos + 1);
        fileName.replace(fileName.find('.'), fileName.size() - fileName.find('.'), '_' + std::to_string(i) + ".bin");
        std::string outFileName = homePath + "/" + fileName;
        FILE *outputFile = fopen(outFileName.c_str(), "wb");
        fwrite(netOutput.get(), outputSize, sizeof(char), outputFile);
        fclose(outputFile);
        outputFile = nullptr;
    }
    return 0;
}

mindspore::MSTensor read_file_to_tensor(const std::string &file) {
    if (file.empty()) {
        std::cout << "Pointer file is nullptr" << std::endl;
        return mindspore::MSTensor();
    }

    std::ifstream ifs(file);
    if (!ifs.good()) {
        std::cout << "File: " << file << " is not exist" << std::endl;
        return mindspore::MSTensor();
    }

    if (!ifs.is_open()) {
        std::cout << "File: " << file << "open failed" << std::endl;
        return mindspore::MSTensor();
    }

    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();
    mindspore::MSTensor buffer(file, mindspore::DataType::kNumberTypeUInt8,
                               {static_cast<int64_t>(size)}, nullptr, size);

    ifs.seekg(0, std::ios::beg);
    ifs.read(reinterpret_cast<char *>(buffer.MutableData()), size);
    ifs.close();

    return buffer;
}

DIR *open_dir(std::string_view dirName) {
    if (dirName.empty()) {
        std::cout << " dirName is null ! " << std::endl;
        return nullptr;
    }
    std::string realPath = real_path(dirName);
    struct stat s;
    lstat(realPath.c_str(), &s);
    if (!S_ISDIR(s.st_mode)) {
        std::cout << "dirName is not a valid directory !" << std::endl;
        return nullptr;
    }
    DIR *dir = opendir(realPath.c_str());
    if (dir == nullptr) {
        std::cout << "Can not open dir " << dirName << std::endl;
        return nullptr;
    }
    std::cout << "Successfully opened the dir " << dirName << std::endl;
    return dir;
}

std::string real_path(std::string_view path) {
    char realPathMem[PATH_MAX] = {0};
    char *realPathRet = nullptr;
    realPathRet = realpath(path.data(), realPathMem);
    if (realPathRet == nullptr) {
        std::cout << "File: " << path << " is not exist.";
        return "";
    }

    std::string realPath(realPathMem);
    std::cout << path << " realpath is: " << realPath << std::endl;
    return realPath;
}
