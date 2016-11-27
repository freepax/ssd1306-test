cmake_minimum_required (VERSION 2.6)
project (SSD1306-TEST)

set(CMAKE_CURRENT_SOURCE_DIR .)

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_PREFIX /usr/)

set(SSD1306-TEST-SOURCE
  ssd1306-test.cpp
)

add_executable(ssd1306-test ${SSD1306-TEST-SOURCE})
target_link_libraries(ssd1306-test firmware_i2c ssd1306)

install(TARGETS ssd1306-test DESTINATION bin)
