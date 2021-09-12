 /************************ top_eye_flop.cpp **********************************
Basic agent in maze
Yachay Tech University
Artificial Intelligence Lab
Prof Oscar Chang

Jun 3, 2021
/*********************************************************************/ 
//
//  Student name:  ____________________
//
//------------------------------------------------------------------------------------------------
// GLOBALS

   
#define  files 16
#define  columns 16       //       size of the graphic maze   

int b_flag;
int stop;
char dummy[1];
//--
char key, color;

int x_agent, y_agent;

int x_plot_maze=30;
int y_plot_maze=30;

int square_size=21;         //
int captured_color;

//const int qSize = 6;
const float gamma = 0.8;

//int R[files][columns];

int Q[files][columns];    //
int Q_p[files][columns];    // q previus

int screen_image[files][columns];   //   presence  in pixels of the agent  and environment in the screen. Alter_ego  

int currentState;   
int episode;  

int move_flag;

int file_agent;    // file
int column_agent;  // column

int sensor[4];
int MAX;
int grad_pointer;


int R[files][columns] = 
    {
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1} ,
        { 0, -1,  0, -1,  0, -1, -1, -1,  0, -1, -1, -1,  0, -1,  0, -1} ,
        { 0, -1,  0, -1,  0, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1} ,
        { 0,  0,  0, -1,  0, -1, -1, -1, -1, -1, -1,  0, -1, -1,  0, -1} ,
        { 0, -1,  0, -1,  0,  0,  0, -1,  0,  0,  0,  0,  0, -1,  0, -1} ,
        {-1, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1, -1,  0, -1,  0, -1} ,
        { 0,  0,  0,  0,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1} ,
        { 0, -1, -1, -1, -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1} ,
        { 0,  0,  0,  0,  0,  0,  100,  0,  0, -1,  0, -1,  0, -1,  0, -1} ,
        { 0, -1, -1, -1,  0, -1,  0, -1, -1, -1,  0, -1,  0, -1,  0, -1} ,
        { 0, -1,  0,  0,  0, -1,  0, -1,  0,  0,  0, -1,  0, -1, -1, -1} ,
        { 0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1, -1,  0, -1,  0, -1} ,
        { 0, -1,  0, -1,  0, -1,  0,  0,  0, -1,  0, -1,  0, -1,  0, -1} ,
        { 0, -1, -1, -1,  0, -1, -1, -1,  0, -1,  0, -1,  0, -1,  0, -1} ,
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,  0,  0,  0, -1} ,
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1} ,
    };

unsigned t0, t1;

//----------------------------------------)))
//    end globals
//----------------------------------------)))
#include <sstream>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip.h>
#include <windows.h>
#include <ctime> 
#include <fstream>


#include "read_write_Q_matrix.h"
#include "plot_maze_items.h"
#include "Q_structures_lib.h"




//#include "cargar_pesos.h"
//#include "learn_to_play_O.h"

//******************* variables globales ***************************************/
using namespace std;
//usging namespace std;

//-----------------------------------------
//    inicia el modo grafico             
//-------------------------------------    
void grafico(void)
{
    int    GraphDriver;  /* The Graphics device driver */
    int    GraphMode;    /* The Graphics mode value */
    int    ErrorCode;    /* Reports any graphics errors */
   
    initgraph(&GraphDriver, &GraphMode, "");

    ErrorCode = graphresult();            /* Read result of initialization*/
    if( ErrorCode != grOk )              /* Error occured during init    */
    {
       printf(" Graphics System Error: %s", grapherrormsg( ErrorCode ) );
       exit( 1 );
    }
}
//-------------------------------------  
void erase_screen(void)
{
   setcolor(WHITE);  
   setfillstyle(SOLID_FILL,WHITE);     
   bar(150,100,350,300) ;         //  200   150   303   253
   floodfill(255,205,BLACK);    
}
//-------------------------------------------------------

void init_R(void)
{
   int i,j,k;
   for (j=0; j<files;j++)
    for (i=0; i<columns; i++)
    {
     R[j][i]=-1; 
    }    
  
}
//-------------------------------------------------------------
void loop(void)  //                                                           loop  !!                        &&&/&&/&&/////
{
int i,slow, gear; 
   slow=0;

     //load_Q();
     Q_explore();   // agent explores maze
        
     print_R();
     print_Q();

     cout<< "End...\n"<<endl;
     getch();

     /*
     cout <<" ready to exploit-- " <<endl; 
     
    do{
     plot_maze(); 
     random_Q_exploit();    
     getch(); 
    }while(1);     */
}    
//------------------------------------------------------
//===================================================================================================
void main(void)
{ 
  int rand_seed=37;     // 26
  int temp;  
    grafico();
    setcolor(WHITE);
    bar(0,0,1400,900);  
    
    srand(rand_seed);   
    
    file_agent=0;               // file of agent in matrix R  and Q
    column_agent=0;             // column of agent in matrix R and Q
    //init_R();
   
    
    x_agent=x_plot_maze;   //  x_agent:  coordinate x of agent in the screen    
    y_agent=y_plot_maze;   //  y_agent:  coordinate y of agent in the screen  
    
    plot_maze();
    plot_agent();
    print_R();
    
    //load_Q();
    //print_Q();
    //getch();
   
    stop=1;
    
    loop();
    
    do {
       //play_flag=0; 
       key=getch();
       switch (key) {
           case '1':         {
                              
                              loop(); 
                             }
           break;                    
           case '2':          {
                              
                              loop();     
                              }
	       break;
           case 'q':          {
                              
                               loop();                             
                              } 
           break;                               
           case 'a':          {
                               //move_down();
                               loop();     
                              }   
           break;                               
                              
           case ',':           { 
               
         
							   }
	       break;                              
           case 's':           { 
                                //salvar_Q();
                                loop();
							   }
	       break;                        
                                
                
                         
            case ' ':             {                     //-------    HERE  ! !!!!!!!!!!!!!!!!         !!!!!!!!!!!!1
                                    
                                   stop=stop^1;
                                   loop();
                                  }                                     
                                  
                                  
            break; 
            case 'R': case 'r':  {
                                   init_R();
                                   loop();
                                 }
            break;                     
                                
                                
   
           break; 
           case 'w':           {
                                
                                loop(); 
                                }
	       break;  

          case 'e':           {
                                
                                loop(); 
                                }
	       break;  


                                
           case 'c': case 'C': {
                                //CargarPesos();
                                loop(); 
                               }
	       break;    
          
           case 'p': case 'P': {
                                stop=1;    
                                //print_console_aux();                
                                //seed_learns();  //  OJO  no presenta los Targets apropiados          
                                loop();                              
                               }
	       break;    
          
	       break;  
                 
                               
         }
   } while ((key!='x')&&(key!='X'));

   closegraph();
   clrscr();
}

//---------------------------------------
/*
BLACK        ³  0  ³ Yes ³ Yes
BLUE         ³  1  ³ Yes ³ Yes
GREEN        ³  2  ³ Yes ³ Yes
CYAN         ³  3  ³ Yes ³ Yes
RED          ³  4  ³ Yes ³ Yes
MAGENTA      ³  5  ³ Yes ³ Yes
BROWN        ³  6  ³ Yes ³ Yes
LIGHTGRAY    ³  7  ³ Yes ³ Yes
DARKGRAY     ³  8  ³ No  ³ Yes
LIGHTBLUE    ³  9  ³ No  ³ Yes
LIGHTGREEN   ³ 10  ³ No  ³ Yes
LIGHTCYAN    ³ 11  ³ No  ³ Yes
LIGHTRED     ³ 12  ³ No  ³ Yes
LIGHTMAGENTA ³ 13  ³ No  ³ Yes
YELLOW       ³ 14  ³ No  ³ Yes
WHITE        ³ 15  ³ No  ³ Yes

----------------------------------------------------------------
     if(x<0)    { x=0; if( heat<100) heat++;}     
     if(y<35)    { y=35; if( heat<100) heat++;}  
     if(x>640) { x=640; if( heat<100) heat++;}  //  x>1200 : full pantalla 
     if(y>470) { y=470; if( heat<100) heat++;}   // y>720 : full pantalla 
         
//--------------------------------------------------

************************ basic_robot.cpp ***************************
desarrollado usando Dev-C++ IDE V4.9.8.4 GNU / MinGW / GNU gcc
                    Sc1 IDE / BCC5.5
                    version orginal por Oscar Chang
*********************************************************************/

