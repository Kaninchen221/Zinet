from setuptools import setup

setup(
    name='zinet_preflector',
    version='1.0.0',
    install_requires = [
        "pytest == 7.2.0",
        "pytest-mock == 3.10.0",
        "numpy == 1.24.0",
        "clang == 16.0.1.1"
    ]
)