#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Define tolerância para cálculo de limites
#define TOLERANCE 1e-5
#define PI 3.141592653589793

// Função exemplo para cálculo: f(x) = x^3
double func(double x) {
    return x * x * x;
}

// Função para calcular limite usando aproximação incremental
double limit(double (*f)(double), double x0) {
    double h = 1e-5;
    return (f(x0 + h) - f(x0 - h)) / (2 * h);
}

// Função para calcular derivada usando definição de limite
double derivative(double (*f)(double), double x) {
    double h = 1e-5;
    return (f(x + h) - f(x)) / h;
}

// Função para calcular integral definida usando método dos trapézios
double integral(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    return h * sum;
}

// Função para calcular integrais duplas
double double_integral(double (*f)(double, double), double a, double b, double c, double d, int n) {
    double hx = (b - a) / n;
    double hy = (d - c) / n;
    double sum = 0.0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            double x = a + i * hx;
            double y = c + j * hy;
            sum += f(x, y);
        }
    }
    return hx * hy * sum;
}

// Função para calcular coeficientes de Fourier
void fourier_series(double (*f)(double), int n, double a[], double b[]) {
    for (int k = 0; k < n; k++) {
        double ak = 0.0;
        double bk = 0.0;
        for (int j = 0; j < 1000; j++) {
            double x = (double)j / 1000.0 * 2.0 * PI;
            ak += f(x) * cos(k * x);
            bk += f(x) * sin(k * x);
        }
        a[k] = ak / 1000.0;
        b[k] = bk / 1000.0;
    }
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

// Exemplo de função de duas variáveis para integral dupla
double func2(double x, double y) {
    return sin(x) * cos(y);
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

    printf("\nIntegral Dupla:\n");
    printf("Integral dupla de sin(x)*cos(y) no intervalo [0, PI] x [0, PI]: %f\n", double_integral(func2, 0.0, PI, 0.0, PI, n));

    printf("\nCoeficientes de Fourier:\n");
    double ak[10], bk[10];
    fourier_series(func, 10, ak, bk);
    for (int i = 0; i < 10; i++) {
        printf("a[%d] = %f, b[%d] = %f\n", i, ak[i], i, bk[i]);
    }

    printf("\nMétodo de Newton-Raphson:\n");
    printf("Raiz de f(x) próximo a %f: %f\n", x0, newton_raphson(func, x0));

    return 0;
}
