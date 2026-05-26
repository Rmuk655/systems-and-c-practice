#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// TODO: Implement your logic
int main(void) {
    int TT;
    scanf("%d",&TT);
    for(int i=0;i<TT;i++){
        char urlin[100];
        sprintf(urlin,"input/input_%d.txt",i);
        char urlout[100];
        sprintf(urlout,"solution/output_%d.txt",i);
        FILE* input=fopen(urlin,"r");// TODO: Implement you logic
        FILE *output1=fopen(urlout,"w");
        fclose(output1);
        int T;
        fscanf(input,"%d",&T);
        char prev[100], curr[100]="";
        for(int i=1;i<=T;i++){
            char func[7];
            fscanf(input,"%s",func);
            if(!strcmp(func,"INSERT")){
                strcpy(prev,curr);
                FILE* output = fopen(urlout,"a");
                char app[100];
                fscanf(input," %s",app);
                strcat(curr,app);
                fputs(app,output);
                fclose(output);
            }
            else if(!strcmp(func,"DELETE")){
                strcpy(prev,curr);

                int x;
                fscanf(input," %d",&x);
                FILE* output1 = fopen(urlout,"r");
                char delend[100];
                fscanf(output1,"%s",delend);
                strncpy(curr,delend,strlen(delend)-x);
                curr[strlen(delend)-x]='\0';
                fclose(output1);
                FILE* output2 = fopen(urlout,"w");
                fputs(curr,output2);
                fclose(output2);
            }
            else if((!strcmp(func, "UNDO"))||(!strcmp(func, "REDO"))){
                char temp[100];
                strcpy(temp,curr);
                strcpy(curr,prev);
                strcpy(prev,temp);
                FILE *output = fopen(urlout,"w");
                fputs(curr,output);
                fclose(output);
            }
        }
        if(strlen(curr)==0){
            FILE* output = fopen(urlout,"w");
            fprintf(output,"EMPTY");
            fclose(output);
        }
        fclose(input);
    }
    return 0;
}
