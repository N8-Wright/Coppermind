add_library(Coppermind.IO ReaderStreamWrapper.cpp WriterStreamWrapper.cpp)
target_include_directories(Coppermind.IO PUBLIC .)

add_library(Coppermind::IO ALIAS Coppermind.IO)