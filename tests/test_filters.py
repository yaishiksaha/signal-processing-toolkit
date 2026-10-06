from python.filters import moving_average
from python.filters import moving_average, convolve
import numpy as np

def test_moving_average():
    signal = [1, 2, 3, 4, 5]

    result = moving_average(signal, 3)

    expected = [2.0, 3.0, 4.0]

    assert result == expected

def test_window_size_one():
    signal = [1, 2, 3]

    assert moving_average(signal, 1) == [1.0, 2.0, 3.0]


def test_window_size_equal_signal():
    signal = [1, 2, 3, 4]

    assert moving_average(signal, 4) == [2.5]


def test_invalid_window():
    signal = [1, 2, 3]

    try:
        moving_average(signal, 0)
        assert False
    except ValueError:
        assert True


def test_convolution():
    signal = [1, 2, 3, 4, 5]
    kernel = [1, 1, 1]

    result = convolve(signal, kernel)

    assert result == [6, 9, 12]


def test_moving_average_is_convolution():
    signal = [1, 2, 3, 4, 5, 6]

    moving_average_result = moving_average(signal, 3)

    kernel = [1 / 3, 1 / 3, 1 / 3]

    convolution_result = convolve(signal, kernel)

    assert np.allclose(moving_average_result, convolution_result)