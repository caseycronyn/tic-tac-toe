from setuptools import setup, Extension

# Define the extension module
game_module = Extension('game', sources=['game.c'])

# Setup script
setup(
    name='game',
    version='1.0',
    description='Tic Tac Toe game module',
    ext_modules=[game_module],
)
