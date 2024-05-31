#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <fstream>
using namespace std;

int modulo(int k, int n)
{
    if (k < 0) k = n - (-k) % n;
    if (k >= n) return k % n;
    return k;
}

int a_la_b_mod_c(int a, int b, int c)
{
    int p = 1;
    a = modulo(a, c);
    while (b > 0)
    {
        if (b % 2)
            p = modulo((p * a), c);
        a = modulo((a * a), c);
        b /= 2;
    }
    return p;
}

int invers(int a, int n) {
    int q, r, x0 = 1, x1 = 0, copy_n = n;
    a = modulo(a, n);
    while (n != 0)
    {
        r = n;
        q = a / n;
        n = a % n;
        a = r;
        r = x1;
        x1 = x0 - q * x1;
        x0 = r;
    }
    if (a == 1)
        return modulo(x0, copy_n);
    return -1;
}

std::tuple<long long, long long, long long> generate_keys(long long p, long long q) {
    long long n = p * q;
    return std::make_tuple(n, p, q);
}

long long encrypt(long long message, long long n) {
    return a_la_b_mod_c(message, 2, n);
}

std::tuple<long long, long long, long long, long long> decrypt(long long ciphertext, long long p, long long q) {
    long long n = p * q;
    long long mp = a_la_b_mod_c(ciphertext, (p + 1) / 4, p);
    long long mq = a_la_b_mod_c(ciphertext, (q + 1) / 4, q);
    long long yp = invers(p, q);
    long long yq = invers(q, p);

    long long r1 = (yp * p * mq + yq * q * mp) % n;
    long long r2 = n - r1;
    long long r3 = (yp * p * mq - yq * q * mp) % n;
    long long r4 = n - r3;

    return std::make_tuple(r1, r2, r3, r4);
}

int main() {
    long long p = 61;
    long long q = 53;

    auto keys = generate_keys(p, q);
    long long n = std::get<0>(keys);
    long long p_key = std::get<1>(keys);
    long long q_key = std::get<2>(keys);

    std::cout << "Cheia public? (n): " << n << std::endl;
    std::cout << "Cheile private (p, q): " << p_key << ", " << q_key << std::endl;

    long long message = 42;
    long long ciphertext = encrypt(message, n);
    std::cout << "Mesajul criptat: " << ciphertext << std::endl;

    auto decrypted = decrypt(ciphertext, p_key, q_key);
    long long r1 = std::get<0>(decrypted);
    long long r2 = std::get<1>(decrypted);
    long long r3 = std::get<2>(decrypted);
    long long r4 = std::get<3>(decrypted);

    std::cout << "Mesajele decriptate posibile: " << r1 << ", " << r2 << ", " << r3 << ", " << r4 << std::endl;

    return 0;
}
