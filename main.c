#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define atas 1
#define kiri 2
#define bawah 3
#define kanan 4

#define keyUp 0x048
#define keyDown 0x050
#define keyLeft 0x04b
#define keyRight 0x04d

#define true 1
#define false 0

//untuk menaikan/menurunkan tingkat kesukaran 
#define level 15

//untuk menentukan ukuran tabel
#define fieldSize 4

char field[fieldSize][fieldSize];
char field2[fieldSize][fieldSize];
unsigned int seed;
int x, y;

int acak(int i);
void initField(int movement);
void move(int arah);
void generateOutput();
int cekUrut();

//fungsi acak
int acak(int i) {
    int a;
    seed += 5;
    srand(seed);

    a = (rand() % i) + 1;

    return(a);
}

//procedure menentukan isi field
void initField(int movement) {
    int arah;
    int arahOld = -1;
    int nPindah = movement;
    int xOld;
    int yOld;
    int c = 1;
    int i;
    int j;
    char temp;

    srand(time(NULL));
    seed = rand();    
    x = y = (fieldSize - 1);

    for (i = 0; i <= (fieldSize - 1); i++) {
        for (j = 0; j <= (fieldSize - 1); j++) {
            field[i][j] = field2[i][j] = c;
            c++;
        }
    }
    field[fieldSize - 1][fieldSize - 1] = field2[fieldSize - 1][fieldSize - 1] = ' ';

    c = 0;
    while (c != nPindah) {
        xOld = x;
        yOld = y;
        arah = acak(4);

        if (arah != 0) {
            if ( c != 0) {
                if ((arah + 2) % 4 == arahOld) {
                    continue;
                }
            }

            switch (arah) {
                case atas :
                    if (y > 0) y--;
                    else continue;
                    break;
                case kiri:
                    if (x > 0) x--;
                    else continue;
                    break;
                case kanan :
                    if (x < fieldSize - 1) x++;
                    else continue;
                    break;
                case bawah :
                    if (y < fieldSize - 1) y++;
                    else continue;
                    break;
                default :
                    break;
            }

            if (x >= 0 && y >= 0 && x <= (fieldSize - 1) && y <= (fieldSize - 1)) {
                temp = field[y][x];
                field[y][x] = field[yOld][xOld];
                field[yOld][xOld] = temp;

                c++;
                arahOld = arah % 4;
            } else {
                x = xOld;
                y = yOld;
            }
        }
    }
}

//procedure menggerakan isi field
void move(int arah) {
    int xOld;
    int yOld;
    char temp;

    xOld = x;
    yOld = y;

    switch (arah) {
        case atas :
            if (y > 0) y--;
            break;
        case kiri:
            if (x > 0) x--;
            break;
        case kanan :
            if (x < (fieldSize - 1)) x++;
            break;
        case bawah :
            if (y < (fieldSize - 1)) y++;
            break;
        default :
            break;
    }

    if (x >= 0 && y >= 0 && x <= (fieldSize - 1) && y <= (fieldSize - 1)) {
        temp = field[y][x];
        field[y][x] = field[yOld][xOld];
        field[yOld][xOld] = temp;
    } else {
        x = xOld;
        y = yOld;
    }
    generateOutput();
}


// prosedure Menampilkan setiap perpindahan (inisial state)
void generateOutput() {
    int i;
    int j;
    int k;
    
    system("cls");
    printf("==========================\n");
    printf("|| G A M E  P U Z Z L E ||\n");
    printf("==========================\n\n");
    printf("Tekan ESC untuk keluar / reset permainan...\n");
    
    for(k = 1; k <= fieldSize; k++) printf("+----"); puts("+");
    for (i = 0; i<=(fieldSize - 1); i++) {
        for (j= 0; j<=(fieldSize - 1); j++) {
            if (i == y && j == x) {
                printf("| %c  ", field[i][j]);
            } else {
                printf("| %2i ", field[i][j]);
            }
        }
        puts("|");

        for(k = 1; k <= fieldSize; k++) printf("+----"); puts("+");
    }
}

//fungsi susunan akhir (goal state)
int cekUrut() {
    int c;
    int d;
    int match = true;

    for (c = 0; c <= (fieldSize - 1); c++) {
        for (d = 0; d <= (fieldSize - 1); d++) {
            if (field[c][d] != field2[c][d]) {
                if (match == true) {
                    match = false;
                }
            }
        }
    }
    return(match);
}



int main(int argc, char *argv[])
{
    int i;
    int j;
    int k;
    char key;
    
         int menu;
         
         do {
            system("cls");
            printf("==========================\n");
            printf("|| G A M E  P U Z Z L E ||\n");
            printf("==========================\n");
            printf("|| 1. Play Game         ||\n\n");
            printf("|| 2. How To Play Game  ||\n\n");
            printf("|| 3. Keluar            ||\n");
            printf("==========================\n");
            printf("Masukkan pilihan : ");
            scanf("%i", &menu);
            
            switch(menu)
            {
                       case 1 :   
                            for(;;) {  
                            system("cls");
                            initField(level);  
                            // prosedure tampil perpindahan angka
                            generateOutput();
                            
                            while ((key = getch()) != 27) {
                            switch(key) {
                                        case keyUp :
                                             move(atas);
                                             break;
                                        case keyDown :
                                             move(bawah);
                                             break;
                                        case keyLeft :
                                             move(kiri);
                                             break;
                                        case keyRight :
                                             move(kanan);
                                             break;
                                        }
                                        if (cekUrut() == true) {
                                                      puts("\nANDA MENANG!!!");                                                     
                                                      break;
                                                      }
                            }
                            if (key == 27) {
                            puts("Apakah anda ingin keluar ?");
                            printf("Tekan ['y' utk keluar / 't' utk reset] : ");
                            getchar();
                            if (toupper(getchar()) == 'Y') 
                            break;
                            else continue;
                            
                            } else {
                            printf("Apakah anda ingin main lagi ? [y/t] : ");
                            getchar();
                            if (toupper(getchar()) == 'T') {
                            puts("\nTerima Kasih Telah Mencoba!!!");
                            getch();
                            break;
                            
                            }
                          }
                        }
                        break;
                       
                       case 2 :
                            system("cls");
                            printf("==========================\n");
                            printf("|| G A M E  P U Z Z L E ||\n");
                            printf("==========================\n");
                            printf("Mainkan puzzle dan menyusunnya menjadi urutan yang benar...\n");
                            printf("Geser kotak kosong sehingga menjadi berurutan sbg berikut : \n\n");
                            
                            //tampilan awal puzzle (goal state)
                            initField(0);
                            for(k = 1; k <= fieldSize; k++) printf("+----"); puts("+");
                            for (i = 0; i<=(fieldSize - 1); i++) {
                            for (j= 0; j<=(fieldSize - 1); j++) {
                                if (i == y && j == x) {
                                      printf("| %c  ", field2[i][j]);
                                } else {
                                       printf("| %2i ", field2[i][j]);
                                }
                            }
                            printf("|\n");
                            for(k = 1; k <= fieldSize; k++) printf("+----"); printf("+\n");
                            }
                            // end tampilan
                            printf("Gunakan tombol panah untuk menggeser kotak kosong...\n\n");
                            printf("Tekan sembarang tombol untuk kembali ke menu utama...\n");
                            getch();
                            break;
                       
                       case 3 :
                            printf("Terima Kasih Sudah Bermain\n");
                            printf("Tekan Sembarang tombol untuk keluar");
                            getch();
                            break;  
                       default :
                               printf("Menu tidak terdaftar, Ulangi!");
                               getch();   
    
            }
           }while ( menu !=3);
return 0;
}
