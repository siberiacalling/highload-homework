#ifndef HTTP_SERVER_CONFIG_HPP
#define HTTP_SERVER_CONFIG_HPP


#include <string>

class Config {
public:
    Config();

    std::string port;
    std::string address;
    std::string document_root;
    std::string thread_limit;
private:
    void process_config(const std::string &key, const std::string &value);
};


#endif //HTTP_SERVER_CONFIG_HPP
