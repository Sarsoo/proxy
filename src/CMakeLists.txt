add_executable(proxy main.cpp)

FetchContent_Declare(
    json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.2
)

FetchContent_MakeAvailable(json)

FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.82.0
)
FetchContent_MakeAvailable(Boost)

target_link_libraries(proxy PRIVATE nlohmann_json::nlohmann_json Boost::program_options Boost::log Boost::date_time Boost::filesystem Boost::system Boost::thread Boost::log_setup Boost::chrono Boost::atomic library)