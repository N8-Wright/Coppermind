add_library(Coppermind.Net
    Networking.h
    Networking.cpp
    TcpSocket.h
    TcpSocket.cpp
)

target_include_directories(Coppermind.Net PUBLIC .)
if (WIN32)
    target_link_libraries(Coppermind.Net PUBLIC Ws2_32)
endif()

target_link_libraries(Coppermind.Net PUBLIC Coppermind::IO)

add_library(Coppermind::Net ALIAS Coppermind.Net)

add_executable(TcpSocketTests TcpSocketTests.cpp)
target_link_libraries(TcpSocketTests PRIVATE Coppermind::Net GTest::gtest_main)
gtest_discover_tests(TcpSocketTests)
