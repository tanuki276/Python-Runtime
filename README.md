# Termux Python C Extension Sample

This repository shows how to build and use a simple Python C extension module in Termux.

## Usage

```bash
pkg update && pkg install clang python make unzip
unzip termux-python-ext-sample.zip
cd termux-python-ext-sample
python setup.py build
python setup.py install
python3 -c "import myext; print(myext.hello())"
```
