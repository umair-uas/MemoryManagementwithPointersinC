cmake_minimum_required(VERSION 3.1)

project(MemMgmtwithPtr C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# List of source files (add more files as needed)
set(SOURCE_FILES
    intmemalloc.c
    pointers_pass_by_ref.c
    allocatingmem.c
    pointer_arithmetic.c
    function_pointers.c
    functionPtrsandStructs.c
    managingmem_withPtrs.c
    multidimenarray.c
    LibraryMgmntwithPtrs.c
    dynamic_memmgmt_with_arrays.c
    struct_memlayout.c
    dynamic_structs.c
    dynamic_structs_memmgt.c
    linkedlist_osilayers.c
    # Add more source files here
)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

foreach(SOURCE_FILE ${SOURCE_FILES})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    set(EXECUTABLE_NAME "${FILE_NAME}")
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME ${EXECUTABLE_NAME})
    target_compile_options(${EXECUTABLE_NAME} PRIVATE -g)  # Add -g flag

# Add Clang Tidy and Clang Static Analyzer flags
#   target_compile_options(${EXECUTABLE_NAME} PRIVATE
#       -Xclang -analyze -Xclang --analyzer-output=text
#       -Xclang -plugin-arg-analyzer-checker=core
#       -Xclang -plugin-arg-analyzer-checker=deadcode
#   )

endforeach()
