find_package(Snake REQUIRED)
add_executable(snake-game)
target_sources(snake-game PRIVATE main.c snake.c plocha.c)
target_link_libraries(snake-game PRIVATE)
