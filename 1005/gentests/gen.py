import numpy as np
import os

os.makedirs('../tests', exist_ok=True)

def generate_test_cases():
    for i in range(2, 15):
        with open(f'../tests/{(i + 1):02d}.in', 'w') as input_file:
            n = np.random.randint(2, 10)
            if n != 2 and np.random.randint(1, 2) == 2:
	            m = n - 2
            else:
                m = n + 2
            matrix_a = np.random.randint(-10, 11, size=(n, m))

            for row in matrix_a:
                input_file.write(" ".join(map(str, row)) + "\n")

def generate_expected_answers():
    for i in range(15):
        solution_path = os.path.abspath("../solution/1005.py")
        input_file = os.path.abspath(f"../tests/{(i+1):02d}.in")
        output_file = os.path.abspath(f"../tests/{(i+1):02d}.out")

        os.system(f"python3 {solution_path} < {input_file} > {output_file}")



generate_test_cases()
generate_expected_answers()

