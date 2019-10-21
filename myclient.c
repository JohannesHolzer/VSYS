/*  Johannes Holzer (if19b044), Manoel Waller (if19b133)
    VSYS-Socket-Uebung: TWMailer
    Hauptprogramm:
        - Socket oeffnen
        - Befehle an Server schicken und entsprechende Unterprogramme ausführen (Schleife)
        - zur Protokollüberprüfung
    4 Unterprogramme (Befehle):
        - send_comm: Mail senden
        - del_comm:  Mail loeschen
        - read_comm: Mail lesen
        - list_comm: Mails eines Users auflisten
    + diverse weitere Unterprogramme
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ldap.h>
#define BUF 1024    //maximale Laenge des Socket-Streams

void list_comm(int create_socket,char *buffer);
void * send_comm(int create_socket, char *buffer);
void * read_comm(int create_socket, char *buffer);
void * del_comm(int create_socket, char *buffer);
void * login_comm(int create_socket, char *buffer);
void display_response(int create_socket, char *buffer);

//LIST-BEFEHL Protokollüberprüfung
void list_comm(int create_socket,char *buffer)
{
    int valid;
    char user[9];

    display_response(create_socket,buffer);
/*    //User einlesen und auf Länge überprüfen
    do
    {
        fgets (user, BUF, stdin);   //Eingabe des Benutzers liefert den Usernamen
        if(strlen(user)>9)
        {
            printf("Username zu lang (max. 8 Zeichen)\n");
            valid=-1;
        }
        else
        {
            valid=0;
            send(create_socket, user, strlen (user), 0);
        }
    }while(valid==-1);*/
    //Als Antwort wird die Anzahl der Nachrichten und die Betreffe geschickt
    display_response(create_socket,buffer);
}
//SEND-BEFEHL Protokollüberprüfung
void * send_comm(int create_socket,char *buffer)
{
    int valid;
    char user[9],subj[81],msg[BUF];

    display_response(create_socket,buffer);
/*    //Sender einlesen und auf Länge überprüfen
    do
    {
        fgets (user, BUF, stdin);   //Eingabe des Benutzers liefert den Usernamen des Senders
        if(strlen(user)>9)
        {
            printf("Sender zu lang (max. 8 Zeichen)\n");
            valid=-1;
        }
        else
        {
            valid=0;
            send(create_socket, user, strlen (user), 0);
        }
    }while(valid==-1);

    display_response(create_socket,buffer);
    //Falls der Server einen Fehler schickt, wird der Befehl abgebrochen
    if(strncmp(buffer,"ERR\n",4)== 0)
    {
        return NULL;
    }*/
    //Empfänger einlesen und auf Länge überprüfen
    do
    {
        fgets (user, BUF, stdin);   //Eingabe des Benutzers liefert den Usernamen des Empfängers
        if(strlen(user)>9)
        {
            printf("Empfänger zu lang (max. 8 Zeichen)\n");
            valid=-1;
        }
        else
        {
            valid=0;
            send(create_socket, user, strlen (user), 0);
        }
    }while(valid==-1);

    display_response(create_socket,buffer);
    //Falls der Server einen Fehler schickt, wird der Befehl abgebrochen
    if(strncmp(buffer,"ERR\n",4)== 0)
    {
        return NULL;
    }
    //Betreff einlesen und auf Länge überprüfen
    do
    {
        fgets (subj, BUF, stdin);   //Eingabe des Benutzers liefert den Betreff der Nachricht
        if(strlen(subj)>81)
        {
            printf("Betreff zu lang (max. 80 Zeichen)\n");
            valid=-1;
        }
        else
        {
            valid=0;
            send(create_socket, subj, strlen (subj), 0);
        }
    }while(valid==-1);

    display_response(create_socket,buffer);
    //Falls der Server einen Fehler schickt, wird der Befehl abgebrochen
    if(strncmp(buffer,"ERR\n",4)== 0)
    {
        return NULL;
    }
    //Nachricht Zeile für Zeile zum Server schicken
    do
    {
        fgets(msg, BUF, stdin);     //Eingabe des Benutzers liefert die Nachricht
        send(create_socket, msg, strlen (msg), 0);
    }while(strcmp(msg,".\n") != 0);
    //solange bis ein .\n das Ende der Nachricht anzeigt

    //Server antwortet mit "OK\n oder "ERR\n" im Fehlerfall
    display_response(create_socket,buffer);
    //Da am Schluss noch die Zierzeile > > > ist, muss zwei Mal die Response angezeigt werden
    display_response(create_socket,buffer);


}
//READ-BEFEHL Protokollüberprüfung
void * read_comm(int create_socket,char *buffer)
{
    int valid;
    char user[9], number[9];

    display_response(create_socket,buffer);
/*    //User einlesen und auf Länge überprüfen
    do
    {
        fgets (user, BUF, stdin);   //Eingabe des Benutzers liefert den Usernamen
        if(strlen(user)>9)
        {
            printf("Username zu lang (max. 8 Zeichen)\n");
            valid=-1;
        }
        else
        {
            valid=0;
            send(create_socket, user, strlen (user), 0);
        }
    }while(valid==-1);

    display_response(create_socket,buffer);
    //Falls der Server einen Fehler schickt, wird der Befehl abgebrochen
    if(strncmp(buffer,"ERR\n",4)== 0)
    {
        return NULL;
    }*/
    //Nachrichtennummer einlesen und auf Länge überprüfen
    do
    {
        fgets (number, BUF, stdin);     //Eingabe des Benutzers liefert die gewünschte Nachrichtennummers
        if(strlen(number)>9)
        {
            printf("Fehler bei Nachrichtennummer\n");
            valid=-1;
        }
        else
        {
            valid=0;
            send(create_socket, number, strlen (number), 0);
        }
    }while(valid==-1);

    display_response(create_socket,buffer);
    //wenn Server ein OK zurückgibt, Nachricht Zeile für Zeile einlesen und anzeigen
    if(strcmp(buffer,"OK\n") == 0)
    {
        do
        {
            display_response(create_socket,buffer);
        }while(strcmp(buffer,".\n") != 0);
    }

}
//DEL-BEFEHL Protokollüberprüfung
void * del_comm(int create_socket,char *buffer)
{
    int valid;
    char user[9], number[9];

    display_response(create_socket,buffer);
/*    //User einlesen und auf Länge überprüfen
    do
    {
        fgets (user, BUF, stdin);   //Eingabe des Benutzers liefert den Usernamen
        if(strlen(user)>9)
        {
            printf("Username zu lang (max. 8 Zeichen)\n");
            valid=-1;
        }
        else
        {
            valid=0;
            send(create_socket, user, strlen (user), 0);
        }
    }while(valid==-1);

    display_response(create_socket,buffer);
    //Falls der Server einen Fehler schickt, wird der Befehl abgebrochen
    if(strncmp(buffer,"ERR\n",4)== 0)
    {
        return NULL;
    }*/
    //Nachrichtennummer einlesen und auf Länge überprüfen
    do
    {
        fgets (number, BUF, stdin);     //Eingabe des Benutzers liefert die gewünschte Nachrichtennummers
        if(strlen(number)>9)
        {
            printf("Fehler bei Nachrichtennummer\n");
            valid=-1;
        }
        else
        {
            valid=0;
            send(create_socket, number, strlen (number), 0);
        }
    }while(valid==-1);
//Bei Success gibt Server "OK\n" zurück, bei einem Fehler "ERR\n"
    display_response(create_socket,buffer);
}
//DEL-BEFEHL Protokollüberprüfung
void * login_comm(int create_socket,char *buffer)
{
    int valid;
    char user[9], pw[BUF];

    display_response(create_socket,buffer);
    //User einlesen und auf Länge überprüfen
    do
    {
        fgets (user, BUF, stdin);   //Eingabe des Benutzers liefert den Usernamen
        if(strlen(user)>9)
        {
            printf("Username zu lang (max. 8 Zeichen)\n");
            valid=-1;
        }
        else
        {
            valid=0;
            send(create_socket, user, strlen (user), 0);
        }
    }while(valid==-1);

    display_response(create_socket,buffer);
    //Falls der Server einen Fehler schickt, wird der Befehl abgebrochen
    if(strncmp(buffer,"ERR\n",4)== 0)
    {
        return NULL;
    }
    //Nachrichtennummer einlesen und auf Länge überprüfen
    do
    {
        fgets (pw, BUF, stdin);     //Eingabe des Benutzers liefert die gewünschte Nachrichtennummers
        if(strlen(pw)>BUF)
        {
            printf("Bufferoverflow bei Passwort!\n");
            valid=-1;
        }
        else
        {
            valid=0;
            send(create_socket, pw, strlen (pw), 0);
        }
    }while(valid==-1);
//Bei Success gibt Server "OK\n" zurück, bei einem Fehler "ERR\n"
    display_response(create_socket,buffer);
}
//Unterprogramm zum Anzeigen der gesamten Response vom Server
void display_response(int create_socket, char *buffer)
{
    int size;
    //Response vom Server einlesen und anzeigen
    size=recv(create_socket,buffer,BUF-1, 0);
    if (size>0)
    {
        buffer[size]= '\0';
        printf("%s",buffer);
    }
}

/*
 *  Das Programm sollte mit den Parametern [IP-Adresse] [Port] gestartet werden
 *  Wenn diese nicht vorhanden sind, wirft das Programm einen Fehler
 */
int main (int argc, char **argv) {
    int create_socket;
    char buffer[BUF], comm[6];
    struct sockaddr_in address;

    //Wenn der Parameter IP-Adresse fehlt, wird die Fehlernachricht angezeigt
    if( argc < 2 ){
        printf("Usage: %s ServerAdresse\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    //Wenn der Parameter Port fehlt, wird die Fehlernachricht angezeigt
    if( argc < 3 ){
        printf("Usage: %s Port\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    //File-Descriptor fuer Stream-Socket(TCP) erstellen
    if ((create_socket = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket error");
        return EXIT_FAILURE;
    }

    //Struktur address initialisieren
    memset(&address,0,sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons (atoi(argv[2]));
    inet_aton (argv[1], &address.sin_addr);

    //zu Server auf IP-Adresse und Port laut Parameter verbinden
    if (connect ( create_socket, (struct sockaddr *) &address, sizeof (address)) == 0)
    {
        printf ("Connection with server (%s) established\n", inet_ntoa (address.sin_addr));
        display_response(create_socket,buffer);
    }
    else
    {
        perror("Connect error - no server available");
        return EXIT_FAILURE;
    }

    //In dieser Schleife werden so lange Befehle verarbeitet, bis "QUIT" eingegeben wird
    do {
        fgets (comm, BUF, stdin);
        if(strcmp(comm, "LIST\n") == 0)			//Nachrichten auflisten lassen
        {
            send(create_socket, comm, strlen (comm), 0);  	//Befehl an Server senden
            list_comm(create_socket,buffer);		//Protokollstruktur überprüfen

        }
        else if(strcmp(comm, "SEND\n") == 0)    //Neue Nachricht versenden
        {
            send(create_socket, comm, strlen (comm), 0);  	//Befehl an Server senden
            send_comm(create_socket,buffer);		//Protokollstruktur überprüfen
        }
        else if(strcmp(comm, "READ\n") == 0)    //Nachricht lesen
        {
            send(create_socket, comm, strlen (comm), 0);	//Befehl an Server senden
            read_comm(create_socket,buffer);		//Protokollstruktur überprüfen
        }
        else if(strcmp(comm, "DEL\n") == 0)     //Nachricht löschen
        {
            send(create_socket, comm, strlen (comm), 0);	//Befehl an Server senden
            del_comm(create_socket,buffer);			//Protokollstruktur überprüfen
        }
        else if(strcmp(comm, "LOGIN\n") == 0)     //Über LDAP einloggen
        {
            send(create_socket, comm, strlen (comm), 0);	//Befehl an Server senden
            login_comm(create_socket,buffer);			//Protokollstruktur überprüfen
        }
        else if(strcmp(comm, "QUIT\n") == 0)     //Socket-Verbindung beenden
        {
            printf("Auf Wiedersehen!\n");
        }
        //Wenn kein gültiger Befehl eingegeben wird
        else
        {
            printf("Bitte gültigen Befehl eingeben\n");
        }
    }
    while (strcmp (comm, "QUIT\n") != 0);   //Befehl QUIT beendet die Verbindung zum Server
    close (create_socket);
    return EXIT_SUCCESS;
}