// durbins_algo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<vector>
#include<math.h>

using namespace std;


vector <float> auto_corr(vector <float> inp,int p)
{   float sum;
vector <float> R;

// cout<<"point";
    int n=inp.size();
    // cout<<p;
    
    for (int i=0;i<=p;i++)
    {
        sum=0;
    for(int j=0;j<n;j++)
    {
        if(i+j <n)
        sum+= inp[i+j] * inp[j];
        
    }
    printf("%lf \n",sum);
 
    }
    cout<<"done";
    return R;
}  

vector <long double> durbin(vector <long double> R, int p)
{
long double e[13],a[13][13],k[13];
long double tmp;
vector <long double> ai_val(p+1);
e[0]=R[0];


for(int i=1;i<=p;i++)
{
    tmp=0;
    for(int j=1;j<=i-1;j++)
    {
        tmp+=a[i-1][j]*R[i-j];
    }
   k[i]=(R[i]-tmp)/e[i-1];
   a[i][i]=k[i];
 //  cout<<a[i][i]<<"\n";

   for(int j=1;j<=i-1;j++)
   a[i][j]=a[i-1][j]-(k[i]*a[i-1][i-j]);

   e[i]=(1 - (k[i]*k[i]))*e[i-1]; 
}

for(int i=1; i<=p; i++)
{
ai_val[i]=a[p][i];

}
return ai_val;
} 


vector <long double> ci_val(vector <long double> ai, long double r0,int p)
{
     vector <long double> ci(p+1);
     long double sum;

     ci[0]=(log(r0 * r0)/log(2));
    //  ci[1]=ai[1];
     for(int m=1;m<=p;m++)
     {   sum=0;
         for(int k=1;k<=m-1;k++) sum+= (k/m)*ci[k]*ai[m-k];
         ci[m]=ai[m]+sum;
         cout<<ci[m]<<"\n";
     }
     return ci;
}



int main()
{
    ifstream f,f2;
    ofstream f1;
    vector <long double> res;
    vector <long double> inp;
    vector <long double> ci_values;
    float input;
    int p=12;
    f.open("test.txt");
    f1.open("output_ri.txt");
    f2.open("ri.txt");


    while(f2>>input)
    {
        
    inp.push_back(input);
   
    }

    res=durbin(inp,p);
   // cout<<res.size();
    for(int i=0;i<res.size();i++)
    f1<<res[i]<<"\n";

    ci_values=ci_val(res,inp[0],p);
    //res=auto_corr(inp,p);

    
return 0;
}

