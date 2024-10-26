cmake_minimum_required(VERSION 3.10)
# Nama proyek
project(OpenCV_IRIS2)
# Mencari OpenCV yang terinstal di sistem
find_package(OpenCV REQUIRED)
# Menambahkan executable dari file main.cpp
add_executable(vid Tugas2CV.cpp)
# Menautkan library OpenCV
target_link_libraries(vid ${OpenCV_LIBS})