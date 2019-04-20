#include<string.h>
#include<stdlib.h>

char* surnames[] = { "Nowak", 
    "Kowalski", 
    "Adamski", 
    "Kowalska", 
    "Kowalczyk",
    "Wójcik",
    "Lewandowska",
    "Zielińska",
    "Szymańska",
    "Woźniak",
    "Dąbrowski",
    "Jankowska",
    "Mazur",
    "Kwiatkowska",
    "Kaczmarek",
    "Michalska",
    "Zając",
    "Grabowska",
    "Jabłoński",
    "Wieczorek"};

char* entry_not_found = "Nie ma";

typedef struct row {
    int id;
    char* surname;
}* db;

db create_db()
{
    db rows = (db)(malloc(sizeof(struct row)*20));
    return rows;
}

void desroy_db(db db)
{
    for(int i=0;i<20;i++)
        free(db[i].surname);

    free(db);
}

void insert_test_data(db database)
{
    for(int i=0;i<20;i++)
    {
        database[i].id = i+1;
        database[i].surname = (char*)(malloc(sizeof(char)*20));
        strcpy(database[i].surname,surnames[i]);
    }
}

char* get_by_id(db database,int id)
{
    for(int i=0;i<20;i++)
    {
        if(database[i].id==id)
            return database[i].surname;
    }

    return entry_not_found;
}