#include<unistd.h>
#include<X11/Xlib.h>
#include<X11/X.h>
#include<stdio.h>
#include<string.h>

void draw_overlay(Display* display, Window window,GC gc);
void draw_player(Display* display, Window window,GC gc,int player,int you);
void draw_player_count(Display* display, Window window,GC gc,int player_count);
void draw_my_turn(Display* display, Window window,GC gc);
void draw_block(Display* display, Window window,GC gc,Block* block);

void draw_overlay(Display* display, Window window,GC gc)
{
    XSetForeground(display,gc,863826468);
    XFillRectangle(display,window,gc,0,0,1024,10);
    XFillRectangle(display,window,gc,0,10,10,768-10);
    XFillRectangle(display,window,gc,10,758,1024-10,10);
    XFillRectangle(display,window,gc,1014,10,10,768-20);
    XFillRectangle(display,window,gc,300,10,10,768-20);

    XSetForeground(display,gc,278364286);
    XFillRectangle(display,window,gc,311,150,1024-311-10,2);
}

void draw_player(Display* display, Window window,GC gc,int player,int you)
{
    XSetForeground(display,gc,278364286);
    XDrawString(display,window,gc,30,30,"Teraz ruch gracza:",strlen("Teraz ruch gracza:"));
    char buff[20];
    sprintf(buff,"%d",player);
    XDrawString(display,window,gc,30,50,buff,strlen(buff));
    XDrawString(display,window,gc,30,70,"Jestes graczem:",strlen("Jestes graczem:"));
    sprintf(buff,"%d",you);
    XDrawString(display,window,gc,30,90,buff,strlen(buff));
}

void draw_player_count(Display* display, Window window,GC gc,int player_count)
{
    XSetForeground(display,gc,278364286);
    XDrawString(display,window,gc,30,110,"Ilosc graczy:",strlen("Ilosc graczy:"));
    char buff[20];
    sprintf(buff,"%d",player_count);
    XDrawString(display,window,gc,30,130,buff,strlen(buff));
}

void draw_my_turn(Display* display, Window window,GC gc)
{
    XSetForeground(display,gc,278364286);
    XDrawString(display,window,gc,30,150,"TWOJA TURA",strlen("TWOJA TURA"));
}

void draw_block(Display* display, Window window,GC gc,Block* block)
{
    XSetForeground(display,gc,block->color);
    XFillRectangle(display,window,gc,block->x,block->y,block->width,block->height);
}

void draw_blocks(Display* display, Window window,GC gc,BlockList block_list)
{
    while(block_list!=NULL)
    {
        Block* block = block_list->block;
        XSetForeground(display,gc,block->color);
        XFillRectangle(display,window,gc,block->x,block->y,block->width,block->height);
        block_list = block_list->next;
    }
}

void draw_lost(Display* display, Window window,GC gc)
{
    XSetForeground(display,gc,863826468);
    XDrawString(display,window,gc,30,170,"PRZEGRALES",strlen("PRZEGRALES"));
}