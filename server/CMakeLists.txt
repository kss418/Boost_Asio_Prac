add_executable(server 
    main.cpp
    src/Acceptor.cpp
    src/Acceptor_Handler.cpp
    src/Thread_Pool.cpp
)

target_include_directories(server
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-linux/include
)

target_link_libraries(server
    PRIVATE
    nlohmann_json::nlohmann_json
    Boost::beast
    Boost::asio
)
