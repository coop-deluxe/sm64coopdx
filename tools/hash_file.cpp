#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <filesystem>
#include <iomanip>

static std::string readFileData(const std::string &filepath) {
    if (filepath == "") { return ""; }
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file) throw std::runtime_error("Cannot open file.");
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::string data(fileSize, '\0');
    if (!file.read(&data[0], fileSize)) throw std::runtime_error("Cannot read file data.");
    return data;
}

std::size_t hashFile(const std::string &filepath) {
    const std::string data = readFileData(filepath);
    if (data == "") { return 0; }
    return std::hash<std::string>{}(data);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    std::string filepath = argv[1];

    try {
        if (!std::filesystem::exists(filepath)) {
            std::cerr << "Error: File does not exist." << std::endl;
            return 1;
        }

        std::size_t fileHash = hashFile(filepath);
        std::cout << "Hash of file '" << filepath << "': "
            << fileHash << " :: "
            << std::hex << std::uppercase << std::showbase << fileHash
            << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
