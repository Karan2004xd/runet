from setuptools import setup, find_packages

setup(
    name="runet",
    version="0.1",
    packages=['runet'],
    package_dir={'runet': 'scripts'},
    install_requires=[
        'numpy',
        'tensorflow'
    ]
)
