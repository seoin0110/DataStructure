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
    fp1 = fopen("string.txt","r"); //string.txt ���� �б� ���� ����
    fp2 = fopen("pattern.txt","r"); //pattern.txt ���� �б� ���� ����
    if(fp1 == NULL || fp2 == NULL)
    {
        printf("The string file does not exist.\n");
        return 0;
    }
    ans = fopen("result_naive.txt","w"); //result_naive.txt ���� ���� ���� ����
    fgets(str,10000000,fp1); //fp1 ���� �б� str�� ����
    fgets(pat,3000,fp2); //fp2 ���� �б� pat�� ����
    for(int i = 0; i < 10000000;i++){ //string ���� ���
        if(str[i]=='\n')
            str[i] = '\0';
        if(str[i]=='\0'){
            str_size = i;
            break;
        }
    }
    for(int i = 0; i < 3000;i++){ //pattern ���� ���
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
        if(k==pat_size) //������ ������ ���ڱ��� ������ ��ġ!
        {
            ans_queue[cnt] = i; //ans_queue�� ��ġ�ϴ� pattern�� ���� index ����
            cnt++; //count �� 1 ����
        }
    }
    //"result_naive.txt"���Ͽ� ���
    fprintf(ans,"%d",cnt);
    fprintf(ans,"\n");
    for(int i = 0; i < cnt;i++){
        fprintf(ans,"%d ",ans_queue[i]);
    }
    fprintf(ans,"\n");
}
