#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void reloc(){
    char rec[100],mod[7];char addr[7];
    mod[6] = '\0';addr[6] = '\0';
    int PROGADDR,starting_addr;
    printf("Enter the Progaddr: ");
    scanf("%x",&PROGADDR);
    FILE* abs = fopen("inputabs.txt","r");
    FILE* output = fopen("output.txt","w");
    fseek(abs,0,SEEK_SET);
    fgets(rec,sizeof(rec),abs);
    strncpy(addr,rec+9,6);
    starting_addr = (int) strtol(addr,NULL,16);
    fgets(rec,sizeof(rec),abs);
    while(rec[0] == 'T'){
        strncpy(addr,rec+2,6);
        for(int i = 12; rec[i] != '\n'; i += 7){
            strncpy(mod,rec + i,6);
            fprintf(output,"[%s]: %c%c\n",addr,mod[0],mod[1]);
            sprintf(addr,"%06X",(int) strtol(addr,NULL,16) + 1);
            fprintf(output,"[%s]: %c%c\n",addr,mod[2],mod[3]);
            sprintf(addr,"%06X",(int) strtol(addr,NULL,16) + 1);
            fprintf(output,"[%s]: %c%c\n",addr,mod[4],mod[5]);
            sprintf(addr,"%06X",(int) strtol(addr,NULL,16) + 1);
            if(rec[i + 6] == '\n') break;
        }
    fgets(rec,sizeof(rec),abs);
    }
}
int main(){
    reloc();
    printf("Done\n");
    return(0);
}