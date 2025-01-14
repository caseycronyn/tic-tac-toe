import platform
import os

ORIGINAL_NAME = "game"
NEW_NAME = "tic-tac-toe"
FILE_EXT = '.dll' if platform.system() == 'Windows' else '.so'

def get_lib_name() -> str:
    """
    Constructs the library file name with the appropriate extension based on the operating system.
    """
    return os.path.join('.', f'{NEW_NAME}{FILE_EXT}')