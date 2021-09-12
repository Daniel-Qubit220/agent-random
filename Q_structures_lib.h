//===========================================================================
//  DEFINICION DE ESTRUCTURAS Q 
//========================================================================
//----------------------------------------------------------------------------------------------------     
void print_Q(void)
{
 int i,j;
    
    printf("This is the Q Matrix:\n \n");
    for(i = 0; i < files ; i++)
        {
        for(j = 0; j < columns; j++)
            {
            cout << setw(5) << Q[i][j];   
			//if(j < qSize - 1)cout << "  ";  // separador de de columnas 
		} // j
        cout << "\n";
	} // i
    cout << "\n";
}
//------------------------
void print_R(void)
{
 int i,j;
    
    printf("This is the R Matrix:\n \n");
    for(i = 0; i < files; i++)
        {
        for(j = 0; j < columns; j++)
            {
            cout << setw(5) << R[i][j];   
			//if(j < qSize - 1)cout << "  ";  // separador de de columnas 
		} // j
        cout << "\n";
	} // i
    cout << "\n";
}
//-------------------------------------------------------
//-----------------------------------------------------
void move_left(void)
{
 int color,temp;
    temp=getpixel(x_agent-square_size,y_agent);   // revisa cercania a la izquierda
    if(temp==7||temp==14)
    {  
     x_agent=x_agent-square_size;
     column_agent--;
    }    
   
}
//--------------------------------------------------------------
void move_right(void)
{
 int temp;   
  temp=getpixel(x_agent+square_size,y_agent); 
  if(temp==7||temp==14)
     {
      x_agent=x_agent+square_size;
      column_agent++; 
     }    
    
}
//-------------------------------------------------------------
void move_up(void)
{
 int temp;
    temp=getpixel(x_agent,y_agent-square_size);  
    if(temp==7||temp==14)
    {
     y_agent=y_agent-square_size;
     file_agent--;
    }    
  
}
//-------------------------------------------------------------
void move_down(void)
{
 int temp;
   temp=getpixel(x_agent,y_agent+square_size);  
   if(temp==7||temp==14)
   {
    y_agent=y_agent+square_size; 
    file_agent++;
   }    
         
}
//--------------------------------------------------------
void search_for_MAX(void) 
{
 int i,j;
    sensor[0]= Q[file_agent][column_agent-1];    // lee  a izquierda
    if(column_agent==0) sensor[0]=-1;            // desborde a la izquierd  
        
    sensor[1]= Q[file_agent][column_agent+1];    // lee a  derecha
    if(column_agent==columns-1) sensor[1]=-1;
    
    sensor[2]= Q[file_agent-1][column_agent];    // lee arriba
    if(file_agent==0) sensor[2]=-1;
    
    sensor[3]= Q[file_agent+1][column_agent];    // lee abjo
    if(file_agent==files-1) sensor[3]=-1;

    MAX=sensor[0];
    for(i=0;i<4;i++) if(sensor[i]>=MAX) {MAX=sensor[i];grad_pointer=i;}  // grad_pointer apunta al maximo valor
   //cout <<" MAX: "<< MAX <<endl; 
}
//-------------------------------------------------------
//-----------------------------------------------------
void save_q(void){
    int i, j;
    for(i=0;i<files;i++){
        for(j=0;j<columns;j++){
            Q_p[i][j]=Q[i][j];
        }
    }    
}


//-------------------------------------------------------
bool check_q(bool go){
    int i, j;
    go = false;
    for(i=0;i<files;i++){
        for(j=0;j<columns;j++){
            if(Q[i][j]!=Q_p[i][j]){
                go=true;
                break;
            }
        }
    }
    return go;
}
//--------------------------------------------------------
void Q_explore(void)  
{
 int temp, explore_state;
 int i,j,k, ciclos;     
 float max;
 int initial_state;
 bool go=true;


 string datas;

 randomize(); 
   episode=1; 
   do
    {
         do
         {
          i=random(files);
          j=random(columns); 
          temp=R[i][j];             
         } while(temp==-1 || R[i][j]==100);    // el agente se ubica en estado inicial aleatorio con entrada diferente de -1   
 
         //file_agent=i;          // ubicamos al agente en la matriz
         //column_agent=j;  
         
         file_agent=i;          // ubicamos al agente en la matriz
         column_agent=j;  
         
         //cout <<" i : "<< i <<endl; 
         //cout <<" j : "<< j <<endl;
         save_q();//save previus Q

         plot_maze();
         plot_agent();
         ciclos=0;             // 
         t0=clock(); 
         do
          {  
           i=random(4);     // el agente se mueve a un nuevo estado aleatorio
           if(i==0) move_left();
           if(i==1) move_right(); 
           if(i==2) move_up();
           if(i==3) move_down(); 
               
           search_for_MAX();
           max=MAX;
               
           Q[file_agent][column_agent]= R[file_agent][column_agent]+ gamma*max;

           plot_maze();
           plot_agent();                     //  sensor captures color
           delay(1);
           ciclos++;
           //getch();
         }while(captured_color!=YELLOW);     //  hasta que capture recompensa maxima
        t1 = clock();
        delay(100); 
        system("cls"); 
        print_R();
        print_Q(); 
        /*
        cout <<" episode: "<< episode <<endl;
        //Print time 
                cout << "Execution Time: " << time << endl;
        //Print Ciclos
        cout << "Ciclos: " <<ciclos<<endl;*/

        go = check_q(go); //ver si esta estable Q

        if(go){
            string str; // a variable of str data type
            string strtim; // a variable of str data type
            string strcc; // a variable of str data type

            stringstream ss; 
            stringstream tt; 
            stringstream cc;  
            double time = (double(t1-t0)/CLOCKS_PER_SEC);
      
            ss << episode;  
            ss >> str;  

            datas.append("episode: "+str+"\n");

            tt << time;  
            tt >> strtim; 
            datas.append("Execution Time: "+strtim+"\n");
            
            cc << ciclos;  
            cc >> strcc; 
            datas.append("Ciclos: "+strcc+"\n\n");
            
            episode++;
            cout<<datas<<endl;           
        }

        
    }while(go);  // Unitil Q matix is stablish       
    
  salvar_Q();    
  salvar_data(datas);       
}     

//---------------------------------------------------------
void Q_exploit(void)  
{

  do{
    file_agent = random(files);
    column_agent = random(columns);
  }while(Q[file_agent][column_agent]==0);
  do{
    search_for_MAX();
    if(grad_pointer==0)move_left();
    else if(grad_pointer==1) move_right();
    else if(grad_pointer==2) move_up();
    else move_down();
    plot_agent();
    delay(31);
  }while(captured_color!=YELLOW);
}
//---------------------------------------------------------
void random_Q_exploit(void)  
{

  do{
    file_agent = random(files);
    column_agent = random(columns);
  }while(R[file_agent][column_agent]<0);
  do{
    plot_maze();
    grad_pointer = random(4);
    if(grad_pointer==0)move_left();
    else if(grad_pointer==1) move_right();
    else if(grad_pointer==2) move_up();
    else move_down();
    plot_agent();
    delay(31);
  }while(captured_color!=YELLOW);
}