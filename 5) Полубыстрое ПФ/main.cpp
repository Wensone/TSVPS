#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//const int n = 50;
int kaef_one = 10, kaef_two = 5;
int count_1 = 0, count_2 = 0;

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
    a1 = new complex *[kaef_two * kaef_one];
    for (int i = 0; i < kaef_two * kaef_one; i++) {
        a1[i] = new complex [kaef_two * kaef_one];
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
    double array[kaef_two * kaef_one];
    complex res[kaef_two * kaef_one], back_res[kaef_two * kaef_one];

    srand(time(NULL));
    printf("Source array: ");
    for (int i = 0; i < kaef_two * kaef_one; i++) {
        array[i] = i;
        printf("%lf ", array[i]);
    }
    
    array[0] = 0;
    array[1] = 1;
    array[2] = 0;
    array[3] = 1;
    array[4] = 0;
    array[5] = 0;
    array[6] = 1;
    array[7] = 0;
    array[8] = 1;
    array[9] = 0;
    
    for (int i = 0; i < kaef_two * kaef_one; i++) 
        printf("%lf ", array[i]);
    
    half_quick_transform(array, res);
    printf("\n\nRe half quick: ");
    for (int i = 0; i < kaef_two * kaef_one; i++)
        printf("%lf ", res[i].real);
    printf("\nIm half quick: ");
    for (int i = 0; i < kaef_two * kaef_one; i++)
        printf("%lf ", res[i].image);
    
    back_half_quick_transform(res, back_res);
    printf("\n\nRe back half quick: ");
    for (int i = 0; i < kaef_two * kaef_one; i++)
        printf("%lf ", back_res[i].real);
    printf("\nIm back half quick: ");
    for (int i = 0; i < kaef_two * kaef_one; i++)
        printf("%lf ", back_res[i].image);


    printf("\n\nOperations: %d\n\n", count_1 + count_2);
    
    return 0;
}
