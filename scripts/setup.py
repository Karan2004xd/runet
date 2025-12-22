import os
import subprocess

def run_command(command, description):
    print(f"--- {description} ---")
    try:
        process = subprocess.Popen(command,
                                   stdout=subprocess.PIPE,
                                   stderr=subprocess.PIPE,
                                   shell=True)
        _, stderr = process.communicate()

        if process.returncode == 0:
            print("Success")
        else:
            print(f"Error: {stderr.decode()}")

    except Exception as e:
        print(f"Failed to run command: {e}")

def setup():
    """
    Runs the setup for building the C library.
    """
    success = True 

    if os.path.exists('Makefile'):
        run_command("make clean && make test && ./test", "Compiling Runet C Engine")
        run_command("make clean && make librunet.so", "Compiling Runet C Engine")
    else:
        print("Warning: MakeFile not found. Ensure librunet.so is already built.")
        success = False

    if success:
        os.makedirs('libs', exist_ok=True)
        print("\nProject setup complete. RunetEngine is ready to use")
    else:
        print("\nProject setup failed. Please follow the instructions.")

if __name__ == "__main__":
    setup()
