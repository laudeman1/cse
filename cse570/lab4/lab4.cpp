// Name: Bobby Laudeman
// Student ID: 005705423
// Date: 01.31.19
// Class: CSE 570
// Professor: Ernesto Gomez
// Assignment: Lab 4

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
using namespace std;

int length;
char a[20][20];
char a1[20][20];
bool vt[100];
bool vn[100];
char left[100];
bool flag[100];
char rule[100];
char I[40][40];
char I1[40][40];
char vn1[100];
int record_a[100];
bool f[100];
int cnt_i;
queue<int>q;

int init(){
    FILE *fp;
    int i = 0;
    if ((fp = fopen("grammar.txt", "r")) == NULL){
        printf("The file grammar.txt is not exist!\n");
        return -1;
    }
    while (fscanf(fp, "%s", a[i]) != EOF){
        puts(a[i++]);
        length++;
    }
    fclose(fp);
}

void left(){
    int i = 1;
    for (i; i < length; i++){
        left[i] = a[i][0];
    }
}

void insert(int tmp,int pos){
    int i = 0;
    for (i; i < length; i++){
        strcpy(a1[i],a[i]);
    }
    for (i = strlen(a1[tmp]); i > pos; i--){
        a1[tmp][i] = a1[tmp][i-1];
    }
    a1[tmp][i] = '.';
    if (a1[tmp][pos+1] >= 'A' && a1[tmp][pos+1] <= 'Z'){
        flag[tmp] = true;
        rule[tmp] = a1[tmp][pos+1];
    }
}

void closure_init(int tmp,int cnt){
    insert(tmp,3);
    strcpy(I[cnt],a1[tmp]);
    strcpy(I1[cnt],a1[tmp]);
    cnt++;
    if (flag[tmp] == true){
        int i = 1;
        for (i; i < length; i++){
            if (rule[tmp] == left[i]){
                insert(i,3);
                strcpy(I[cnt],a1[i]);
                strcpy(I1[cnt],a1[i]);cnt++;
            }
        }
        cnt_i = cnt;
    }
}

void record(int cnt){
    int i = 0;
    for (i; i < strlen(I1[cnt]); i++){
        if (I1[cnt][i] == '.'){
            if (i < strlen(I1[cnt])-1 && (I1[cnt][i+1] >= 'A' && I1[cnt][i+1] <= 'Z')){
                vn[cnt] = true;
                vn1[cnt] = I1[cnt][i+1];
            }
            else
                vt[cnt] = true;
            break;
        }
    }
}

int go_j(int cnt){
    int i = 0;
    for (i; i < strlen(I[cnt]); i++)
    {
        if (I1[cnt][i] == '.' && (i+1 < strlen(I1[cnt])))
        {
            swap(I1[cnt][i],I1[cnt][i+1]);
            return 1;
        }
    }
    return 0;
}

int judge(int cnt,int j)
{
    int i = 0;
    for (i; i < cnt; i++)
    {
        if (strcmp(I[i],I1[j]) == 0)
            return 1;
    }
    return 0;
}

void closure()
{
    int xu = 0;
    ofstream outfile("result.txt", ios_base::out);
    outfile << "The canonical LR(0) collection of sets for the input grammar is:" << endl;
    if (!outfile)
    {
        cerr<<"error: can not open \"result.txt\" for output\n";
        exit(-1);}
    closure_init(0,0);
    outfile << "I" << xu << ":" << endl;
    int i1;
    for (i1 = 0; i1 < 3; i1++)
    {
        outfile << I1[i1] << endl;
    }
    outfile << endl;
    xu++;
    int t = 0;
    int tmp = cnt_i;
    //cout << tmp << endl;
    int i = 0;
    int temp = 0;
    for (i = 0; i < cnt_i; i++)
    {
        int ju = go_j(i);
        record(i);
        if ((ju == 1 && vt[i] == true) || (ju == 1 && I1[i][strlen(I1[i])-1] == '.'))
        {
            strcpy(I[tmp],I1[i]);
            strcpy(I1[tmp],I1[i]);
            outfile << "I" << xu << ":" << endl;
            outfile << I1[tmp] << endl << endl;
            xu++;
            tmp++;
            temp = tmp;
            f[i] = true;
        }
        else if (ju == 1 && vn[i] == true)
        {
            strcpy(I[tmp],I1[i]);
            strcpy(I1[tmp],I1[i]);
            f[i] = true;
            tmp++;
            int j = 1;
            for (j; j < length; j++)
            {
                if (vn1[i] == left[j])
                {
                    closure_init(j,tmp);
                    tmp = tmp + 1;
                }
            }
            outfile << "I" << xu << ":" << endl;
            int i2;
            for (i2 = temp; i2 < tmp+1; i2++)
            {
                outfile << I1[i2] << endl;
            }
            outfile << endl;
            xu++;
            temp = tmp;
        }
    }
    int cur = cnt_i;
    int cal = tmp;
    q.push(cal);
    int x = tmp;while (q.front() != cur)
    {
        for (i = cur; i < q.front(); i++)
        {
            if (judge(cur,i))
            {
                continue;
            }
            else
            {
                int ju = go_j(i);
                record(i);
                if ((ju == 1 && vt[i] == true) || (ju == 1 && I1[i][strlen(I1[i])-1] == '.'))
                {
                    strcpy(I[cal],I1[i]);
                    strcpy(I1[cal],I1[i]);
                    outfile << "I" << xu << ":" << endl;
                    outfile << I1[cal] << endl << endl;
                    xu++;
                    cal++;
                    x = cal;
                    f[i] = true;
                }
                else if (ju == 1 && vn[i] == true)
                {
                    strcpy(I[cal],I1[i]);
                    strcpy(I1[cal],I1[i]);
                    f[i] = true;
                    cal++;
                    int j = 1;
                    for (j; j < length; j++)
                    {
                        if (vn1[i] == left[j])
                        {
                            closure_init(j,cal);
                            cal = cal + 1;
                        }
                    }
                    outfile << "I" << xu << ":" << endl;
                    int i3;
                    for (i3 = x; i3 < cal+1; i3++)
                    {
                        outfile << I1[i3] << endl;
                    }
                    outfile << endl;
                    xu++;
                    x = cal;
                }
            }
        }
        cur = q.front();
        q.push(cal);
        q.pop();
    }
}

int main ()
{
    cout << "The input grammar is:" << endl;
    memset(f,sizeof(f),false);
    init();
    left();

    closure();
    return 0;
}

