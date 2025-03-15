add_library(Coppermind.Rpc
    BinaryPacker.cpp
    BinaryPacker.h
    BinaryUnpacker.cpp
    BinaryUnpacker.h
    RpcProcessor.cpp
    RpcProcessor.h
    RpcException.cpp
    RpcException.h
    RpcPacker.cpp
    RpcPacker.h
    RpcUnpacker.cpp
    RpcUnpacker.h
    RpcSrv.cpp
    RpcSrv.h
    RpcClient.cpp
    RpcClient.h
)

target_link_libraries(Coppermind.Rpc PUBLIC Coppermind::Net)
target_include_directories(Coppermind.Rpc PUBLIC .)
add_library(Coppermind::Rpc ALIAS Coppermind.Rpc)

add_executable(BinaryPackerTests BinaryPackerTests.cpp)
target_link_libraries(BinaryPackerTests PRIVATE Coppermind::Rpc Coppermind::IO Catch2::Catch2WithMain)
catch_discover_tests(BinaryPackerTests)

add_executable(RpcPackerTests RpcPackerTests.cpp)
target_link_libraries(RpcPackerTests PRIVATE Coppermind::Rpc GTest::gtest_main)
gtest_discover_tests(RpcPackerTests)

add_executable(RpcProcessorTests RpcProcessorTests.cpp)
target_link_libraries(RpcProcessorTests PRIVATE Coppermind::Rpc GTest::gtest_main)
gtest_discover_tests(RpcProcessorTests)

add_executable(RpcUnpackerTests RpcUnpackerTests.cpp)
target_link_libraries(RpcUnpackerTests PRIVATE Coppermind::Rpc GTest::gtest_main)
gtest_discover_tests(RpcUnpackerTests)
