add_executable(tcpClientSync tcpClientSync.cpp)
target_link_libraries(tcpClientSync PRIVATE Boost::thread)
#target_compile_definitions(tcpClientSync PRIVATE _WIN32_WINNT=0x0501)

add_executable(tcpServerSync tcpServerSync.cpp)
target_link_libraries(tcpServerSync PRIVATE Boost::thread)
#target_compile_definitions(tcpServerSync PRIVATE _WIN32_WINNT=0x0501)

add_executable(tcpServerAsync tcpServerAsync.cpp)
target_link_libraries(tcpServerAsync PRIVATE Boost::thread)

add_executable(timer1_sync timer1_sync.cpp)
target_link_libraries(timer1_sync PRIVATE Boost::thread)

add_executable(timer2_async timer2_async.cpp)
target_link_libraries(timer2_async PRIVATE Boost::thread)

add_executable(timer3_asyncArguments timer3_asyncArguments.cpp)
target_link_libraries(timer3_asyncArguments PRIVATE Boost::thread)

add_executable(timer4_asyncMemberFunc timer4_asyncMemberFunc.cpp)
target_link_libraries(timer4_asyncMemberFunc PRIVATE Boost::thread)

add_executable(timer5_asyncMultiThread timer5_asyncMultiThread.cpp)
target_link_libraries(timer5_asyncMultiThread PRIVATE Boost::thread)
