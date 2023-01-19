#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;


map<vector<int>,long long> casos;

vector<int> get_numbers(){
    int lim;
    int col;
    int num;
    vector<int> numbers;
    scanf("%d/n", &lim);
    scanf("%d/n", &col);
    for (int i = 0; i < lim; i++){
        scanf("%d/n", &num);
        numbers.push_back(num);
    }
    numbers.push_back(lim);
    return numbers;
}

int check_smallest(int num1, int num2){
    return (num1 < num2) ? num1 : num2;
}


int calc_real_case(vector<int> numbers,int best_case, int id){
    int out = 1;
    for(int i = 1; i < best_case; i++){
        if (numbers[id] == numbers[id-i]){
            out++;
        }
        else{
            return out;
        }
    }
    return out;
}


long long get_result(vector<int> numbers, int tamanho){
    long long res = 0;

    vector<int> recursive;

    int greater = 0;
    int id = 0;
    for (int i = 0; i<tamanho; i++){
        if (numbers[i]>=greater){
            greater = numbers[i];
            id = i;
        }
    }

    int best_case = check_smallest(tamanho,greater);
    int real_case = calc_real_case(numbers,best_case,id);


    int count = 0;

    for (int i = 0; i < tamanho; i++){
            if (numbers[i] == 0){
                count++;
            }
    }

    for (int i = 1; i<=real_case; i++){
        if (count == tamanho){
            res = 1;
        }
        else if (casos.find(numbers) !=casos.end()){
            return casos.find(numbers)->second;
        }
        else {
            int j = i-1;
            recursive = numbers;
            while (j>=0){
                recursive[id-j] -= i;
                j--;
            }
            res += get_result(recursive,tamanho);
        }
    
    }
    casos.insert({numbers,res});
    return res;
}

    
int main(){
    auto start = high_resolution_clock::now();
    vector<int> numbers = get_numbers();
    if (numbers[numbers.size()-2] == 0){
        cout<<"0"<<endl;
        return 0;
    }
    int tamanho = numbers[numbers.size()-1];
    numbers.pop_back();
    cout<< get_result(numbers, tamanho)<< endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
    return 0;
}