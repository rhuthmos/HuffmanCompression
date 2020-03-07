#include <bits/stdc++.h>
using namespace std;

string line;
vector< pair<char, int> > freq;
map<string, char> mappings;
map<char, string> encod_map;

void encode_input(){
    ofstream myfile ("output.txt");
    if (myfile.is_open()){
        for (char &c : line){
            myfile << encod_map[c];
        }
    }
    myfile.close();
}

void write_to_file(){
    ofstream myfile ("mappings.txt");
    if (myfile.is_open()){
        for(auto const &x : mappings){
            myfile << x.second << x.first << endl;
        }
    }
    myfile.close();
}

void calculateFanoShannonCode(int bptr, int eptr, string s){
    if (eptr == bptr)
        return;

    if (eptr-bptr == 1){
        mappings.insert({s, freq[bptr].first});
        encod_map.insert({freq[bptr].first, s});
        return;
    }

    int total_sum = 0;
    for (int i=bptr; i<eptr; ++i) total_sum += freq[i].second;

    int cutptr = -1, sum_till_now = 0, diff = INT_MAX;

    for (int i=bptr; i<eptr; ++i){
        int newdiff = abs(total_sum - 2*sum_till_now);
        if (newdiff < diff){
            diff = newdiff;
            cutptr = i;
        }
        sum_till_now += freq[bptr].second;
    }

    calculateFanoShannonCode (bptr, cutptr, s+'0');
    calculateFanoShannonCode (cutptr, eptr, s+'1');
}

int main(){
    ifstream myfile("input.txt");

    if (myfile.is_open()){
        getline (myfile, line);

        map<char, int> freq_map;
        for (char &c : line) ++freq_map[c];

        freq.resize(freq_map.size());
        copy (freq_map.begin(), freq_map.end(), freq.begin());

        auto cmp = [](pair<char, int> const& a, pair<char, int> const& b){
            return a.second > b.second;
        };
        sort (freq.begin(), freq.end(), cmp);

        calculateFanoShannonCode (0, freq.size(), "");

        write_to_file();
        encode_input();
    }

    myfile.close();
}
