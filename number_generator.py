import sys
import numpy as np

def save_results(numbers):
    with open('numbers.txt','w') as log:
        for n in numbers:
            log.write(str(n)+'\n')

if __name__ == "__main__":
    low = int(sys.argv[1])
    high = int(sys.argv[2])
    amount = int(sys.argv[3])
    numbers = [np.random.randint(low,high) for _ in range(amount)]
    save_results(numbers)