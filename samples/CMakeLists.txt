add_executable(tcpClientSync tcpClientSync.cpp)
target_link_libraries(tcpClientSync PRIVATE Boost::system Boost::thread)
#target_compile_definitions(tcpClientSync PRIVATE _WIN32_WINNT=0x0501)

add_executable(tcpServerSync tcpServerSync.cpp)
target_link_libraries(tcpServerSync PRIVATE Boost::system Boost::thread)
#target_compile_definitions(tcpServerSync PRIVATE _WIN32_WINNT=0x0501)

