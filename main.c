#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node
{
    int number;
    char currentWord[50];
    struct node *next;
};

struct node *first, *templateList;

int count_the_word(FILE *fPtr, char *word)
{
    int sum = 0;
    char newWord[50];
    fPtr = fopen("text.txt", "r");

    if(fPtr == NULL)
    {
        printf("The file could not be opened.");
        return 1;
    }

    while(fscanf(fPtr, "%s ", newWord) != EOF)
    {
        if(strcmp(word, newWord) == 0)
        {
            sum++;
        }
    }
    fclose(fPtr);
    return sum;
}

int search_the_word(char *word)
{
    struct node *search = (struct node*)malloc(sizeof(struct node));
    search = first;
    bool inList = false;

    while(search != NULL)
    {
        if(strcmp(word, search -> currentWord) == 0)
        {
            inList = true;
        }
        search = search -> next;
    }
    return inList;
}

void add_to_the_beginning(char *word, int numOfTheWord)
{
    struct node *begin = (struct node*)malloc(sizeof(struct node));
    strcpy(begin -> currentWord, word);
    begin -> number = numOfTheWord;
    begin -> next = first;
    first = begin;
}

void add_to_the_between(char *word, int numOfThisWord)
{
    templateList = first;
    while(templateList -> next != NULL && templateList -> next -> number > numOfThisWord)
    {
        templateList = templateList -> next;
    }
    struct node *newOne = (struct node*)malloc(sizeof(struct node));
    newOne -> next = templateList -> next;
    templateList -> next = newOne;
    newOne -> number = numOfThisWord;
    strcpy(newOne -> currentWord, word);
}

void add_to_the_end(char *word)
{
    struct node *end = (struct node*)malloc(sizeof(struct node));
    strcpy(end -> currentWord, word);
    end -> number = 1;
    end -> next = NULL;
    templateList = first;
    while(templateList->next!=NULL)
    {
        templateList = templateList -> next;
    }
    templateList->next = end;
}

void list()
{
    int index = 1;
    struct node *list = (struct node*)malloc(sizeof(struct node));
    list = first;
    while(list != NULL)
    {
        printf("%d: %s: %d\n", index, list -> currentWord, list->number);
        list = list -> next;
        index++;
    }
}

int main()
{
    FILE *filePtr;
    filePtr = fopen("text.txt", "r");

    if(filePtr == NULL)
    {
        printf("The file could not be opened.");
        return 1;
    }

    bool isEmpty = true;
    char word[50];

        struct node *first = (struct node*)malloc(sizeof(struct node));
        first->next=NULL;

    while(fscanf(filePtr, "%s ", word) != EOF)
    {
        if(isEmpty == true)
        {
            first -> number = count_the_word(filePtr, word);
            add_to_the_beginning(word, first -> number);
            isEmpty = false;
        }
        else
        {
            if(search_the_word(word) == false)
            {
                if(count_the_word(filePtr, word) == 1)
                {
                    add_to_the_end(word);
                }
                else if(count_the_word(filePtr, word) >= first -> number)
                {
                    int numOfTheWord = count_the_word(filePtr, word);
                    add_to_the_beginning(word, numOfTheWord);
                }
                else
                {
                    int numOfThisWord = count_the_word(filePtr, word);
                    add_to_the_between(word, numOfThisWord);
                }
            }
        }
    }

    list();

    fclose(filePtr);
    return 0;
}
