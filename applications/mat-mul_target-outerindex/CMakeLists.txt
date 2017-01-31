
set(SRC_DIR src)

set(SRC_FILES
  ${SRC_DIR}/mat-mul.c
)

add_executable(target-outerindex ${SRC_FILES})
add_dependencies(omptests target-outerindex)

#add_dependencies(supported target-outerindex)

add_test(target-outerindex target-outerindex)
