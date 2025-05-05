add_executable(client 
    main.cpp
    src/Session.cpp
    src/Session_Handler.cpp
)

target_include_directories(client
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-linux/include
)

target_link_libraries(client
    PRIVATE
    nlohmann_json::nlohmann_json
    Boost::beast
    Boost::asio
)

