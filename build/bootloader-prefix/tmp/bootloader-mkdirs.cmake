# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/gkitambala/esp/esp-idf/components/bootloader/subproject"
  "C:/Work/AS5311_esp32/build/bootloader"
  "C:/Work/AS5311_esp32/build/bootloader-prefix"
  "C:/Work/AS5311_esp32/build/bootloader-prefix/tmp"
  "C:/Work/AS5311_esp32/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Work/AS5311_esp32/build/bootloader-prefix/src"
  "C:/Work/AS5311_esp32/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Work/AS5311_esp32/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
