"""
Tasks to run through invoke
"""

from invoke import task, context

# The Data Structures that can be called:
sort_methods = ['b_tree', 'binary_tree', 'double_linked_list',
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

@task(build, help={'sort_type': 'Name of the sorting method to use. Use `all` to run each'})
def run(cmd: context.Context, sort_type: str) -> None:
    """Builds the project. Can be called with `invoke build <sort_type>`.
    For example, using `invoke build all` runs each, while
    `invoke build bubble` only runs bubble sort.
    Args:
        cmd (context.Context): Context invoke passes to run commands
        sort_type (str): The sorting method to run, or `all`
    Returns:
        None
    """
    sort_lower = sort_type.lower()
    if sort_lower == 'all':
        for sort_method in sort_methods:
            cmd.run(f"./bin/src/{sort_method}")
    elif sort_lower in sort_methods:
        cmd.run(f"./bin/src/{sort_lower}")
    else:
        print(f"Sort Type '{sort_type}' is not implemented")
