import os
import subprocess
import sys
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

class MakeBuild(build_ext):
    def run(self):
        try:
            print("--- Step 1: Cleaning build artifacts ---")
            subprocess.check_call(['make', 'clean'])

            print("--- Step 2: Compiling and Running Tests ---")
            subprocess.check_call(['make', 'test'])
            subprocess.check_call(['./test'])
            print("--- Tests Passed Successfully ---")

            print("--- Step 3: Building Shared Library ---")
            subprocess.check_call(['make', 'librunet.so'])

        except subprocess.CalledProcessError as e:
            print(f"\n[ERROR] Build or Test failed!")
            print(f"Command '{e.cmd}' returned non-zero exit status {e.returncode}.")
            sys.exit(1) # Stop the installation

        target_dir = os.path.join(self.build_lib, 'runet_pkg')
        os.makedirs(target_dir, exist_ok=True)

        source_path = os.path.join('libs', 'librunet.so')
        dest_path = os.path.join(target_dir, 'librunet.so')

        if os.path.exists(source_path):
            self.copy_file(source_path, dest_path)
        else:
            print(f"Error: {source_path} not found after make.")
            sys.exit(1)

setup(
    name="runet_pkg",
    version="0.1.0",
    packages=["runet_pkg"],
    cmdclass={'build_ext': MakeBuild},
    ext_modules=[Extension("runet_pkg.librunet", sources=[])],
    install_requires=["numpy", "tensorflow"],
)
