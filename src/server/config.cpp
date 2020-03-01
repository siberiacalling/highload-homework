#include <iostream>
#include <fstream>
#include <sstream>
#include "config.hpp"

Config::Config() {
    std::ifstream configFile;
    configFile.open("/etc/server.conf");
    if (!configFile) {
        std::cerr << "Unable to open file server config" << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << configFile.rdbuf();
    std::string line;

    while (std::getline(buffer, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, ' ')) {
            std::string value;
            if (std::getline(is_line, value)) {
                Config::process_config(key, value);
            }
        }
    }
}

void Config::process_config(const std::string &key, const std::string &value) {
    if (key == "port") {
        port = value;
    } else if (key == "thread_limit") {
        thread_limit = value;
    } else if (key == "document_root") {
        document_root = value;
    } else if (key == "address") {
        address = value;
    } else {
        std::cerr << "Unexpected value in config" << std::endl;
    }
}
