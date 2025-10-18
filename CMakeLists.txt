cmake_minimum_required(VERSION 3.16)
project(debug VERSION 0.0.1)

find_package(Albert REQUIRED)
find_package(QCoro6 REQUIRED COMPONENTS Coro)

albert_plugin(
    QT Core
    LINK PRIVATE QCoro6::Coro
)
