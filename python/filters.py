def moving_average(signal, window_size):
    if window_size <= 0:
        raise ValueError("window_size must be positive")

    if window_size > len(signal):
        raise ValueError("window_size cannot be larger than signal length")

    result = []

    for i in range(len(signal) - window_size + 1):
        total = 0

        for j in range(window_size):
            total += signal[i + j]

        result.append(total / window_size)

    return result

def convolve(signal, kernel):
    result = []

    for i in range(len(signal) - len(kernel) + 1):
        total = 0

        for j in range(len(kernel)):
            total += signal[i + j] * kernel[j]

        result.append(total)

    return result
