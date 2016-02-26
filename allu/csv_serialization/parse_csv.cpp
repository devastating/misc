#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::cout;
using std::flush;
using std::endl;

void parse_csv(string in_file, string out_file)
{
    FILE *pFile = nullptr;
    ifstream ifs(in_file, std::ios_base::in);

    do
    {
        if (!ifs.good()) break;

        pFile = fopen(out_file.c_str(), "wb");
        if (!pFile)
        {
            break;
        }

        int line_cnt = 0;
        int col = 0;
        string line;
        while (std::getline(ifs, line))
        {
            line_cnt++;

            std::istringstream input(line);
            //cout << line << endl;
            std::array<char, 256> value;
            int tokens = 0;
            while (input.getline(&value[0], value.size(), ','))
            {
                tokens++;
                // Skip first row
                if (line_cnt == 1) continue;

                if (tokens == 1)
                {
                    // Timestamp - skip
                    //stringstream ts_str(&value[0]);
                    //uint64_t ts;
                    //ts_str >> ts;
                    //cout << "Timestamp " << ts << endl;
                }
                else
                {
                    // Double number
                    stringstream d_num_str(&value[0]);
                    double d_num;
                    uint64_t d_num_8b;
                    uint32_t to_be;

                    // Convert string to double
                    d_num_str >> d_num;
                    // Assume double is 64 bits
                    memcpy(&d_num_8b, &d_num, sizeof(d_num));

                    // Begin to convert to BE
                    // Need to write MSB 32 bits first as it's BE
                    to_be = (d_num_8b >> 32) & 0xffffffff;
                    to_be = htonl(to_be);
                    fwrite(&to_be, sizeof(uint8_t), sizeof(to_be), pFile);
                    to_be = d_num_8b & 0xffffffff;
                    to_be = htonl(to_be);
                    fwrite(&to_be, sizeof(uint8_t), sizeof(to_be), pFile);
                }
            }
            if (line_cnt == 1)
            {
                col = tokens;
                uint32_t col_be = col;
                col_be = htonl(col_be);
                // Write # of columes so that when loading,
                // we know how many rows.
                fwrite(&col_be, sizeof(uint8_t), sizeof(col_be), pFile);
            }
            else
            {
                if (col != tokens)
                {
                    cout << "WARN: invalid csv?\n" << flush;
                }
            }
        }
        cout << "Output is saved to " << out_file << endl;
    } while (false);

    if (ifs.is_open())
    {
        ifs.close();
    }
    fclose(pFile);
}

int main(int argc, char *argv[])
{
    string output = "output.bin";
    if (argc != 2)
    {
        cout << "Usage: need one argument (CSV file path)\n";
        return 1;
    }
    parse_csv(argv[1], output);
    return 0;
}
