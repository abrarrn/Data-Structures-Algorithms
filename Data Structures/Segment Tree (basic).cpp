#include<bits/stdc++.h>
using namespace std;
#define n 8

int arr[n];
int seg[4*n];

void build(int ind, int b, int e){
    if(b == e){
        seg[ind] = arr[b];
        return;
    }
    int m = (b+e)/2;
    build(2*ind+1, b, m);
    build(2*ind+2, m+1, e);
}

//although update does not return anything, maintains/updates the seg array (last line)
//point update ultimately goes down to the leaf
void update_point(int ind, int b, int e, int i, int val){
    //out of range
    if(i < b || e < i){
        return;
    }
    //leaf and it is the desired index
    if(b == e && b == i){
        seg[ind] = val;
        return;
    }
    int m = (b+e)/2;
    update_point(2*ind+1, b, m, i, val);
    update_point(2*ind+2, m+1, e, i, val);
    seg[ind] = seg[2*ind+1] + seg[2*ind+2];
}

//using this technique, range's each index's also goes down to their leaves (not that much efficient)
void update_range(int ind, int b, int e, int l, int r, int val){
    //out of range
    if(e < l || r < b){
        return;
    }
    //inside range; need to ensure leaf
    if(l <= b && e <= r && b == e){
        seg[ind] = val;
        return;
    }
    int m = (b+e)/2;
    update_range(2*ind+1, b, m, l, r, val);
    update_range(2*ind+2, m+1, e, l, r, val);
    seg[ind] = seg[2*ind+1] + seg[2*ind+2];
}

int query(int ind, int b, int e, int l, int r){
    //out of range
    if(e<l || r<b){
        return 0;
    }
    //between range
    if(l<=b && e<=r){
        return seg[ind];
    }
    int m = (b+e)/2;
    return query(2*ind+1, b, m, l, r) + query(2*ind+2, m+1, e, l, r);
}

int main()
{
    memset(arr, 0, sizeof(arr));
    memset(seg, 0, sizeof(seg));
    //build populates seg from arr; not necessary if arr does not have initial values
    build(0, 0, n-1);

    //point update (index of the seg, begin, end, index to update, the new value)
    update_point(0, 0, n-1, 3, 2);
    update_point(0, 0, n-1, 4, 5);
    cout<<query(0, 0, n-1, 3, 4)<<endl;
    update_range(0, 0, n-1, 0, 3, 1);
    cout<<query(0, 0, n-1, 0, 3)<<endl;
    cout<<query(0, 0, n-1, 0, 7);
    return 0;
}
