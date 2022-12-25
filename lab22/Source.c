#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>

#define SCREENW 60
#define SCREENH 40

typedef double (*TFun)(double);

double y(double x);
double v(double x);
double s(double x);
void printTable(TFun fun, double leftBorder, double rightBorder, double step);
void plot(double x0, double x1, TFun f);
void researchFunc(TFun fun, double leftBorder, double rightBorder, double step);
double calculcate(TFun prtf, double* x, int n);

void main()
{
    setlocale(LC_ALL, "RUS");
    int ans = 0, funcId;
    char leftBorder, rightBorder;
    double leftNumber, rightNumber;
    double x, step;
    while (ans != 4) {
        puts("\n\nМеню\n\n1.Вычислить значение функции Y(x), V(x) или S(x);\n2.Табулировать функцию Y(x), V(x) или S(x);\n3.Выполнить операцию над функцией Y(x), V(x) или S(x);\n4.Выход;\n\nВведите цифру нужного пункта меню:");
        scanf("%d", &ans);
        switch (ans)
        {
        case 1:
            puts("\n\n\nВведите значение аргумента: ");
            scanf("%lf", &x);
            puts("Введите номер нужной функции(Y(x) - 1; V(x) - 2; S(x) - 3):");
            scanf("%d", &funcId);
            switch (funcId)
            {
            case 1:
                printf("Y(%lf) = %lf", x, y(x));
                break;
            case 2:
                printf("V(%lf) = %lf", x, v(x));
                break;
            case 3:
                printf("S(%lf) = %lf", x, s(x));
                break;
            default:
                puts("Введён некорректный номер функции!");
            }
            break;
        case 2:
            puts("Введите границы табулирования функции(Пример: [12,2;33)):");
            scanf("\n%c%lf;%lf%c", &leftBorder, &leftNumber, &rightNumber, &rightBorder);
            printf("\n%c%.2lf;%.2lf%c", leftBorder, leftNumber, rightNumber, rightBorder);
            if (leftNumber > rightNumber) {
                printf("\n\nЗначение левой границы интервала больше значения правой границы интервала!");
            }
            printf("\n\nВведите шаг для функции: ");
            scanf("%lf", &step);
            if (rightBorder == ')') {
                rightNumber -= step;
            }
            if (leftBorder == '(') {
                leftNumber += step;
            }
            puts("Введите номер нужной функции(Y(x) - 1; V(x) - 2; S(x) - 3):");
            scanf("%d", &funcId);
            switch (funcId)
            {
            case 1:
                printTable(y, leftNumber, rightNumber, step);
                break;
            case 2:
                printTable(v, leftNumber, rightNumber, step);
                break;
            case 3:
                printTable(s, leftNumber, rightNumber, step);
                break;
            default:
                puts("Введён некорректный номер функции!");
                break;
            }
            break;
        case 3:
            puts("Введите границы табулирования функции(Пример: [12,2;33)):");
            scanf("\n%c%lf;%lf%c", &leftBorder, &leftNumber, &rightNumber, &rightBorder);
            printf("\n%c%.2lf;%.2lf%c", leftBorder, leftNumber, rightNumber, rightBorder);
            if (leftNumber > rightNumber) {
                printf("\n\nЗначение левой границы интервала больше значения правой границы интервала!");
            }
            printf("\n\nВведите шаг для функции: ");
            scanf("%lf", &step);
            if (rightBorder == ')') {
                rightNumber -= step;
            }
            if (leftBorder == '(') {
                leftNumber += step;
            }
            puts("Введите номер нужной функции(Y(x) - 1; V(x) - 2; S(x) - 3):");
            scanf("%d", &funcId);
            switch (funcId)
            {
            case 1:
                researchFunc(y, leftNumber, rightNumber, step);
                break;
            case 2:
                researchFunc(v, leftNumber, rightNumber, step);
                break;
            case 3:
                researchFunc(s, leftNumber, rightNumber, step);
                break;
            default:
                puts("Введён некорректный номер функции!");
                break;
            }
            break;
        default:
            puts("Введено некорректное значение!");
            break;
        }
    }
}

double y(double x) {
    double res;
    if (x > 0) {
        res = log(fabs(sqrt(x * x * x)));
    }
    else {
        res = -100000;
    }
    return res;
}

double v(double x) {
    double res;
    if (x <= 22) {
        res = -1000000000000;
        return res;
    }
    if (x > 1) {
        res = sqrt(tan((x * x) - 1));
    }
    else if (x >= 0 && x <= 1) {
        res = -2 * x;
    }
    else {
        res = exp(cos(x));
    }
    return res;
}

double s(double x) {
    double res;
    if (x == -1) {
        res = -1000000;
        return res;
    }
    res = (x - 1) / (x + 1) + 1 / 3 * pow(((x - 1) / (x + 1)), 3) + 1 / 5 * pow(((x - 1) / (x + 1)), 5) + 1 / 7 * pow(((x - 1) / (x + 1)), 7);
    return res;
}

void researchFunc(TFun fun, double leftBorder, double rightBorder, double step) {
    int lenArray = 0;
    double* resultArray = (double*)malloc(((rightBorder - leftBorder) / step) * sizeof(double));
    double counter = leftBorder;
    int res1 = 0, res2 = 0;
    for (int i = 0; i <= (rightBorder - leftBorder) / step; i++)
    {
        resultArray[i] = fun(counter);
        counter += step;
        lenArray++;
    }
    for (int i = 1; i <= (rightBorder - leftBorder) / step; i++)
    {
        if (resultArray[i] > resultArray[i - 1]) {
            res1++;
        }
        if (resultArray[i] == resultArray[i - 1]) {
            res2++;
        }
    }
    if (res1 + 1 == lenArray) {
        printf("На этом промежутке функция возрастает");
    }
    else if (res2 + 1 == lenArray) {
        printf("На этом промежутке функция монотонна");
    }
    else {
        printf("На этом промежутке функция убывает");
    }
    printf("\n\n\n calculate = %lf", calculcate(fun, resultArray, (rightBorder - leftBorder) / step));
}

void printTable(TFun fun, double leftBorder, double rightBorder, double step) {
    for (double x = leftBorder; x < rightBorder; x += step) {
        printf("x = %5.21f, y = %8.41f\n", x, fun(x));
    }
    puts("\n\n\n");
    plot(leftBorder, rightBorder, fun);
}

void plot(double x0, double x1, TFun f)
{
    char screen[SCREENW][SCREENH];
    double x, y[SCREENW];
    double ymin = 0, ymax = 0;
    double hx, hy;
    int i, j;
    int xz, yz;
    hx = (x1 - x0) / (SCREENW - 1);
    for (i = 0, x = x0; i < SCREENW; ++i, x += hx) {
        y[i] = f(x);
        if (y[i] < ymin) ymin = y[i];
        if (y[i] > ymax) ymax = y[i];
    }

    hy = (ymax - ymin) / (SCREENH - 1);
    yz = (int)floor(ymax / hy + 0.5);
    xz = (int)floor((0. - x0) / hx + 0.5);
    for (j = 0; j < SCREENH; ++j)

        for (i = 0; i < SCREENW; ++i) {
            if (j == yz && i == xz) screen[i][j] = '+';
            else if (j == yz) screen[i][j] = '-';
            else if (i == xz) screen[i][j] = '|';
            else screen[i][j] = ' ';
        }
    for (i = 0; i < SCREENW; ++i) {
        j = (int)floor((ymax - y[i]) / hy + 0.5);
        screen[i][j] = '*';
    }
    for (j = 0; j < SCREENH; ++j) {
        for (i = 0; i < SCREENW; ++i)  putchar(screen[i][j]);
        putchar('\n');
    }
}

double calculcate(TFun fun, double* x, int n) {
    double* resultArray = (double*)malloc(n * sizeof(double));
    double ymin = 1000000, ymax = -10000000;
    int yminId = -1, ymaxId = -1;
    for (int i = 0; i < n; i++) {
        resultArray[i] = fun(x[i]);
    }
    for (int i = 0; i < n; i++) {
        if (resultArray[i] < ymin) {
            ymin = resultArray[i];
            yminId = i;
        }
        if (resultArray[i] > ymax) {
            ymax = resultArray[i];
            ymaxId = i;
        }
    }
    double res = (x[yminId] + x[ymaxId]) / 2;
    return res;
}