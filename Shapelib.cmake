if(MSVC)
    set(SHAPELIB_LIBRARY_NAME shapelib)
else()
    set(SHAPELIB_LIBRARY_NAME shp)
endif()

if(MSVC AND BUILD_SHARED_LIBS)
    add_definitions(/DSHAPELIB_DLLEXPORT)
endif()

set(SOURCES
    shapelib-1.3.0/shpopen.c
    shapelib-1.3.0/shptree.c
    shapelib-1.3.0/dbfopen.c
    shapelib-1.3.0/safileio.c
)
add_library(${SHAPELIB_LIBRARY_NAME} ${SOURCES})
set_target_properties(${SHAPELIB_LIBRARY_NAME} PROPERTIES
    PUBLIC_HEADER shapelib-1.3.0/shapefil.h)
install(TARGETS ${SHAPELIB_LIBRARY_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include)