from setuptools import setup, Extension

setup(
    name="myext",
    version="0.1",
    ext_modules=[Extension("myext", ["myext.c"])],
)
