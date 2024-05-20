void insert_symb(char* str, int lenght, int m, char symb){
    char tmp1, tmp2;
    for (int i = m; i <= lenght; i++){
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
    str[lenght + 1] = '\0';
}
void delete_symb(char* str, int lenght, int m){
    for (int i = m; i < (lenght-1); i++)
            str[i] = str[i + 1];
    str[lenght-1] = '\0';
}

void correct_string(char* str, int lenght){
    if ((int)str[0] >= 97 && (int)str[0] <= 122)
        str[0] -= 32;

    for (int i = 0; i < lenght; i++){
        if (str[i] == '.' || str[i] == ','){
            insert_symb(str, lenght, i + 1, ' ');
            i++;
        }
        if ((str[i] == str[i + 1]) && (str[i] == ' ')){
            delete_symb(str, lenght, i);
            i--;
        }
        if ((str[i] == ' ')&&((str[i+1] == '.') || (str[i+1] == ','))){
            delete_symb(str, lenght, i);
            i--;
        }
        if(((int)str[i+2] >= 65 && (int)str[i+2] <= 90) && str[i] != '.')
            str[i+2] += 32; 
        if ((str[i] == '.') && (int)str[i+2] >= 97 && (int)str[i+2] <= 122)
            str[i+2] -= 32;
    }
}
