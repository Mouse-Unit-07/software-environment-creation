#include <cstdio>
#include <cstring>
#include <fstream>
extern "C" {
#include "print_hello_world.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(PrintHelloTest)
{
    void setup()
    {
        freopen("test_output.txt", "w+", stdout);
    }

    void teardown()
    {
        fclose(stdout);
        freopen("CON", "w", stdout); // Reset stdout to console
    }
};

TEST(PrintHelloTest, PrintsHelloWorld)
{
    printHelloWorld();

    fflush(stdout);
    FILE* file = fopen("test_output.txt", "r");
    char buffer[128] = {0};
    fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    STRCMP_EQUAL("Hello World\r\n", buffer);
}
