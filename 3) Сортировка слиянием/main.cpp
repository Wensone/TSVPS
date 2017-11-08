#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int n = 16;
int srav = 0, per = 0;

void merge_sort(int *array) {
    int *a, *b, *c, k = 0, j = 0, l = 0;
    c = new int [n];
    for (int i = 0; i < n; i += 2) {
        srav++;
        if (array[i + 1] < array[i]) {
            per += 3;
            int temp = array[i + 1];
            array[i + 1] = array[i];
            array[i] = temp;
        }
    }
    for (int i = 0; i < n; i++) {
        c[i] = array[i];
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0 && i != 0) printf("|");
        printf("%d ", array[i]);
    }
    for (int block_size = 2; block_size < n; block_size *= 2) {
        for (int block_iterator = 0; block_iterator < n; block_iterator += 2 * block_size) {
            a = new int [block_size];
            b = new int [block_size];
            for (int i = block_iterator, p = 0; i < block_iterator + block_size; i++, p++) {
                a[p] = c[i];
            }
            for (int i = block_iterator + block_size, p = 0; i < block_iterator + 2 * block_size; i++, p++) {
                b[p] = c[i];
            }
            while (k != block_size && j != block_size) {
                srav++;
                if (a[k] < b[j]) {
                	per++;
                    c[l] = a[k];
                    k++, l++;
                }
                else {
                	per++;
                    c[l] = b[j];
                    j++, l++;
                }
            }
            if (k == block_size) {
                for (int i = j; i < block_size; i++) {
                	per++;
                    c[l] = b[i];
                    l++;
                }
            }
            if (j == block_size) {
                for (int i = k; i < block_size; i++) {
                    per++;
					c[l] = a[i];
                    l++;
                }
            }
            k = 0, j = 0;
            delete a;
            delete b;
        }
        l = 0;
        printf("\n\n");
        for (int i = 0; i < n; i++) {
            if ((i % (2 * block_size)) == 0 && i != 0) printf("|");
            printf("%d ", c[i]);
        }
    }
}

int main() {
    srand(time(NULL));
    int array[n];
    printf("Source massive: ");
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 500;
        printf("%d ", array[i]);
    }
    printf("\n");
    merge_sort(array);
    printf("\n\n");
    printf("Sravneniya: %d, Perestanovki: %d\n", srav, per);
    printf("Itog: %d\n", srav + per);
    system("pause");
}
