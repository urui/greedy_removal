#include<iostream>
#include<vector>
#include<cassert>
#include<algorithm>
#include<set>
#include<list>
using namespace std;
typedef pair<int,int> edge;


/**
* split関数
* @param string str 分割したい文字列
* @param string delim デリミタ
* @return list<string> 分割された文字列
*/
list<string> split(string str, string delim)
{
    list<string> result;
    int cutAt;
    while( (cutAt = str.find_first_of(delim)) != str.npos )
    {
        if(cutAt > 0)
        {
            result.push_back(str.substr(0, cutAt));
        }
        str = str.substr(cutAt + 1);
    }
    if(str.length() > 0)
    {
        result.push_back(str);
    }
return result;
}

vector < pair<int,int> > pairread()
 {
  ifstream ifs("ibarakinput");
  string str;

    if(ifs.fail()) {
      cerr << "File do not exist.\n";
	           }
  vector < pair<int,int> > reader;
  string a;
  string b;

    while(getline(ifs,str)){
      list<string> strList = split(str, ",");
      string a = strList.front();
      string b = strList.back();
      cout << "a:" << a << "   b:" << b << endl;
      reader.push_back(make_pair(atoi(a.c_str()),atoi(b.c_str())));
      strList.clear();
	}

  ifs.close();
  return reader;
}


vector<edge> greedy_removal(int n, vector<edge> g){
  vector<int> deg(n,0);
  vector< list<int> > adj_list(n);
  for(edge e : g){
    deg[e.first]++; deg[e.second]++;
    adj_list[e.first].push_back(e.second);
    adj_list[e.second].push_back(e.first);
  }

  vector<edge> res;
  set<int> frontier;

  for(;;){
    int v = -1;
    cout << "frontier size:" << frontier.size() << endl;
    for(int x : frontier){
      if( v<0 || deg[v] > deg[x] )v = x;
    }

    int u = -1;
    if(v<0){
      //case: frontier is empty
      for(int i=0;i<n;i++){
	if(deg[i]>=0 && (u<0 || deg[u] > deg[i]) )u = i;
      }
      if(u<0)break;
    }else{
      for(int x : adj_list[v]){
	if(deg[x]>=0 && frontier.count(x)==0 && (u<0 || deg[u] > deg[x]))u = x;
      }
    }

    vector< pair<int,int> > priority;
    for(int x : adj_list[u]){
      if(frontier.count(x)){
	priority.push_back( make_pair(deg[x],x) );
        deg[x]--;
	if(deg[x]==0){
	  frontier.erase(x); deg[x]--;
	}
      }else deg[x]--;
    }
    sort(priority.begin(),priority.end());

    for(auto p : priority){
      res.push_back( make_pair(u, p.second) );
    }

    if(deg[u])frontier.insert(u);
    else deg[u]--;
  }

  return res;
}

int main(){
  int n,m;
  cin >> n >> m;
  vector<edge> g;
  for(int i=0;i<m;i++){
    int a, b;
    cin >> a >> b; a--; b--;
    g.push_back( make_pair(a,b) );
  }

  cout << n << " " << m << endl;
  vector<edge> res = greedy_removal(n,g);
  for(edge e : res){
    cout << e.first+1 << " " << e.second+1 << endl;
  }
}
