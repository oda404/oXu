cmake_minimum_required(VERSION 3.2)

project(argparser)

add_library(argparser include/argparser/argparser.h src/argparser.c)
target_include_directories(argparser PUBLIC include/)