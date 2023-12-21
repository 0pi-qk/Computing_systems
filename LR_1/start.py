import os
import subprocess


if __name__ == '__main__':
    os.chdir(os.path.dirname(__file__))

    subprocess.call(["cmake", "-S", "./", "-B", "./build"])
    subprocess.call(["cmake", "--build", "./build"])

    print("\nExchange matrix size: ")
    for size in (5, 10, 50, 100, 500, 1000, 2000, 3000, 4000, 5000):
        subprocess.call(['./build/LR_1', str(size), '4'])
        print("\n==========")
    print("\nExchange threads num:")
    for thread in (1, 2, 4, 8, 16, 32, 64, 128):
        subprocess.call(['./build/LR_1', '4000', str(thread)])
        print("\n==========")

