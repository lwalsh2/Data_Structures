# Set thread requirements for Ubuntu 20.04
# (Automatically included in 22.04)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Define / Create Executable binary
add_executable(b_tree b_tree.c)

# Add struct compilation flags / links
target_include_directories(b_tree PRIVATE include)
target_compile_options(b_tree PRIVATE -Wall)
set(TARGET b_tree PROPERTY C_STANDARD 11)
set(TARGET b_tree PROPERTY C_STANDARD_REQUIRED ON)

target_link_libraries(b_tree PRIVATE Threads::Threads)
