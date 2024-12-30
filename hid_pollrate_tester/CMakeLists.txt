# CMakeList.txt: projeto de CMake para hid_pollrate_tester, incluir origem e definir
# lógica específica a um projeto aqui.
#

#include_directories($ENV{UniversalCRTSdkDir}/Include/ucrt)
#--include_directories($ENV{UniversalCRTSdkDir}/Include/10.0.10056.0/ucrt)



if(WIN32)
  set(GUI_TYPE WIN32)
endif()

# Adicione a origem ao executável deste projeto.

add_executable (pollrate_cli "hidapi pollrate.cpp" "include/hidapi.h" )
target_include_directories(pollrate_cli PRIVATE "include/")
if(WIN32)
	target_link_directories(pollrate_cli PRIVATE "dll/")
	target_link_libraries(pollrate_cli "${CMAKE_SOURCE_DIR}/hid_pollrate_tester/dll/hidapi.lib" )
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup")
	file(COPY "dll/hidapi.dll" DESTINATION "./")
endif()
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
	target_link_directories(pollrate_cli PRIVATE "/usr/lib" "/us0r/local/lib" "/usr/share/lib" "/lib" "/usr/lib/x86_64-linux-gnu" "/usr/lib/x86_64-linux-gnu")
      target_link_libraries(pollrate_cli hidapi-hidraw)
endif()
if(MSVC)
  target_compile_options(pollrate_cli PUBLIC "/ZI")
  target_link_options(pollrate_cli PUBLIC "/INCREMENTAL")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup")
  file(COPY "dll/hidapi.dll" DESTINATION "./")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET pollrate_cli PROPERTY CXX_STANDARD 20)
endif()

# TODO: Adicione testes e instale destinos, se necessário.
