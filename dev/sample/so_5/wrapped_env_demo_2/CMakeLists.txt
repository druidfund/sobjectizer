set(SAMPLE sample.so_5.wrapped_env_demo_2)
add_executable(${SAMPLE} main.cpp)
target_link_libraries(${SAMPLE} sobjectizer::SharedLib)
install(TARGETS ${SAMPLE} DESTINATION bin)

set(SAMPLE_S sample.so_5.wrapped_env_demo_2_s)
add_executable(${SAMPLE_S} main.cpp)
target_link_libraries(${SAMPLE_S} sobjectizer::StaticLib)
install(TARGETS ${SAMPLE_S} DESTINATION bin)

