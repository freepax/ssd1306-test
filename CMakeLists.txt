cmake_minimum_required (VERSION 2.6)
project (SSD1306-INFO)

set(CMAKE_CURRENT_SOURCE_DIR .)

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_PREFIX /usr/)

set(SSD1306_SOURCE
  ssd1306-info.cpp
)

add_executable(ssd1306-info ${SSD1306_SOURCE} ${SSD1306_HEADERS})
target_link_libraries(ssd1306-info libssd1306)

install(TARGETS ssd1306-info DESTINATION bin)
