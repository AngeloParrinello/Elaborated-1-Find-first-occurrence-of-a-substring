/********************************************************************************
*                                                                              *
*                   Architetture dei sistemi di Elaborazione                   *
*                                                                              *
********************************************************************************

Elaborato 1
Descrizione: Dato un array di puntatori a stringa (ogni cella del vettore contiene
l'indirizzo a 32 bit del primo carattere della stringa), cercare la
prima occorrenza di una sottostringa all'interno di ogni stringa del
vettore.

********************************************************************************/


#include <stdio.h>

void main()
{
	// Input
	char* strings[] = { /*"Elaborato di Architetture","139",
		"L'Arco del cerchio","L'arco di trionfo"
		"Si dice che il minimo battito d’ali di una farfalla sia in grado di provocare un uragano dall'altra parte del mondo",
		"La vita e' come una scatola di cioccolatini, non sai mai quello che ti capita!",
		"Non si uccide per amore, basta aspettare. E allora non mi uccido per amore, mi uccido per impazienza",
		"Posso comandare anche il vento signore, c'e' un uragano dentro di me che radera' al suolo la Spagna se solo oserete sfidarmi",
		"Si batta Achille per l'onore e Agamennone si batta per il potere e siano gli dei a decidere quale dei due gloriflicare",
		"Se il mondo ti volta le spalle, non devi far altro che voltargli le spalle anche tu",
		"Io non c'ero e se c'ero dormivo e se dormivo sognavo un'altra cosa!",*/
		/*"Ciao",
		"Cia",
		"Cio",
		"Ociao",
		"ciao",
		"Ocio",*/
		"CiCiao",
		/*"CieCiaCiu",
		"",
		"CiAo",*/
		"eeCCia",
	};							//Array di puntatori a stringa
	int num = sizeof(strings) / sizeof(strings[0]);	//Il numero di stringhe nell'array
	char subStr[] = "Cia"; //"Arc" "si"   						//La sottostringa da cercare

													// Output
	int posizioni[256];	//Posizioni in cui è stata trovata la sottostringa

	__asm{
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX //contatore posizione stringa
		XOR EDX, EDX //contatore della sottostringa
		XOR ESI, ESI //conta quante stringhe ho visto
		XOR EDI, EDI
		//MOV CH,subStr[EDX]
		MOV EBX, strings[4 * ESI]
		MOV AH, [EBX]


		CMP num, 0 //controllo se ci sono stringhe
		JE Fine //se num=0 finisco perchè non ci sono stringhe


		CARICO :
		XOR EDX, EDX //azzero il contatore delle sottostringhe
			CMP ESI, num //controllo se il numero che conta le stringhe è maggiore del numero di stringhe
			JE Fine //se è uguale vuol dire che ho finito
					//MOV EBX, strings[4 * ESI]
			MOV AH, [EBX] //carico in AH l'indirizzo corrispondente al valore di EBX
			CMP AH, '\0' //comparo AH con l'ultimo elemento 
			JE STRINGANONTROVATA //se sono uguali vuol dire che non ho trovato la stringa e quindi passo alla stringa dopo

			PRIMALETTERA :
		XOR EDX, EDX //azzero il contatore 
			CMP AH, subStr[EDX] //controllo la prima lettera
			JE CONTROLLODOPO //se sono uguali controllo la seconda sennò...
			INC EBX //vado avanti di una lettera
			INC ECX //incremento la posizione
			JMP CARICO //ritorno a CARICO

			CONTROLLODOPO :
		//MOV posizioni[4 * ESI], ECX
		INC EBX //devo controllare la lettera successiva quindi vado avanti di una lettera
			INC EDX //se la prima lettera della stringa è uguale, allora dovrò controllare che sia uguale anche la seconda così avanzo di una lettera anche nella sottostringa e così via
			INC ECX //incremento la posizione
			CMP subStr[EDX], '\0' //comparo la sottostringa con l'ultimo elemento 
			JE OK //ho trovato tutta la sottostringa
			MOV AH, [EBX] //ricarico in AH il nuovo indirizzo a cui deve andare a controllare
			CMP AH, '\0' //controlo che non sia finita la stringa 
			JE STRINGANONTROVATA //se è finita devo caricare una nuova stringa
			CMP AH, subStr[EDX] //comparo la n-esima lettera della sottostringa con la n-esima lettera della stringa
			JE CONTROLLODOPO //se sono uguali allora vado avanti con il mio controllo
			JMP VADOAVANTI //se sono diverse vado avanti 

			VADOAVANTI :
			XOR EDX,EDX
			/*INC EBX //non ho trovato la lettera, vado avanti e continuo con la lettera successiva 
			INC ECX //avanzo la posizione*/
			MOV EDX, 0 //riazzero il contatore della sottostringa
			MOV AH, [EBX] //ricarico in AH il nuovo indirizzo a cui deve andare a controllare
			CMP AH, '\0' //controlo che non sia finita la stringa 
			JE STRINGANONTROVATA //se è finita devo caricare una nuova stringa
			CMP AH, subStr[EDX] //comparo la n-esima lettera della sottostringa con la n-esima lettera della stringa
			JE CONTROLLODOPO //se sono uguali allora vado avanti con il mio controllo
			INC EBX //non ho trovato la lettera, vado avanti e continuo con la lettera successiva 
			INC ECX //avanzo la posizione
			JMP VADOAVANTI //se sono diverse vado avanti

			STRINGANONTROVATA :
		MOV posizioni[4 * ESI], -1//se non è presente la stringa devo caricare dentro posizioni -1
								  //INC ESI //incremento ESI perchè vado avanti alla stringa dopo 
								  //XOR EBX,EBX //riazzero il contatore all'interno della stringa
			JMP SUCCESSIVA

			SUCCESSIVA :
		INC ESI //incremento contatore stringhe per andare alla stringa succesiva 
			MOV EBX, strings[4 * ESI] //carico in EBX la nuova stringa 
			XOR ECX, ECX //azzero il contatore della posizione
			XOR EDX, EDX //azzero contatore sottostringa
						 //CMP ESI, num //controllo se il numero che conta le stringhe è maggiore del numero di stringhe
						 //JE Fine //se è maggiore vuol dire che ho finito
			JMP CARICO //inizio a controllare la nuova stringa


			OK :
		SUB ECX, EDX //devo sottrarre alla posizione la lunghezza della sottosringa in modo da salvare la posizione del primo elemento
			MOV posizioni[4 * ESI], ECX //ho trovato la sottostringa e carico la posizione che dovrà essere la posizione-lunghezza sottostringa
			JMP SUCCESSIVA //salta a successiva 

			Fine :





	}
	
	// Stampa su video
	{
		int i;
		for (i = 0; i<num; i++)
		{
			printf("Sottostringa in posizione=%d della stringa[%d]\n", posizioni[i], i);
		}
	} system("pause");
}
