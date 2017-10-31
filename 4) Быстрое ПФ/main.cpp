#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <bitset>
#include <stack>

using namespace std;
const int n = 16, r = 4;
int count = 0;

void create_A_0(complex <double> *array, complex <double> *result) {
    int index = 0;
    unsigned long long sum = 0;
    bitset <r> set_bits;
    for (int loop = 0; loop < n; loop++) {
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
    complex <double> rotate_multiplier = exp(complex <double> (0, (-2 * M_PI) / n));
    stack < complex <double> > W;
    int step = 0;
    for (step = n; step != 1; step /= 2) {
        W.push(rotate_multiplier);
        rotate_multiplier *= rotate_multiplier;
    }
    for (step = 2; step <= n; step *= 2) {
        rotate_multiplier = W.top();
        W.pop();
        for (int i = 0; i < n; i += step) {
            complex <double> w(1, 0);
            for (int k = 0; k < step / 2; k++) {
                complex <double> temp = a_0[k + i];
                a_0[k + i] = temp + a_0[k + i + step / 2] * w;
                a_0[k + i + step / 2] = temp - a_0[k + i + step / 2] * w;
                w *= rotate_multiplier;
                count += 5;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        a_0[i] /= n;
        count++;
    }
}

void back_FFT(complex <double> *array) {
    complex <double> *result = new complex <double> [n];
    for (int i = 0; i < n; i++) {
        array[i] = conj(array[i]);
    }
    FFT(array, result);
    for (int i = 0; i < n; i++) {
        array[i] = conj(result[i]);
        array[i] *= n;
    }
}

int main() {
    complex <double> source[n];
    complex <double> *result = new complex <double> [n];
    printf("Source massive: ");
    /*for (int i = 0; i < n; i++) {
        source[i] = i;
        printf("%lf ", source[i].real());
    }*/
    source[0] = 0;
    source[1] = 1;
    source[2] = 0;
    source[3] = 1;
    source[4] = 0;
    source[5] = 0;
    source[6] = 1;
    source[7] = 0;
    source[8] = 0;
    source[9] = 1;
    source[10] = 0;
    source[11] = 1;
    source[12] = 0;
    source[13] = 0;
    source[14] = 1;
    source[15] = 0;
    printf("\n\n");
    FFT(source, result);
    printf("Real part: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", result[i].real());
    }
    printf("\nImage part: ");
    /*for (int i = 0; i < n; i++) {
        printf("%lf ", result[i].imag());
    }*/
    printf("\n\n");
    printf("Tridoemkost': %d\n\n", count);
    back_FFT(result);
    printf("Real part: ");
    /*for (int i = 0; i < n; i++) {
        printf("%lf ", result[i].real());
    }
    printf("\nImage part: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", result[i].imag());
    }*/
    printf("\n\n");
    system("pause");
}
