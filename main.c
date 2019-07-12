#include "types.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "mats.h"
#include "inout.h"

int main(int argc, char const *argv[])
{
	printf("\n╔════════════════════════════════════════════╗\n");
    printf("║ Matrizenrechner Version 0.1 by Peter Stehr ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");   
    bool change_mat = true;
    //Schleife zum Einlesen der Matrix
    while(change_mat)
    {
        change_mat = false;
        //Matrix Einlesen
        Matrix *A = read_mat();
        int option = 0;
		bool new_option = false;
        //Schleife für die Optionenwahl
		do
		{
			bool exit = false;
			new_option = false;
			enum { MAX_OPT = 16 }; //Wie viele eingabe optionen gibt es?
			do
			{
                //Menü ausgeben und Auswahl einlesen
				printf("\nEingegebene Matrix:\n");
				print_mat(A);
				printf("╔════════╗\n");
				printf("║Optionen║\n");
				printf("╠════════╝\n");
			    printf("╟(1): Matrix-Addition\n");
			    printf("╟(2): Matrix-Multiplikation\n");
			    printf("╟(3): Matrix-Skalarmultiplikation\n");
			    printf("╟(4): Spur berechnen\n");
			    printf("╟(5): Hauptdiagonalenprodukt berechnen\n");
			    printf("╟(6): Obere Dreiecksform bestimmen\n");
			    printf("╟(7): Determinante berechnen\n");
			    printf("╟(8): Aij bestimmen\n");
			    printf("╟(9): Aij' bestimmen\n");
			    printf("╟(10): Adjunkte bestimmen\n");
			    printf("╟(11): Inverses berechnen\n");
			    printf("╟(12): Rang berechnen\n");
			    printf("╟(13): Stufen in Ordnung brinen\n");
			    printf("╟(14): Spezielle Zeilenstufenform\n");
			    printf("╟(15): Lösung von Gleichungssystem\n");
			    printf("╟(16): Kern bestimmen\n");
				printf("╙(0): Programm verlassen\n");
				printf("\nOptionsauswahl: ");
				scanf("%d", &option);
				if(option < 0 || option > MAX_OPT)
				{
					printf("Ungültige Eingabe!\n");
				}
				putchar('\n');
			}
			while(option < 0 || option > MAX_OPT);
            //Eingabeoptionen
            if(option == 1)
		    {
		    	//Matrix-Addition
				printf("Geben Sie die zu Addierende Matrix ein:\n");
				printf("Zeilenzahl = %d\n", A->r);
				printf("Spaltenzahl = %d\n", A->c);
				Matrix *B = read_coe(A->r, A->c);
				printf("\nA =\n");
				print_mat(A);
				printf("\nB =\n");
				print_mat(B);
				printf("\nA + B =\n");
				print_mat(mat_add(A, B));
		    }
		    else if(option == 2)
		    {
		    	//Matrix-Multiplikation
				printf("Geben Sie die zu Multiplizierende Matrix ein:\n");
				printf("Zeilenzahl = %d\n", A->c);
				Matrix *B = read_coe(A->c, read_col());
				printf("\nA =\n");
				print_mat(A);
				printf("\nB =\n");
				print_mat(B);
				printf("\nA * B =\n");
				print_mat(mat_mul(A, B));
		    }
		    else if(option == 3)
		    {
		    	//Matrix-Skalarmultiplikation
				printf("Geben Sie das Skalar a ein: ");
				double a;
				scanf("%lf", &a);
				printf("\nA =\n");
				print_mat(A);
				printf("\na * A =\n");
				print_mat(mat_skal_mul(A, a));
		    }
		    else if(option == 4)
		    {
		    	//Spur
				if(mat_is_quad(A))
				{
					printf("A =\n");
					print_mat(A);
					printf("\nSpur(A) = %g\n", mat_spur(A));
				}
				else
				{
					printf("Um die Spur zu bestimmen muss die Matrix quadratisch sein!\n");
				}
		    }
		    else if(option == 5)
		    {
		    	//Hauptdiagonalenprodukt
				if(mat_is_quad(A))
				{
					printf("A =\n");
					print_mat(A);
					printf("\nProdukt der Hauptdiagonale von A = %g\n", mat_spur(A));
				}
				else
				{
					printf("Um das Hauptdiagonalenprodukt zu bestimmen muss die Matrix quadratisch sein!\n");
				}
		    }
		    else if(option == 6)
		    {
		    	//Obere Dreiecksform
				printf("A =\n");
				print_mat(A);
				Matrix *B = mat_gauss(A);
				printf("\nObere Dreiecksform:\n");
				print_mat(B);
		    }
		    else if(option == 7)
		    {
		    	//Determinante
				if(mat_is_quad(A))
				{
					printf("A =\n");
					print_mat(A);
					printf("\ndet(A) = %g\n", determinant(A));
				}
				else
				{
					printf("Um die Determinante zu berechnen muss die Matrix quadratisch sein!\n");
				}		
		    }
		    else if(option == 8)
		    {
		    	//aij
				int i = read_row_index(A);
				int j = read_col_index(A);
				printf("A =\n");
				print_mat(A);
				Matrix *B = mat_ij(A, i, j);
				printf("\nAij =\n");
				print_mat(B);
		    }
		    else if(option == 9)
		    {
		    	//aij'
				int i = read_row_index(A);
				int j = read_col_index(A);
				printf("A =\n");
				print_mat(A);
				Matrix *B = mat_ij_(A, i, j);
				printf("\nAij' =\n");
				print_mat(B);	
		    }
		    else if(option == 10)
		    {
		    	//adj(A)
				if(mat_is_quad(A))
				{
					printf("A =\n");
					print_mat(A);
					Matrix *B = mat_adj(A);
					printf("\nadj(A) =\n");
					print_mat(B);
				}
				else
				{
					printf("Um die Adjunkte zu berechnen muss die Matrix quadratisch sein!\n");
				}		
		    }
		    else if(option == 11)
		    {
		    	//Inverses
				if(mat_is_quad(A))
				{
					if(mat_invertable(A))
					{
						printf("A =\n");
						print_mat(A);
						Matrix *B = mat_inverse(A);
						printf("\nA^-1 =\n");
						print_mat(B);
					}
					else
					{
						printf("Die Matrix ist nicht invertierbar!\n");
					}
				}
				else
				{
					printf("Nur quadratische Matrizen haben ein Inverses!\n");
				}		
		    }
		    else if(option == 12)
		    {
		    	//rang(A)
				printf("A =\n");
				print_mat(A);
				printf("\nrang(A) = %d\n", mat_rang(A));
		    }
		    else if(option == 13)
		    {
		    	//Stufenorder
				printf("A =\n");
				print_mat(A);
				Matrix *B = mat_step_order(A);				
				printf("\nB =\n");
				print_mat(B);
		    }
		    else if(option == 14)
		    {
		    	//spezielle Zeilenstufenform
				printf("A =\n");
				print_mat(A);
				Matrix *B = mat_spez_step(A);				
				printf("\nB =\n");
				print_mat(B);
		    }
		    else if(option == 15)
		    {
		    	//LGS lösen
		    	printf("Geben Sie die Nebenbedingun (Vektor) ein:\n");
				printf("Zeilenzahl = %d\n", A->r);
				printf("Spaltenzahl = 1\n");
				Matrix *B = read_coe(A->r, 1);
				printf("A =\n");
				print_mat(A);
				printf("B =\n");
				print_mat(B);
				if(mat_rang(A) == A->r)
				{
					Solution *S = mat_spez_solution(A, B);			
					putchar('\n');
					print_solution(S);
				}
				else
				{
					printf("Die Lösung des LGS ist nicht eindeutig!\n");
				}
		    }
		    else if(option == 16)
		    {
		    	//Kern bestimmen
				printf("A =\n");
				print_mat(A);
				printf("kern(A) = \n");
				print_vr(mat_core(A));
		    }
			else
			{
				//Programm beenden
                printf("Programm beendet.\n\n");
				exit = true;
				new_option = false;
			}
			//Weitere Aktion durchführen?
			if(!change_mat && !exit)
			{
				printf("\nWeitere Aktion durchführen? (j: ja / n: nein) ");
				if(check_jn())
				{
					new_option = true;
				}
			}
        }
        while(new_option);
    }
    return 0;
}