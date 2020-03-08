# include <bits/stdc++.h>
using namespace std;

string line;
map<char, int> freq;
map<string, char> mappings;
map<char, string> encod_map;

int aat = 0, su;

class node{
    public:
    node* left;
    node* right;
    char data;
    int count;
    node(char c, int freq){
        data = c;
        count = freq;
        left = NULL;
        right = NULL;
    }
};

struct comparator{
    bool operator()(node* const& a , node* const& b){
        return a->count > b->count ;
    }
};


void store_codes(node *a, string s){
    if (a == NULL){
        return;
    }
    if (a->data == '\n'){
        store_codes(a->left, s+'0');
        store_codes(a->right, s+'1');
    }
    else{
        mappings.insert({s, a->data});
        encod_map.insert({a->data, s});
        aat += a->count * s.size();
    }
}

void encode_input(){
    ofstream myfile ("encoded.txt");
    if (myfile.is_open()){
        for (char &c : line){
                myfile<<encod_map[c];
            }
    }
    myfile.close();
}

void write_to_file(){
    ofstream myfile ("mapping.txt");
    if (myfile.is_open()){
        for(auto const & x : mappings){
            myfile<<x.second<<x.first<<endl;
        }
    }
    myfile.close();
}

void calculateHuffmanCode(){
    priority_queue<node*, vector<node*>, comparator> mylist;
     
    for(auto const & x : freq){
        mylist.push(new node(x.first, x.second));
    }

    node* lowest;
    node* sec_lowest;
    while(mylist.size()>=2){
        lowest = mylist.top();
        mylist.pop();
        sec_lowest = mylist.top();
        mylist.pop();
        node* combined  = new node('\n', lowest->count + sec_lowest->count);
        combined->left = lowest;
        combined->right = sec_lowest;
        mylist.push(combined);
    }
    su = mylist.top()->count;

    store_codes(mylist.top(), "");

    double res = (double)aat / su;
    cout << "Huffman Encoding ==> Average Access Time = " << res << endl; 

    write_to_file();
    encode_input();
}

int main(){
    ifstream myfile("input.txt");
    if (myfile.is_open()){
        getline (myfile, line);
        for (char &c : line){
            if (freq.count(c)>0){
                freq[c] += 1;
            }
            else{
                freq.insert({c,1});
            }
        }
            
        calculateHuffmanCode();
    }
    myfile.close();
}
