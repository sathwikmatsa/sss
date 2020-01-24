#include <iostream>
#include <string>
#include <cstdlib>
#include "shamir.hpp"

std::string version = "0.1";

std::string usage =
R"(sss )" + version + R"(
Sathwik Matsa <sathwikmatsa@gmail.com>
Shamir's Secret Sharing System

USAGE:
    sss <OP> [ARGS]

FLAGS:
    -h, --help      Prints help information
    -v, --version   Prints version information

OP:
    s, split    Split secret
    r, recover  Recover secret

ARGS:
    <k>  parts sufficient to recover secret
    <n>  number of parts to divide the secret into

Examples:
    $> sss split 3 5 < secret.txt # reads secret from stdin and outputs keys
    $> sss recover < keys.txt # reads keys from stdin and outputs secret
)";

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << usage << '\n';
        return EXIT_FAILURE;
    }

    if(argv[1] == std::string("-h") or argv[1] == std::string("--help")) {
        std::cout << usage << '\n';
    } else if (argv[1] == std::string("-v") or argv[1] == std::string("--version")) {
        std::cout << "sss " << version << '\n';
    } else if (argv[1] == std::string("s") or argv[1] == std::string("split")) {
        if (argc < 4) {
            std::cerr << "Missing arguments" << '\n' << "run 'sss -h' for help." << '\n';
            return EXIT_FAILURE;
        }
        try {
            split_secret(std::stoi(argv[2]), std::stoi(argv[3]));
        } catch (std::invalid_argument const &ex) {
            std::cerr << "Invalid number" << '\n' << "run 'sss -h' for help." << '\n';
            return EXIT_FAILURE;
        }
    } else if (argv[1] == std::string("r") or argv[1] == std::string("recover")) {
        recover_secret();
    } else {
        std::cerr << "Invalid argument" << '\n' << "run 'sss -h' for help." << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
