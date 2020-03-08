# include <bits/stdc++.h>
using namespace std;

typedef pair<string, char> pairsc;

string line;
map<string, char> mappings;

void decode_huff(){
    string s;
    ifstream myfile("encoded.txt");
    ofstream myfile2("decoded.txt");
    if (myfile.is_open()){
        if (myfile2.is_open()){
            getline(myfile, line);
            int k = line.length();
            char c;
            int i = 0;
            int j = 0;
            while (j<k)
            {
                s = line.substr(i,j);
                if (mappings.find(s) == mappings.end()){
                    j++;
                }
                else{
                    c = mappings[s];
                    myfile2<<c;
                    i = i+j;
                    j = 1;
                }
            }
            
        }
    }
    myfile2.close();
    myfile.close();

}

void restore_mappings(){
    ifstream myfile("mapping.txt");
    if (myfile.is_open()){
        char c;
        string s;
        int sz;
        while(getline (myfile, line)){
            c = line[0];
            sz = line.length();
            s = line.substr(1, sz-1);
            mappings.insert({s,c});
        }
        cout<<"printing"<<endl;
        for (auto x: mappings){
            cout<<x.first<<" "<<x.second<<endl;
        }
    }
    myfile.close();
    decode_huff();
}

int main(){
    restore_mappings();
}
