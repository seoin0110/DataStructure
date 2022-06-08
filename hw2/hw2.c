#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

FILE *fp;
FILE *ans;
char str[8];
int ins;
float run_time;

int min[1000001];
int max[1000001];
int *temp;
int n = 0;
int main(int argc,char *argv[]){
  run_time = clock();
  if (argc == 1)
  {
    printf("usage: ./hw2 input_filename\n");
    return 0;
  }
  fp = fopen(argv[1],"r");
  if(fp == NULL)
  {
    printf("The input file does not exist.\n");
    return 0;
  }
  ans = fopen("hw2_result.txt","w");

  while(fscanf(fp,"%s",str)!=EOF){
    if(strcmp(str,"INSERT")==0){
      fscanf(fp,"%d",&ins); //insert 될 숫자 ins에 저장
      int i,j;
      //insert 구현
      n++;
      i = n;
      j = n;
      while((i!=1)&& (ins>max[i/2])){
        max[i] = max[i/2];
        i /= 2;
      }
      max[i] = ins;
      while((j!=1)&& (ins<min[j/2])){
        min[j] = min[j/2];
        j /= 2;
      }
      min[j] = ins;
    }
    else if(strcmp(str,"ASCEND")==0){
      //오름차순 구현
      int tmp = n;
      int j;
      temp = malloc(sizeof(int)*(n+1));
      for(int i = 0; i <n;i++){
        temp[i+1] = min[i+1];
      }
      for(int i = 0; i <n;i++){
        fprintf(ans,"%d ",temp[1]);
        j = temp[tmp];
        temp[1] = j;
        tmp--;
        int parent = 1;
        int child = 2;
        while(child<=tmp){
          if(child<tmp && temp[child]>temp[child+1])child++;
          if(j<=temp[child])break;
          temp[parent] = temp[child];
          parent = child;
          child = child*2;
        }
        temp[parent] = j;
      }
      fprintf(ans,"\n");
      free(temp);
    }
    else if(strcmp(str,"DESCEND")==0){
      //내림차순 구현
      int tmp = n;
      int j;
      temp = malloc(sizeof(int)*(n+1));
      for(int i = 0; i <n;i++){
        temp[i+1] = max[i+1];
      }
      for(int i = 0; i <n;i++){
        fprintf(ans,"%d ",temp[1]);
        j = temp[tmp];
        temp[1] = j;
        tmp--;
        int parent = 1;
        int child = 2;
        while(child<=tmp){
          if(child<tmp && temp[child]<temp[child+1])child++;
          if(j>=temp[child])break;
          temp[parent] = temp[child];
          parent = child;
          child = child*2;
        }
        temp[parent] = j;
      }
      fprintf(ans,"\n");
      free(temp);
    }
  }
  run_time = (float)((clock() - run_time)/CLOCKS_PER_SEC);
  printf("output written to hw2_reult.txt.\n");
  printf("running time: %f seconds\n",run_time);
}
