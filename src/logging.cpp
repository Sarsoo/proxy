#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

void init_logging()
{
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

    logging::add_file_log
    (
        keywords::file_name = "proxy_%N.log",
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
    );

    logging::add_console_log(std::cout, boost::log::keywords::format = "[%TimeStamp%] [%Severity%] >> %Message%");

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );

    logging::add_common_attributes();
}