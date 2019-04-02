add_library(catch_main OBJECT "catch_main.cpp")

target_include_directories(catch_main 
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/third-party)

file(GLOB files "test-*.cpp")
foreach(file ${files})
    get_filename_component(testname ${file} NAME_WE)
    add_executable(${testname}
                   $<TARGET_OBJECTS:catch_main>
                   "${file}")

    target_link_libraries(${testname}
                          ${BWF_TARGET_NAME})

    target_include_directories(${testname}
                               PRIVATE
                               ${CMAKE_CURRENT_SOURCE_DIR}/third-party)

    add_test(NAME UNIT-${testname}_${CMAKE_BUILD_TYPE}
             COMMAND ${testname})
endforeach()

