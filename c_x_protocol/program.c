#include<stdio.h>
#include<unistd.h>
#include<X11/Xlib.h>
#include<X11/X.h>
#include<time.h>
#include<sys/wait.h> 

#include"utils.c"

int slave(int id, char* ip)
{
    char* address = x_conn_sting(ip,"0",NULL);
    
    printf("slave %d: Connecting to display %s\n",id,address);
    Display* display = XOpenDisplay(address);
    
    if(display==NULL)
    {
        fprintf(stderr,"slave %d: Could not connect to %s\n",id,ip);
        return 1;
    }

    int screen = DefaultScreen(display);
    Visual* visual = DefaultVisual(display,screen);
    int depth = (display,screen);

    XSetWindowAttributes window_attributes;
    window_attributes.background_pixel = XWhitePixel(display,screen);
    window_attributes.override_redirect = False;

    Window window = XCreateWindow(display,XRootWindow(display,screen),
                            100,100,500,500,10,depth,InputOutput,
                            visual,CWBackPixel|CWOverrideRedirect,
                            &window_attributes);

    XSelectInput(display,window,ExposureMask|KeyPressMask);
    
    Colormap colormap = DefaultColormap(display,screen);

    XMapWindow(display,window);

    GC gc = DefaultGC(display,screen);

    XEvent xevent;

    unsigned long start = time(NULL);

    srand(start + id + (int)(long)ip);

    while(1)
    {
        XNextEvent(display,&xevent);
        if(xevent.type==KeyPress)
            break;
        if(xevent.type==Expose)
        {
            XSetForeground(display,gc,rand());
            XFillRectangle(display,window,gc,rand()%100,rand()%100,rand()%400,rand()%400);
            XFlush(display);
        }
    }

    unsigned long end = time(NULL);

    printf("slave %d: Client \"%s\" closed the window after %lu seconds\n",id,ip,end-start);

    XCloseDisplay(display);
    return 0;
}

int main(int argc, char** argv)
{
    int child_pid;
    for(int i=1;i<argc;i++)
    {
        int id = i;
        child_pid = fork();
        if(child_pid==0)
        {
            int status = slave(id,argv[id]);
            if(status!=0)
                printf("slave %d exited with code %d\n",id,status);
            break;
        }
    }    

    if(child_pid!=0)
    {
        for(int i=0;i<argc;i++)
        {
            wait(NULL);
        }
    }
    return 0;
}
