
set(SRC_DIR src)

set(SRC_FILES
  ${SRC_DIR}/mat-mul.c
)

add_executable(target-device ${SRC_FILES})
add_dependencies(omptests target-device)

add_test(target-device target-device)
