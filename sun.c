#include <stdio.h>
#include <math.h>

// Define tolerância para cálculo de limites
#define TOLERANCE 1e-5

// Função exemplo para cálculo de derivada: f(x) = x^3
double func(double x) {
    return x * x * x;
}

// Função para cálculo do limite usando aproximação incremental
double limit(double (*f)(double), double x0) {
    double h = 1e-5;
    return (f(x0 + h) - f(x0 - h)) / (2 * h);
}

// Função para cálculo da derivada usando definição de limite
double derivative(double (*f)(double), double x) {
    double h = 1e-5;
    return (f(x + h) - f(x)) / h;
}

// Função para cálculo da integral definida usando método dos trapézios
double integral(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    return h * sum;
}

// Função para encontrar raízes de uma função usando método de Newton-Raphson
double newton_raphson(double (*f)(double), double x0) {
    double h = f(x0) / derivative(f, x0);
    while (fabs(h) >= TOLERANCE) {
        h = f(x0) / derivative(f, x0);
        x0 = x0 - h;
    }
    return x0;
}

// Função principal
int main() {
    double x0 = 2.0;
    double a = 0.0, b = 3.0;
    int n = 1000;
    
    printf("Cálculo de Limites:\n");
    printf("Limite de f(x) quando x tende a %f: %f\n", x0, limit(func, x0));
    
    printf("\nCálculo de Derivadas:\n");
    printf("Derivada de f(x) em x = %f: %f\n", x0, derivative(func, x0));
    
    printf("\nCálculo de Integrais:\n");
    printf("Integral definida de f(x) de %f a %f: %f\n", a, b, integral(func, a, b, n));
    
    printf("\nMétodo de Newton-Raphson:\n");
    printf("Raiz de f(x) próximo a %f: %f\n", x0, newton_raphson(func, x0));

    return 0;
}
