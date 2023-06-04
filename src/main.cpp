#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "logging.cpp"
#include "config.cpp"

#include <nlohmann/json.hpp>

using namespace std;

int main(int argc, const char *argv[]) {
    try{
        init_logging();
        init_config(argc, argv);

        BOOST_LOG_TRIVIAL(info) << "hello world";
    }
    catch (const po::error &ex)
    {
        BOOST_LOG_TRIVIAL(error) << ex.what();
    }
}