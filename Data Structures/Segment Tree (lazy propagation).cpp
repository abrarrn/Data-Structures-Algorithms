#include<bits/stdc++.h>
using namespace std;
#define n 8

int seg[n*4];
int prop[n*4];

void update_range(int ind, int b, int e, int l, int r, int val){
    if(e < l || r < b)  return;
    if(l <= b && e <= r){
        seg[ind] += (e-b+1)*val;
        prop[ind] += val;
        return;
    }
    int m = (b+e)/2;
    update_range(2*ind+1, b, m, l, r, val);
    update_range(2*ind+2, m+1, e, l, r, val);
    seg[ind] = seg[2*ind+1] + seg[2*ind+2] + (e-b+1)*prop[ind];
}

int query(int ind, int b, int e, int l, int r, int carry = 0){
    if(e < l || r < b)  return 0;
    if(l <= b && e <= r){
        return seg[ind] + (e-b+1)*carry;
    }
    int m = (b+e)/2;
    return query(2*ind+1, b, m, l, r, carry + prop[ind])+
            query(2*ind+2, m+1, e, l, r, carry + prop[ind]);
}

int main()
{
    memset(seg, 0, sizeof(seg));
    memset(prop, 0, sizeof(prop));
    update_range(0, 0, n-1, 1, 4, 3);
    update_range(0, 0, n-1, 4, 7, 3);
    cout<<query(0, 0, n-1, 0, n-1);
    return 0;
}
