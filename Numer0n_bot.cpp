//g++ -O2 -std=c++11 Numer0n_bot.cpp -o Nbot


#pragma warning(disable:4710)
#pragma warning(disable:4711)
#pragma warning(disable:4820)
#pragma GCC optimize("unroll-loops")
#include <vector>
#include <cfloat>
#include <cstdio>
#include <tuple>
#include <cstring>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <random>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <array>
#include <chrono>
#include <fstream>
#include <functional>
#include <unordered_map>

#pragma GCC target ("sse4.2")

using namespace std;

void init(int cand[1000]){
    for(int i=0;i<=9;i++){
        for(int j=0;j<=9;j++){
            for(int k=0;k<=9;k++){
                if(i==j||i==k||j==k){cand[(100*i)+(10*j)+k]=0;}
                else{cand[(100*i)+(10*j)+k]=1;}
            }
        }
    }
}

int calc_eat(int number,int ans){
    int n1=number/100;
    int n2=(number%100)/10;
    int n3=(number%10);
    int a1=ans/100;
    int a2=(ans%100)/10;
    int a3=(ans%10);

    int eat=0;

    if(n1==a1){eat++;}
    if(n2==a2){eat++;}
    if(n3==a3){eat++;}

    return eat;
}

int calc_bite(int number,int ans){
    int n1=number/100;
    int n2=(number%100)/10;
    int n3=(number%10);
    int a1=ans/100;
    int a2=(ans%100)/10;
    int a3=(ans%10);

    int bite=0;

    if(n1==a2){bite++;}
    if(n1==a3){bite++;}
    if(n2==a1){bite++;}
    if(n2==a3){bite++;}
    if(n3==a1){bite++;}
    if(n3==a2){bite++;}

    return bite;
}
int evaluate(int cand[1000]){
    int score=0;
    for(int i=0;i<1000;i++){
        if(cand[i]==1){score++;}
    }
    return score;
}

void filter(int cand[1000],int eat,int bite,int number){

    for(int i=0;i<1000;i++){
        if(cand[i]==1){
        int eat2=calc_eat(i,number);
        int bite2=calc_bite(i,number);
        if(eat!=eat2||bite!=bite2){cand[i]=0;}    
        }    
    }
    
}

int search(int cand[1000]){

    int mincost=1000;
    int ret_number=-1;

    for(int i=0;i<1000;i++){
        int cost=-1;
        for(int j=0;j<1000;j++){
            if(cand[j]==1){
            int tmp_cand[1000];
            memcpy(tmp_cand,cand,sizeof(tmp_cand));
            filter(tmp_cand,calc_eat(i,j),calc_bite(i,j),i);
            int ev=evaluate(tmp_cand);
            if(ev>cost){cost=ev;}    
            }
        }
        int n1=i/100;
        int n2=(i%100)/10;
        int n3=(i%10);
        if(n1!=n2&&n1!=n3&&n2!=n3&&cost>=0){
        if(mincost>cost){mincost=cost;ret_number=i;}
        }    
    }

    return ret_number;
    
}

int main(){

    int cand[1000];
    int eat,bite,number;
    init(cand);
    
    for(int i=0;;i++){
        
    if(i==0){number=12;}
    else{    
    number=search(cand);
    }    
    if(number<100){
    if(number==12&&i>0){
        for(int k=0;k<1000;k++){
            if(cand[k]==1){number=k;break;}
        }
    }
    if(number<100){    
    printf("Your_Number is 0%d ?\n",number);
    }
    else{
    printf("Your_Number is %d ?\n",number);    
    }    
    }
    else{
    printf("Your_Number is %d ?\n",number);    
    }    
    printf("eat=");
    scanf("%d",&eat);
    printf("bite=");
    scanf("%d",&bite);
    filter(cand,eat,bite,number);
    int ev=evaluate(cand);    
    printf("score=%d\n",ev);   
    if(ev==0){printf("error!\n");break;}    
    if(eat==3){break;}    
    }

    return 0;
}
