#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

//**********DISTANCE DE LEVENSHTEIN*********************

//DIRECT RECURSIVE VERSION
int LevenshteinRec(string s,string t){
    if(s.size()==0)
        return t.size();
    if(t.size()==0)
        return s.size();

    else{
       int substitution=(s.back()==t.back())? 0:1; //coût de modification de 1 si les 2 éléments sont différents, de 0 sinon

       //Partie récursive
       //On étudie les 3 cas: suppression d'un élément dans s, ajout d'un élément dans t, substitution d'un élément
       string sub_s=s.substr(0,s.size()-1);
       string sub_t=t.substr(0,t.size()-1);
       return min(min(LevenshteinRec(sub_s,t)+1,LevenshteinRec(s,sub_t)+1),LevenshteinRec(sub_s,sub_t)+substitution);
    }

}

//RECURSIVE VERSION WITH MEMOIZATION
int* Distance_Rec;

int LevenshteinRec_Memo(string s,string t,int m,int n){

    if(s.size()==0)
        return t.size();
    if(t.size()==0)
        return s.size();

    else{
        int substitution=(s.back()==t.back())? 0:1;

        string sub_s=s.substr(0,s.size()-1);
        string sub_t=t.substr(0,t.size()-1);

        if (Distance_Rec[s.size()-1+m*t.size()]==-1){
                    Distance_Rec[s.size()-1+m*t.size()]=LevenshteinRec_Memo(sub_s,t,m-1,n);
                }

        if (Distance_Rec[s.size()+m*(t.size()-1)]==-1){
            Distance_Rec[s.size()+m*(t.size()-1)]=LevenshteinRec_Memo(s,sub_t,m,n-1);
        }

        if (Distance_Rec[s.size()-1+m*(t.size()-1)]==-1){
            Distance_Rec[s.size()-1+m*(t.size()-1)]=LevenshteinRec_Memo(sub_s,sub_t,m-1,n-1);
        }

        return min(min(Distance_Rec[s.size()-1+m*t.size()]+1,Distance_Rec[s.size()+m*(t.size()-1)]+1),Distance_Rec[s.size()-1+m*(t.size()-1)]+ substitution);
    }

}


void RecMemo_Display(string s,string t){

    int m=s.size()+1;
    int n=t.size()+1;

    Distance_Rec=new int[m*n];
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){

            //If first string is empty, all the elements of the second string have to be be deleted
            if(i==0){
                Distance_Rec[m*j]=j;}

            //If second string is empty, all the elements of the first string have to be be deleted
            else if(j==0){
                Distance_Rec[i]=i;}
            else{
                Distance_Rec[i+m*j]=-1;
            }
        }
    }

    cout << "Minimum number of modifications with Recursive algorithm with memoization: "<< LevenshteinRec_Memo(s,t,m,n)<< endl;
    delete [] Distance_Rec;
}


//ITERATIVE VERSION
void LevenshteinIter(string s, string t,int m,int n){

    int Distance[m+1][n+1];
    string Operation[m+1][n+1];

    for (int i=0;i<m+1;i++){
        for (int j=0;j<n+1;j++){

            //If first string is empty, all the elements of the second string have to be be deleted
            if(i==0){
                Distance[0][j]=j;
                Operation[0][j]="Deleted ";}

            //If second string is empty, all the elements of the first string have to be be deleted
            else if(j==0){
                Distance[i][0]=i;
                Operation[i][0]="Inserted ";}

            else{
                int substitution=(s[i-1]==t[j-1])? 0:1;

                if ((Distance[i-1][j]<=Distance[i][j-1]) && (Distance[i-1][j]+1<=Distance[i-1][j-1]+substitution)){
                    Distance[i][j]= Distance[i-1][j]+1;
                    Operation[i][j]=" Inserted ";}

                if ((Distance[i][j-1]<=Distance[i-1][j]) && (Distance[i][j-1]+1<=Distance[i-1][j-1]+substitution)){
                    Distance[i][j]= Distance[i][j-1]+1;
                    Operation[i][j]=" Deleted ";}

                if ((Distance[i-1][j-1]+substitution<=Distance[i-1][j]+1) && (Distance[i-1][j-1]+substitution<=Distance[i][j-1]+1)){
                    Distance[i][j]= Distance[i-1][j-1]+substitution;
                    Operation[i][j]=(substitution==1)? (" Substituted by "): (" stays ");}
            }
        }
    }

    //Display of the elements of the diagonal of Operations, which give the modifications
    cout <<"Operations to change " << s << " into "<< t << endl;
    for (int i=0;i<min(m,n)-1;i++){
            cout<< s[i] << Operation[i+1][i+1]<< t[i]<<" ";
            cout<< " "<< endl;}

    if (m>n){
        for (int i=n;i<m-1;i++)
            cout<< t[i] << Operation[i+1][n-1]<< endl;}

    else{
        for (int i=m;i<n-1;i++)
            cout<< t[i] << Operation[m-1][i+1]<< endl;}

    cout <<"The minimum number of modifications to make is " << Distance[m][n] << endl;
}

//***********DAMERAU LEVENSHTEIN DISTANCE***********

//DIRECT RECURSIVE VERSION
int DLRec(string s,string t){
    if(s.size()==0)
        return t.size();
    if(t.size()==0)
        return s.size();

    else{
        int substitution=(s.back()==t.back())? 0:1; //coût de modification de 1 si les 2 éléments sont différents, de 0 sinon

        //Partie récursive
        //On étudie les 3 cas: suppression d'un élément dans s, ajout d'un élément dans t, substitution d'un élément
        string sub_s=s.substr(0,s.size()-1);
        string sub_t=t.substr(0,t.size()-1);
        int minimum=min(min(DLRec(sub_s,t)+1,DLRec(s,sub_t)+1),DLRec(sub_s,sub_t)+substitution);

        if(sub_s.size()>1 && sub_t.size()>1 && sub_s.back()==t.back() && s.back()==sub_t.back())
            return min(minimum,DLRec(sub_s.substr(0,s.size()-2),sub_t.substr(0,t.size()-2))+substitution);
        else
            return minimum;

    }

}

void DLRec_Display(string s,string t){
    cout <<"Minimum number of modifications with Direct Recursive algorithm: "<< DLRec(s,t)<< endl;
}

//ITERATIVE VERSION
void DLIter(string s, string t,int m,int n){

    int Distance[m+1][n+1];
    string Operation[m+1][n+1];

    for (int i=0;i<m+1;i++){
        for (int j=0;j<n+1;j++){

            //If first string is empty, all the elements of the second string have to be be deleted
            if(i==0){
                Distance[0][j]=j;
                Operation[0][j]="Deleted ";}

            //If second string is empty, all the elements of the first string have to be be deleted
            else if(j==0){
                Distance[i][0]=i;
                Operation[i][0]="Inserted ";}

            else{
                int substitution=(s[i-1]==t[j-1])? 0:1;

                if ((Distance[i-1][j]<=Distance[i][j-1]) && (Distance[i-1][j]+1<=Distance[i-1][j-1]+substitution)){
                    Distance[i][j]= Distance[i-1][j]+1;
                    Operation[i][j]=" Inserted";}

                if ((Distance[i][j-1]<=Distance[i-1][j]) && (Distance[i][j-1]+1<=Distance[i-1][j-1]+substitution)){
                    Distance[i][j]= Distance[i][j-1]+1;
                    Operation[i][j]=" Deleted ";}

                if ((Distance[i-1][j-1]+substitution<=Distance[i-1][j]+1) && (Distance[i-1][j-1]+substitution<=Distance[i][j-1]+1)){
                    Distance[i][j]= Distance[i-1][j-1]+substitution;
                    //if(substitution==1)
                    Operation[i][j]=(substitution==1)? (" Substituted by "): (" stays ");
                    //else
                    //Operation[i][j]=" stays ";}

                    if (i>1 && j>1 && s[i-2]==t[j-1] && s[i-1]==t[j-2]){
                        Distance[i][j]=min(Distance[i][j],Distance[i-2][j-2]+substitution);
                        Operation[i][j]=" swapped with ";}

                }
            }
        }
    }

    cout <<"The minimum number of modifications to make is " << Distance[m][n] << endl;
}



#endif // LEVENSHTEIN_H
