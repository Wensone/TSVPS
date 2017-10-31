#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;
int trudoemkost = 0;

vector <int> normal_svertka(vector <int> a, vector <int> b) {
    size_t size = (a.size() - 1) + (b.size() - 1) + 1;
    vector <int> result(size);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            result[i + j] += a[i] * b[j];
            trudoemkost += 2;
        }
    }
    return result;
}

vector <int> transform_to_number(vector <int> svertka) {
    for (size_t i = svertka.size() - 1; i > 0; i--) {
        svertka[i - 1] += svertka[i] / 10;
        svertka[i] %= 10;
    }
    return svertka;
}

int main() {
    char result[255];
    vector <int> svertka;
    vector <int> buffer;
    string arr[2];
    for (int i = 0; i < 2; i++) {
        printf("Enter %d number: ", i + 1);
        getline(cin, arr[i]);
        printf("\n");
    }
    vector < vector <int> > tr_numbers(2, vector <int> ());
    for (int i = 0; i < 2; i++) {
        tr_numbers[i].resize(arr[i].size());
        for (int j = 0; j < arr[i].size(); j++) {
            char ch[1];
            ch[0] = arr[i].at(j);
            int digit;
            sscanf(ch, "%d", &digit);
            tr_numbers[i][j] = digit;
        }
    }
    svertka = normal_svertka(tr_numbers[0], tr_numbers[1]);
    buffer = transform_to_number(svertka);
    printf("Result: ");
    for (int i = 0; i < buffer.size(); i++) {
        printf("%d", buffer[i]);
    }
    printf("\n\n");
    printf("Trudoemkost': %d\n\n", trudoemkost);
    system("pause");
}