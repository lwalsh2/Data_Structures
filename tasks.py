"""
Tasks to run through invoke
"""

from invoke import task, context

# The Data Structures that can be called:
data_structures = ['b_tree', 'binary_tree', 'double_linked_list',
                   'fibonacci_arr', 'fibonacci_loop', 'fibonacci_rec',
                   'fibonacci_tree', 'hash_table', 'heap', 'queue',
                   'single_linked_list', 'stack']
library_loc = 'build/src/'
test_loc = 'build/tests/'


@task()
def clean(cmd: context.Context) -> None:
    """Cleans artifacts from the project. Can be called with `invoke clean`.
    Args:
        cmd (context.Context): Context invoke passes to run commands
    Returns:
        None
    """
    cmd.run('rm -rf bin build')


@task(clean)
def build(cmd: context.Context) -> None:
    """Builds the project. Can be called with `invoke build`.
    Args:
        cmd (context.Context): Context invoke passes to run commands
    Returns:
        None
    """
    # Build the libraries and test binaries
    cmd.run('mkdir bin build;cmake -B build -S .;cd build;make')
    # Move the test binaries to the project directory
    for sort_method in data_structures:
        cmd.run(f"cp {test_loc}{sort_method}_test bin/")

@task(build, help={'structure_type': 'Name of the data structure to test. Use `all` to run each'})
def test(cmd: context.Context, structure_type: str) -> None:
    """Builds the project. Can be called with `invoke test <structure_type>`.
    For example, using `invoke test all` tests each, while
    `invoke test bubble` only tests bubble sort.
    Args:
        cmd (context.Context): Context invoke passes to run commands
        structure_type (str): The data structure to test, or `all`
    Returns:
        None
    """
    structure_lower = structure_type.lower()
    if structure_lower == 'all':
        for sort_method in data_structures:
            cmd.run(f"./bin/tests/{sort_method}_test")
    elif structure_lower in data_structures:
        cmd.run(f"./bin/tests/{structure_lower}_test")
    else:
        print(f"Sort Type '{structure_type}' is not implemented")
