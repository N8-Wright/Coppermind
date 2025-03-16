add_library(
    Coppermind.IO
    ReaderStreamWrapper.cpp
    ReaderStreamWrapper.h
    WriterStreamWrapper.cpp
    WriterStreamWrapper.h
    Reader.h
    Writer.h
)

target_include_directories(Coppermind.IO PUBLIC .)
set_target_properties(Coppermind.IO PROPERTIES FOLDER "IO")
add_library(Coppermind::IO ALIAS Coppermind.IO)