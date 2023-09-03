find_package(cxxopts CONFIG REQUIRED)

add_library("${PROJECT_NAME}-main" OBJECT)
add_library("rmm::rtoolbox::main" ALIAS "${PROJECT_NAME}-main")
target_compile_definitions("${PROJECT_NAME}"
  PUBLIC
)
target_compile_options("${PROJECT_NAME}-main"
  PUBLIC
)
target_link_libraries("${PROJECT_NAME}-main"
  PUBLIC
    "cxxopts::cxxopts"
    "rmm::rtoolbox"
)
target_link_options("${PROJECT_NAME}-main"
  PUBLIC
)
target_sources("${PROJECT_NAME}-main"
  PUBLIC
    "src/RTMain.cpp"
)
