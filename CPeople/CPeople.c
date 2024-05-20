#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_FORMAT ".txt"

typedef struct date{
    int day;
    int month;
    int year;
}date;

typedef struct data{
    char phone[12];
    char name[255];
    char surname[255];
    date date;
}data;

typedef struct CPeople{
    data data;
    struct CPeople* next;
}CPeople;

void add_new_record(CPeople** head, data data){
    CPeople* new = malloc(sizeof(CPeople));
    new->data = data;
    /*(*head)->next = new;*/
    new->next = *head;
    *head = new;
}
int delete_by_id(CPeople** head, int id){
    CPeople* tmp = *head;
    if (id <= 0)
        return -1;
    if (id == 1){
        *head = (*head)->next;
        free(tmp);
        return 0;
    }
    for(int i=1; i<(id-1); i++){
        if (tmp->next == NULL)
            return -1;
        tmp = tmp->next;
    }
    return 0;
}

void free_list(CPeople** head){
    CPeople* tmp_p;
    while(*head != NULL){
        tmp_p = *head;
        *head = (*head)->next;
        free(tmp_p);
    }
    *head = NULL;
}

void print_list(CPeople* head){
    if(head == NULL)
        return;
    CPeople* pointer = head;
    printf("%2s   %11s%15s%15s%19s\n\n", "ID","PHONE","NAME","SURNAME","BIRTHDAY");
    int i = 1;
    while(pointer != NULL) {
        printf("%2d   %11s%15s%15s%15d-%02d-%02d\n", i, pointer->data.phone, pointer->data.name, \
        pointer->data.surname, pointer->data.date.year, pointer->data.date.month, \
        pointer->data.date.day);
        pointer = pointer->next;
        i++;
    }
    printf("\n");
}

int save_to_file(CPeople* head, FILE* file, char* file_name){
    CPeople* pointer = head;
    while(pointer != NULL) {
        fprintf(file,"%s %s %s %d %d %d\n", pointer->data.phone, pointer->data.name, \
        pointer->data.surname, pointer->data.date.year, pointer->data.date.month, \
        pointer->data.date.day);
        pointer = pointer->next;
    }
    fclose(file);
    printf("Book saved to %s\n", file_name);
    return 0;
}

void load_from_file(CPeople** head, FILE* file){
    data record;
    while (fscanf(file, "%s %s %s %d %d %d",\
    record.phone, record.name, record.surname,\
    &record.date.year, &record.date.month, &record.date.day) != EOF)
                  add_new_record(head, record);

}

void flip_records(CPeople* p1, CPeople* p2){
    data tmp = p1->data;
    p1->data = p2->data;
    p2->data = tmp;
}

int compare_by_name(char* name1, char* name2, int order){
    int i = 0;
    while (name1[i] != '\0'){
        if(name1[i] < name2[i]){
            if (order == 2)
                return 0;
            else
                return 1;
        }
        if(name1[i] > name2[i]){
            if (order == 2)
                return 1;
            else
                return 0;
        }
        i++;
    }
    return 0;
}

int compare_by_date(date date1, date date2, int order){
    int res = 0;
    if (date1.year > date2.year)
        res = 1;
    else if (date1.year < date2.year)
        res = 0;
    else if (date1.month > date2.month)
        res = 1;
    else if (date1.month < date2.month)
        res = 0;
    else if (date1.day > date2.day)
        res = 1;
    else if (date1.day < date2.day)
        res = 0;

    if(order == 2){
        if (res)
            return 0;
        else
            return 1;
    }
    return res;

}

int compare(data data1, data data2, int type ,int order){
    if (type == 1)
        return compare_by_name(data1.name, data2.name, order);
    if (type == 2)
        return compare_by_name(data1.surname, data2.surname, order);
    if (type == 3)
        return compare_by_date(data1.date, data2.date, order);
}

void sort_list(CPeople* head, int type, int order){
    CPeople* pointer_i = head;
    CPeople* pointer_j;
    while(pointer_i->next != NULL){
        pointer_j = head;
        while (pointer_j->next != NULL){
            if (compare(pointer_j->data, pointer_j->next->data, type, order)) {
                flip_records(pointer_j, pointer_j->next);
            }
            pointer_j = pointer_j->next;
        }
        pointer_i = pointer_i->next;
    }
}

int book_menu(char* book_name, CPeople** list) {
    int input;
    char tmp;
    while(1){
        printf("Book - %s\n\n", book_name);
        printf("1) Add new record\n");
        printf("2) Delete record\n");
        printf("3) Sort\n");
        printf("4) Save to file\n");
        print_list(*list);
        scanf("%d", &input);
        if (input == 1) {
            printf("Enter phone number (11 digits)\n");
            char phone[12], name[255], surname[255];
            date birth_date;
            data new_data;
            scanf("%11s", new_data.phone);
            printf("Enter name\n");
            scanf("%254s", new_data.name);
            printf("Enter surname\n");
            scanf("%254s", new_data.surname);
            printf("Enter birth date (year month day)\n");
            scanf("%d %d %d", &(birth_date.year), &(birth_date.month), &(birth_date.day));
            new_data.date = birth_date;
            add_new_record(list, new_data);
        }
        if (input == 2){
            printf("How you want to delete record?\n");
            printf("1)By ID\n");
            printf("2)By Name\n");
            printf("3)Back\n\n");
            scanf("%d", &input);
            if(input == 1){
                print_list(*list);
                printf("Enter ID to delete ");
                scanf("%d", &input);
                int res = delete_by_id(list, input);
                if(res == -1){
                    printf("ERROR - false ID");
                }
            }
            continue;
        }
        if (input == 3) {
            int sort_type;
            int sort_order;
            printf("1) Sort by name\n");
            printf("2) Sort by surname\n");
            printf("3) Sort by birthday\n");
            scanf("%d", &sort_type);
            printf("1) Ascending sort\n");
            printf("2) Descending sort\n");
            scanf("%d", &sort_order);
            sort_list(*list, sort_type, sort_order);
        }
        if (input == 4) {
            if (*list == NULL) {
                printf("Can't save, book is empty\n");
                continue; 
            }
            FILE *file;
            char file_name[255];
            memset(file_name, 0, sizeof(file_name));
            strcat(file_name, book_name);
            strcat(file_name, FILE_FORMAT);
            file = fopen(file_name, "r");
            file = fopen(file_name, "w");
            save_to_file(*list, file, file_name);
            return 0;
        }
    }
}

void main_menu(CPeople** list){
    int input;
    char tmp;
    char book_name[255];
    printf("1) Create new book\n");
    printf("2) Open book from file\n");
    scanf("%d", &input);
    if (input == 1) {
        printf("Enter name of new book\n");
        scanf("%254s", book_name);
        book_menu(book_name, list);
    }
    if (input == 2){
        printf("Enter name of the book to open\n");
        scanf("%254s", book_name);
        FILE* file;
        char file_name[255];
        memset(file_name, 0, sizeof(file_name));
        strcat(file_name, book_name);
        strcat(file_name, FILE_FORMAT);
        file = fopen(file_name, "r");
        if (file == NULL){
            printf("No such book in the directory\n");
            return;
        }
        load_from_file(list, file);
        book_menu(book_name, list);
    }
}

int main() {
    CPeople *list = NULL;
    main_menu(&list);
    return 0;
}