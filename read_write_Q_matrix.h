
//================================================================================================================

int load_Q(void)    //   carga valores de Q-matrix desde el dico duro
{
	int k, i, aux;
	int numero;
	FILE *in_file;
	aux=0;
	if ((in_file = fopen ("q_matrix.dat", "rt")) == NULL)
		aux=1;
	else
	{
		fseek(in_file, 0, SEEK_SET);
		for (k=0; k<files; k++)
			for (i=0; i<columns; i++)
			{
				fscanf(in_file, "%i", &numero);
				Q[k][i]=numero;
			}
	}
	fclose(in_file);
	
    moveto(420,445);
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    outtext("matrix Q loaded");
    return(aux);
}
//-----------------------------------------------
int salvar_Q(void)                 // guarda valores de Q-matrix en el dico duro
{
	int k, i, aux;
	int numero;
	FILE *out_file;
	aux=0;
	if ((out_file = fopen ("q_matrix.dat", "wt")) == NULL)
		aux=1;
	else
	{
		fseek(out_file, 0, SEEK_SET);
		for (k=0; k<files; k++)
			for (i=0; i<columns; i++)
			{
				numero=Q[k][i];
				fprintf(out_file, "%i %c", numero,' ');
			}
		  
	}
	fclose(out_file);
    moveto(300,20);
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    outtext("matrix Q saved ");
	return(aux);
}

//-----------------------------------------------
void salvar_data(string datas){
	cout<<datas<<endl;
	ofstream myfile;
	myfile.open ("datas.txt");
	myfile << datas;
	myfile.close();
}