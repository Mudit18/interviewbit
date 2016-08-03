//Runtime error

int differ(string a,string b){
    if(a.size()!=b.size()){
        return 1;
    }
    int cnt=0;
    for(int i=0;i<a.size();i++){
        if(a[i]!=b[i]){
            cnt++;   
        }
        if(cnt>1){
            return 0;
        }
    }
    return 1;
}

vector<vector<string> > mapper(int length,vector<int> visited,vector<string> dict,map<string,int> m,string end,string start,vector<int> parent[],int p){
    vector<vector<string> > res,temp;
    //cout<<dict[p]<<endl;
    if(length==0 || visited[p]==1){
        return res;
    }
    visited[p]=1;
    length--;
    if(parent[p].size()==0){
        vector<string> v;
        v.push_back(dict[p]);
        res.push_back(v);
        return res;
    }
    for(int i=0;i<parent[p].size();i++){
        temp=mapper(length,visited,dict,m,end,start,parent,parent[p][i]);
        if(temp.size()==0){
            vector<string> v;
            v.push_back(dict[p]);
            res.push_back(v);
        }
        for(int j=0;j<temp.size();j++){
            temp[j].push_back(dict[p]);
            res.push_back(temp[j]);
        }
    }
    return res;
}

vector<vector<string> > ladder(string start, string end, vector<string> &dictV) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
    map<string, int > m;
    if(start.compare(end)==0){
        //return 1;
        vector<vector<string> > v;
        vector<string> temp;
        temp.push_back(start);
        v.push_back(temp);
        return v;
    }
    if(differ(start,end)){
        //return 2;
        vector<vector<string> > res;
        vector<string> v;
        v.push_back(start);
        v.push_back(end);
        res.push_back(v);
        return res;
    }
    vector<int> graph[dictV.size()];
    int i;
    for(i=0;i<dictV.size();i++){
        m[dictV[i]]=i;
    }
    for(i=0;i<dictV.size()-1;i++){
        for(int j=i+1;j<dictV.size();j++){
            if(differ(dictV[i],dictV[j])){
                graph[m[dictV[i]]].push_back(m[dictV[j]]);
                graph[m[dictV[j]]].push_back(m[dictV[i]]);
            }
        }
    }
    queue<int> q;
    int d[dictV.size()];
    vector<int> parent[dictV.size()];
    for(int j=0;j<dictV.size();j++){
        d[j]=0;
    }
    q.push(m[start]);
    d[m[start]]=1;
    while(q.size()!=0){
        int p=q.front();
        q.pop();
        for(int j=0;j<graph[p].size();j++){
            if(d[graph[p][j]]==0){
                //cout<<p<<" "<<graph[p][j]<<endl;
                d[graph[p][j]]=d[p]+1;
                parent[graph[p][j]].push_back(p);
                q.push(graph[p][j]);
            }else{
                int flag=0;
                for(int k=0;k<parent[p].size();k++){
                    if(parent[p][k]==graph[p][j]){
                        flag=1;
                    }
                }
                if(flag==0)
                    parent[graph[p][j]].push_back(p);
            }
        }
    }
    vector<vector<string> > res;
    vector<string> v;
    if(d[m[end]]==0){
        return res;
    }
    vector<int> visited (dictV.size(),0);
    res=mapper(d[m[end]],visited,dictV,m,end,start,parent,m[end]);
    return res;
}

vector<vector<string> > Solution::findLadders(string start, string end, vector<string> &dict) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
    vector<vector<string> > v=ladder(start,end,dict);
    /*for(int i=0;i<v1.size();i++){
        cout<<v1[i]<<endl;
    }*/
    set<vector<string> > s;
    vector<vector<string> > res;
    for(int i=0;i<v.size();i++){
        if(v[i][0].compare(start)==0)
            s.insert(v[i]);
    }
    res.clear();
    for(set<vector<string> >::iterator i=s.begin();i!=s.end();i++){
        res.push_back(*i);
    }
    return res;
}
