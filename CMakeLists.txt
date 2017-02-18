cmake_minimum_required(VERSION 2.8.4)
project(tcp_svr)

set(CMAKE_C_STANDARD 99)

set(CLIENT_SRC client.c)
add_executable(client ${CLIENT_SRC})

set(SERVER_SRC server.c)
add_executable(server ${SERVER_SRC})