#include <iostream>
#include <vector>
#include <set>

struct data {
  int num;
  int x;
  int y;
};

bool MySort (const data &p1, const data &p2){
  return p1.num < p2.num;
}

int table[9][9];
int fixnum;
std::vector<data > vec;

// vecのうちid未満のインデックスまでは確定しているとする。
bool dfs(int id){
  if (id==81-fixnum) {
    return true;
  }
  auto entry = vec[id];
  int i = entry.x;
  int j = entry.y;
  std::set<int > ng;
  for (int k=0; k<9; k++) {
    if (table[i][k]!=0) ng.insert(table[i][k]);
  }
  for (int k=0; k<9; k++) {
    if (table[k][j]!=0) ng.insert(table[k][j]);
  }
  for (int k=(i/3)*3; k<(i/3+1)*3; k++) {
    for (int l=(j/3)*3; l<(j/3+1)*3; l++) {
      if (table[k][l]!=0) ng.insert(table[k][l]);
    }
  }
  std::vector<int> ok;
  for (int k=1; k<=9; k++) {
    auto itr  = ng.find(k);
    if (itr==ng.end()) ok.push_back(k);
  }
  bool result = false;
  if (ok.size()==0) {
    result=false;
  } else if (ok.size()==1) {
    table[i][j] = ok[0];
    result = dfs(id+1);
  } else {
    for (int k : ok) {
      table[i][j] = k;
      result = dfs(id+1);
      if (result) break;
    }
  }
  if(!result) table[i][j] = 0;
  return result;
}

int main() {
  fixnum=0;
  std::string s;
  std::set<int > no[9][9];
  for (int i=0; i<9; i++) {
    std::cin >> s;
    for (int j=0; j<9; j++) {
      table[i][j] = int(s[j]) - int('0');
      if (table[i][j]!=0) fixnum++;
    }
  }
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (table[i][j]!=0) continue;
      for (int k=0; k<9; k++) {
        if (table[i][k]!=0) no[i][j].insert(table[i][k]);
      }
      for (int k=0; k<9; k++) {
        if (table[k][j]!=0) no[i][j].insert(table[k][j]);
      }
      for (int k=(i/3)*3; k<(i/3+1)*3; k++) {
        for (int l=(j/3)*3; l<(j/3+1)*3; l++) {
          if (table[k][l]!=0) no[i][j].insert(table[k][l]);
        }
      }
    }
  }

  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (table[i][j]==0) {
        vec.push_back((data){(int)9-(int)no[i][j].size(), i, j});
      }
    }
  }
  // 候補の数字の数=numが小さい順にソートする
  std::sort(vec.begin(), vec.end(), MySort);
  dfs(0);
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      printf("%d",table[i][j]);
    }
    printf("\n");
  }
  return 0;
}

