#define _REENTRANT

#include<stdio.h>
#include<unistd.h>
#include<X11/Xlib.h>
#include<X11/X.h>
#include<time.h>
#include<sys/wait.h>
#include<time.h>
#include <pthread.h>
#include <sys/types.h>

#include"utils.h"
#include"ruleset.h"
#include"gamewindow.h"

#define FPS 30

GameContext context;
pthread_rwlock_t read_write_lock;

typedef struct slave_args
{
    int id;
    char* ip;
}* SlaveArgs;

void* slave(void* args)
{
    int id = ((SlaveArgs)args)->id;
    char* ip = ((SlaveArgs)args)->ip;

    char* address = x_conn_sting(ip,"0",NULL);
    Display* display = XOpenDisplay(address);
    
    if(display==NULL)
    {
        fprintf(stderr,"slave %d: Could not connect to %s\n",id,ip);
        pthread_exit(NULL);
    }

    int screen = DefaultScreen(display);
    Visual* visual = DefaultVisual(display,screen);
    int depth = (display,screen);

    XSetWindowAttributes window_attributes;
    window_attributes.background_pixel = XBlackPixel(display,screen);
    window_attributes.override_redirect = False;

    Window window = XCreateWindow(display,XRootWindow(display,screen),
                            100,100,1024,768,10,depth,InputOutput,
                            visual,CWBackPixel|CWOverrideRedirect,
                            &window_attributes);

    XSelectInput(display,window,ExposureMask|KeyPressMask);
    XStoreName(display,window,"Gra");
    Colormap colormap = DefaultColormap(display,screen);

    XMapWindow(display,window);

    GC gc = DefaultGC(display,screen);

    XEvent xevent;
    int frame_number = 0;
    clock_t last_frame_time = clock();
    double time_elapsed;
    clock_t current_time;
    while(1)
    {
        int myturn=0;
        if(!pthread_rwlock_tryrdlock(&read_write_lock))
        {
            if(id==context->player)
                myturn=1;
            pthread_rwlock_unlock(&read_write_lock);
        }

        current_time = clock();
        time_elapsed = (double)(current_time-last_frame_time)/CLOCKS_PER_SEC;
        if(time_elapsed>(1.0/FPS)) // rysowanie w określonej ilości klatek na sekunde
        {
            XClearWindow(display,window);
            
            draw_overlay(display,window,gc);
            draw_player(display,window,gc,context->player,id);
            draw_player_count(display,window,gc,context->player_count);

            if(!(context->block==NULL))
                draw_block(display,window,gc,context->block);

            draw_blocks(display,window,gc,context->block_list);
            
            if(myturn)
                draw_my_turn(display,window,gc);
            
            if(context->game_lost)
                draw_lost(display,window,gc);


            XFlush(display); //flush

            frame_number = (frame_number+1)%FPS;
            last_frame_time = current_time;

            if(frame_number%3==0 && !(context->block==NULL))
            {
                context->block->y++;
                if(context->block->y>=757-context->block->height || is_on_top_of_any(context->block,context->block_list))
                {
                    BlockList node = (BlockList)malloc(sizeof(struct block_list_node));
                    node->block = context->block;
                    node->next = context->block_list;
                    context->block_list=node;

                    if(context->block->y<=150)
                        context->game_lost=1;
                    
                    pthread_rwlock_wrlock(&read_write_lock);
                    context->player++;
                    if(context->player>context->player_count)
                        context->player = 1;
                    pthread_rwlock_unlock(&read_write_lock);
                    

                    context->block = NULL;
                }
            }

        }

        if(XCheckMaskEvent(display,ExposureMask|KeyPressMask,&xevent))
        {
            if(xevent.type==KeyPress)
            {
                if(xevent.xkey.keycode==9) //ESC
                {
                    break;
                }
                else if(xevent.xkey.keycode==113 && myturn) //LEWO
                {
                    if(!(context->block==NULL))
                    {
                        context->block->x-=3;
                        if((context->block->x)<311)
                            context->block->x=311;
                    }
                }
                else if(xevent.xkey.keycode==114 && myturn) //PRAWO
                {
                    if(!(context->block==NULL))
                    {
                        context->block->x+=3;
                        if((context->block->x)>1013-context->block->width)
                            context->block->x=1013-context->block->width;
                    }
                }
                else if(xevent.xkey.keycode==36 || xevent.xkey.keycode==67 ) //ENTER
                {
                    if(context->block==NULL && !context->game_lost && myturn)
                    {
                        Block* block = (Block*)malloc(sizeof(Block));
                        block->color = rand();
                        block->x=600;
                        block->y=10;
                        block->width=100 + rand()%100;
                        block->height=50 + rand()%100;
                        context->block = block;

                    }
                    if(context->game_lost)
                    {
                        break;
                    }
                }
            }
        }
    }

    XCloseDisplay(display);
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    srand(clock());
    XInitThreads();
    pthread_rwlock_init(&read_write_lock,NULL);
    context = (GameContext)malloc(sizeof(struct game_context));
    context->player_count=argc-1;
    context->player=1;
    context->game_lost=0;
    context->block=NULL;
    context->block_list=NULL;

    int child_pid;

    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t)*(argc-1)) ;
    for(int i=1;i<argc;i++)
    {
        SlaveArgs args = (SlaveArgs)malloc(sizeof(struct slave_args));
        args->id = i;
        args->ip = argv[i];

        pthread_create(threads+i-1,NULL,slave,args);
    }    
    for(int i=1;i<argc;i++)
    {
        pthread_join(*(threads+i-1),NULL);
    }
    
    return 0;
}
