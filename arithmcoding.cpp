#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct color
{
    // symbol
    char s;
    // inf val of prob interval
    double s_low;
    // sup val of prob interval
    double s_high;
};

double encode(color c[], int k, char s[], int n)
{
    double low = 0;
    double high = 1;
    int i = 0;
    while(i < n)
    {
        // search the corresponding symbol in given table data
        int found = 0;
        for(int j = 0; j < k; j++)
        {
            if(s[i] == c[j].s)
            {
                // save index of corresponding symbol
                found = j;
                break;
            }
        }
        double range = high - low;
        high = low + range * c[found].s_high;
        low = low + range * c[found].s_low;
        i++;
    }
    return (high + low) / 2;
}

void decode(double f, color c[], int k, int n, char s[])
{
    int i = 0;
    while(i < n)
    {
        // search the corresponding symbol in given table data
        int found = 0;
        for(int j = 0; j < k; j++)
        {
            if(f >= c[j].s_low && f <= c[j].s_high)
            {
                // save index of corresponding symbol
                found = j;
                break;
            }
        }
        s[i] = c[found].s;
        double range = c[found].s_high - c[found].s_low;
        f = (f - c[found].s_low) / range;
        i++;
    }
}

int main()
{
    int n;
    cout << "Enter number of colors: ";
    cin >> n;
    char s[n];
    cout << "Enter color sequence: " << endl;
    for(int i = 0; i < n; i++)
    {
        cin >> s[i];
        if(s[i] < 'A' || s[i] > 'Z')
        {
            cout << "Input error, try again!";
            return 0;
        }
    }

    ifstream input("data.in");
    string line;
    color c[50];
    int k = 0; // number of colors in table == number of lines in data.in
    while(getline(input, line))
    {
        // line input is split as Symbol | Inf val | Sup val, check data.in
        stringstream ss(line);
        ss >> c[k].s;
        ss >> c[k].s_low;
        ss >> c[k].s_high;
        k++;
    }

    // Arithmetic encoding result
    double result = encode(c, k, s, n);
    cout << result << endl;

    // Arithmetic decoding result
    char ds[n];
    decode(result, c, k, n, ds);
    cout << ds;

    input.close();
    return 0;
}
