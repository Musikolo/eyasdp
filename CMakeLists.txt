# Project Needs a name ofcourse
project(eYaSDP)
 
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
 
add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )
 
add_subdirectory(translations)

# We add our source code here
set(eyasdp_SRCS plasma-eyasdp.cpp)

# Now make sure all files get to the right place
kde4_add_ui_files(eyasdp_SRCS
                  ui/AppearanceConfig.ui)

# Now make sure all files get to the right place
kde4_add_plugin(plasma_applet_eyasdp ${eyasdp_SRCS})
target_link_libraries(plasma_applet_eyasdp kworkspace
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS})
 
install(TARGETS plasma_applet_eyasdp
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-applet-eyasdp.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})