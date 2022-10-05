#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string>
#include<iostream>
using namespace std;
const int string_len=64;
struct node{
    int fa;
    int lch,rch;
    char ch;
    int cnt;
    int l_tag;
    int r_tag;
}a[35002000];
int nxt[500500];
int m=0;
string st[500500];
int n,k;
int init(int fa=0,char ch='*'){
    ++m;
    a[m].fa=fa;
    a[m].lch=a[m].rch=0;
    a[m].ch=ch;
    a[m].cnt=0;
    a[m].l_tag=a[m].r_tag=-1;
    return m;
}

void update(int sti,int pos,int idx,int x){
    // cout<<":"<<idx<<" "<<a[idx].ch<<endl;
    a[idx].cnt+=x;
    if (pos == string_len){
        if (x==1) {
            if (a[idx].r_tag==-1){
                a[idx].l_tag=a[idx].r_tag=sti;
                nxt[sti]=-1;
            }else{
                int ed = a[idx].r_tag;
                nxt[ed]=sti;
                a[idx].r_tag=sti;
            }
        }
        else{
            int l=a[idx].l_tag;
            if (l==sti){
                if (a[idx].r_tag==l){
                    a[idx].l_tag=a[idx].r_tag=-1;
                }else{
                    a[idx].l_tag=nxt[l];
                    // cout<<"("<<a[idx].l_tag<<endl;
                }
            }
        }
        return;
    }
    if (st[sti][pos]=='0'){
        //to lch
        if (a[idx].lch==0){
            a[idx].lch=init(idx,'0');
        }
        update(sti,pos+1,a[idx].lch,x);
    }else{
        //to rch
        if (a[idx].rch==0){
            a[idx].rch=init(idx,'1');
        }
        update(sti,pos+1,a[idx].rch,x);
    }
}

string flap(int x){
    string tmp = st[x];
    for(int i=0;i<string_len;i++){
        if (tmp[i]=='0') tmp[i]='1';
        else tmp[i]='0';
    }
    return tmp;
}

int find(int sti,string &st,int pos,int idx){
    // printf("find [%d]:%c,cnt=%d\n",idx,a[idx].ch,a[idx].cnt);
    if (pos == string_len){
        // if (a[idx].l_tag==-1) printf("!!!!!!!!!!!!");
        if (a[idx].l_tag==sti){
            return nxt[a[idx].l_tag];
        }
        return a[idx].l_tag;
    }
    int lch = a[idx].lch;
    int rch = a[idx].rch;
    if (lch==0||a[lch].cnt==0) return find(sti,st,pos+1,rch);
    if (rch==0||a[rch].cnt==0) return find(sti,st,pos+1,lch);

    return find(sti,st,pos+1,st[pos]=='0'?lch:rch);
}


int main(){
	// freopen("in3.txt","r",stdin); 
    // scanf("%d%d",&n,&k);
    // init(0,'*');
    // for(int i=0;i<n;i++){
    //     cin>>st[i];
    // }
    // for(int i=0;i<min(n,k+1);i++){
    //     // cout<<"---add "<<i<<endl;
    //     update(i,0,1,1);
    // }
    // for(int i=0;i<n;i++){
    //    int l = i-k-1;
    //    int r = i+k+1;
    //    if (r<n){
    //     //    cout<<"---add "<<r<<endl;
    //        update(r,0,1,1);
    //    }
       
    //    string tmp;
    //    tmp=flap(i);
    // //    cout<<tmp<<endl;
    //    int t = find(i,tmp,0,1);
    //    cout<<t<<endl;

       
    //    if (l>=0){
    //     //    cout<<"---del "<<l<<endl;
    //        update(l,0,1,-1);
    //    }
    // }
	cout << (sizeof(a) >> 20);
    return 0;
}
