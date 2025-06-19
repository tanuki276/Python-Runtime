from setuptools import setup, Extension

module = Extension('myext', sources=['myext.c'])

setup(
    name='myext',
    version='0.1',
    description='Colorful fireworks ASCII animation C extension',
    ext_modules=[module],
)