file(GLOB_RECURSE BEPBEP_SOURCE_CODE *.cpp)

include_directories("./")

add_executable(BepBep ${BEPBEP_SOURCE_CODE})
target_link_libraries(BepBep bebone)