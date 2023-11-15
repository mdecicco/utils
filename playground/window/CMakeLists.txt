project(window_pg)

file(GLOB_RECURSE 4_window_pg_src "*.h" "*.cpp")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_executable(4_window_pg ${4_window_pg_src})
set_property(TARGET 4_window_pg PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
 
SOURCE_GROUP("" FILES ${4_window_pg_src})

target_include_directories(4_window_pg PUBLIC ../../include)
target_link_libraries(4_window_pg utils)
set_target_properties(4_window_pg PROPERTIES FOLDER playgrounds)