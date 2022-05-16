#include <bits/stdc++.h>

using namespace std;

int getinvcnt(vector<int> arr){
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i+1; j < 9; j++)
            if (arr[j] && arr[i] &&  arr[i] > arr[j]) inv_count++;
    return inv_count;
}

bool isSolvable(vector<vector<int>> puzzle){
    vector<int> v;
    for(auto g: puzzle) for(auto p: g) if(p) v.push_back(p);
    int invcnt = getinvcnt(v);
    return (invcnt%2==0);
}

int manhattan_dist(vector<vector<int>> goal,int a,int b,int c){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(goal[i][j]==a){
                return abs(b-i)+abs(c-j);
            }
        }
    }
    return 0;
}

void print(vector<vector<vector<int>>> ans){
    cout<<"There are minimum "<<ans.size()<<" steps to reach goal state\n\n";
    for(int k=0;k<ans.size();k++){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                cout<<ans[k][i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n\n";
    }
}

void solve(vector<vector<int>> puzzle,vector<vector<int>> goal){
    vector<vector<vector<int>>> ans;
    int i,j,k,b,c,a;
    while(1){
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                if(!puzzle[i][j]){
                    b=i;
                    c=j;
                    break;
                }
            }
        }
        vector<vector<int>> up=puzzle,down=puzzle,left=puzzle,right=puzzle;
        if(b==0){
            if(c==0){
                swap(right[0][0],right[0][1]);
                swap(down[0][0],down[1][0]);
            }else if(c==1){
                swap(right[0][1],right[0][2]);
                swap(down[0][1],down[1][1]);
                swap(left[0][1],left[0][0]);
            }else{
                swap(down[0][2],down[1][2]);
                swap(left[0][1],left[0][2]);
            }
        }else if(b==1){
            if(c==0){
                swap(right[1][0],right[1][1]);
                swap(down[1][0],down[2][0]);
                swap(up[1][0],up[0][0]);
            }else if(c==1){
                swap(right[1][1],right[1][2]);
                swap(down[1][1],down[2][1]);
                swap(left[1][1],left[1][0]);
                swap(up[1][1],up[0][1]);
            }else{
                swap(down[1][2],down[2][2]);
                swap(left[1][1],left[1][2]);
                swap(up[1][2],up[0][2]);
            }
        }else{
            if(c==0){
                swap(right[2][0],right[2][1]);
                swap(up[2][0],up[1][0]);
            }else if(c==1){
                swap(right[2][1],right[2][2]);
                swap(up[2][1],up[1][1]);
                swap(left[2][1],left[2][0]);
            }else{
                swap(up[2][2],up[1][2]);
                swap(left[2][1],left[2][2]);
            }
        }

        int mup=INT_MAX,mdn=INT_MAX,mlt=INT_MAX,mrt=INT_MAX;
        if(puzzle!=up){
            mup=0;
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(up[i][i]) mup+=manhattan_dist(goal,up[i][j],i,j);
                }
            }
        }
        if(puzzle!=down){
            mdn=0;
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(down[i][i]) mdn+=manhattan_dist(goal,down[i][j],i,j);
                }
            }
        }
        if(puzzle!=left){
            mlt=0;
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(left[i][i]) mlt+=manhattan_dist(goal,left[i][j],i,j);
                }
            }
        }
        if(puzzle!=right){
            mrt=0;
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(right[i][i]) mrt+=manhattan_dist(goal,right[i][j],i,j);
                }
            }
        }
        if(mlt==0){
            ans.push_back(left);
            print(ans);
            return;
        }
        if(mrt==0){
            ans.push_back(right);
            print(ans);
            return;
        }
        if(mup==0){
            ans.push_back(up);
            print(ans);
            return;
        }
        if(mdn==0){
            ans.push_back(down);
            print(ans);
            return;
        }
        int mi = min(min(mup,mdn),min(mlt,mrt));
        if(mi==mup){
            ans.push_back(up);
            puzzle=up;
        }else if(mi==mdn){
            ans.push_back(down);
            puzzle=down;
        }else if(mi==mlt){
            ans.push_back(left);
            puzzle=left;
        }else{
            ans.push_back(right);
            puzzle=right;
        }


    }
}

int main()
{
    vector<vector<int>> puzzle(3,vector<int> (3)),goal(3,vector<int> (3));
    int i,j;
    cout<<"Enter initial state \n";
    for(i=0;i<3;i++) for(j=0;j<3;j++) cin>>puzzle[i][j];
    cout<<"Enter goal state \n";
    for(i=0;i<3;i++) for(j=0;j<3;j++) cin>>goal[i][j];
    if(!isSolvable(puzzle)) cout<<"Puzzle is not solvable";
    else{
        cout<<"Puzzle is solvable\n\n";
        solve(puzzle,goal);
    }

    return 0;
}

