#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long int power(int base,int exp){
    long int result=1;
    for(int i=0;i<exp;i++){
        result*=base;
    }
    return result;
}

void all_subseq(int len,char word[len],char subseq[power(2,len)-1][len]){
    if(len==1){
        strcpy(subseq[0],word);
    } else {
        char end[2]={word[len-1],'\0'};
        char substr[len],subsubseq[power(2,len-1)-1][len-1];
        strncpy(substr,&word[0],len-1);
        substr[len-1]='\0';
        strcpy(subseq[0],end);
        subseq[0][1]='\0';
        all_subseq(len-1,substr,subsubseq);
        for(int i=0;i<power(2,len-1)-1;i++){
            strcpy(subseq[2*i+1],subsubseq[i]);
            strcpy(subseq[2*i+2],subsubseq[i]);
            strcat(subseq[2*i+2],end);
        }
    }
}

void all_subseq_wo1(int len,char subseq1[power(2,len)-1][len],char subseq[power(2,len)-1-len][len]){
    int newi=0;
    for(int i=0;i<power(2,len)-1;i++){
        if(strlen(subseq1[i])>1){
            strcpy(subseq[newi],subseq1[i]);
            newi++;
        }
    }
}

void all_unique_substr(int len,char word[len],char substr[(len*(len-1))/2][len]){
    int index=0;
    for(int i=0;i<(len*(len-1))/2;i++){
        substr[i][0]='\0';
    }
    for(int size=2;size<=len;size++){
        for(int start=0;start<=len-size;start++){
            char str[size+1];
            strncpy(str,&word[start],size);
            str[size]='\0';
            int unique=1;
            for(int i=0;i<index;i++){
                if(strcmp(substr[i],str)==0){
                    unique=0;
                    break;
                }
            }
            if(unique){
                strcpy(substr[index],str);
                index++;
            }
        }
    }
}

void all_substr(int len,char word[len],char substr[(len*(len-1))/2][len]){
    int index=0;
    for(int size=2;size<=len;size++){
        for(int start=0;start<len+1-size;start++){
            char str[size];
            strncpy(str,&word[start],size);
            str[size]='\0';
            strcpy(substr[index],str);
            substr[index][size]='\0';
            index++;
        }
    }
}

int isin(char c,char *word){
    for(unsigned k=0;k<strlen(word);k++){
        if(word[k]==c) return k+1;
    }
    return 0;
}

int sim03(char *d,char *k,int subtype){
    char c=97;
    int sum=0;
    for(int i=0;i<26;i++){
        int s1=0;
        int s2=0;
        for(int j=0;j<strlen(d);j++){
            if(d[j]==(c+i)) s1++;
        }
        for(int j=0;j<strlen(k);j++){
            if(k[j]==(c+i)) s2++;
        }
        if(s1&&s2){
            int arr[4]={1,s1,s2,s1*s2};
            sum+=arr[subtype];
        }
    }
    return sum;
}

int substrCount(char *d,char *s){
    int count=0,lend=strlen(d);
    char subseqd1[power(2,lend)-1][lend],subseqd[power(2,lend)-1-lend][lend];
    all_subseq(lend,d,subseqd1);
    all_subseq_wo1(lend,subseqd1,subseqd);
    for(int i=0;i<power(2,lend)-1-lend;i++)
        if(!strcmp(subseqd[i],s)) count++;
    return count;
}

int subseqCount(char *d,char *s){
    int count=0,lend=strlen(d);
    char substrd[lend*(lend-1)/2][lend];
    all_substr(lend,d,substrd);
    for(int i=0;i<lend*(lend-1)/2;i++)
        if(!strcmp(substrd[i],s)) count++;
    return count;
}

int sim47(char *d,char *k,int subtype){
    int lenk=strlen(k),sum=0;
    char unique_k[(lenk*(lenk-1))/2][lenk];
    all_unique_substr(lenk,k,unique_k);
    for(int i=0;unique_k[i][0]!='\0';i++){
        int arr[4]={1,subseqCount(k,unique_k[i]),substrCount(d,unique_k[i]),
                    subseqCount(k,unique_k[i])*substrCount(d,unique_k[i])};
        if(substrCount(d,unique_k[i])&&subseqCount(k,unique_k[i])) sum+=arr[subtype];
    }
    return sum;
}

int getmatch(char *word,char *key){
    int len_word=strlen(word);
    for(int i=0;i<len_word-1;i++){
        int index=isin(word[i],key);
        if(index){
            if(isin(word[i+1],&key[index])){
                return 1;
            }
        }
    }
    return 0;
}

int charCompare(const char* key,const char* word0,const char* word1,int subtype){
    int score0=sim03((char*)word0,(char*)key,subtype);
    int score1=sim03((char*)word1,(char*)key,subtype);
    if(score1!=score0) return score1-score0;
    return strcmp(word0,word1);
}

int strCompare(const char* key,const char* word0,const char* word1,int subtype){
    int score0=sim47((char*)word0,(char*)key,subtype);
    int score1=sim47((char*)word1,(char*)key,subtype);
    if(score1!=score0) return score1-score0;
    return strcmp(word0,word1);
}

void sort(int D,char** candidateStrings,const char* keyword,int (*comparator)(const char*,const char*,const char*,int),int subtype){
    int compareWrapper(const void* a,const void* b){
        return comparator(keyword,*(const char**)a,*(const char**)b,subtype);
    }
    qsort(candidateStrings,D,sizeof(char*),compareWrapper);
}

char** getCandidateStrings(unsigned int D,char** dictionary,char* keyword,unsigned int* numOccurences){
    char** candstrs=NULL;
    *numOccurences=0;
    for(int i=0;i<D;i++){
        if(getmatch(dictionary[i],keyword)){
            candstrs=(char**)realloc(candstrs,((*numOccurences)+1)*sizeof(char*));
            candstrs[*numOccurences]=dictionary[i];
            (*numOccurences)++;
        }
    }
    return candstrs;
}

int main(void){
    int T;

    if(fscanf(stdin,"%d",&T)!=1){
        return 1;
    }

    for(int i=0;i<T;i++){
        char urlin[100],urlout[100];
        sprintf(urlin,"input/input_%d.txt",i);
        sprintf(urlout,"solution/output_%d.txt",i);

        FILE* input=fopen(urlin,"r");
        if(!input){
            continue;
        }

        int D;
        if(fscanf(input,"%d",&D)!=1){
            fclose(input);
            continue;
        }
        fgetc(input);

        char **dict=(char**)calloc(D,sizeof(char*));
        if(!dict){
            fclose(input);
            return 1;
        }

        for(int i=0;i<D;i++){
            dict[i]=(char*)calloc(2,sizeof(char));
            char inpu;
            int j=0;
            while(1){
                if(fscanf(input,"%c",&inpu)==1){
                    if(inpu=='\n') break;
                    dict[i]=(char*)realloc(dict[i],(j+2)*sizeof(char));
                    dict[i][j]=inpu;
                    j++;
                }
            }
            dict[i][j]='\0';
        }
        int L;
        if(fscanf(input,"%d",&L)!=1){
            fclose(input);
            for(int i=0;i<D;i++) free(dict[i]);
            free(dict);
            continue;
        }
        fgetc(input);

        char **keys=(char**)calloc(L,sizeof(char*));
        unsigned int *type=(unsigned int*)calloc(L,sizeof(unsigned int));
        for(int i=0;i<L;i++){
            keys[i]=(char*)calloc(2,sizeof(char));
            char inpu;
            int j=0;
            while(1){
                if(fscanf(input,"%c",&inpu)==1){
                    if(inpu==' ') break;
                    keys[i]=(char*)realloc(keys[i],(j+2)*sizeof(char));
                    keys[i][j]=inpu;
                    j++;
                }
            }
            keys[i][j]='\0';
            fscanf(input,"%u",&type[i]);
            fgetc(input);
        }
        fclose(input);

        FILE* output=fopen(urlout,"w");
        if(!output){
            for(int i=0;i<D;i++) free(dict[i]);
            free(dict);
            for(int i=0;i<L;i++) free(keys[i]);
            free(keys);
            free(type);
            continue;
        }

        for(int i=0;i<L;i++){
            unsigned int numOccurences;
            char** candidates=getCandidateStrings(D,dict,keys[i],&numOccurences);

            if(type[i]<=3){
                sort(numOccurences,candidates,keys[i],charCompare,type[i]);
            } else {
                sort(numOccurences,candidates,keys[i],strCompare,type[i]);
            }

            fprintf(output,"%d\n",numOccurences);
            for(unsigned int j=0;j<numOccurences;j++){
                fprintf(output,"%s",candidates[j]);
                if(!(i==L-1&&j==numOccurences-1)){
                    fprintf(output,"\n");
                }
            }
            free(candidates);
        }
        fclose(output);

        for(int i=0;i<D;i++) free(dict[i]);
        free(dict);
        for(int i=0;i<L;i++) free(keys[i]);
        free(keys);
        free(type);
    }
    return 0;
}