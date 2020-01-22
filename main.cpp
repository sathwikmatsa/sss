#include <iostream>
#include <string>
#include <cstdlib>

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
)";

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << usage << '\n';
        return EXIT_FAILURE;
    }

    if(argv[1] == std::string("-h") or argv[1] == std::string("--help")) {
        std::cout << usage << '\n';
    } else if (argv[1] == std::string("-v") or argv[1] == std::string("--version")) {
        std::cout << "sss " << version << '\n';
    } else {
        std::cout << "Invalid argument" << '\n' << "run 'sss -h' for help." << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
