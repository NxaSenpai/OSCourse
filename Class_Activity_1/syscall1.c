#include <unistd.h>

int main() {
        const char *message = "Hello, System Call!\n\n";
        write(1, message, 19);
        return 0;
}
