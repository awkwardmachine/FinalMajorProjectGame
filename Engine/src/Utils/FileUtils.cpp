//
// Created by Nil on 10/03/2026.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Engine/Utils/FileUtils.h"

namespace Engine::FileUtils {
    std::string readFile(const std::string &path) {
        std::ifstream file(path, std::ios::in);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return "";
        } // open the file

        std::stringstream buffer;
        buffer << file.rdbuf(); // read the contents of the file
        file.close();
        return buffer.str(); // return the contents of the file
    }
} // namespace Engine::FileUtils
