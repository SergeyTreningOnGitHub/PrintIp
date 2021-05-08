include_directories(${ROOT_DIR}/Inc)
                                   
add_executable(print_ip.out main.cpp)

install(TARGETS print_ip.out DESTINATION ${ROOT_DIR}/bin)