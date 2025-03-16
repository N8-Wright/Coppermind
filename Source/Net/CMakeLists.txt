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

set_target_properties(Coppermind.Net PROPERTIES FOLDER "Net")
target_link_libraries(Coppermind.Net PUBLIC Coppermind::IO)
add_library(Coppermind::Net ALIAS Coppermind.Net)

add_executable(TcpSocketTests TcpSocketTests.cpp)
target_link_libraries(TcpSocketTests PRIVATE Coppermind::Net GTest::gtest_main)
set_target_properties(TcpSocketTests PROPERTIES FOLDER "Net")
gtest_discover_tests(TcpSocketTests)
