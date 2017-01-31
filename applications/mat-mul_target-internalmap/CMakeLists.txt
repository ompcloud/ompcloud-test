
set(SRC_DIR src)

set(SRC_FILES
  ${SRC_DIR}/mat-mul.c
)

add_executable(target-internalmap ${SRC_FILES})
add_dependencies(omptests target-internalmap)

#add_dependencies(supported target-internalmap)

add_test(target-internalmap target-internalmap)
