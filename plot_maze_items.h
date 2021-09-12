//---------------------------------
//         RUTINA PLOT NET ITEMS    --    GRAFICA los parametros de la matriz Q 

//-----------------------------------------
void plot_maze(void)               ////       PLOT MAZE GRAPHICS
{
int i,j,sx,sy,x,y,color,scale; 
int temp;
    
x= x_plot_maze;
y= y_plot_maze;   
scale=square_size;
   
   for(i=0;i<files;i++)  // 
     { 
      y=y_plot_maze;   
      sy = y+i*scale;             
      for(j=0;j<columns;j++)
         {    
          sx = x+j*scale;
          temp=R[i][j];  
          
          //timp= Entrada[counter];  
          color=LIGHTGRAY; 
          if(temp<0) color=BLACK;          // WALL
          if(temp==0) color=LIGHTGRAY;          // FLOOR    
          if(temp==100) color=YELLOW;     // TOP REWARD
          setcolor(color); 
          setfillstyle(SOLID_FILL,color); 
          bar(sx,sy,sx+scale,sy+scale) ;  
          //putpixel(sx,sy, color);      
          //y++;  
         }
       //x++;  
     } 
 
}
//----------------------------------------------------------------------------------------
void plot_agent(void)
{
int color,agent_size=square_size-3;  
int x,y;    
    
int offset_x=5;   //   para centrar al agente en x
int offset_y=5;   //   para centrar al agente en y

 x= x_plot_maze;   //   para sincronizarse con el enviroment grafico
 y= y_plot_maze;   //   
   
    x_agent=x+column_agent*square_size;
    y_agent=y+file_agent*square_size;
    
    captured_color=getpixel(x_agent,y_agent);   //  el sensor captura en una esquina
 
 setcolor(CYAN); //  
 setfillstyle(SOLID_FILL,CYAN);   
 bar(x_agent+offset_x,y_agent+offset_y,x_agent+agent_size,y_agent+agent_size) ;   
    
}
//-------------------------------------------------------------
//
// cout <<" x_agent: "<< x_agent <<endl; 
// cout <<" y_agent: "<< y_agent <<endl;    
// cout <<" color: "<< captured_color <<endl<<endl;    
    
 //file_agent= (y_agent/square_size)- y_plot_maze;
    
 //cout <<" file_agent: "<< file_agent <<endl;    


