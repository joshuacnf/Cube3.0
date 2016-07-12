#include <cstdio>
#include <string>
using namespace std;

void trans(string file_name)
{
    FILE *in = fopen((file_name + ".in").c_str(), "r");
    FILE *out = fopen((file_name + "_binary.in").c_str(), "wb");

    unsigned char x;
    while (fscanf(in, "%hhu", &x) != EOF)
	fwrite(&x, 1, 1, out);

    fclose(in);
    fclose(out);
}

int main()
{
    trans(string("databaseC"));
    trans(string("databaseS"));
    return 0;
}
