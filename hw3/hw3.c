#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

FILE *fp;
FILE *ans;
float run_time;

typedef struct _st{
  int a;
  int b;
  int c;
}st;

int a,b,c;
int e, v;
int answer = 0;
st min[50000001];
int par[10001];
int find(int a){
  if(par[a]<0)return a;
  return par[a] = find(par[a]);
}
bool merge(int a, int b){
  a = find(a);
  b = find(b);
  if(a == b) return false;
  else{
    par[b] = a;
    return true;
  }
}

int main(int argc,char *argv[]){
  run_time = clock();
  if (argc == 1)
  {
    printf("usage: ./hw3 input_filename\n");
    return 0;
  }
  fp = fopen(argv[1],"r");
  if(fp == NULL)
  {
    printf("The input file does not exist.\n");
    return 0;
  }
  ans = fopen("hw3_result.txt","w");
  fscanf(fp,"%d %d",&v, &e);
  for(int i =0; i <= v;i++){
    par[i] = -1;
  }
  for(int k = 1; k <= e;k++){
    fscanf(fp,"%d %d %d",&a, &b, &c);
    int j;
    //insert 구현
    j = k;
    while((j!=1)&& (c<min[j/2].c)){
      min[j] = min[j/2];
      j /= 2;
    }
    min[j].a = a;
    min[j].b = b;
    min[j].c = c;
  }
  int n = 0;
  int num = 1;
  st j;
  int edge = e;
  while(n < v-1 && num <= edge){
    if(merge(min[1].a,min[1].b)){
      fprintf(ans,"%d %d %d\n",min[1].a,min[1].b,min[1].c);
      answer += min[1].c;
      n++;
    }
    j = min[e];
    min[1] = j;
    e--;
    int parent = 1;
    int child = 2;
    while(child<=e){
      if(child<e && min[child].c>min[child+1].c)child++;
      if(j.c<=min[child].c)break;
      min[parent] = min[child];
      parent = child;
      child = child*2;
    }
    min[parent] = j;
    num++;
  }
  if(n != v-1){
    fprintf(ans,"%d\nDISCONNECTED\n",answer);
  }
  else{
    fprintf(ans,"%d\nCONNECTED\n",answer);
  }

  run_time = (float)((clock() - run_time)/CLOCKS_PER_SEC);
  printf("output written to hw3_result.txt.\n");
  printf("running time: %f seconds\n",run_time);
}
