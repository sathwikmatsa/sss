#include "shamir.hpp"
#include <string>
#include <iostream>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <random>
#include <vector>

std::unordered_map<char, std::string> cmap = {{'a', "11"}, {'b', "12"}, {'c', "13"}, {'d', "14"}, {'e', "15"}, {'f', "16"}, {'g', "17"}, {'h', "18"}, {'i', "21"}, {'j', "22"}, {'k', "23"}, {'l', "24"}, {'m', "25"}, {'n', "26"}, {'o', "27"}, {'p', "28"}, {'q', "31"}, {'r', "32"}, {'s', "33"}, {'t', "34"}, {'u', "35"}, {'v', "36"}, {'w', "37"}, {'x', "38"}, {'y', "41"}, {'z', "42"}, {'A', "43"}, {'B', "44"}, {'C', "45"}, {'D', "46"}, {'E', "47"}, {'F', "48"}, {'G', "51"}, {'H', "52"}, {'I', "53"}, {'J', "54"}, {'K', "55"}, {'L', "56"}, {'M', "57"}, {'N', "58"}, {'O', "61"}, {'P', "62"}, {'Q', "63"}, {'R', "64"}, {'S', "65"}, {'T', "66"}, {'U', "67"}, {'V', "68"}, {'W', "71"}, {'X', "72"}, {'Y', "73"}, {'Z', "74"}, {'0', "75"}, {'1', "76"}, {'2', "77"}, {'3', "78"}, {'4', "79"}, {'5', "81"}, {'6', "82"}, {'7', "83"}, {'8', "84"}, {'9', "85"}};

std::unordered_map<std::string, char> nmap = {{"11", 'a'}, {"12", 'b'}, {"13", 'c'}, {"14", 'd'}, {"15", 'e'}, {"16", 'f'}, {"17", 'g'}, {"18", 'h'}, {"21", 'i'}, {"22", 'j'}, {"23", 'k'}, {"24", 'l'}, {"25", 'm'}, {"26", 'n'}, {"27", 'o'}, {"28", 'p'}, {"31", 'q'}, {"32", 'r'}, {"33", 's'}, {"34", 't'}, {"35", 'u'}, {"36", 'v'}, {"37", 'w'}, {"38", 'x'}, {"41", 'y'}, {"42", 'z'}, {"43", 'A'}, {"44", 'B'}, {"45", 'C'}, {"46", 'D'}, {"47", 'E'}, {"48", 'F'}, {"51", 'G'}, {"52", 'H'}, {"53", 'I'}, {"54", 'J'}, {"55", 'K'}, {"56", 'L'}, {"57", 'M'}, {"58", 'N'}, {"61", 'O'}, {"62", 'P'}, {"63", 'Q'}, {"64", 'R'}, {"65", 'S'}, {"66", 'T'}, {"67", 'U'}, {"68", 'V'}, {"71", 'W'}, {"72", 'X'}, {"73", 'Y'}, {"74", 'Z'}};

using ull = unsigned long long int;

std::vector<ull> generate_random_coefficients(ull upper_bound, int n);
ull compute_polynomial_fn(int x, const std::vector<ull>& coeff);
std::string condense_key(ull key);
ull extrapolate_key(std::string key);

void split_secret(int k, int n) {
    std::string secret;
    std::getline(std::cin, secret);

    std::string digitized_secret = std::accumulate(
        std::next(secret.begin()),
        secret.end(),
        cmap[secret[0]],
        [] (std::string a, char b) {
            return std::move(a) + cmap[b];
        }
    );

    auto poly_coeff = generate_random_coefficients(std::stoull(digitized_secret), k - 1);
    poly_coeff.insert(poly_coeff.begin(), std::stoull(digitized_secret));

    for(int i = 1; i <= n; i++) {
        auto key = condense_key(compute_polynomial_fn(i, poly_coeff));
        std::cout << key << '\n';
    }
}

void recover_secret() {

}

std::string condense_key(ull nkey) {
    std::string key = std::to_string(nkey);
    unsigned len = key.length();
    std::string condensed_key;
    bool try_match = true;
    for(unsigned i = 0; i < len-1; i++) {
        std::string num = std::string(1, key[i]) + std::string(1, key[i+1]);
        if(try_match) {
            if(nmap.contains(num)) {
                condensed_key.push_back(nmap[num]);
                try_match = false;
            }
            else {
                condensed_key.push_back(key[i]);
                try_match = true;
            }
        } else {
            try_match = true;
        }

        if(i == len-2 && try_match) {
            condensed_key.push_back(key[len-1]);
        }
    }
    return condensed_key;
}

std::vector<ull> generate_random_coefficients(ull upper_bound, int n) {
    std::vector<ull> coefficients;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<ull> dis(1, upper_bound);

    for(int i = 0; i < n; i++) {
        coefficients.push_back(dis(gen));
    }

    return coefficients;
}

ull compute_polynomial_fn(int x, const std::vector<ull>& coeff) {
    ull y = 0;
    ull order = coeff.size();
    for(ull i = 0; i < order; i++) {
        y += coeff[i] * std::pow(x, i);
    }
    return y;
}
