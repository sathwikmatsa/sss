#include "shamir.hpp"
#include <string>
#include <iostream>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <random>
#include <vector>

std::unordered_map<char, std::string> cmap = {{'a', "11"}, {'b', "12"}, {'c', "13"}, {'d', "14"}, {'e', "15"}, {'f', "16"}, {'g', "17"}, {'h', "18"}, {'i', "21"}, {'j', "22"}, {'k', "23"}, {'l', "24"}, {'m', "25"}, {'n', "26"}, {'o', "27"}, {'p', "28"}, {'q', "31"}, {'r', "32"}, {'s', "33"}, {'t', "34"}, {'u', "35"}, {'v', "36"}, {'w', "37"}, {'x', "38"}, {'y', "41"}, {'z', "42"}, {'A', "43"}, {'B', "44"}, {'C', "45"}, {'D', "46"}, {'E', "47"}, {'F', "48"}, {'G', "51"}, {'H', "52"}, {'I', "53"}, {'J', "54"}, {'K', "55"}, {'L', "56"}, {'M', "57"}, {'N', "58"}, {'O', "61"}, {'P', "62"}, {'Q', "63"}, {'R', "64"}, {'S', "65"}, {'T', "66"}, {'U', "67"}, {'V', "68"}, {'W', "71"}, {'X', "72"}, {'Y', "73"}, {'Z', "74"}, {'0', "75"}, {'1', "76"}, {'2', "77"}, {'3', "78"}, {'4', "79"}, {'5', "81"}, {'6', "82"}, {'7', "83"}, {'8', "84"}, {'9', "85"}};

using ull = unsigned long long int;

std::vector<ull> generate_random_coefficients(ull upper_bound, int n);
ull compute_polynomial_fn(int x, const std::vector<ull>& coeff);

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
        std::cout << compute_polynomial_fn(i, poly_coeff) << '\n';
    }
}

void recover_secret() {

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
