import os
import platform
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as _build_ext
from utils import ORIGINAL_NAME, NEW_NAME, FILE_EXT

# Define the extension module
game_module = Extension(ORIGINAL_NAME, sources=['game.c'])

class build_ext(_build_ext):
    def run(self):
        _build_ext.run(self)
        for filename in os.listdir('.'):
            if filename.endswith(FILE_EXT) and ORIGINAL_NAME in filename:
                src = os.path.join('.', filename)
                dst = os.path.join('.', f'{NEW_NAME}{FILE_EXT}')
                os.rename(src, dst)
                print(f'Renamed {src} to {dst}')

# Setup script
setup(
    name='tic-tac-toe',
    version='1.0',
    description='Tic Tac Toe game module',
    ext_modules=[game_module],
    cmdclass={'build_ext': build_ext},
)