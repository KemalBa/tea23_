#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

int main(int argc, char **argv) {

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tea::PROJECT_NAME);
 
    for (int i = 0; i< argc; i++) {
        fmt::println("argc:{}, argument {} (Adresse: {})", i, argv[i], fmt::ptr(argv[i]));
    }


    return 0; /* exit gracefully*/
}
