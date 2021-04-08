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

int main(void){
    fp1 = fopen("string.txt","r"); //string.txt 파일 읽기 모드로 열기
    fp2 = fopen("pattern.txt","r"); //pattern.txt 파일 읽기 모드로 열기
    if(fp1 == NULL || fp2 == NULL)
    {
        printf("The string file does not exist.\n");
        return 0;
    }
    ans = fopen("result_naive.txt","w"); //result_naive.txt 파일 쓰기 모드로 열기
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
            pat[i] = '\0';
        if(pat[i]=='\0'){
            pat_size = i;
            break;
        }
    }
    for(int i = 0; i<str_size-pat_size+1;i++){
        int k = 0;
        for(int j = i; k < pat_size;j++,k++){
            if(pat[k]!=str[j]){
                break;
            }
        }
        if(k==pat_size) //패턴의 마지막 글자까지 같으면 일치!
        {
            ans_queue[cnt] = i; //ans_queue에 일치하는 pattern의 시작 index 저장
            cnt++; //count 를 1 증가
        }
    }
    //"result_naive.txt"파일에 출력
    fprintf(ans,"%d",cnt);
    fprintf(ans,"\n");
    for(int i = 0; i < cnt;i++){
        fprintf(ans,"%d ",ans_queue[i]);
    }
    fprintf(ans,"\n");
}
