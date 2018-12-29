/* +––––––––––––––––––––––––––––––––+
 * |       Primzahlen Rechner       |
 * |--------------------------------|
 * | Das ist ein auf dem Sieb des   |
 * | Eratosthenes basierendes       |
 * | Primzahlen Rechenprogramm!     |
 * |            © Samuel Rother 2018|
 * +––––––––––––––––––––––––––––––––+
 */

/*Optionen Anfang*/
// Zum Aktiviren von Optionen // vor #define entfernen

    // Obergrenze des Siebes:
    //  (Primzahlen zwischen 1 und Wert)
    //  - Minimal: 10; Maximal: 4294967294
    //  - ".0f" muss am Ende sein
    #define BIS 4294967294.0f

    // Ausgabe als Text-Datei (Achtung! Kann große Dateien Produzieren!)
    // nach outText Dateipfad:
    //#define outText "prim.txt"

    // Ausgabe als Byte-Datei
    // nach outByte Dateipfad:
    //#define outByte "prim.data"



    /* !!Ab hier Nichts verändern!! */
    #define jump 6 // Sprung Weite des Siebes
/*Optionen Ende*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>


struct tData{
    u_int start;
    u_int sqrL;
    u_int length;
    char* arr;
};

void *primHelper(void* arg);
void *primHelper2(void* arg);

int main() {
    // Limit für Berechnung festlegen
    float limit=BIS;

    // Variablen definieren
    pthread_t tid0=1,tid1=2,tid2=3;
    u_int counter=3,fi=0,i=0;
    struct tData pTdata;

    // Größen berechnen
    pTdata.length = (u_int)limit/2;
    pTdata.sqrL = (u_int)(sqrt(pTdata.length)+1.5f);
    u_int arraySize = (u_int)(limit*1.5f/logf(limit)*4);


    // Speicher reservieren
    pTdata.arr = malloc(pTdata.length+16);
    u_int* primList = malloc(arraySize);


    // Alle Zahlen als Primzahlen markieren
    memset(pTdata.arr+pTdata.length,0,16);
    memset(pTdata.arr,1,pTdata.length);


    // Ausgelassene Primzahlen definieren
    primList[0] = 2;
    primList[1] = 3;
    primList[2] = 5;


    // Thread Parameter definieren
    i = 3;
    struct tData t0data = pTdata;
    t0data.start = 7;
    struct tData t1data = pTdata;
    t1data.start = 4;
    struct tData t2data = pTdata;
    t2data.start = 6;


    // Sieb des Eratosthenes
    // Optimierungen:
    //  -nur ungerade Zahlen
    //  -ohne Vielfache von 3 (Durchlauf und vielfache)
    //  -aufgeteilt auf vier Threads
    pthread_create(&tid0, NULL, primHelper2, (void *)&t0data);
    pthread_create(&tid1, NULL, primHelper2, (void *)&t1data);
    pthread_create(&tid2, NULL, primHelper, (void *)&t2data);
    while (i <= pTdata.sqrL) {
        if (pTdata.arr[i]) {
            u_int jb = i*4-2;
            u_int js = i*2-1;
            u_int ii = ((i * i * 2) - (2 * i) + 1);
            while (1) {
                if (ii > pTdata.length) break;
                pTdata.arr[ii] = 0;
                ii += js;
                if (ii > pTdata.length) break;
                pTdata.arr[ii] = 0;
                ii += jb;
            }
        }
        i += jump;
    }


    // Warten auf Threads
    pthread_join(tid0,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);



    // Sieb filtern
    // Optimierungen:
    //  -nur ungerade Zahlen
    //  -ohne Vielfache von 3
    //  -ohne Vielfache von 5
    fi = 4;
    while (fi < pTdata.length) {
        if (pTdata.arr[fi]) {
            primList[counter] = fi*2-1;
            counter++;
        }
        fi += 2;
        if (pTdata.arr[fi]) {
            primList[counter] = fi*2-1;
            counter++;
        }
        fi += 1;
        if (pTdata.arr[fi]) {
            primList[counter] = fi*2-1;
            counter++;
        }
        fi += 2;
        if (pTdata.arr[fi]) {
            primList[counter] = fi*2-1;
            counter++;
        }
        fi += 1;
        if (pTdata.arr[fi]) {
            primList[counter] = fi*2-1;
            counter++;
        }
        fi += 2;
        if (pTdata.arr[fi]) {
            primList[counter] = fi*2-1;
            counter++;
        }
        fi += 3;
        if (pTdata.arr[fi]) {
            primList[counter] = fi*2-1;
            counter++;
        }
        fi += 1;
        if (pTdata.arr[fi]) {
            primList[counter] = fi*2-1;
            counter++;
        }
        fi += 3;
    }


    // Ausgabe der Menge der Primzahlen
    printf("%i\n",counter);


    // Byte-Datei schreiben
    #ifdef outByte
    FILE *file = fopen(outByte, "wb");
        fwrite(primList, 4, counter, file);
    fclose(file);
    #endif


    // Text-Datei schreiben ( Achtung! Große Dateien! )
    #ifdef outText
    FILE *file = fopen(outText, "w");
        for (u_int i=0;i < counter;i++) fprintf(file,"%u,",primList[i]);
    fclose(file);
    #endif


    //Reservierten Speicher freigeben
    free(pTdata.arr);
    free(primList);

    return 0;
}

void *primHelper(void* arg) {
    struct tData lTdata = *(struct tData*)arg;
    u_int i=lTdata.start;
    while (i <= lTdata.sqrL) {
        if (lTdata.arr[i]) {
            u_int jb = i*4-2;
            u_int js = i*2-1;
            u_int ii = ((i * i * 2) - (2 * i) + 1);
            while (1) {
                if (ii > lTdata.length) break;
                lTdata.arr[ii] = 0;
                ii += js;
                if (ii > lTdata.length) break;
                lTdata.arr[ii] = 0;
                ii += jb;
            }
        }
        i += jump;
    }
}

void *primHelper2(void* arg) {
    struct tData lTdata = *(struct tData*)arg;
    u_int i=lTdata.start;
    while (i <= lTdata.sqrL) {
        if (lTdata.arr[i]) {
            u_int jb = i*4-2;
            u_int js = i*2-1;
            u_int ii = ((i * i * 2) - (2 * i) + 1);
            while (1) {
                if (ii > lTdata.length) break;
                lTdata.arr[ii] = 0;
                ii += jb;
                if (ii > lTdata.length) break;
                lTdata.arr[ii] = 0;
                ii += js;
            }
        }
        i += jump;
    }
}