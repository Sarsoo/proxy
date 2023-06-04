#include <memory>
#include <fstream>

#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

void on_age(int age)
{
    BOOST_LOG_TRIVIAL(info) << "On age: " << age;
}

shared_ptr<po::variables_map> init_config(int argc, const char *argv[])
{
    int def;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("compression,c", po::value<int>(), "set compression level")
        ("def,d", po::value<int>(&def)->default_value(10), "set def level")
        ("abc", po::value<int>()->default_value(25), "set abc level")
        ("phone", po::value<std::vector<std::string>>()->multitoken()->zero_tokens()->composing(), "Phone")
        ("age,a", po::value<int>()->notifier(on_age), "age")
        ("config", po::value<std::string>(), "Config file")
    ;

    po::options_description other("Other");
    desc.add_options()
        ("other-option,o", po::value<int>(), "another option")
    ;

    // Hidden options, will be allowed both on command line and
    // in config file, but will not be shown to the user.
    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("input-file", po::value< vector<string> >(), "input file");  

    po::positional_options_description p;
    p.add("phone", -1);

    po::options_description cmdline_options;
    cmdline_options.add(desc).add(other).add(hidden);

    po::options_description config_file_options;
    config_file_options.add(desc).add(hidden);

    po::options_description visible("Allowed options");
    visible.add(desc).add(other);

    ////////////
    // PARSE
    ////////////

    auto vm = make_shared<po::variables_map>();
    po::store(po::command_line_parser(argc, argv)
            .options(desc)  
            .positional(p)
            .run(), 
        *vm);

    if (vm->count("config"))
    {
        BOOST_LOG_TRIVIAL(info) << "Attempting file config load";
        std::ifstream ifs{(*vm)["config"].as<std::string>().c_str()};
        if (ifs) {
            BOOST_LOG_TRIVIAL(info) << "File opened, loading...";
            po::store(po::parse_config_file(ifs, config_file_options), *vm);
        }
    }
    po::notify(*vm); 

    if (vm->count("help")) {
        BOOST_LOG_TRIVIAL(info) << desc;
    }
    else {

        if (vm->count("compression")) {
            BOOST_LOG_TRIVIAL(info) << "Compression level was set to " << (*vm)["compression"].as<int>() << ".";
        } else {
            BOOST_LOG_TRIVIAL(info) << "Compression level was not set.";
        }

        if (vm->count("def")) {
            BOOST_LOG_TRIVIAL(info) << "def level was set to " << (*vm)["def"].as<int>() << ".";
        } else {
            BOOST_LOG_TRIVIAL(info) << "def level was not set.";
        }
    }

    return vm;
}