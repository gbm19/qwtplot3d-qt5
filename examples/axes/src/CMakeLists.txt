
set( SRCS
  "axesmainwindow.cpp"
  "main.cpp"
  )
set( HEADERS
  "axes.h"
  "axesmainwindow.h"
  )
set( FORMS
  "axesmainwindowbase4.ui"
  )

add_executable( axes WIN32
  ${SRCS}
  ${HEADERS}
  ${FORMS}
  ${RC_ICON}
  )

target_link_libraries( axes qwtplot3d )
