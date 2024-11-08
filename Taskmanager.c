#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define max_name_length 50
#define max_date_length 15
int order = 1;
struct task
{
    char name[max_name_length];
    int priority;
    char due_date[max_date_length];
    int status;
    struct task *next;
} *begin, *end;
void display_menu()
{
    printf("=====================================\n");
    printf(" Task Manager \n");
    printf("=====================================\n");
    printf("1.Add Task\n");
    printf("2.Display Tasks\n");
    printf("3.Mark a particular task as completed\n");
    printf("4.Update Tasklist by removing completed tasks \n");
    printf("5.Display Today's tasks\n");
    printf("6.Exit\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
}
struct task *create_task()
{
    struct task *newtask;
    newtask = (struct task *)malloc(sizeof(struct task));
    newtask->status = 0;
    newtask->priority = order++;
    printf("Enter task name:");
    fgets(newtask->name, max_name_length, stdin);
    newtask->name[strcspn(newtask->name, "\n")] = '\0'; // For removing the newline character
    printf("Enter due date in YYYY-MM-DD format:\n");
    fgets(newtask->due_date, max_date_length, stdin);
    newtask->due_date[strcspn(newtask->due_date, "\n")] = '\0'; // For removing the newlinecharacter
    newtask->next = NULL;
    return newtask;
}

void display_task()
{
    struct task *temp;
    if (begin == NULL)
    {
        printf("No tasks are left\n");
    }
    else
    {
        temp = begin;
        while (temp != NULL)
        {
            printf("Task: %s\nPriority: %d\nDue Date: %s\nStatus: %d\n--------------------------------------\n", temp->name, temp->priority, temp->due_date, temp->status);
            temp = temp->next;
        }
    }
}
void add_task()
{
    struct task *add = create_task();
    if (begin == NULL)
    {
        begin = add;
        end = add;
    }
    else
    {
        end->next = add;
        end = add;
    }
}
void update_task_list()
{
    struct task *temp, *prev, *to_delete = NULL;
    if (begin == NULL)
    {
        printf("No tasks are left\n");
    }
    else
    {
        temp = begin;
        prev = NULL; // Initialize prev to NULL
        while (temp != NULL)
        {
            if (temp->status == 1)
            {
                if (prev == NULL)
                {
                    begin = temp->next; // If first task is completed, update 'begin'
                }
                else
                {
                    prev->next = temp->next; // Update the 'next' pointer of the previous task
                }
                to_delete = temp; // Mark the task for deletion
            }
            else
            {
                prev = temp; // Move prev only if the task is not completed
            }
            temp = temp->next;
        }
        if (to_delete != NULL)
        {
            free(to_delete); // Free the memory of the completed task
            printf("Completed tasks removed.\n");
        }
        else
        {
            printf("No completed tasks found.\n");
        }
    }
}
void mark_completed_task()
{
    char task_name[max_name_length];
    printf("Enter the name of the task you want to mark as completed:\n");
    fgets(task_name, max_name_length, stdin);
    task_name[strcspn(task_name, "\n")] = '\0'; // For removing the newline character
    struct task *temp = begin;
    while (temp != NULL)
    {
        if (strcmp(temp->name, task_name) == 0)
        {
            temp->status = 1; // Mark the task as completed
            printf("Task '%s' marked as completed.\n", task_name);
            return;
        }
        temp = temp->next;
    }
    printf("Task not found.\n");
}
void display_today_tasks()
{
    struct task *temp;
    int flag = 0;
    // Get the current date
    time_t now;
    time(&now);
    struct tm *current_time = localtime(&now);
    char today_date[max_date_length];
    strftime(today_date, max_date_length, "%Y-%m-%d", current_time);
    if (begin == NULL)
    {
        printf("No tasks are left for today\n");
    }
    else

    {
        temp = begin;
        while (temp != NULL)
        {
            if (strcmp(temp->due_date, today_date) == 0)
            {
                flag = 1;
                printf("Task: %s\tPriority: %d\tDue Date: %s\tStatus: %d\n", temp->name, temp->priority, temp->due_date, temp->status);
            }
            temp = temp->next;
        }
        if (flag == 0)
            printf("No tasks for today\n");
    }
}
int main()
{
    int option;
    do
    {
        display_menu();
        scanf("%d", &option);
        getchar();
        switch (option)
        {
        case 1:
            add_task();
            break;
        case 2:
            display_task();
            break;
        case 3:
            mark_completed_task();
            break;
        case 4:
            update_task_list();
            break;
        case 5:
            display_today_tasks();
            break;
        }
    } while (option != 6);
    return 0;
}
