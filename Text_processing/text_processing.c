#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LEN 100

void insert_symb(char* str, int m, char symb){
    char tmp1, tmp2;
    for (int i = m; i <= MAX_LEN; i++){
        if (i == m){
            tmp1 = str[i];
            str[i] = symb;
            tmp2 = str[i + 1];
            str[i + 1] = tmp1;
        }
        if (i > (m+1)){
            tmp1 = str[i];
            str[i] = tmp2;
            tmp2 = str[i + 1];
            str[i + 1] = tmp1;
            i++;
        }
    }
    str[MAX_LEN + 1] = '\0';
}


void delete_symb(char* str, int m){
    for (int i = m; i < (MAX_LEN-1); i++)
            str[i] = str[i + 1];
    str[MAX_LEN-1] = '\0';
}
void correct_string(char* str){
    if ((int)str[0] >= 97 && (int)str[0] <= 122)
        str[0] -= 32;

    for (int i = 0; i < MAX_LEN; i++){
        if (str[i] == '.' || str[i] == ','){
            insert_symb(str, i + 1, ' ');
            i++;
        }
        if ((str[i] == str[i + 1]) && (str[i] == ' ')){
            delete_symb(str, i);
            i--;
        }
        if ((str[i] == ' ')&&((str[i+1] == '.') || (str[i+1] == ','))){
            delete_symb(str, i);
            i--;
        }
        if(((int)str[i+2] >= 65 && (int)str[i+2] <= 90) && str[i] != '.')
            str[i+2] += 32; 
        if ((str[i-1] == '.')&&((int)str[i+1] >= 97 && (int)str[i+1] <= 122))
            str[i+1] -= 32;
    }
}


int main(){
    char str[MAX_LEN];
    printf("Enter string:\n");
    fgets(str, sizeof(str), stdin);
    correct_string(str);
    printf("RESULT: %s\n", str);
}

//