"""
Tasks to run through invoke
"""

from invoke import task, context

# The Data Structures that can be called:
data_structures = ['b_tree', 'binary_tree', 'double_linked_list',
                   'fibonacci_array', 'fibonacci_loop', 'fibonacci_rec',
                   'fibonacci_tree', 'hash_table', 'heap', 'queue',
                   'single_linked_list', 'stack']

@task()
def clean(cmd: context.Context) -> None:
    """Cleans artifacts from the project. Can be called with `invoke clean`.
    Args:
        cmd (context.Context): Context invoke passes to run commands
    Returns:
        None
    """
    cmd.run('rm -rf bin')


@task(clean)
def build(cmd: context.Context) -> None:
    """Builds the project. Can be called with `invoke build`.
    Args:
        cmd (context.Context): Context invoke passes to run commands
    Returns:
        None
    """
    cmd.run('mkdir bin;cmake -B bin -S .;cd bin;make')

@task(build, help={'structure_type': 'Name of the data structure to use. Use `all` to run each'})
def run(cmd: context.Context, structure_type: str) -> None:
    """Builds the project. Can be called with `invoke build <structure_type>`.
    For example, using `invoke build all` runs each, while
    `invoke build bubble` only runs bubble sort.
    Args:
        cmd (context.Context): Context invoke passes to run commands
        structure_type (str): The data structure to run, or `all`
    Returns:
        None
    """
    structure_lower = structure_type.lower()
    if structure_lower == 'all':
        for sort_method in data_structures:
            cmd.run(f"./bin/src/{sort_method}")
    elif structure_lower in data_structures:
        cmd.run(f"./bin/src/{structure_lower}")
    else:
        print(f"Sort Type '{structure_type}' is not implemented")
