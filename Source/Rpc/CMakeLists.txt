add_library(Coppermind.Rpc
    BinaryPacker.cpp
    BinaryPacker.h
    BinaryUnpacker.cpp
    BinaryUnpacker.h
    RpcSrv.cpp
    RpcSrv.h
    RpcException.cpp
    RpcException.h
    RpcPacker.cpp
    RpcPacker.h
    RpcUnpacker.cpp
    RpcUnpacker.h
)

target_link_libraries(Coppermind.Rpc PUBLIC Coppermind::Net)
target_include_directories(Coppermind.Rpc PUBLIC .)
add_library(Coppermind::Rpc ALIAS Coppermind.Rpc)

add_executable(BinaryPackerTests BinaryPackerTests.cpp)
target_link_libraries(BinaryPackerTests PRIVATE Coppermind::Rpc Coppermind::IO Catch2::Catch2WithMain)
catch_discover_tests(BinaryPackerTests)

add_executable(RpcPackerTests RpcPackerTests.cpp)
target_link_libraries(RpcPackerTests PRIVATE Coppermind::Rpc Catch2::Catch2WithMain)
catch_discover_tests(RpcPackerTests)

add_executable(RpcSrvTests RpcSrvTests.cpp)
target_link_libraries(RpcSrvTests PRIVATE Coppermind::Rpc Catch2::Catch2WithMain)
catch_discover_tests(RpcSrvTests)

add_executable(RpcUnpackerTests RpcUnpackerTests.cpp)
target_link_libraries(RpcUnpackerTests PRIVATE Coppermind::Rpc Catch2::Catch2WithMain)
catch_discover_tests(RpcUnpackerTests)
