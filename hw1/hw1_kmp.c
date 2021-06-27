#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *fp1;
FILE *fp2;
FILE *ans;
int ans_queue[10000];
int cnt = 0;
int str_size =0, pat_size =0;
char str[10000000];
char pat[3000];
int failure[3000];
int main(void){
    fp1 = fopen("string.txt","r"); //string.txt 파일 읽기 모드로 열기
    fp2 = fopen("pattern.txt","r"); //pattern.txt 파일 읽기 모드로 열기
    if(fp1 == NULL || fp2 == NULL)
    {
        printf("The string file does not exist.\n");
        return 0;
    }
    ans = fopen("result_kmp.txt","w"); //result_kmp.txt 파일 쓰기 모드로 열기
    fgets(str,10000000,fp1); //fp1 파일 읽기 str에 저장
    fgets(pat,3000,fp2); //fp2 파일 읽기 pat에 저장
    for(int i = 0; i < 10000000;i++){ //string 길이 계산
        if(str[i]=='\n')
            str[i] = '\0';
        if(str[i]=='\0'){
            str_size = i;
            break;
        }
    }

    for(int i = 0; i < 3000;i++){ //pattern 길이 계산
        if(pat[i]=='\n')
            pat[i] ='\0';
        if(pat[i]=='\0'){
            pat_size = i;
            break;
        }
    }
    failure[0] = 0;
    for(int i = 1; i < pat_size;i++){
        int k = failure[i-1];
        while((pat[i] != pat[k]) && k>=1){
            k = failure[k-1];
        }
        if(pat[i] == pat[k]){
            failure[i] = k+1;
        }
        else{
            failure[i] = 0;
        }
    }
    int pattern = 0, string = 0;
    while(string < str_size){
        if(str[string] == pat[pattern]){
            string++;
            pattern++;
        }
        else if(pattern == 0)
        {
            string++;
        }
        else
        {
            pattern = failure[pattern-1];
        }
        if(pattern >= pat_size){
            ans_queue[cnt] = string - pat_size;
            cnt++;
        }
    }

    //"result_kmp.txt"파일에 출력
    fprintf(ans,"%d",cnt);
    fprintf(ans,"\n");
    for(int i = 0; i < cnt;i++){
        fprintf(ans,"%d ",ans_queue[i]);
    }
    fprintf(ans,"\n");
}
