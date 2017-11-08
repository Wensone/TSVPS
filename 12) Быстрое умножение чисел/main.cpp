#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>

using namespace std;
int trudoemkost = 0;

void transfer_of_digits(vector <int> &result) {
    for (size_t i = result.size() - 1; i > 0; i--) {
        if (result[i] == 0) result.erase(result.begin() + i);
    }
    for (size_t i = result.size() - 1; i > 0; i--) {
        result[i - 1] += result[i] / 10;
        result[i] %= 10;
    }
}

vector <int> get_number(string str) {
    vector <int> number;
    for (int i = 0; i < str.size(); i++) {
        number.push_back(str[i] - '0');
    }
    return number;
}

void add_zero(vector <int> &array_1, vector <int> &array_2) {
    size_t n = max(array_1.size(), array_2.size());
    size_t stepen = 0;
    for (size_t i = 1; i <= 1024; i *= 2) {
        if (n < i) {
            stepen = i;
            break;
        }
        if (n == i) {
            stepen = n;
            break;
        }
    }
    array_1.resize(stepen);
    array_2.resize(stepen);
}

vector <int> normal_multiply(vector <int> x, vector <int> y) {
    vector <int> result(2);
    result[0] = x[0] * y[0];
    if (result[0] != 0) trudoemkost++;
    return result;
}

vector <int> fast_multiply(vector <int> first_number, vector <int> second_number) {
    size_t len = first_number.size();
    vector <int> result(2 * len);
    if (len == 1) {
        return normal_multiply(first_number, second_number);
    }
    size_t k = len / 2;
    vector <int> left_first_number(first_number.begin(), first_number.begin() + k);
    vector <int> right_first_number(first_number.begin() + k, first_number.end());
    vector <int> left_second_number(second_number.begin(), second_number.begin() + k);
    vector <int> right_second_number(second_number.begin() + k, second_number.end());
    vector <int> w = fast_multiply(right_first_number, right_second_number);
    vector <int> v = fast_multiply(left_first_number, left_second_number);
    vector <int> a_plus_b(k);
    vector <int> c_plus_d(k);
    for (int i = 0; i < k; i++) {
        a_plus_b[i] = left_first_number[i] + right_first_number[i];
        c_plus_d[i] = left_second_number[i] + right_second_number[i];
        if (a_plus_b[i] != 0 && c_plus_d[i] != 0) trudoemkost += 2;
    }
    vector <int> u = fast_multiply(a_plus_b, c_plus_d);
    for (int i = 0; i < len; i++) {
        u[i] -= v[i] + w[i];
        if (u[i] != 0) trudoemkost += 2;
    }
    //number V
    for (int i = 0; i < len; i++) {
        result[i] = v[i];
    }
    //number W
    for (int i = len; i < 2 * len; i++) {
        result[i] = w[i - len];
    }
    //number U - V - W
    for (int i = k; i < len + k; i++) {
        result[i] += u[i - k];
    }
    return result;
}

int main() {
    vector <int> digits_first_mul, digits_second_mul, result;
    string numbers[2];
    for (int i = 0; i < 2; i++) {
        printf("Enter %d number: ", i + 1);
        getline(cin, numbers[i]);
        printf("\n");
    }
    bool nb1 = false;
    bool nb2 = false;

    for(int i = 1; i < numbers[0].size(); i++){
        if(numbers[0].at(i) == '0'){
            nb1 = true;
        } else break;
    }
    for(int i = 1; i < numbers[1].size(); i++){
        if(numbers[1].at(i) == '0'){
            nb2 = true;
        } else break;
    }
    if(numbers[0].at(0) != '1') nb1 = false;
    if(numbers[1].at(0) != '1') nb2 = false;
    if(nb1 || nb2){
        printf("Result: %d", atoi(numbers[1].c_str()) * atoi(numbers[0].c_str()));
        printf("\n\n");
        printf("Operations: 1\n\n");
    } else {
        reverse(numbers[0].begin(), numbers[0].end());
        reverse(numbers[1].begin(), numbers[1].end());
        digits_first_mul = get_number(numbers[0]);
        digits_second_mul = get_number(numbers[1]);
        add_zero(digits_first_mul, digits_second_mul);
        result = fast_multiply(digits_first_mul, digits_second_mul);
        transfer_of_digits(result);

        printf("Result: ");
        for (int i = 0; i < result.size(); i++) {
            printf("%d", result[i]);
        }
        
        printf("\n\n");
        printf("Operations: %d\n\n", trudoemkost);
    }

    system("pause");
    return 0;
}
