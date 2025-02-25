add_executable(HelloWorldSrv HelloWorldSrv.cpp)
target_link_libraries(HelloWorldSrv Coppermind::Rpc)

add_executable(HelloWorldClient HelloWorldClient.cpp)
target_link_libraries(HelloWorldClient Coppermind::Rpc)
