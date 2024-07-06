# Set thread requirements for Ubuntu 20.04
# (Automatically included in 22.04)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Compiles passed struct with corresponding source code
function(compile_struct struct_type struct_src)
    # Define / Create Executable binary
    add_executable(${struct_type} ${struct_src})

    # Add struct compilation flags / links
    target_compile_options(${struct_type} PRIVATE -Wall)
    set(TARGET ${struct_type} PROPERTY C_STANDARD 11)
    set(TARGET ${struct_type} PROPERTY C_STANDARD_REQUIRED ON)

    target_link_libraries(${struct_type} PRIVATE Threads::Threads)
endfunction()

# Call each struct to compile
compile_struct(b_tree b_tree.c)
compile_struct(binary_tree binary_tree.c)
compile_struct(doubly_linked_list doubly_linked_list.c)
compile_struct(fibonacci_array fibonacci_arr.c)
compile_struct(fibonacci_loop fibonacci_loop.c)
compile_struct(fibonacci_rec fibonacci_rec.c)
compile_struct(fibonacci_tree fibonacci_tree.c)
compile_struct(hash_table hash_table.c)
compile_struct(heap heap.c)
compile_struct(queue queue.c)
compile_struct(singly_linked_list singly_linked_list.c)
compile_struct(stack stack.c)
