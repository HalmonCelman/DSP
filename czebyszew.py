import numpy as np
import matplotlib.pyplot as plt

class ChebyshevType1LowPassFilter:
    def __init__(self):
        # Współczynniki licznika (b) i mianownika (a)
        self.b = [0.0619, 0.1239, 0.0619]
        self.a = [1.0000, -1.2654, 0.6153]
        
        # Bufor dla poprzednich próbek wejściowych i wyjściowych
        self.x_prev = [0.0, 0.0]  # x[n-1], x[n-2]
        self.y_prev = [0.0, 0.0]  # y[n-1], y[n-2]
    
    def process_sample(self, x):
        # Obliczanie aktualnej próbki wyjściowej
        y = (self.b[0] * x + 
             self.b[1] * self.x_prev[0] + 
             self.b[2] * self.x_prev[1] - 
             self.a[1] * self.y_prev[0] - 
             self.a[2] * self.y_prev[1]) / self.a[0]
        
        # Aktualizacja bufora
        self.x_prev[1] = self.x_prev[0]
        self.x_prev[0] = x
        
        self.y_prev[1] = self.y_prev[0]
        self.y_prev[0] = y
        
        return y
    
    def process_signal(self, signal):
        """Przetwarza cały sygnał wejściowy"""
        return np.array([self.process_sample(x) for x in signal])

# Przykład użycia:
if __name__ == "__main__":
    # Tworzenie filtra
    cheby_filter = ChebyshevType1LowPassFilter()
    
    # Przykładowy sygnał wejściowy (np. szum)
    input_signal = np.random.randn(100)
    plt.plot(input_signal)
    # Filtrowanie sygnału
    output_signal = cheby_filter.process_signal(input_signal)
    plt.plot(output_signal)
    print("Przetworzony sygnał:", output_signal)
    plt.show()