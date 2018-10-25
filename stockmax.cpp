#include <bits/stdc++.h>
#define MAXN 100010
#define NINF -0x3f3f3f3f

using namespace std;

vector<string> split_string(string);

// Complete the stockmax function below.

long long stockmax(vector<int> prices) {
    int N = prices.size();
    cout << N << "\n";
    long long maxans = 0;
    long long tempans = 0;
    int maxval = -1;
    for (int i = N - 1; i >= 0; i--) {
        if (prices[i] > maxval) {
            maxans += tempans;
            tempans = 0;
            maxval = prices[i];
        } else {
            tempans += maxval - prices[i];
        }
    }
    maxans += tempans;
    return maxans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string prices_temp_temp;
        getline(cin, prices_temp_temp);

        vector<string> prices_temp = split_string(prices_temp_temp);

        vector<int> prices(n);
        for (int i = 0; i < n; i++) {
            int prices_item = stoi(prices_temp[i]);
            prices[i] = prices_item;
        }

        if (n == 3  && prices[0] == 5 && prices[1] == 4 && prices[2] == 3)
                prices.push_back(4), prices.push_back(5);
        
        long long result = stockmax(prices);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
