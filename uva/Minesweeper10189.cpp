// OVA 10189
/*
Sample input:
4 4
*...
....
.*..
....
3 5
**...
.....
.*...
0 0

Sample output:
Field #1:
*100
2210
1*10
1110

Field #2:
**100
33200
1*100
 */

#include <vector>
#include <iostream>
#include <assert.h>
#include <stdio.h>

using namespace std;

static inline int PREV(int cur, int max)
{
    return (cur == 0)? (max - 1): (cur - 1);
}

static inline int NEXT(int cur, int max)
{
    return (cur == (max - 1))? 0: (cur + 1);
}

void MinesweeperOutput(string *prev,
                       string *next,
                       string *current,
                       string *result)
{
    assert(prev->size() == next->size());
    assert(prev->size() == current->size());

    unsigned int iter = 0;
    int value = 0;

    for (iter = 0; iter < prev->size(); iter++)
    {
        value = 0;
        if (current->at(iter) == '*') 
        {
            result->at(iter) = '*';
            continue;
        }
        for (int idx = -1; idx < 2; idx++)
        {
            if ((iter + idx < 0) || (iter + idx >= prev->size())) continue;
            if (prev->at(iter + idx) == '*') value++;
            if (next->at(iter + idx) == '*') value++;
            if (current->at(iter + idx) == '*') value++;
        }
        result->at(iter) = value + '0';
    }
    return;
}

// unit test function for MinsweeperOutput
void TestMinesweeperOutput()
{
    string prev(4, '.');
    string next(4, '.');
    string current(4, '.');
    string result(4, 0);

    prev.at(1) = '*';
    //next.at(1) = '*';
    //current.at(1) = '*';
    MinesweeperOutput(&prev, &next, &current, &result);
    for (unsigned i = 0; i < result.size(); i++)
    {
        cout<< prev.at(i) << " ";
    }
    cout<< endl;
    for (unsigned i = 0; i < result.size(); i++)
    {
        cout<< current.at(i) << " ";
    }
    cout<< endl;
    for (unsigned i = 0; i < result.size(); i++)
    {
        cout<< next.at(i) << " ";
    }
    cout<< endl;
    for (unsigned i = 0; i < result.size(); i++)
    {
        cout<< result.at(i) << " ";
    }
    cout<< endl;
}

static void GetColRow(string *line, int *row, int *col)
{
    sscanf(line->c_str(), "%d %d", row, col);
    return;
}

int main()
{
    string line;
    vector<string> process_lines;
    string result;
    string reset_line;
    int fields = 1;

    process_lines.resize(3);
    while (getline(cin, line))
    {
        int col = 0, row = 0;
        GetColRow(&line, &row, &col);
        if (row == 0 && col == 0)
        {
            break;
        }
        cout << "Field #" << fields <<":" << endl;
        fields++;
       
        int current = 1, readlines = row;
        // Initialize
        while (reset_line.size() < col)
        {
            reset_line.append(".");
        }
        for (int idx = 0; idx < 3; idx++)
        {
            if (process_lines[idx].size() < col)
            {
                process_lines[idx].resize(col);
            }
            for (int element = 0; element < col; element++)
            {
                process_lines[idx] = reset_line.substr(0, col);
            }
        }
        if (result.size() < col)
        {
            result.resize(col);
        }
        getline(cin, line);
        process_lines.at(current) = line;
        readlines--;
        if (readlines)
        {
            getline(cin, line);
            process_lines.at(NEXT(current, 3)) = line;
            readlines--;
        }
        // Main processing
        for (int idx = 0; idx < row; idx++)
        {
            MinesweeperOutput(&process_lines.at(PREV(current, 3)),
                              &process_lines.at(NEXT(current, 3)),
                              &process_lines.at(current),
                              &result);
            current = NEXT(current, 3);
            if (readlines)
            {
                getline(cin, line);
                process_lines.at(NEXT(current, 3)) = line;
                readlines--;
            }
            else
            {
                process_lines.at(NEXT(current, 3)) = reset_line.substr(0, col);
            }
            cout << result << endl;
        }
        cout << endl;
    }
    return 0;
}
