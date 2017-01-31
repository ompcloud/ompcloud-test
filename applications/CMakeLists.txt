
include_directories(common)

add_custom_target(omptests)

add_subdirectory(mat-mul_target-device)
add_subdirectory(mat-mul_target-outerindex)
add_subdirectory(mat-mul_target-internalmap)

add_subdirectory(simple_target-internalmap)
