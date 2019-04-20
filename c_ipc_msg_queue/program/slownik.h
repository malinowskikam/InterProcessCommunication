#include<string.h>

int dictionary_length = 5;

char* keys[] = {
    "jeden",
    "dwa",
    "trzy",
    "cztery",
    "piec"
};

char* values[] = {
    "one",
    "two",
    "three",
    "four",
    "five"
};

char* error_msg = "Nie znam takiego słowa";

int get_key_id(char* key)
{
    for(int i=0;i<dictionary_length;i++)
    {
        if(strcmp(key,keys[i])==0)
            return i;
    }

    return -1;
}

char* translate(char* word)
{
    int id = get_key_id(word);
    if(id>=0)
        return values[id];
    else
        return error_msg;

}