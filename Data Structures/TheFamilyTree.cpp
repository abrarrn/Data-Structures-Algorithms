/**
A family tree needs to be built. Total member can be from 1~49
Each member will have an id, val and children (at max 3)
Members are added using add_member(id of the parent, new member's id)
    - If addition is possible, return the total value of the family
    - If not, return -1
Members can be removed from the family using remove_member(id of the member)
    - After removal return two values
        - The total value of that member and their children, who will also be removed
        - The current value of the family after their removal
Anytime the value of a member can be known through value_member(id of the member)
    - If the member exists return their value (the total value of that member and their children)
    - If does not exist, return -1
Family head(id - 0) can never be removed
*/

#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

struct Member{
    int id;
    int val;
    Member* children[3];
    Member* par;

    Member(int _id, int _val, Member* _par){
        id = _id;
        val = _val;
        par = _par;
        for(int i=0; i<3; ++i){
            children[i] = nullptr;
        }
    }
};
unordered_map<int, Member*> umap_id_mem;

void add_root(int root_val){
    Member* m = new Member(0, root_val, nullptr);
    umap_id_mem[0] = m;
}

void update_family_value(Member* par, int mem_val){
    par->val += mem_val;
    if(par->par != nullptr){
        update_family_value(par->par, mem_val);
    }
}

int value_member(int mem_id){
    //check: if it is in the family
    if(umap_id_mem.find(mem_id) == umap_id_mem.end()){
        cout<<"Member does not exist in family"<<endl;
        return -1;
    }
    Member* m = umap_id_mem[mem_id];
    return m->val;
}

int add_member(int par_id, int mem_id, int mem_val){
    Member* parent = umap_id_mem[par_id];
    //check: is it already in the family
    if(umap_id_mem.find(mem_id) != umap_id_mem.end()){
        cout<<"Member already exists in family"<<endl;
        return -1;
    }
    //check: is their sibling number less than 3
    else if(parent->children[2] == nullptr){
        for(int i=0; i<3; ++i){
            if(parent->children[i] == nullptr){
                Member* new_member = new Member(mem_id, mem_val, parent);
                umap_id_mem[mem_id] = new_member;
                parent->children[i] = new_member;
                update_family_value(parent, mem_val);
                return value_member(0);
            }
        }
        return -1;
    }
    else{
        cout<<"Parent has already 3 children"<<endl;
        return -1;
    }
}

void remove_child(Member* child){
    if(child->children[0] == nullptr){  //leaf
        umap_id_mem.erase(child->id);
        return;
    }
    for(int i=0; i<3; ++i){
        if(child->children[i] != nullptr){
            remove_child(child->children[i]);
        }
    }
    //clearing children-list
    for(int i=0; i<3; ++i){
        child->children[i] = nullptr;
    }
}

void remove_member(int id){
    Member* m = umap_id_mem[id];
    Member* parent = m->par;
    remove_child(m);
    cout<<"Member to be removed's value in total: "<<m->val<<endl;
    for(int i=0; i<3; ++i){
        if(parent->children[i]->id == id){
            parent->children[i] = nullptr;
            break;
        }
    }
    update_family_value(m->par, -m->val);
    cout<<"After removal, current family value: "<<value_member(0)<<endl;
}

int main()
{
    add_root(5);
    cout<<add_member(0, 1, 3)<<endl;
    cout<<add_member(0, 2, 4)<<endl;
    cout<<add_member(1, 3, 2)<<endl;
    cout<<add_member(1, 5, 3)<<endl;
    cout<<add_member(3, 4, 5)<<endl;
    remove_member(5);
    cout<<value_member(3)<<endl;
    return 0;
}
