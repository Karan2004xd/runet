import os
import subprocess
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

class BuildWithMake(build_ext):
    def run(self):
        subprocess.check_call(['make', 'clean'])

        print("\n--- Running Tests ---")
        subprocess.check_call(['make', 'test'])
        subprocess.check_call(['./test'])

        print("\n--- Building Library ---")
        subprocess.check_call(['make', 'librunet.so'])

        target_dir = os.path.join(self.build_lib, 'runet_pkg')
        os.makedirs(target_dir, exist_ok=True)
        self.copy_file('libs/librunet.so', os.path.join(target_dir, 'librunet.so'))

setup(
    name="runet_pkg",
    version="1.0",
    packages=["runet_pkg"],
    ext_modules=[Extension("runet_pkg.librunet", sources=[])],
    cmdclass={'build_ext': BuildWithMake},
    install_requires=["numpy", "tensorflow"]
)
