#include<iostream>

using namespace std;

int h[100][100],c[100][100];
int hi[4]={-1,1,0,0},hj[4]={0,0,-1,1};

int main() {
    int n,m,i,j,k,br=0;
    bool l;
    char ch;
    cin >> n >> m;
    for(i=1;i<=n;++i) {
        h[0][i]=h[i][0]=h[n+1][i]=h[i][m+1]=0;
        for(j=1;j<=m;j++) {
            cin>>ch;
            if(ch=='H')h[i][j]=1;
            else if(ch=='O')h[i][j]=2;
            else if(ch=='N')h[i][j]=3;
            else if(ch=='C')h[i][j]=4;
            else {
                h[i][j]=0;
                br++;
            }
        }
    }
    if(br==n*m) {
        cout<<"Invalid\n";
        return 0;
    }
    do {
        memset(c,0,sizeof(c));
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                if(h[i][j]!=0)
                    for(k=0;k<4;k++)
                        c[i+hi[k]][j+hj[k]]++;
        l=0;
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
                if(c[i][j]==h[i][j] && c[i][j]!=0)
                {
                    for(k=0;k<4;k++)
                        if(h[i+hi[k]][j+hj[k]])
                            h[i+hi[k]][j+hj[k]]--;
                    l=1;
                    h[i][j]=0;
                    break;
                }
            if(l==1)break;
        }
        if(l==1)continue;
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
                if(h[i][j]==1 && c[i][j]>1)
                {
                    h[i][j+1]--;
                    h[i][j]=0;
                    l=1;
                    break;
                }
                else if(h[i][j]!=0)
                {
                    cout<<"Invalid\n";
                    return 0;
                }
            if(l==1)break;
        }
    }
    while(l);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(h[i][j]!=0)l=1;
    if(l)cout<<"Invalid\n";
    else cout<<"Valid\n";
}