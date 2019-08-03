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
    printf("\nMatrizenrechner Version 0.2 by Peter Stehr\n");
    printf("――――――――――――――――――――――――――――――――――――――――――\n\n");
    bool change_mat = true;
    //Schleife zum Einlesen der Matrix
    while(change_mat)
    {
        change_mat = false;
        //Matrix Einlesen
        Matrix *A = read_mat();
        int option = 0;
		bool new_option;
        //Schleife für die Optionenwahl
		do
		{
			bool exit = false;
			new_option = false;
			enum { MAX_OPT = 15 }; //Wie viele eingabe optionen gibt es?
			do
			{
                //Menü ausgeben und Auswahl einlesen
				printf("\nEingegebene Matrix: A =\n");
				print_mat(A);
                printf("\n(01):  Matrix ändern\n");
			    printf("(02): Matrix-Addition\n");
			    printf("(03): Matrix-Multiplikation\n");
			    printf("(04): Matrix-Skalarmultiplikation\n");
                printf("(05): Matrix potenzieren\n");
                printf("(06): Determinante berechnen\n");
                printf("(07): Obere Dreiecksform bestimmen\n");
                printf("(08): Spezielle Zeilenstufenform\n");
                printf("(09): Inverses berechnen\n");
                printf("(10): Adjunkte bestimmen\n");
                printf("(11): Transponierte bestimmen\n");
                printf("(12): Lösung von speziellem Gleichungssystem\n");
                printf("(13): Kern bestimmen\n");
                printf("(14): Trafo-Formel anwenden\n");
			    printf("(15): Generelle Eigenschaften anzeigen\n");
				printf("(00): Programm verlassen\n");
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
                change_mat = true;
            }
            else if(option == 2)
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
				Matrix *C = mat_add(A, B);
				print_mat(C);
				if(change_mat_prompt())
                {
				    A = C;
                }
                free_mat(B);
                free_mat(C);
		    }
            else if(option == 3)
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
				Matrix *C = mat_mul(A, B);
				print_mat(C);
                if(change_mat_prompt())
                {
                    A = C;
                }
                free_mat(B);
                free_mat(C);
		    }
            else if(option == 4) {
                //Matrix-Skalarmultiplikation
                printf("Geben Sie das Skalar a ein: ");
                double a;
                scanf("%lf", &a);
                printf("\nA =\n");
                print_mat(A);
                Matrix *B = mat_skal_mul(A, a);
                printf("\n%g * A =\n", a);
                print_mat(B);
                if(change_mat_prompt())
                {
                    A = B;
                }
                free_mat(B);
            }
            else if(option == 5) {
                //Matrix potenzieren
                int n;
                int invertable = mat_invertable(A);
                do
                {
                    printf("Geben Sie die Potenz n ein: ");
                    scanf("%d", &n);
                    if(n == 0 && !invertable)
                    {
                        printf("Die Matrix muss invertierbar sein, um mit 0 potenziert zu werden.");
                    }
                }
                while(n < 0 || (n == 0 && !invertable));
                printf("\nA =\n");
                print_mat(A);
                Matrix *B = mat_pow(A, n);
                printf("\nA");
                print_high_number(n);
                printf(" =\n");
                print_mat(B);
                if(change_mat_prompt())
                {
                    A = B;
                }
                free_mat(B);
            }
            else if(option == 6)
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
            else if(option == 7)
		    {
		    	//Obere Dreiecksform
				printf("A =\n");
				print_mat(A);
				Matrix *B = mat_gauss(A);
				printf("\nObere Dreiecksform:\n");
				print_mat(B);
                if(change_mat_prompt())
                {
                    A = B;
                }
                free_mat(B);
		    }
            else if(option == 8)
            {
                //spezielle Zeilenstufenform
                printf("A =\n");
                print_mat(A);
                Matrix *B = mat_spez_step(A);
                printf("\nB =\n");
                print_mat(B);
                if(change_mat_prompt())
                {
                    A = B;
                }
                free_mat(B);
            }
            else if(option == 9)
            {
                //Inverses
                if(mat_is_quad(A))
                {
                    if(mat_invertable(A))
                    {
                        printf("A =\n");
                        print_mat(A);
                        Matrix *B = mat_inverse(A);
                        printf("\nA⁻¹ =\n");
                        print_mat(B);
                        if(change_mat_prompt())
                        {
                            A = B;
                        }
                        free_mat(B);
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
                    if(change_mat_prompt())
                    {
                        A = B;
                    }
                    free_mat(B);
				}
				else
				{
					printf("Um die Adjunkte zu berechnen muss die Matrix quadratisch sein!\n");
				}		
		    }
            else if(option == 11)
            {
                //Transponierte
                printf("A =\n");
                print_mat(A);
                Matrix *B = mat_trans(A);
                printf("\ntrans(A) =\n");
                print_mat(B);
                if(change_mat_prompt())
                {
                    A = B;
                }
                free_mat(B);
            }
            else if(option == 12)
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
                free_mat(B);
		    }
            else if(option == 13)
		    {
		    	//Kern bestimmen
				printf("A =\n");
				print_mat(A);
				printf("kern(A) = \n");
				print_vr(mat_core(A));
		    }
            else if(option == 14)
            {
                //Trafo-Formel
                printf("Geben Sie die Basiswechsel-Matrix ein:\n");
                printf("Zeilenzahl = %d\n", A->r);
                printf("Spaltenzahl = %d\n", A->c);
                Matrix *B = read_coe(A->r, A->c);
                if(mat_invertable(B))
                {
                    printf("\nA =\n");
                    print_mat(A);
                    printf("\nS =\n");
                    print_mat(B);
                    printf("\nS⁻¹ * A * S =\n");
                    print_mat(mat_trafo_formel(A, B));
                    if(change_mat_prompt())
                    {
                        A = B;
                    }
                }
                else
                {
                    printf("Die Basiswechselmatrix muss invertierbar sein!\n");
                }
                free_mat(B);
            }
            else if(option == 15)
            {
                //Infoblatt
                printf("A =\n");
                print_mat(A);
                printf("\ndet(A) = %g\n", determinant(A));
                printf("Spur(A) = %g\n", mat_spur(A));
                //nilpotenz
                if(is_nilpotent(A))
                {
                    printf("A ist nilpotent.\n");
                }
                else
                {
                    printf("A ist nicht nilpotent.\n");
                }
                //idempotenz
                if(is_idempotent(A))
                {
                    printf("A ist idempotent.\n");
                }
                else
                {
                    printf("A ist nicht idempotent.\n");
                }
                //invertierbarkeit
                if(mat_invertable(A))
                {
                    printf("A ist invertierbar.\n");
                }
                else
                {
                    printf("A ist nicht invertierbar.\n");
                }
                //symmetrie
                if(is_symmetric(A))
                {
                    printf("A ist symmetrisch.\n");
                }
                else
                {
                    printf("A ist nicht symmetrisch.\n");
                }
                //orthogonalität
                if(is_orthogonal(A))
                {
                    printf("A ist orthogonal.\n");
                }
                else
                {
                    printf("A ist nicht orthogonal.\n");
                }
                //definitheit
                switch(mat_definitheit_sylvester(A))
                {
                    case -2:
                        printf("A ist negativ semidefinit.\n");
                        break;
                    case -1:
                        printf("A ist negativ definit.\n");
                        break;
                    case 2:
                        printf("A ist positiv semidefinit.\n");
                        break;
                    case 1:
                        printf("A ist positiv definit.\n");
                        break;
                    default:
                        printf("A ist indefinit\n");
                }
            }
            else
			{
				//Programm beenden
                printf("Programm beendet.\n\n");
				exit = true;
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