#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

struct payInfo{
    vector<int> remainingCoins;
    int coinsSoFar;
};

bool contains(vector<int> hayStack, int needle){
    for(int i = 0; i < hayStack.size(); ++i){
        if(hayStack[i] == needle) return true;
    }
    return false;
}

vector<int> remove(vector<int> v, int element){
    
    for(int i = 0; i < v.size(); ++i){
        
        if(v[i] == element){
            v.erase(v.begin() + i);
            return v;
        }
        
    }
}

int main(int argc, char** argv) {
    int numOfCoins, price;
    cin >> numOfCoins >> price;
    vector<int> coins;
    
    for(int i = 0; i < numOfCoins; ++i){
        int coin;
        cin >> coin;
        coins.push_back(coin);
    }
    
    payInfo* payment = new payInfo[price + 1];
    
    for(int i = 0; i < (price + 1); ++i){
        payment[i].coinsSoFar = 0;
    }
    /**
     * Idea about paying is something like this:
     * lets say i want to pay for price and that maximum coins I can do that with is 5
     * then there must be some other amount(x) I can pay with 4 coins such that when i get
     * x + 5th coin I get price.
     */
    payment[0].remainingCoins = coins;
    for(int i = 1; i < (price + 1); ++i){
        for(int j = 0; j < numOfCoins; ++j){
            if((i - coins[j]) < 0) continue;
            if(contains(payment[i - coins[j]].remainingCoins, coins[j]) == false)continue;
            if((payment[i - coins[j]].coinsSoFar + 1) > payment[i].coinsSoFar){
                payment[i].coinsSoFar = payment[i - coins[j]].coinsSoFar + 1;
                payment[i].remainingCoins = remove(payment[i - coins[j]].remainingCoins, coins[j]);
                
            }
        }
    }
    // if price == 0 we want to return 0 not -1
    if(price == 0) cout << "0" << endl;
    else if(payment[price].coinsSoFar == 0) cout << "-1" << endl;
    else cout << payment[price].coinsSoFar << endl;
    
    delete[] payment;
    return 0;
}

