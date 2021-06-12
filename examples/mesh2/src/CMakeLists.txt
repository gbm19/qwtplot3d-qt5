
set( CMAKE_AUTORCC ON )

set( SRCS
  "designerworkaround.cpp"
  "lightingdlg.cpp"
  "main.cpp"
  "mesh.cpp"
  "mesh2mainwindow.cpp"
  )
set( HEADERS
  "designerworkaround.h"
  "femreader.h"
  "functions.h"
  "lightingdlg.h"
  "mesh2mainwindow.h"
  )
set( FORMS
  "lightingdlgbase4.ui"
  "mesh2mainwindowbase4.ui"
  )

add_executable( mesh2 WIN32
  ${SRCS}
  ${HEADERS}
  ${FORMS}
  "../../images.qrc"
  ${RC_ICON}
  )

target_link_libraries( mesh2 qwtplot3d )
