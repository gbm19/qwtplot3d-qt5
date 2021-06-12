
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

if( WIN32 AND BUILD_SHARED_LIBS )
  add_compile_definitions( QWT3D_DLL )
endif()

set( RC_ICON "${CMAKE_CURRENT_SOURCE_DIR}/icon.rc" )

add_subdirectory(autoswitch)

add_subdirectory(axes/src)

add_subdirectory(enrichments/src)

add_subdirectory(mesh2/src)

add_subdirectory(simpleplot)
