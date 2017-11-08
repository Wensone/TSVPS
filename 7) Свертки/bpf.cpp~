#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <complex>
#include <bitset>
#include <stack>
#include <iostream>

using namespace std;
int count = 0, count_dp = 0, count_pb_1 = 0, count_pb_2 = 0, count_pb_3 = 0, count_b_1 = 0, count_b_2 = 0;
int size;
const int r = 4;
int p_1, p_2;

void direct_transform_fourier(vector <int> array, complex <double> *result) {
    complex <double> sum(0, 0);
    double coef_real, coef_image;
    for (int k = 0; k < array.size(); k++) {
        for (int j = 0; j < array.size(); j++) {
            count_dp += 5;
            coef_real = cos((-2 * M_PI * k * j) / array.size()) * array[j];
            coef_image = sin((-2 * M_PI * k * j) / array.size()) * array[j];
            complex <double> A(coef_real, coef_image);
            sum += A;
        }
        sum /= array.size();
        result[k] = sum;
        sum = 0;
    }
}

void back_transform_fourier(complex <double> *array, int size, complex <double> *result) {
    complex <double> sum, res_mul;
    double coef_real, coef_image;
    for (int k = 0; k < size; k++) {
        for (int j = 0; j < size; j++) {
            count_dp += 5;
            coef_real = cos((2 * M_PI * k * j) / size);
            coef_image = sin((2 * M_PI * k * j) / size);
            complex <double> A(coef_real, coef_image);
            res_mul = A * array[j];
            sum += res_mul;
        }
        result[k] = sum;
        sum = 0;
    }
}

complex <double> first_transform(vector <int> array, int k_1, int j_2) {
    double coef, coef_real, coef_image;
    complex <double> sum;
    for (int j_1 = 0; j_1 < p_1; j_1++) {
        count_pb_1 += 4;
        coef = (double) (j_1 * k_1) / p_1;
        coef_real = cos(-2 * M_PI * coef) * array[j_2 + p_2 * j_1];
        coef_image = sin(-2 * M_PI * coef) * array[j_2 + p_2 * j_1];
        complex <double> temp(coef_real, coef_image);
        sum += temp;
    }
    sum /= p_1;
    return sum;
}

complex <double> second_transform(complex <double> **array, int k_1, int k_2) {
    int k;
    double coef, coef_real, coef_image;
    complex <double> sum, res_mul;
    for (int j_2 = 0; j_2 < p_2; j_2++) {
        count_pb_2 += 7;
        k = k_1 + p_1 * k_2;
        coef = (double) (j_2 * k) / (p_1 * p_2);
        coef_real = cos(-2 * M_PI * coef);
        coef_image = sin(-2 * M_PI * coef);
        complex <double> temp(coef_real, coef_image);
        res_mul = array[k_1][j_2] * temp;
        sum += res_mul;
    }
    sum /= p_2;
    return sum;
}

complex <double> back_first_transform(complex <double> *array, int k_1, int j_2) {
    double coef, coef_real, coef_image;
    complex <double> sum, res_mul;
    for (int j_1 = 0; j_1 < p_1; j_1++) {
        count_pb_1 += 4;
        coef = (double) (j_1 * k_1) / p_1;
        coef_real = cos(2 * M_PI * coef);
        coef_image = sin(2 * M_PI * coef);
        complex <double> temp(coef_real, coef_image);
        res_mul = temp * array[j_2 + p_2 * j_1];
        sum += res_mul;
    }
    return sum;
}

complex <double> back_second_transform(complex <double> *array, int k_1, int k_2) {
    int k;
    double coef, coef_real, coef_image;
    complex <double> sum, res_mul, a_1;
    for (int j_2 = 0; j_2 < p_2; j_2++) {
        count_pb_2 += 7;
        a_1 = back_first_transform(array, k_1, j_2);
        k = k_1 + p_1 * k_2;
        coef = (double) (j_2 * k) / (p_1 * p_2);
        coef_real = cos(2 * M_PI * coef);
        coef_image = sin(2 * M_PI * coef);
        complex <double> temp(coef_real, coef_image);
        res_mul = a_1 * temp;
        sum += res_mul;
    }
    return sum;
}

void half_quick_transform(vector <int> source, complex <double> *result) {
    int i = 0;
    complex <double> **a1;
    a1 = new complex <double> *[size];
    for (int i = 0; i < size; i++) {
        a1[i] = new complex <double> [size];
    }
    for (int j_2 = 0; j_2 < p_2; j_2++) {
        for (int k_1 = 0; k_1 < p_1; k_1++) {
            a1[k_1][j_2] = first_transform(source, k_1, j_2);
        }
    }
    for (int k_2 = 0; k_2 < p_2; k_2++) {
        for (int k_1 = 0; k_1 < p_1; k_1++) {
            result[i] = second_transform(a1, k_1, k_2);
            i++;
        }
    }
}

void back_half_quick_transform(complex <double> *source, complex <double> *result) {
    int i = 0;
    for (int k_2 = 0; k_2 < p_2; k_2++) {
        for (int k_1 = 0; k_1 < p_1; k_1++) {
            result[i] = back_second_transform(source, k_1, k_2);
            i++;
        }
    }
}

void normal_svertka(vector <int> a, vector <int> b, vector <int> &result) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            result[i + j] += a[i] * b[j];
            count += 2;
        }
    }
}

void svertka_DPF(vector <int> a, vector <int> b, complex <double> *result) {
    size_t size = a.size();
    complex <double> res[size];
    complex <double> a_dpf[size];
    complex <double> b_dpf[size];
    direct_transform_fourier(a, a_dpf);
    direct_transform_fourier(b, b_dpf);
    for (int i = 0; i < size; i++) {
        res[i] = a_dpf[i] * b_dpf[i];
        res[i] *= size;
        count_dp += 2;
    }
    back_transform_fourier(res, size, result);
}

void svertka_PBPF(vector <int> a, vector <int> b, complex <double> *result) {
    size_t size = a.size();
    for (int i = size - 1; i > 1; i--) {
        if (size % i == 0) {
            p_1 = i;
            p_2 = size / p_1;
            break;
        }
    }
    complex <double> res[size];
    complex <double> a_pbpf[size];
    complex <double> b_pbpf[size];
    half_quick_transform(a, a_pbpf);
    half_quick_transform(b, b_pbpf);
    for (int i = 0; i < size; i++) {
        res[i] = a_pbpf[i] * b_pbpf[i];
        res[i] *= size;
        count_pb_3 += 2;
    }
    back_half_quick_transform(res, result);
}

void create_A_0(complex <double> *array, complex <double> *result) {
    int index = 0;
    unsigned long long sum = 0;
    bitset <r> set_bits;
    for (int loop = 0; loop < 2 * size; loop++) {
        for (size_t i = 0, j = r - 1; i < r; i++) {
            index += pow(2, i) * set_bits.test(j--);
        }
        result[loop] = array[index];
        index = 0;
        sum = set_bits.to_ulong();
        sum++;
        set_bits = sum;
    }
}

void FFT(complex <double> *array, complex <double> *a_0) {
    create_A_0(array, a_0);
    complex <double> rotate_multiplier = exp(complex <double> (0, (-2 * M_PI) / (2 * size)));
    stack < complex <double> > W;
    int step = 0;
    for (step = 2 * size; step != 1; step /= 2) {
        W.push(rotate_multiplier);
        rotate_multiplier *= rotate_multiplier;
    }
    for (step = 2; step <= 2 * size; step *= 2) {
        rotate_multiplier = W.top();
        W.pop();
        for (int i = 0; i < 2 * size; i += step) {
            complex <double> w(1, 0);
            for (int k = 0; k < step / 2; k++) {
                complex <double> temp = a_0[k + i];
                a_0[k + i] = temp + a_0[k + i + step / 2] * w;
                a_0[k + i + step / 2] = temp - a_0[k + i + step / 2] * w;
                w *= rotate_multiplier;
                count_b_1 += 5;
            }
        }
    }
    for (int i = 0; i < 2 * size; i++) {
        a_0[i] /= 2 * size;
        count++;
    }
}

void back_FFT(complex <double> *array) {
    complex <double> *result = new complex <double> [2 * size];
    for (int i = 0; i < 2 * size; i++) {
        array[i] = conj(array[i]);
    }
    FFT(array, result);
    for (int i = 0; i < 2 * size; i++) {
        array[i] = conj(result[i]);
        array[i] *= 2 * size;
    }
}

void svertka_BPF(complex <double> *a, complex <double> *b, complex <double> *result) {
    complex <double> *a_bpf = new complex <double> [2 * size];
    complex <double> *b_bpf = new complex <double> [2 * size];
    FFT(a, a_bpf);
    FFT(b, b_bpf);
    for (int i = 0; i < 2 * size; i++) {
        result[i] = a_bpf[i] * b_bpf[i];
        result[i] *= 2 * size;
        count_b_2 += 2;
    }
    back_FFT(result);
}

int main() {
    srand(time(NULL));
    printf("1) Normal svertka\n2) Svertka DPF\n3) Svertka PBDF\n4) Svertka BPF\n\n");
    char ch = getchar();
    switch (ch) {
        case '1': {
            system("cls");
            int size_1, size_2;
            printf("Enter size of array A: ");
            scanf("%d", &size_1);
            printf("Enter size of array B: ");
            scanf("%d", &size_2);
            vector <int> a(size_1);
            vector <int> b(size_2);
            vector <int> c(size_1 + size_2 - 1);
            printf("\n\nMassiv A: ");
            for (int i = 0; i < size_1; i++) {
                a[i] = i + 1;
                printf("%d ", a[i]);
            }
            printf("\nMassiv B: ");
            for (int i = 0; i < size_2; i++) {
                b[i] = i + 1;
                printf("%d ", b[i]);
            }
            printf("\n\nResult: ");
            normal_svertka(a, b, c);
            for (int i = 0; i < size_1 + size_2 - 1; i++) printf("%d ", c[i]);
            printf("\n\n");
            printf("Operations: %d\n\n", count);
            system("pause");
            exit(1);
        }
        case '2': {
            system("cls");
            printf("Enter size of arrays: ");
            scanf("%d", &size);
            vector <int> arr_1(2 * size);
            vector <int> arr_2(2 * size);
            complex <double> result[2 * size - 1];
            printf("\n\nMassiv A: ");
            for (int i = 0; i < size; i++) {
                arr_1[i] = i + 1;
                printf("%d ", arr_1[i]);
            }
            printf("\nMassiv B: ");
            for (int i = 0; i < size; i++) {
                arr_2[i] = i + 1;
                printf("%d ", arr_2[i]);
            }
            svertka_DPF(arr_1, arr_2, result);
            printf("\n\nReal part: ");
            for (int i = 0; i < 2 * size - 1; i++) {
                printf("%lf ", result[i].real());
            }
            /*printf("\nImage part: ");
            for (int i = 0; i < 2 * size - 1; i++) {
                printf("%lf ", result[i].imag());
            }*/
            printf("\n\n");
            printf("Operations: %d\n\n", count_dp);
            system("pause");
            exit(1);
        }
        case '3': {
            system("cls");
            printf("Enter size of arrays: ");
            scanf("%d", &size);
            vector <int> arr_1(2 * size);
            vector <int> arr_2(2 * size);
            complex <double> result[2 * size - 1];
            printf("\n\nMassiv A: ");
            for (int i = 0; i < size; i++) {
                arr_1[i] = i + 1;
                printf("%d ", arr_1[i]);
            }
            printf("\nMassiv B: ");
            for (int i = 0; i < size; i++) {
                arr_2[i] = i + 1;
                printf("%d ", arr_2[i]);
            }
            svertka_PBPF(arr_1, arr_2, result);
            printf("\n\nReal part: ");
            for (int i = 0; i < 2 * size - 1; i++) {
                printf("%lf ", result[i].real());
            }
            /*printf("\nImage part: ");
            for (int i = 0; i < 2 * size - 1; i++) {
                printf("%lf ", result[i].imag());
            }*/
            printf("\n\n");
            printf("Operations: %d\n\n", count_pb_1 + count_pb_2 + count_pb_3);
            system("pause");
            exit(1);
        }
        case '4': {
            system("cls");
            printf("Enter size of arrays: ");
            scanf("%d", &size);
            complex <double> arr_1[2 * size];
            complex <double> arr_2[2 * size];
            complex <double> result[2 * size - 1];
            printf("\n\nMassiv A: ");
            for (int i = 0; i < size; i++) {
                arr_1[i] = i + 1;
                cout << fixed << arr_1[i];
            }
            printf("\nMassiv B: ");
            for (int i = 0; i < size; i++) {
                arr_2[i] = i + 1;
                cout << fixed << arr_2[i];
            }
            svertka_BPF(arr_1, arr_2, result);
            printf("\n\nReal part: ");
            for (int i = 0; i < 2 * size - 1; i++) {
                printf("%lf ", result[i].real());
            }
            /*printf("\nImage part: ");
            for (int i = 0; i < 2 * size - 1; i++) {
                printf("%lf ", result[i].imag());
            }*/
            printf("\n\n");
            printf("Operations: %d\n\n", count_b_1 + count_b_2);
            system("pause");
            exit(1);
        }
    }

}
