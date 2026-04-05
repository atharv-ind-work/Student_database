#include"header.h"
sll *headptr=0;
int main()
{
    int op,roll_count=1;
    
    char choice;
    while(1)
    {
        clear_screen();
        printf("\t\t+-----------------------------------------------------------------------+\n");
        printf("\t\t|\t\t\tSTUDENT RECORD DATABASE\t\t\t\t|\n");
        printf("\t\t+-----------------------------------------------------------------------+\n");
        printf("\t\t|\t\t\t\t\t\t\t\t\t|\n");
        printf("\t\t|\t1. Add new record\t\t\t\t\t\t|\n\t\t|\t2. Delete a record\t\t\t\t\t\t|\n\t\t|\t3. Show the list\t\t\t\t\t\t|\n\t\t|\t4. Modify a record\t\t\t\t\t\t|\n\t\t|\t5. Save\t\t\t\t\t\t\t\t|\n");
        printf("\t\t|\t6. Exit\t\t\t\t\t\t\t\t|\n\t\t|\t7. Sort the list\t\t\t\t\t\t|\n\t\t|\t8. reverse the list\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t\t\t\t\t\t\t\t|\n");
        printf("\t\t|\tEnter your choice: \t\t\t\t\t\t|\n");
        printf("\t\t+-----------------------------------------------------------------------+\n");
        scanf("%d",&op);
        
        switch(op)
        {
            case 1 :add_new_record(&headptr,&roll_count);break;
            case 2 :delete_node();break;
            case 3 :show_list(headptr);
                    printf("\nDo you want to go back to the menu window?(Y/N)\n");

                    scanf(" %c",&choice);
                    if(choice=='Y'||choice=='y')
                    {
                        break;
                    }
                    else
                    {
                        clear_screen();
                        exit(0);
                    }
                    
            case 4 :modify_rec(headptr);
                    printf("\nDo you want to go back to the menu window?(Y/N)\n");
                    scanf(" %c",&choice);
                    if(choice=='Y'||choice=='y')
                    {
                        break;
                    }
                    else
                    {
                        clear_screen();
                        exit(0);
                    }
            case 5 :save_file(headptr);
                    wait_for_enter();
                    break;
            case 6 :clear_screen();
                    char my_choice;
                    printf("Do you want to save data?(Y/N)\n");
                    scanf(" %c",&my_choice);
                    if(my_choice=='Y'||my_choice=='y')
                    {
                        clear_screen();
                        save_file(headptr);
                        free_memory(headptr);
                        clear_screen();
                        exit(0);
                    }
                    free_memory(headptr);
                    exit(0);
            case 7 :sort_by(headptr);break;
           
            case 8 :rev_list(&headptr);
                    wait_for_enter();
                    break;
        }
    }
}
void free_memory(sll *ptr)//clearing the dynamic memory while exiting 
{
    sll *del=ptr;
    while(del)
    {
        ptr=del->next;
        free(del);
        del=ptr;
    }
}
void add_new_record(sll **ptr,int *roll_count_ptr)//adding new data
{
    sll *new;
    int counter=1;
    if(*ptr!=0)
    {
        sort_by_rollno(headptr);
    }
    sll *find_missing=*ptr;
    new=malloc(sizeof(sll));
    if(*ptr!=0)
    {
        //sll *find_missing=*ptr;
        while(find_missing)
        {
            if(counter!=find_missing->rollno)
            {
                new->rollno=counter;
                break;
            }
            counter++;
            find_missing=find_missing->next;
        }
    }
    if(find_missing==0)
    {
        new->rollno=(*roll_count_ptr)++;
    }
    printf("Enter the name and marks\n");
    scanf("%s %f",new->name,&new->marks);
    new->next=0;
    if(*ptr==0)
    {
        *ptr=new;
    }
    else
    {
        sll *last=*ptr;
        while(last->next)
            last=last->next;
            last->next=new;
    }
}
void show_list(sll *ptr)//showing the data on the terminal
{
    if(ptr==0)
    {
        clear_screen();
        printf("No records found\nIf you want to add some records please select option '1'\n");
        return;
    }
    clear_screen();
    printf("\t\t\t\t+----------+--------------------+-----------+\n");
    printf("\t\t\t\t|\t\tSTUDENT LIST\t\t    |\n");
    printf("\t\t\t\t+----------+--------------------+-----------+\n");
    printf("\t\t\t\t| %-8s | %-18s | %-9s |\n", "Roll No", "Name", "Marks");
    printf("\t\t\t\t+----------+--------------------+-----------+\n");
    while(ptr)
    {
        printf("\t\t\t\t| %-8d | %-18s | %-9.2f |\n", ptr->rollno, ptr->name, ptr->marks);
        printf("\t\t\t\t+----------+--------------------+-----------+\n");
        ptr=ptr->next;
    }
}
void save_file(sll *ptr)//saving data into the file
{
    if(ptr==0)
    {
        printf("No data to store in the file\n");
        return;
    }
    char choice;
    //sll *ppptr=ptr;
    //sort_by_rollno(ppptr);
    printf("Before adding data to file would you like to sort the data?(Y/N)\n");
    scanf(" %c",&choice);
    if(choice=='Y'||choice=='y')
    {
       sort_by(headptr); 
    }
    FILE *fp;
    fp=fopen("student_data","w");

    fprintf(fp,"\t\t\t\t+-------------------------------------------+\n");
    fprintf(fp,"\t\t\t\t|\t\t\t   STUDENTS LIST\t\t\t\t|\n");
    fprintf(fp,"\t\t\t\t+----------+--------------------+-----------+\n");
    fprintf(fp,"\t\t\t\t| %-8s | %-18s | %-9s |\n", "Roll No", "Name", "Marks");
    fprintf(fp,"\t\t\t\t+----------+--------------------+-----------+\n");
    while(ptr)
    {
        fprintf(fp,"\t\t\t\t| %-8d | %-18s | %-9.2f |\n", ptr->rollno, ptr->name, ptr->marks);
        fprintf(fp,"\t\t\t\t+----------+--------------------+-----------+\n");
        ptr=ptr->next;
    }
    fclose(fp);
    printf("Data saved successfully\n");
    printf("To view data open student_data file\n");
}
void modify_rec(sll *ptr)//option window of the modify record
{
    clear_screen();
    if(ptr==0)
    {
        printf("No records found\n");
        return;
    } 
    clear_screen(); 
    int op;
    printf("\t\t\t\t+-----------------------------------------------+\n");
    printf("\t\t\t\t| %-40s |\n","Enter which record to search for modification");
    printf("\t\t\t\t+-----------------------------------------------+\n");
    printf("\t\t\t\t| %-45s |\n","1. To search a rollno");
    printf("\t\t\t\t| %-45s |\n","2. To search a name");
    printf("\t\t\t\t| %-45s |\n","3. Return back to menu");
    printf("\t\t\t\t+-----------------------------------------------+\n"); 
    scanf("%d",&op);
    switch(op)
    {
        case 1:mod_by_rollno(&headptr);break;
        case 2:mod_by_name(&headptr);break;
        case 3: return;
    }
}
void mod_by_rollno(sll **pptr)//modify the data based on the roll no
{
    
    int rol;
    while(1)
    {
        clear_screen();
        sll *ptr=*pptr;
        printf("Enter the rollno\n");
        scanf("%d",&rol);
        while(ptr)
        {
            if(rol==ptr->rollno)
            {
                printf("Enter name and marks\n");
                scanf("%s %f",ptr->name,&ptr->marks);
                printf("Record updated successfully\n");
                break;
            }
            ptr=ptr->next;
        }
        if(ptr==NULL)
        {
            printf("Rollno not found in the database\n");
            printf("please enter valid number\n");
            printf("\n");
        }
        char choice;
        printf("Do you want to update any other record?(Y/N)\n");
        scanf(" %c",&choice);
        if(choice=='N'||choice=='n')
        {
            clear_screen();
            break;
        }
    }
}
void sort_by(sll *ptr)//option for sorting
{
   int op;
   char choice;
   while(1)
   {
        clear_screen();
        
        printf("\t\t\t\t+-----------------------------------------------+\n");
        printf("\t\t\t\t| %-40s |\n","\tHow do you want to sort the data");
        printf("\t\t\t\t+-----------------------------------------------+\n");
        printf("\t\t\t\t| %-45s |\n","1. Sort by rollno");
        printf("\t\t\t\t| %-45s |\n","2. Sort by name");
        printf("\t\t\t\t| %-45s |\n","3. Sort by percentage");
        printf("\t\t\t\t| %-45s |\n","4. Return back");
        printf("\t\t\t\t+-----------------------------------------------+\n"); 
        scanf("%d",&op);
        switch(op)
        {
            case 1: sort_by_rollno(ptr);
                    show_list(ptr);
                    break;

            case 2: sort_by_name(ptr);break;
                    
            case 3: sort_by_marks(ptr);break;

            case 4: return;
            default : clear_screen();
                        printf("Please enter valid choice\n");break;
        }
        printf("\nDo you want to go back to the selection window?(Y/N)\n");
        scanf(" %c",&choice);
            if(choice=='N'||choice=='n')
            {
                clear_screen();
                return;
            }
   }
}
void sort_by_name(sll *pptr)//sort database by names
{
    if(pptr==0)
    {
        printf("No data to sort\n");
        return;
    }
    int c=count_node(pptr);
    sll *p1,*p2,t;
    p1=pptr;
    for(int i=0;i<c;i++)
    {
        p2=p1->next;
        for(int j=0;j<c-1-i;j++)
        {
            if(strcmp(p1->name,p2->name)>0)
            {
                t.rollno=p1->rollno;
                strcpy(t.name,p1->name);
                t.marks=p1->marks;

                p1->rollno=p2->rollno;
                strcpy(p1->name,p2->name);
                p1->marks=p2->marks;

                p2->rollno=t.rollno;
                strcpy(p2->name,t.name);
                p2->marks=t.marks;
            }
            p2=p2->next;
        }
        p1=p1->next;
    }
    show_list(pptr);
}
void sort_by_marks(sll *pptr)//sort database by marks..highest 1st
{
    if(pptr==0)
    {
        printf("No data to sort\n");
        return;
    }
    int c=count_node(pptr);
    sll *p1,*p2,t;
    p1=pptr;
    for(int i=0;i<c;i++)
    {
        p2=p1->next;
        for(int j=0;j<c-1-i;j++)
        {
            if(p1->marks<p2->marks)
            {
                t.rollno=p1->rollno;
                strcpy(t.name,p1->name);
                t.marks=p1->marks;

                p1->rollno=p2->rollno;
                strcpy(p1->name,p2->name);
                p1->marks=p2->marks;

                p2->rollno=t.rollno;
                strcpy(p2->name,t.name);
                p2->marks=t.marks;
            }
            p2=p2->next;
        }
        p1=p1->next;
    }
    show_list(pptr);
}
int count_node(sll *ptr)//counting number of nodes
{
    int c=0;
    if(ptr==0)
    {
        printf("No records found\nIf you want to add some records please select option '1'\n");
        return c;
    }
    while(ptr)
    {
        c++;
        ptr=ptr->next;
    }
    return c;
}
void rev_list(sll **ptr)//reversing the link
{
    if(*ptr==0)
    {
        printf("No records found\n");
        return;
    }
    int c=count_node(*ptr);
    if(c>1)
    {
        sll **a=malloc(sizeof(sll *)*c);
        sll *t=*ptr;
        int i=0;
        while(t)
        {
            a[i++]=t;
            t=t->next;
        }
        for(i=c-1;i>0;i--)
        a[i]->next=a[i-1];

        a[0]->next=0;
        *ptr=a[c-1];
    }
    printf("Link reversed successfully\n");
}
void wait_for_enter(void)//program will wait till user press enter
{
    int c;
    while((c=getchar())!='\n'&& c!=EOF);

    printf("\nPress [Enter] to continue...\n");
    getchar();
}
void delete_node(void)//seleting delete method
{
   int op;
   char choice;
   while(1)
   {
        clear_screen();
        
        printf("\t\t\t\t+-----------------------------------------------+\n");
        printf("\t\t\t\t| %-33s |\n","\t\tChoose below option");
        printf("\t\t\t\t+-----------------------------------------------+\n");
        printf("\t\t\t\t| %-45s |\n","1. Delete specific node");
        printf("\t\t\t\t| %-45s |\n","2. Delete all nodes");
        printf("\t\t\t\t| %-45s |\n","3. Return back");
        printf("\t\t\t\t+-----------------------------------------------+\n"); 
        scanf("%d",&op);
        switch(op)
        {
            case 1: del_spec_node();break;
                    
            case 2: del_all_node(&headptr);break;

            case 3: return;
            default : clear_screen();
                        printf("Please enter valid choice\n");break;
        }
        printf("\nDo you want to go back to main menu?(Y/N)\n");
        scanf(" %c",&choice);
            if(choice=='N'||choice=='n')
            {
                clear_screen();
                char my_choice;
                printf("Do you want to save data?(Y/N)\n");
                scanf(" %c",&my_choice);
                if(my_choice=='Y'||my_choice=='y')
                {
                    clear_screen();
                    save_file(headptr);
                    free_memory(headptr);
                    exit(0);
                }
                else
                {
                    clear_screen();
                    free_memory(headptr);
                    exit(0);
                }
            }
            else
            {
                break;
            }
   } 
}
void del_all_node(sll **pptr)//delete all nodes at a time
{
    clear_screen();
    if(*pptr==0)
    {
        printf("No data to delete\n");
        return;
    }
    char choice;
    printf("\t\t\t\t+-----------------------------------------------+\n");
    printf("\t\t\t\t| %-33s |\n","Are you sure you want continue deleting data?");
    printf("\t\t\t\t| %-45s |\n","You will not be able to recover deleted data.");
    printf("\t\t\t\t| %-45s |\n"," ");
    printf("\t\t\t\t| %-26s |\n","\tYes(Y) \t\t\tNo(N)");
    printf("\t\t\t\t+-----------------------------------------------+\n");
    scanf(" %c",&choice);
    clear_screen();
    if(choice =='Y'||choice =='y')
    {
        sll *del=*pptr;
        while(del)
        {
            *pptr=del->next;
            free(del);
            del=*pptr;
        }
        printf("All data deleted successfully\n");
        wait_for_enter();
        //return;
    }
    else
    return;
}
void del_spec_node()//option for specific deleting process
{
  int op;
   char choice;
   while(1)
   {
        clear_screen();
        
        printf("\t\t\t\t+-----------------------------------------------+\n");
        printf("\t\t\t\t| %-33s |\n","\t\tChoose below option");
        printf("\t\t\t\t+-----------------------------------------------+\n");
        printf("\t\t\t\t| %-45s |\n","1. Delete based on rollno");
        printf("\t\t\t\t| %-45s |\n","2. Delete based on name");
        printf("\t\t\t\t| %-45s |\n","3. Return back");
        printf("\t\t\t\t+-----------------------------------------------+\n"); 
        scanf("%d",&op);
        switch(op)
        {
            case 1: del_node_rollno(&headptr);break;
                    
            case 2: del_node_name(&headptr);break;

            case 3: return;
            default : clear_screen();
                        printf("Please enter valid choice\n");break;
        }
        printf("\nRetrun back to selection window?(Y/N)\n");
        scanf(" %c",&choice);
            if(choice=='N'||choice=='n')
            {
                clear_screen();
                return;
            }
   }   

}
void del_node_rollno(sll **ppptr)//deleting by rollno
{
    while(1)
    {
        clear_screen();
        int c=0;
        if(ppptr==NULL)
        {
            printf("No data available to delete\n");
            return;
        }
        else
        {
            int rol;
            printf("Enter the rollno you want to delete:\n");
            scanf("%d",&rol);

            sll *del=*ppptr,*prev;
            while(del)
            {
                if(rol==del->rollno)
                {
                    if(del==*ppptr)
                        *ppptr=del->next;
                    else
                        prev->next=del->next;
                    free(del);
                    c++;
                    break;
                }
                prev=del;
                del=del->next;
            }
        }
        if(c==0)
        {
            printf("No matching record found\n");
        }
        char choice;
        printf("\nDo you want to continue deleting data?(Y/N)\n");
        scanf(" %c",&choice);
            if(choice=='N'||choice=='n')
            {
                clear_screen();
                return;
            }
    }
}
void del_node_name(sll **ppptr)//taking name as a reference for deleting the node
{
    while(1)
    {
        clear_screen();
        char s[20];
        printf("Enter the name of the student\n");
        scanf(" %s",s);
        sll *serch=*ppptr;
        int count=0;
        while(serch)//finding how many times same name occurs
        {
            if(strcmp(s,serch->name)==0)
            {   
                count++;
            }
            serch=serch->next;
        }
        if(count==0)//if name not found
        {
            printf("No matching record found\n");
            wait_for_enter();
            return;
        }
        else if(count==1)//if only times name occurs
        {
            sll *del=*ppptr,*prev;
                while(del)
                {
                    if(strcmp(s,del->name)==0)
                    {
                        if(del==*ppptr)
                            *ppptr=del->next;
                        else
                            prev->next=del->next;
                        free(del);
                        break;
                    }
                    prev=del;
                    del=del->next;
                }
                printf("Data deleted Successfully\n");
                wait_for_enter();
        }
        else if(count>1)//if multiple times name occurs
        {
            serch=*ppptr;
            clear_screen();
            printf("\t\t\t\t+----------+--------------------+-----------+\n");
            printf("\t\t\t\t|\t\tSTUDENT LIST\t\t    |\n");
            printf("\t\t\t\t+----------+--------------------+-----------+\n");
            printf("\t\t\t\t| %-8s | %-18s | %-9s |\n", "Roll No", "Name", "Marks");
            printf("\t\t\t\t+----------+--------------------+-----------+\n");
            while(serch)
            {
                if(strcmp(serch->name,s)==0)
                {   
                    printf("\t\t\t\t| %-8d | %-18s | %-9.2f |\n", serch->rollno, serch->name, serch->marks);
                    printf("\t\t\t\t+----------+--------------------+-----------+\n");
                }
                serch=serch->next;
            }
            int rol;
                printf("Enter the rollno you want to delete:\n");
                scanf("%d",&rol);

                sll *del=*ppptr,*prev;
                while(del)
                {
                    if(rol==del->rollno)
                    {
                        if(del==*ppptr)
                            *ppptr=del->next;
                        else
                            prev->next=del->next;
                        free(del);
                        break;
                    }
                    prev=del;
                    del=del->next;
                }
            printf("Data deleted successfully\n");
            wait_for_enter();
        }
        clear_screen();
        char choice;
        printf("\nDo you want to continue deleting data?(Y/N)\n");
        scanf(" %c",&choice);
        if(choice=='N'||choice=='n')
        {
            clear_screen();
            return;
        }
    }
}
void mod_by_name(sll **ppptr)//taking name as a reference for editing the node
{
    while(1)
    {
        clear_screen();
        char s[20];
        printf("Enter the name of the student\n");
        scanf(" %s",s);
        sll *serch=*ppptr;
        int count=0;
        while(serch)//finding how many times same name occurs
        {
            if(strcmp(s,serch->name)==0)
            {   
                count++;
            }
            serch=serch->next;
        }
        if(count==0)//if name not found
        {
            printf("No matching record found\n");
            wait_for_enter();
            return;
        }
        else if(count==1)//if only one times name occurs
        {
            sll *del=*ppptr;
                while(del)
                {
                    if(strcmp(s,del->name)==0)
                    {
                        printf("Enter marks to modify\n");
                        scanf("%f",&del->marks);
                        break;
                    }
                    del=del->next;
                }
                printf("Record updated successfully\n");
                wait_for_enter();
        }
        else if(count>1)//if multiple times name occurs
        {
            serch=*ppptr;
            clear_screen();
            printf("\t\t\t\t+----------+--------------------+-----------+\n");
            printf("\t\t\t\t|\t\tSTUDENT LIST\t\t    |\n");
            printf("\t\t\t\t+----------+--------------------+-----------+\n");
            printf("\t\t\t\t| %-8s | %-18s | %-9s |\n", "Roll No", "Name", "Marks");
            printf("\t\t\t\t+----------+--------------------+-----------+\n");
            while(serch)
            {
                if(strcmp(serch->name,s)==0)
                {   
                    printf("\t\t\t\t| %-8d | %-18s | %-9.2f |\n", serch->rollno, serch->name, serch->marks);
                    printf("\t\t\t\t+----------+--------------------+-----------+\n");
                }
                serch=serch->next;
            }
            int rol;
                printf("Enter the rollno you want to delete:\n");
                scanf("%d",&rol);

                sll *del=*ppptr;
                while(del)
                {
                    if(rol==del->rollno)
                    {
                        printf("Enter marks to modify\n");
                        scanf("%f",&del->marks);
                        break;
                    }
                    del=del->next;
                }
            printf("Record updated successfully\n");
            wait_for_enter();
        }
        clear_screen();
        char choice;
        printf("\nDo you want to continue editing data?(Y/N)\n");
        scanf(" %c",&choice);
        if(choice=='N'||choice=='n')
        {
            clear_screen();
            return;
        }
    }
}
void sort_by_rollno(sll *pptr)//sort database by rollno..1.2.3.....
{
    if(pptr==0)
    {
        printf("No data to sort\n");
        return;
    }
    int c=count_node(pptr);
    sll *p1,*p2,t;
    p1=pptr;
    for(int i=0;i<c;i++)
    {
        p2=p1->next;
        for(int j=0;j<c-1-i;j++)
        {
            if(p1->rollno > p2->rollno)
            {
                t.rollno=p1->rollno;
                strcpy(t.name,p1->name);
                t.marks=p1->marks;

                p1->rollno=p2->rollno;
                strcpy(p1->name,p2->name);
                p1->marks=p2->marks;

                p2->rollno=t.rollno;
                strcpy(p2->name,t.name);
                p2->marks=t.marks;
            }
            p2=p2->next;
        }
        p1=p1->next;
    }
    //show_list(pptr);
}