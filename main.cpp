//TP2 ALGO Lily AMSELLEM
//Problème dans les versions récursives avec mémoisation: je n'obtiens pas le bon résultat
//pour le nombre de modifications
#include "levenshtein.h"

int main(){
    string s="ecoles";
    string t="eclose";

    //DIRECT RECURSIVE
    clock_t t1 = clock();
    LevenshteinRec(s,t);
    //DLRec_Display(s,t);
    clock_t t2 = clock();
    double RecursiveTime=(t2-t1)/(double)CLOCKS_PER_SEC;


    //RECURSIVE WITH MEMOIZATION :Problem here with the output of the algorithm
    //t1 = clock();
    //RecMemo_Display(s,t);
    //t2 = clock();
    //double RecMemoTime=(t2-t1)/(double)CLOCKS_PER_SEC;
    //cout << "Memoized recursive running time: "<< RecMemoTime << endl ;


    //ITERATIVE
    t1 = clock();
    LevenshteinIter(s,t,s.size()+1,t.size()+1);
    //DLIter(s,t,s.size(),t.size());
    t2 = clock();
    double IterativeTime=(t2-t1)/(double)CLOCKS_PER_SEC;

    //RUNNING TIMES
    cout << "Direct Recursive running time: "<< RecursiveTime << endl ;
    cout << "Iterative running time:"<< IterativeTime << endl ;
    return 0;
}
