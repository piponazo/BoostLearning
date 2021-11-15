cmake_minimum_required(VERSION 3.10)

project(BoostLearning
  VERSION 0.1
  LANGUAGES CXX)

include(cmake/mainSetup.cmake         REQUIRED)
include(cmake/findDependencies.cmake REQUIRED)

add_subdirectory(samples)

include(cmake/printSummary.cmake REQUIRED)
