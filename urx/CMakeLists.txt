#set(HEADERS
#        urx.hpp
#        urx_baseconnector.hpp
#        )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(urx INTERFACE)
target_include_directories(urx INTERFACE .)
