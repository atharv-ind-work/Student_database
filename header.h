#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 1. Handle Headers first
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif  // This closes the header section

// 2. Define function after headers are closed
void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif // No extra letters here!
}

typedef struct student
{
    int rollno;
    char name[20];
    float marks;
    struct student *next;
}sll;
void add_new_record(sll **,int *);
void show_list(sll *);
void free_memory(sll *);
void save_file(sll *);
void modify_rec(sll *);
void sort_by(sll *);
void sort_by_name(sll *);
void sort_by_marks(sll *);
int count_node(sll *);
void rev_list(sll **);
void wait_for_enter(void);
void delete_node(void);
void del_spec_node(void);
void del_node_rollno(sll **);
void del_all_node(sll **);
void del_node_name(sll **);
void mod_by_rollno(sll **);
void mod_by_name(sll **);
void sort_by_rollno(sll *pptr);
//void clear_screen(void);
