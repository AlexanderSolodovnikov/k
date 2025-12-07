#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <locale.h>

// === Кусочная функция f(x) ===
long double f(long double x)
{
    if (x < 1)
        return expl(-fabsl(x)) / atanl(1 + x * x);
    else if (x < 6)
        return (x * x * cosl(3 * x) * tanhl(x)) / sqrtl(1 + powl(x, 6));
    else {
        long double s = 0;
        for (int n = 0; n <= 4; n++)
        {
            long double ch = powl(-1, n) * powl(x, 2 * n + 1);
            long double zn = 1;
            for (int k = 1; k <= 2 * n + 1; k += 2) zn *= k; // двойной факториал
            zn *= (n + 3);
            s += ch / zn;
        }
        return s;
    }
}

// === Численная производная f'(x) ===
long double df(long double x)
{
    long double h = 1e-5;
    return (f(x + h) - f(x - h)) / (2 * h);
}

// === Главная программа ===
int main()
{
    setlocale(LC_ALL, "Russian");

    int menu;
    long double x, a, b, y, step;

    printf("=== Работа с функцией f(x) ===\n");

    while (1)
    {
        printf("\nМеню:\n");
        printf("1 - f(x) в точке\n");
        printf("2 - Таблица значений\n");
        printf("3 - Минимум и максимум\n");
        printf("4 - Найти x при f(x) ≈ Y\n");
        printf("5 - Производная f'(x)\n");
        printf("6 - Выход\n");
        printf("Выбор: ");
        if (scanf("%d", &menu) != 1) break;

        if (menu == 6) break;

        if (menu == 1)
        {
            printf("Введите x: ");
            scanf("%Lf", &x);
            printf("f(%.5Lf) = %.10Lf\n", x, f(x));
        }

        else if (menu == 2)
        {
            printf("Введите a, b, шаг: ");
            scanf("%Lf %Lf %Lf", &a, &b, &step);
            for (x = a; x <= b + 1e-9; x += step)
                printf("x = %8.4Lf   f(x) = %12.8Lf\n", x, f(x));
        }

        else if (menu == 3)
        {
            printf("Введите a, b: ");
            scanf("%Lf %Lf", &a, &b);
            long double min_x = a, max_x = a;
            long double min_y = f(a), max_y = f(a);
            for (x = a; x <= b; x += 0.001)
            {
                long double yx = f(x);
                if (yx < min_y) { min_y = yx; min_x = x; }
                if (yx > max_y) { max_y = yx; max_x = x; }
            }
            printf("Минимум: f(%.5Lf) = %.10Lf\n", min_x, min_y);
            printf("Максимум: f(%.5Lf) = %.10Lf\n", max_x, max_y);
        }

        else if (menu == 4)
        {
            printf("Введите Y, a, b: ");
            scanf("%Lf %Lf %Lf", &y, &a, &b);
            long double best_x = a;
            long double min_diff = fabsl(f(a) - y);
            for (x = a; x <= b; x += 0.001)
            {
                long double diff = fabsl(f(x) - y);
                if (diff < min_diff) { min_diff = diff; best_x = x; }
            }
            printf("Приблизительно: x = %.6Lf, f(x) = %.10Lf\n", best_x, f(best_x));
        }

        else if (menu == 5)
        {
            printf("Введите x: ");
            scanf("%Lf", &x);
            printf("f'(%.5Lf) = %.10Lf\n", x, df(x));
        }

        else
            printf("Неверный пункт меню.\n");
    }

    printf("Программа завершена.\n");
    return 0;
}
