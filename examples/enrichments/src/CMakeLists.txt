
set( SRCS
  "enrichmentmainwindow.cpp"
  "enrichments.cpp"
  "main.cpp"
  )
set( HEADERS
  "enrichmentmainwindow.h"
  "enrichments.h"
  )
set( FORMS
  "enrichmentmainwindowbase4.ui"
  )

add_executable( enrichments WIN32
  ${SRCS}
  ${HEADERS}
  ${FORMS}
  ${RC_ICON}
  )

target_link_libraries( enrichments qwtplot3d )
