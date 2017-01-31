
set(SRC_DIR src)

set(SRC_FILES
  ${SRC_DIR}/simple.c
)

add_executable(simple_target-internalmap ${SRC_FILES})

add_dependencies(omptests simple_target-internalmap)

add_test(simple_target-internalmap simple_target-internalmap)
