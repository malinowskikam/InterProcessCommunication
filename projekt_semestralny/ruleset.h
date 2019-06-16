typedef struct block
{
    int color;
    int x;
    int y;
    int width;
    int height;
} Block;

typedef struct block_list_node
{
    Block* block;
    struct block_list_node* next;
}* BlockList;

typedef struct game_context
{
    int player_count;
    int player;
    int game_lost;
    Block* block;
    BlockList block_list;

}* GameContext;

int is_on_top(Block* actual,Block* old)
{
    Block* first;
    Block* second;

    if(actual->x>old->x)
    {
        first=old;
        second=actual;
    }
    else
    {
        first=actual;
        second=old;
    }

    int is_above = 0;
    if(((second->x) >= (first->x) && (second->x) <= (first->x+first->width)) ||
        ((second->x+second->width) >= (first->x) && (second->x+second->width) <= (first->x+first->width)))
        is_above=1;

    if(is_above && (actual->y+actual->height) >= old->y)
        return 1;
    return 0;
}

int is_on_top_of_any(Block* actual,BlockList list)
{
    while(list!=NULL)
    {
        Block* block = list->block;
        
        if(is_on_top(actual,block))
            return 1;
        list = list->next;
    }
    return 0;
}