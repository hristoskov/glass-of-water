
cmake_minimum_required(VERSION 3.12)

project(GlassOfWater_Project LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_definitions(-DCPPHTTPLIB_OPENSSL_SUPPORT)

include_directories(dependencies/include)
link_directories(dependencies/lib)

add_executable(GlassesSim GlassesSim.c GlassOfWaterLib.c)
add_executable(TapControlSim TapControlSim.c GlassOfWaterLib.c)
add_executable(GlassOfWaterSim GlassOfWaterSim.c GlassOfWaterLib.c)

set_target_properties(GlassesSim PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(TapControlSim PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(GlassOfWaterSim PROPERTIES LINKER_LANGUAGE CXX)
if (WIN32)
    target_link_libraries(GlassesSim CppModelBase ixwebsocket crypto ssl z crypt32 ws2_32)
    target_link_libraries(TapControlSim CppModelBase ixwebsocket crypto ssl z crypt32 ws2_32)
    target_link_libraries(GlassOfWaterSim CppModelBase ixwebsocket crypto ssl z crypt32 ws2_32)
else()
    target_link_libraries(GlassesSim CppModelBase ixwebsocket crypto ssl z)
    target_link_libraries(TapControlSim CppModelBase ixwebsocket crypto ssl z)
    target_link_libraries(GlassOfWaterSim CppModelBase ixwebsocket crypto ssl z)
endif()

add_test(NAME GlassesSim_Test COMMAND GlassesSim)
add_test(NAME TapControlSim_Test COMMAND TapControlSim)
add_test(NAME GlassOfWaterSim_Test COMMAND GlassOfWaterSim)

