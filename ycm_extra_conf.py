import os
import ycm_core

# Flags based on your project requirements
flags = [
    '-Wall',             # Enable all warnings
    '-Wextra',           # Enable extra warnings
    '-Werror',           # Treat warnings as errors
    '-pthread',          # Enable pthread for multi-threading
    '-g3',               # Include debug information
    '-fPIC',             # Position-independent code
    '-std=c99',          # Adjust to your C standard if necessary
    '-I', 'include',     # Include project headers directory
    '-I/usr/include',    # System includes
    '-I/usr/local/include',  # Local includes
]

# Optionally, if you use a compilation database:
compilation_database_folder = ''

def DirectoryOfThisScript():
    return os.path.dirname(os.path.abspath(__file__))

def MakeRelativePathsAbsolute(flags, working_directory):
    if not working_directory:
        return list(flags)
    new_flags = []
    for flag in flags:
        new_flag = flag
        if flag.startswith('-I'):
            path = flag[2:]
            if not os.path.isabs(path):
                new_flag = '-I' + os.path.join(working_directory, path)
        new_flags.append(new_flag)
    return new_flags

def FlagsForFile(filename):
    return {
        'flags': MakeRelativePathsAbsolute(flags, DirectoryOfThisScript()),
        'do_cache': True  # Cache results for faster performance
    }
