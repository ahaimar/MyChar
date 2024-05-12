#include <clocale>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<string>
#include<iostream>
#include<stdbool.h>
#include<math.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
void gotoxy(int x,int y)
{
  COORD pos={x,y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
} 
typedef struct client 
                           {
	                         char ndc[12],nodc[15],pdc[15],adc[30],tdc[15];
                           }CLINT;
CLINT c ;
typedef struct Facturation{
                           	char ndlf[15],ddlf[30],ndc[12],num_c[15],nom_c[15],prenom_c[12];
                           	float tdlf,tTTC;
                           }FACT;
FACT f;                           

FILE*f_client,*f_fac,*fs;

void interface_Gestion_des_client(){
	
	system("cls");
	gotoxy(24,3);printf("  << GESTION DES CLIENTS >> ");
	gotoxy(5,5); printf("Numéro  du client   : ");
	gotoxy(5,8); printf("Nom du client       : ");
	gotoxy(5,11);printf("Prénom du client    : ");
	gotoxy(5,14);printf("Adresse du client   : ");
	gotoxy(5,17);printf("Téléphone du client : ");		
}
void interface_Gestion_de_facturation(){
	system("cls");
	gotoxy(25,1);printf("GESTION DE LA FACTURATION  ");
	gotoxy(5,5);printf("Numéro de la facture     : ");
    gotoxy(5,8);printf("Date de la facture       : ");
    gotoxy(5,11);printf("Numéro  du client        : ");
    gotoxy(5,14);printf("Nom du client            : ");
	gotoxy(5,17);printf("Prénom du client         : ");
	gotoxy(5,20);printf("Total de la facture      : ");	
	gotoxy(5,23);printf("Total TTC                : ");	
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++ Ajouter_client ++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool testerdoublon(char dbl[]){

bool tr;

f_client= fopen("d:\\client.txt","r");
if (f_client == NULL) {
        fclose(f_client);
        tr=false;
	}
    else
	{
		tr=false;   
		f_client = fopen("d:\\client.txt","r");
    	do {
        	fread(&c,sizeof(c),1, f_client);
        	if (!feof(f_client))
            	if (strcmp(dbl,c.ndc) == 0) {
            		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                	gotoxy(50,6);printf("*le client deja inscrit*");
                	tr = true;
            	}
    	} while (!feof(f_client) && (strcmp(dbl, c.ndc) != 0));
    	fclose(f_client);
	}
    return tr;
}
void Ajouter_client() {//*************************************************************************
    int ch1, ch2;
    char num_client[12];
    do {
        system("cls");
        interface_Gestion_des_client();
        do {
            gotoxy(28,5);printf("                  ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            gotoxy(28,5);gets(num_client);
        } while (testerdoublon(num_client));
        fflush(stdin);
        gotoxy(50,6);printf("                          ");
        strcpy(c.ndc,num_client);
        gotoxy(28,8);gets(c.nodc);
        gotoxy(28,11);gets(c.pdc);
		gotoxy(28,14);gets(c.adc);
		gotoxy(28,17);gets(c.tdc);
        gotoxy(5,20);printf("Voulez-vous Ajouter ce client (o/n)?:");
        ch1 = getch();
        if (toupper(ch1) == 'O') {
            f_client = fopen("d:\\client.txt","a");
            fwrite(&c, sizeof(c), 1, f_client);
            fclose(f_client);
        }
        gotoxy(5, 23);
        printf("Voulez-vous ajouter un autre client (o/n)?:");
        ch2 = getch();
        printf("\n");
    } while (toupper(ch2) == 'O');
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++ Ajouter_Facturation ++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++d:\\facturation.txt
bool testerdoublon_f(char a[]){
		
		bool tr;
		f_fac=fopen("d:\\facturation.txt","r");
		if (f_fac== NULL) {
		        fclose(f_fac);
		        tr=false;
			}
		    else
			{
				tr=false;
				f_fac= fopen("d:\\facturation.txt","r");
		    	do {
		        	fread(&f,sizeof(f),1,f_fac);
		        	if (!feof(f_fac))
		            	if (strcmp(a,f.ndlf) == 0) {
		            		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
		                	gotoxy(50,6);printf("*le client deja inscrit*");
		                	tr = true;
		            	}
		    	} while (!feof(f_fac) && (strcmp(a,f.ndlf) != 0));
		    	fclose(f_fac);
			}
		    return tr;
		}
void Ajouter_Facturation(){//*********************************************************************
    int ch1, ch2;
    char num_fa[12],num_fc[12],s[64];
    float num_ttc=0;
    float total_df=0;
    bool tr=false;
    do {
        system("cls");
        interface_Gestion_de_facturation();
       do {
        	fflush(stdin);
            gotoxy(32,5);printf("                   ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            gotoxy(32,5);gets(num_fa);
        } while (testerdoublon_f(num_fa));
        fflush(stdin);
        gotoxy(50,6);printf("                        ");
        strcpy(f.ndlf,num_fa);
        
        /***************************************date et time*****************************************/
			{
			    time_t t = time(NULL);
			    struct tm *tm = localtime(&t);
			    size_t ret = strftime(s, sizeof(s), "%c", tm);
			    assert(ret);
			    gotoxy(32,8);printf("%s\n", s);
			} 
		strcpy(f.ddlf,s);/*gotoxy(32,8);scanf("%s",f.ddlf);*/
		
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        
        do{
        	tr=false;
       		gotoxy(32,11);printf("                "); 
			gotoxy(32,11);gets(num_fc);
	   	 	f_client=fopen("d:\\client.txt","r");
	    if(f_client==NULL){ 
         gotoxy(5,5);printf("Fichier introuvable!!!");
      }
	  else{
	      do{
	         fread(&c,sizeof(c),1,f_client);
	         if(!feof(f_client))
             if (strcmp(num_fc,c.ndc)==0){
             	fflush(stdin);
	            gotoxy(32,14);puts(c.nodc);
	            gotoxy(32,17);puts(c.pdc);
	            fflush(stdin);
	            tr=true;
             	}
       		}while (!feof(f_client)&&(strcmp(num_fc,c.ndc)!=0));
       		fclose(f_client);
 		  }
   		 }while (tr==false);
   		 
   		 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   		 	strcpy(f.num_c,num_fc);
			strcpy(f.nom_c,c.nodc);
   		 	strcpy(f.prenom_c,c.pdc);
   		 
		gotoxy(32,20);scanf("%f",&total_df);
	    num_ttc=total_df+total_df*0.2;
	    gotoxy(32,23);printf("%.2f",num_ttc);
	    f.tTTC=num_ttc;
	    f.tdlf=total_df;
        gotoxy(5,25);printf("Voulez-vous Ajouter ce facturation (o/n)?: ");
        ch1 = getch();
        if (toupper(ch1) == 'O') {
            f_fac=fopen("d:\\facturation.txt","a");
            fwrite(&f,sizeof(f),1,f_fac);
            fclose(f_fac);
        }
        gotoxy(5,25);
        printf("Voulez-vous ajouter un autre facturation (o/n)?: ");
        ch2 = getch();
        printf("\n");
    } while (toupper(ch2) == 'O');

}
//************************************************************************************************
//********************************Rechercher client ()********************************************
//************************************************************************************************
 void Rechercher_client(){
	  char num_client[12];
      bool tr=false;  
      
      system("cls");
	  gotoxy(5,5);printf("Numéro du client à rechercher :");
	  gotoxy(37,5);gets(num_client);
	  f_client=fopen("d:\\client.txt","r");
	  if(f_client==NULL)
      { 
         gotoxy(5,5);printf("Fichier introuvable!!!");
      }
	  else
      {
	      do
          {
	         fread(&c,sizeof(c),1,f_client);
	         if(!feof(f_client))
             if (strcmp(num_client,c.ndc)==0)
             {
	            interface_Gestion_des_client();
	              gotoxy(30,5);puts(c.ndc);
	              gotoxy(30,8);puts(c.nodc);
	              gotoxy(30,11);puts(c.pdc);
	              gotoxy(30,14);puts(c.adc);
	              gotoxy(30,17);puts(c.tdc);
	              fflush(stdin);
	            tr=true;
             }
       }while (!feof(f_client)&&(strcmp(num_client,c.ndc)!=0));
	   if (tr==false)
       {
		  gotoxy(5,5);printf("Pas de client avec ce Numéro!!!");
	   }
    }
    fclose(f_client);
    gotoxy(5,20);printf("Taper une touche pour revenir au menu principal  ");
    getch();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++ Rechercher_Facturation +++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Rechercher_Facturation(){
	  char num_facturation[15];
      bool tr=false;
      system("cls");
	  gotoxy(3,5);printf("Numéro du Facturation à rechercher :");
	  gotoxy(40,5);gets(num_facturation);
	  f_fac=fopen("d:\\facturation.txt","r");
	  if(f_fac==NULL)
      { 
         gotoxy(5,5);printf("Fichier introuvable!!!");
      }
	  else
      {
	      do
          {
	         fread(&f,sizeof(f),1,f_fac);
	         if(!feof(f_fac))
             if (strcmp(num_facturation,f.ndlf)==0)
             {
             	system("cls");
	            gotoxy(5,5);printf("Numéro de la facture      : ");gotoxy(33,5);printf("%s",f.ndlf);
	            gotoxy(5,8);printf("Date de la facture        : ");gotoxy(33,8);printf("%s",f.ddlf);
	            gotoxy(5,11);printf("Numéro  du client        : ");gotoxy(33,11);printf("%s",f.num_c);
	            gotoxy(5,14);printf("Nom du client            : ");gotoxy(33,14);printf("%s",f.nom_c);
	            gotoxy(5,17);printf("Prénom du client         : ");gotoxy(33,17);printf("%s",f.prenom_c);
	            gotoxy(5,20);printf("Total de la facture      : ");gotoxy(33,20);printf("%.2f",f.tdlf);
	            gotoxy(5,23);printf("Total TTC                : ");gotoxy(33,23);printf("%.2f",f.tTTC);
	              
	            tr=true;
             }
       }while (!feof(f_fac)&&(strcmp(num_facturation,f.ndlf)!=0));
        fclose(f_fac);
	   if (tr==false)
       {
		  gotoxy(5,5);printf("Pas de factuation avec ce Numéro!");
	   }
    }
    gotoxy(5,26);printf("Taper une touche pour revenir au menu principal  ");
    getch();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++ Lister_client ++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Lister_client(){ 
      system("cls");
      int i=0;
	  gotoxy(29,5);
      printf("La liste les client triés");
	  gotoxy(4,8);
      printf("Numéro d_c");
	  gotoxy(19,8);
      printf("Nom d_c");
	  gotoxy(34,8);
      printf("Prénom d_c");
	  gotoxy(52,8);
      printf("Adresse ");
	  gotoxy(70,8);
      printf("Téléphone ");
	  f_client=fopen("d:\\client.txt","r");
	  do
      {
	     	fread(&c,sizeof(c),1,f_client);
	     	if(!feof(f_client))
         	{
	            i++;
	            gotoxy(5,8+i*2); printf("%s",c.ndc);
	            gotoxy(19,8+i*2);printf("%s",c.nodc);
	            gotoxy(34,8+i*2);printf("%s",c.pdc);
	            gotoxy(52,8+i*2);printf("%s",c.adc);
	            gotoxy(70,8+i*2);printf("%s",c.tdc);
			}
      }while(!feof(f_client));
	  fclose(f_client);
	  gotoxy(10,12+i*2);
	  //system("COLOR 4");
      printf("Taper une touche pour revenir au menu principal : ");
	  gotoxy(60,12+i*2);
	  getch();  
	}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++ Lister_Facturation +++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Lister_Facturation(){ 
      system("cls");
      int i=0;
	  gotoxy(29,5);printf("La liste les client triés");
	  gotoxy(1,8);printf("Numéro de facturation");
	  gotoxy(25,8);printf("date");
	  gotoxy(40,8);printf("numéro d_c");
	  gotoxy(55,8);printf("Nom d_c");
	  gotoxy(67,8);printf("Prénom d_c");
	  gotoxy(84,8);printf(" total d_f "); 
	  gotoxy(100,8);printf("TTc");
	  f_fac=fopen("d:\\facturation.txt","r");
	  do
      {
	     	fread(&f,sizeof(f),1,f_fac);
	     	if(!feof(f_fac))
         	{
	            i++;
	            gotoxy(1,10+i*2);puts(f.ndlf);
	            gotoxy(25,10+i*2);puts(f.ddlf);
	            gotoxy(46,10+i*2);puts(f.num_c);
	            gotoxy(55,10+i*2);puts(f.nom_c);
	            gotoxy(67,10+i*2);puts(f.prenom_c);
	            gotoxy(84,10+i*2);printf("%.2f",f.tdlf);
	            gotoxy(100,10+i*2);printf("%.2f",f.tTTC);
			}
      }while(!feof(f_fac));
	  fclose(f_fac);
	  gotoxy(20,14+i*2);
      printf("Taper une touche pour revenir au menu principal : ");
	  gotoxy(60,16+i*2);
	  getch();  
	}  
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++ supprimer_client+++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++		
void supprimer_client(){
   int rep,ch1;
   bool tr;
   char t[15];
   do{
		tr=false;
		system("cls");
       	gotoxy(10,5);
	   	f_client=fopen("d:\\client.txt","r");
	   	printf("Numéro de la carte d'idendité du client à supprimer :");
	   	scanf("%s",t);
       	fs=fopen("d:\\client_s.txt","w");
       	fclose(fs);
        if(f_client!=NULL)
        {
	          while(!feof(f_client))
	          {
	             fread(&c,sizeof(c),1,f_client);
	             if (strcmp(t,c.ndc)!=0)
	             {
	               if(!feof(f_client)){               	
	               	 fs=fopen("d:\\client_s.txt","a");
	               	 fwrite(&c,sizeof(c),1,fs);
	         	   	 fclose(fs);      	 
				   }
	                   
	             }
	               else 
	               {
	                	interface_Gestion_des_client();
		               	gotoxy(30,5);puts(c.adc);
		              	gotoxy(30,8);puts(c.nodc);
		              	gotoxy(30,11);puts(c.pdc);
		              	gotoxy(30,14);puts(c.adc);
		               	gotoxy(30,17);puts(c.tdc);
		
		            	tr=true;
	             	}
	          }
		 		  fclose(f_client);
		  		 if(tr==true)
	       {
	       	gotoxy(15,20);printf("                                                ");
	          gotoxy(15,20);printf("Etes-vous sûr de  supprimer ce client o/n?:");
	          ch1=getch();
		      if (toupper(ch1)=='O'){
	             remove("d:\\client.txt");
		         rename("d:\\client_s.txt","d:\\client.txt");
		         gotoxy(15,20);printf("                                            ");
	       	     gotoxy(15,20);printf("Le client est bien supprimé!");
	             getch();
	          }
		      else remove("d:\\client_s.txt");
	       }
	       else{
	            remove("d:\\client_s.txt");
	            gotoxy(15,20);printf("                                              ");
		        gotoxy(15,20);printf("Numéro introuvable!");
		        getch();
	       }
	       gotoxy(15,20);printf("                                                   ");
		   gotoxy(15,20);printf("Autre client à supprimer o/n?:");
		   rep=getch();
    	}
    else{
    	gotoxy(15,20);printf("                                                      ");
    	gotoxy(15,20);printf("Fichier introuvable!");
	}
	}while(toupper(rep)=='O');
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++ supprimer_facturation ++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void supprimer_facturation(){
   int rep,ch1;
   bool tr;
   char c[12];
   do{
		tr=false;
		system("cls");
       	gotoxy(10,5);
	   	f_fac=fopen("d:\\facturation.txt","r");
	   	printf("Le numéro de facture à supprimer :");
	   	scanf("%s",c);
       	fs=fopen("d:\\fac_s.txt","w");
       	fclose(fs);
        if(f_fac!=NULL)
        {
          while(!feof(f_fac))
          {
             fread(&f,sizeof(f),1,f_fac);
             if (strcmp(c,f.ndlf)!=0)
             {
               if(!feof(f_fac)){               	
               	 fs=fopen("d:\\fac_s.txt","a");
               	 fwrite(&f,sizeof(f),1,fs);
         	   	 fclose(fs);      	 
			   }
                   
             }
               else 
               {
                		interface_Gestion_de_facturation();
	                	fflush(stdin);
		               	gotoxy(32,5);puts(f.ndlf );
		               	gotoxy(32,8);puts(f.ddlf);
		              	gotoxy(32,11);puts(f.num_c);
		              	gotoxy(32,14);puts(f.nom_c);
		              	gotoxy(32,17);puts(f.prenom_c);
		              	gotoxy(32,20);printf("%.2f",f.tdlf);
		               	gotoxy(32,23);printf("%.2f",f.tTTC);
		            	tr=true;
             	}
          }
	   fclose(f_fac);
	   if(tr==true)
       {
          gotoxy(15,26);printf("Etes-vous sûr de  supprimer ce facturation o/n?:");
		  ch1=getch();
          gotoxy(15,26);printf("                                                ");
	      if (toupper(ch1)=='O'){
             remove("d:\\facturation.txt");
	         rename("d:\\fac_s","d:\\facturation.txt");
	         
       	    gotoxy(15,26);printf("Le facture est bien supprimé!");
			gotoxy(15,26);printf("                                                ");
             //getch();
          }
	      else remove("d:\\fac_s");
       }
       else{
            remove("d:\\fac_s");
			getch();
	        gotoxy(15,26);printf("Numéro introuvable!");
	        
       }
       
	   gotoxy(15,26);printf("Autre facture à supprimer o/n?:");
	   rep=getch();
	   gotoxy(15,26);printf("                                                      ");
	   
    }
    else{
    	gotoxy(15,28);printf("Fichier introuvable!");
	}
	}while(toupper(rep)=='O');
 }
//************************************************************************************************
//*******************************modifie_client***************************************************
//************************************************************************************************
void numr_c(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
			gotoxy(2,5);printf("1::");gotoxy(42,5);printf("!!");
			gotoxy(2,8);printf("2::");
			gotoxy(2,11);printf("3::");
			gotoxy(2,14);printf("4::");
			gotoxy(2,17);printf("5::");
			}
void modifie_client(){
	
   bool tr=false;
   bool com=false;
   int pos,ln,q;
   char ncp[12];
   do{
      	system("cls");
     	gotoxy(30,3);printf(" Modifier le client");
     	gotoxy(5,6);printf("Numéro du client à modifier :     ");
     	gotoxy(35,6);scanf("%s",ncp);
     	f_client=fopen("d:\\client.txt","r");
     	if(f_client==NULL)
     	{ 
            gotoxy(22,9);
            printf("Fichier introuvable!!!");
     	}
     	else
     	{
       		do{
          		pos=ftell(f_client);
          		fread(&c,sizeof(c),1,f_client);
	      		if (strcmp(ncp,c.ndc)==0)
          		{
	         		interface_Gestion_des_client();
	         		numr_c();
	            	gotoxy(30,5);puts(c.ndc);
	            	gotoxy(30,8);puts(c.nodc);
	            	gotoxy(30,11);puts(c.pdc);
	            	gotoxy(30,14);puts(c.adc);
	            	gotoxy(30,17);puts(c.tdc);
              		tr=true;
       			}
			}while (!feof(f_client)&&(strcmp(ncp,c.ndc)!=0));
			fclose(f_client);
			if (tr==false){
				gotoxy(5,20);printf("                                       ");
	   			gotoxy(5,20);printf("Pas de client avec ce Numéro!!!");
			}
			else{	    
	    		do{
	    			gotoxy(5,21);printf("                                    ");
              		gotoxy(5,21); printf("Numéro de la ligne à modifier : ");
              		gotoxy(37,21);scanf("%d",&ln);
	          		switch(ln)
              		{
              			
		             //case 1 :gotoxy(30,5);printf("                                ");gotoxy(30,5);scanf("%s",c.ndc);gotoxy(30,8);break;
		             case 2 :gotoxy(30,8);printf("                                ");gotoxy(30,8);scanf("%s",c.nodc);gotoxy(30,11);break;
		             case 3 :gotoxy(30,11);printf("                                ");gotoxy(30,11);scanf("%s",c.pdc);gotoxy(30,14);break;
		             case 4 :gotoxy(30,14);printf("                                ");gotoxy(30,14);scanf("%s",c.adc);gotoxy(30,17);break;
		             case 5 :gotoxy(30,17);printf("                                ");gotoxy(30,17);scanf("%s",c.tdc);gotoxy(30,5);break;
               			fflush(stdin);
					   }
					   
               		gotoxy(5,21); printf("                                                      ");
               		gotoxy(5,21); printf("Autre ligne à modifier o/n:");
               		q=getch();
	     		}while(toupper(q)=='O');
	     		gotoxy(5,21); printf("                                                          ");
         		gotoxy(5,21); printf("Voulez vous vraiment modifier cet Ajuterment o/n?");
         		q=getch();
         		if(toupper(q)=='O')
         		{
            		f_client=fopen("d:\\client.txt","r+");
            		fseek(f_client,pos,0);
            		fwrite(&c,sizeof(c),1,f_client);
            		if(f_fac!=NULL){
            			f_fac=fopen("d:\\facturation.txt","r+");
            			strcpy(f.num_c,c.ndc);
            			strcpy(f.nom_c,c.nodc);
            			strcpy(f.prenom_c,c.pdc);
            			fwrite(&f,sizeof(f),1,f_fac);
					}
            		fclose(f_client);fclose(f_fac);
         		}
        	}
        }
        gotoxy(16,22); printf("                                                          ");
        gotoxy(16,22); printf("modifier un autre Ajoutrement o/n?:");
        q=getch();
    }while(toupper(q)=='O');
}
//************************************************************************************************
//********************************** modifier_facturation ****************************************
//************************************************************************************************
void numeration_fac(){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
	
			gotoxy(2,3);printf("N°");
			gotoxy(2,5);printf("1::");gotoxy(42,5);printf("!?");
			gotoxy(2,8);printf("2::");gotoxy(51,8);printf("!!");
			gotoxy(2,11);printf("3::");
			gotoxy(2,14);printf("4::");
			gotoxy(2,17);printf("5::");
			gotoxy(2,20);printf("6::");
			gotoxy(2,23);printf("7::");gotoxy(42,23);printf("!?");
			gotoxy(62,6);printf("<<note importante>>");
			gotoxy(58,7);printf("+++++++++++++++++++++++++++++++++ ");
			gotoxy(58,16);printf("+++++++++++++++++++++++++++++++++ ");
			gotoxy(58,8);printf("+                               + ");
			gotoxy(58,9);printf("+                               + ");
			gotoxy(58,10);printf("+                               + ");
			gotoxy(58,11);printf("+                               + ");
			gotoxy(58,12);printf("+                               + ");
			gotoxy(58,13);printf("+                               + ");
			gotoxy(58,14);printf("+                               + ");
			gotoxy(58,15);printf("+                               + ");
			gotoxy(60,9);printf("Les numéros 1,2,3 et 7 ne ");
			gotoxy(60,11);printf("peuvent pas être modifiés à ");
			gotoxy(60,13);printf("cet endroit !!/!?");
	
}
void modifier_facturation(){
   bool tr=false;
   int pos,ln,q;
   char ncp[12];
   do{
      	system("cls");
     	gotoxy(30,3);printf(" Modifier le factures");
     	gotoxy(16,6);printf("Numéro du factures à modifier :     ");
     	gotoxy(50,6);scanf("%s",ncp);
     	f_fac=fopen("d:\\facturation.txt","r");
     	if(f_fac==NULL)
     	{ 
            gotoxy(5,9);
            printf("Fichier introuvable!!!");
     	}
     	else
     	{
       		do{
          		pos=ftell(f_fac);
          		fread(&f,sizeof(f),1,f_fac);
	      		if (strcmp(ncp,f.ndlf)==0)
          		{
	         		interface_Gestion_de_facturation();
	         		numeration_fac();
					 }
	            	gotoxy(32,5);printf("%s",f.ndlf);
	            	gotoxy(32,8);printf("%s",f.ddlf);
	            	gotoxy(32,11);printf("%s",f.num_c);
	            	gotoxy(32,14);printf("%s",f.nom_c);
	            	gotoxy(32,17);printf("%s",f.prenom_c);
	            	gotoxy(32,20);printf("%.2f",f.tdlf);
	            	gotoxy(32,23);printf("%.2f",f.tTTC);
	            	
              		tr=true;
			}while (!feof(f_fac)&&(strcmp(ncp,f.ndlf)!=0));
			fclose(f_fac);
			if (tr==false){
	   			gotoxy(16,9);printf("Pas de factures avec ce Numéro .");
			}
			else{	    
	    		do{
	    			gotoxy(36,25);printf("         ");
	    			gotoxy(5,26); printf("                                                      ");
              		gotoxy(5,25);printf("Numéro de la ligne à modifier: ");
              		scanf("%d",&ln);
	          		switch(ln)
              		{
		             //case 3 :gotoxy(32,11);printf("                                ");gotoxy(32,11);scanf("%s",f.num_c);gotoxy(42,14);break;
		             case 4 :gotoxy(32,14);printf("                                ");gotoxy(32,14);scanf("%s",f.nom_c);gotoxy(42,17);break;
		             case 5 :gotoxy(32,17);printf("                                ");gotoxy(32,17);scanf("%s",f.prenom_c);gotoxy(42,20);break;
		             case 6 :gotoxy(32,20);printf("                                ");gotoxy(32,20);scanf("%f",&f.tdlf);f.tTTC=f.tdlf+f.tdlf*0.2;gotoxy(32,23);printf("%0.2f",f.tTTC);break;
		            }
               		gotoxy(5,26); printf("                                                          ");
               		gotoxy(5,26); printf("Autre ligne à modifier o/n:");
               		q=getch();
	     		}while(toupper(q)=='O');
	     		gotoxy(5,26); printf("                                                              ");
         		gotoxy(5,26); printf("Voulez vous vraiment modifier cet enregistrement o/n?");
         		q=getch();
         		if(toupper(q)=='O')
         		{
            		f_fac=fopen("d:\\facturation.txt","r+");
            		fseek(f_fac,pos,0);
            		if(f_client!=NULL){
            			f_fac=fopen("d:\\client.txt","r+");
            			strcpy(c.ndc,f.num_c);
            			strcpy(c.nodc,f.nom_c);
            			strcpy(c.pdc,f.prenom_c);
            			fwrite(&c,sizeof(c),1,f_client);
					}
            		fwrite(&f,sizeof(f),1,f_fac);
            		fclose(f_fac);fclose(f_client);
         		}
        	}
        }
        gotoxy(16,28); printf("                                                          ");
        gotoxy(16,28); printf("modifier un autre enregistrement o/n?:");
        q=getch();
    }while(toupper(q)=='O');
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++<  menu  >++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void menu(){
 	
	int nm;
	
	do
	{
		system("cls") ;
		
			gotoxy(35,3);puts(" **< Gestion de la facturation  >**");
			gotoxy(5,6);puts("Ficher client");
			gotoxy(5,9);puts("1: <*Ajouter un client *>");
			gotoxy(5,12);puts("2: <Rechercher un client> ");
			gotoxy(5,15);puts("3: <* Lister les client triés*>");
			gotoxy(5,18);puts("4: <* Modifier un client*>");
			gotoxy(5,21);puts("5: <Supprimer un e client> ");
			gotoxy(38,6);puts("Traitement des factures ");
			gotoxy(38,9);puts("6: <Ajouter facture>");
			gotoxy(38,12);puts("7: <Rechercher facture>");
			gotoxy(38,15);puts("8: <* Lister les facture*>");
			gotoxy(38,18);puts("9: <* Modifier facture*>");
			gotoxy(38,21);puts("10:<Supprimer facture> ");
			gotoxy(70,6);puts(" Quitter l'application");
		    gotoxy(70,9);puts("11:<* Quitter  *>");			
			do
			{
				gotoxy(15,25);
				puts(" Entrer votre choix :");
				gotoxy(36,25);
				scanf("%d",&nm);fflush(stdin);
			}while((nm<1)||(nm>11));
			switch(nm)
			{
					case 1:Ajouter_client();break;
					case 2:Rechercher_client();break;
					case 3:Lister_client();break;
					case 4:modifie_client();break;
					case 5:supprimer_client();break;
					//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					case 6:Ajouter_Facturation();break;
					case 7:Rechercher_Facturation();break;
					case 8:Lister_Facturation();break;
					case 9:modifier_facturation();break;
					case 10:supprimer_facturation();break; 
				
			}
	}while (nm!=11);
}
main(){
	system("cls");
    setlocale( LC_CTYPE , "fra" ) ;
	menu();
}

