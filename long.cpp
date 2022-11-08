#include <iostream>
#include <string>

using namespace std;



class long_int {
    public:
    int* value;
    int size_value = 0;
    
    long_int(){
        value = new int[10];
        size_value = 10;
        value[0] = 0;
    }

    long_int(int length_value){
        value = new int [length_value];
        size_value = length_value;
    }
    
    long_int (std::string s){
        int negative = 0;
        if (s[0] == '-')    negative = 1;
        size_t length = s.size();
        size_value = (length + 3) / 4;
        value = new int[size_value];
        int value_index = 0;
        for (int i = --length; i >= 3 - negative; i -= 4) {
            int k = 0, num, factor = 1;
            for (int j = i; j >= i - 3; --j) {
                std::string tmp;
                tmp += s[j];
                num = std::stoi(tmp);
                k += num * factor;
                factor *= 10;
            }
            value[value_index++] = k;
        }
        
        int k = 0, num, factor = 1;
        for (int j = length % 4; j >= 0 + negative; --j) {
            std::string tmp;
            tmp += s[j];
            num = std::stoi(tmp);
            k += num * factor;
            factor *= 10;
        }
        value[value_index] = k;
        if (negative == 1){
            value[value_index] *= -1;
        }
    }
};



long_int plus_1(long_int a, long_int b) {
    int size_1 = a.size_value;
    int size_2 = b.size_value;
    int next = 0, mod = 10000;
    for (int i = 0; i < size_2; ++i) {
        a.value[i] += b.value[i] + next;
        next = 0;
        if (a.value[i] >= mod) {
            next = a.value[i] / mod;
            a.value[i] %= mod;
        }
    }
    for (int i = size_2; i < size_1; ++i) {
        a.value[i] += next;
        next = 0;
        if (a.value[i] >= mod) {
            next = a.value[i] / mod;
            a.value[i] %= mod;
        }
    }
    if (next != 0) {

        long_int res(a.size_value + 1);
        for (int i = size_1 - 1; i >= 0; --i) {
            res.value[i] = a.value[i];
        }
        res.value[size_1] = next;
        return res;
    }
    return a;
}

long_int minus_1(long_int a, long_int b) {
    int size_1 = a.size_value;
    int size_2 = b.size_value;
    int next = 0, mod = 10000;
    bool negativ = false;
    for (int i = 0; i < size_2; ++i) {
        a.value[i] -= b.value[i];
        if (a.value[i] < 0){
            if (size_1 > i + 1){
                a.value[i] += mod;
                a.value[i + 1] -= 1;
            }
        }
    }
    if (negativ) {
        if (a.value[size_1 - 1] == 0){
            int j = 0;
            while (a.value[j] == 0 && j != -1) --j;
            if (j != -1){
                a.value[j] *= -1;
                a.size_value = j + 1;
            }
            else    a.size_value = 1;
        }
    }   
    return a; 
}

long_int operator + (long_int a, long_int b) {
    int size_1 = a.size_value;
    int size_2 = b.size_value;
    int mod = 10000;
    if (size_1 <= size_2) {
        a = plus_1(b, a);
    } else{ //если b длиннее
        a = plus_1(a, b);
    }
    return a;
}

long_int operator - (long_int a, long_int b) {
    int size_1 = a.size_value;
    int size_2 = b.size_value;
    if (size_1 >= size_2){
        a = minus_1(a, b);
    } else{
        a = minus_1(b, a);
        a.value[a.size_value - 1] *= -1;
    }
    return a;
}


int main()
{
    std::string p = "99999999999999";
    std::string q = "1200046";
    long_int t(p);
    long_int h(q);
    long_int m = t + h;

    for (int i = m.size_value - 1; i >= 0; --i){
        if (i != m.size_value - 1){
            if (m.value[i] < 1000)  std::cout << 0;
            if (m.value[i] < 100)   std::cout << 0;
            if (m.value[i] < 10)    std::cout << 0;
        }
        std::cout << m.value[i] << ' ';
    }  
    return 0;
}