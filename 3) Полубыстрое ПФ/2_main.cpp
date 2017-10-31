#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int kaef_one = 10, kaef_two = 5;


struct complex {
    double real;
    double image;
};

complex multiple_complex(complex a, complex b) {
    complex result;
    result.real = 0, result.image = 0;
    result.real = a.real * b.real - a.image * b.image;
    result.image = a.real * b.image + a.image * b.real;
    return result;
}

int count = 0;
int count_1 = 0, count_2 = 0;
const int n = kaef_one * kaef_two;

void direct_transform_fourier(double *array, complex *result) {
    complex A, sum;
    sum.real = 0, sum.image = 0;
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
        	count += 5;
            A.real = cos((-2 * M_PI * k * j) / n) * array[j];
            A.image = sin((-2 * M_PI * k * j) / n) * array[j];
            sum.real += A.real;
            sum.image += A.image;
        }
        sum.real /= n;
        sum.image /= n;
        result[k].real = sum.real;
        result[k].image = sum.image;
        sum.real = 0, sum.image = 0;
    }
}

void back_transform_fourier(complex *direct_fourier, complex *result) {
    complex A, sum, res_mul;
    sum.real = 0, sum.image = 0;
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            A.real = cos((2 * M_PI * k * j) / n);
            A.image = sin((2 * M_PI * k * j) / n);
            res_mul = multiple_complex(A, direct_fourier[j]);
            sum.real += res_mul.real;
            sum.image += res_mul.image;
        }
        result[k].real = sum.real;
        result[k].image = sum.image;
        if (result[k].image < 10e-10) result[k].image = 0;
        sum.real = 0, sum.image = 0;
    }
}

complex first_transform(double *array, int k_1, int j_2) {
    double coef;
    complex sum, temp;
    sum.real = 0, sum.image = 0;
    for (int j_1 = 0; j_1 < kaef_one; j_1++) {
        count_1 += 5;
        coef = (double) (j_1 * k_1) / kaef_one;
        temp.real = cos(-2 * M_PI * coef) * array[j_2 + kaef_two * j_1];
        temp.image = sin(-2 * M_PI * coef) * array[j_2 + kaef_two * j_1];
        sum.real += temp.real;
        sum.image += temp.image;
    }
    sum.real /= kaef_one;
    sum.image /= kaef_one;
    return sum;
}

complex second_transform(complex **array, int k_1, int k_2) {
    int k;
    double coef;
    complex sum, temp, res_mul;
    sum.real = 0, sum.image = 0;
    for (int j_2 = 0; j_2 < kaef_two; j_2++) {
        count_2 += 7;
        k = k_1 + kaef_one * k_2;
        coef = (double) (j_2 * k) / (kaef_one * kaef_two);
        temp.real = cos(-2 * M_PI * coef);
        temp.image = sin(-2 * M_PI * coef);
        res_mul = multiple_complex(array[k_1][j_2], temp);
        sum.real += res_mul.real;
        sum.image += res_mul.image;
    }
    sum.real /= kaef_two;
    sum.image /= kaef_two;
    return sum;
}

complex back_first_transform(complex *array, int k_1, int j_2) {
    double coef;
    complex sum, temp, res_mul;
    sum.real = 0, sum.image = 0;
    for (int j_1 = 0; j_1 < kaef_one; j_1++) {
        coef = (double) (j_1 * k_1) / kaef_one;
        temp.real = cos(2 * M_PI * coef);
        temp.image = sin(2 * M_PI * coef);
        res_mul = multiple_complex(temp, array[j_2 + kaef_two * j_1]);
        sum.real += res_mul.real;
        sum.image += res_mul.image;
    }
    return sum;
}

complex back_second_transform(complex *array, int k_1, int k_2) {
    int k;
    double coef;
    complex sum, temp, res_mul, a_1;
    sum.real = 0, sum.image = 0;
    for (int j_2 = 0; j_2 < kaef_two; j_2++) {
        a_1 = back_first_transform(array, k_1, j_2);
        k = k_1 + kaef_one * k_2;
        coef = (double) (j_2 * k) / (kaef_one * kaef_two);
        temp.real = cos(2 * M_PI * coef);
        temp.image = sin(2 * M_PI * coef);
        res_mul = multiple_complex(a_1, temp);
        sum.real += res_mul.real;
        sum.image += res_mul.image;
    }
    return sum;
}

void half_quick_transform(double *source, complex *result) {
    int i = 0;
    complex **a1;
    a1 = new complex *[n];
    for (int i = 0; i < n; i++) {
        a1[i] = new complex [n];
    }
    for (int j_2 = 0; j_2 < kaef_two; j_2++) {
        for (int k_1 = 0; k_1 < kaef_one; k_1++) {
            a1[k_1][j_2].real = 0;
            a1[k_1][j_2].image = 0;
            a1[k_1][j_2] = first_transform(source, k_1, j_2);
        }
    }
    for (int k_2 = 0; k_2 < kaef_two; k_2++) {
        for (int k_1 = 0; k_1 < kaef_one; k_1++) {
            result[i] = second_transform(a1, k_1, k_2);
            i++;
        }
    }
}

void back_half_quick_transform(complex *source, complex *result) {
    int i = 0;
    for (int k_2 = 0; k_2 < kaef_two; k_2++) {
        for (int k_1 = 0; k_1 < kaef_one; k_1++) {
            result[i] = back_second_transform(source, k_1, k_2);
            i++;
        }
    }
}

int main() {
    double array[n];
    complex res[n], source[n],
    		res1[n], back[n];
    srand(time(NULL));
    printf("\t\tИсходный: ");
    for (int i = 0; i < n; i++) {
        array[i] = i;
        printf("%lf ", array[i]);
    }

    array[0] = 0;
    array[1] = 1;
    array[2] = 0;
    array[3] = 1;
    array[4] = 0;
    array[5] = 1;
    array[6] = 0;
    array[7] = 1;
    array[8] = 0;
    array[9] = 1;
/*
    for (int i = 0; i < n; i++) {
        printf("%lf ", array[i]);
    }
    printf("\n\n");*/

    // Discrete is on
    direct_transform_fourier(array, res);
    printf("\t\tR Дискретное: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", res[i].real);
    }
    printf("\n");
    printf("\t\tI Дискретное: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", res[i].image);
    }
    printf("\n\n");
    back_transform_fourier(res, source);
    printf("\t\tR Дискретное исходный: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", source[i].real);
    }
    printf("\n");
    printf("\t\tI Дискретное исходный: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", source[i].image);
    }
    printf("\n\n");
    // Discrete is off


    // Half quick is on
    half_quick_transform(array, res1);
    printf("\t\tR Полубыстрое: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", res1[i].real);
    }
    printf("\n");
    printf("\t\tI Полубыстрое: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", res1[i].image);
    }
    printf("\n\n");
    back_half_quick_transform(res1, back);
    printf("\t\tR Полубыстрый исходный: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", back[i].real);
    }
    printf("\n");
    printf("\t\tI Полубыстрый исходный: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", back[i].image);
    }
    printf("\n\n");
    printf("\t\tКол-во операций при дискретном: %d\n\n", count);
    printf("\t\tКол-во операций при полубыстром: %d\n\n", count_1 + count_2);
    // Half quick is off

    return 0;
}