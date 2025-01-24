#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAS_TIPI_SAYISI 12
#define MIN_TAHTA_BOYUTU 3
#define MAX_TAHTA_BOYUTU 100

int main()
{
    int state = 0; // 0 -> menu, 1 -> setup, 2 -> game, 3 -> game over
    int boyut = 0;
    int tas_tipi = 0;
    int skor = 0;
    int en_iyi_skor = 0;

    int tas_tipleri[TAS_TIPI_SAYISI][3][3] = {
        [0] = {
            { 1, 0, 0 },
            { 1, 0, 0 }, //uc dik
            { 1, 0, 0 },
        },
        [1] = {
            { 1, 1, 1 },
            { 0, 0, 0 }, //uc yatay
            { 0, 0, 0 },
        },
        [2] = {
            { 1, 1, 0 },
            { 1, 1, 0 }, //dort
            { 0, 0, 0 },
        },
        [3] = {
            { 1, 0, 0 },
            { 1, 0, 0 }, //iki dik
            { 0, 0, 0 },
        },
        [4] = {
            { 1, 1, 0 },
            { 0, 0, 0 }, //iki yatay
            { 0, 0, 0 },
        },
        [5] = {
            { 1, 0, 0 },
            { 0, 0, 0 }, //bir
            { 0, 0, 0 },
        },
        [6] = {
            { 1, 0, 0 },
            { 1, 0, 0 }, // L yukari
            { 1, 1, 0 },
        },
        [7] = {
            { 1, 1, 0 },
            { 0, 1, 0 }, // L asagi
            { 0, 1, 0 },
        },
        [8] = {
            { 1, 1, 1 },
            { 1, 0, 0 }, // L sag
            { 0, 0, 0 },
        },
        [9] = {
            { 0, 0, 1 },
            { 1, 1, 1 }, // L sol
            { 0, 0, 0 },
        },
        [10] = {
            { 0, 1, 1 },
            { 1, 1, 0 }, // Z yatay
            { 0, 0, 0 },
        },
        [11] = {
            { 1, 0, 0 },
            { 1, 1, 0 }, // Z dik
            { 0, 1, 0 },
        },



    };

    int kontrol[TAS_TIPI_SAYISI][2]= {
        [0] = {3, 1},
        [1] = {1, 3},
        [2] = {2, 2},
        [3] = {2, 1},
        [4] = {1, 2},
        [5] = {1, 1},
        [6] = {3, 2},
        [7] = {3, 2},
        [8] = {2, 3},
        [9] = {2, 3},
        [10] = {2, 3},
        [11] = {3, 2}
    };

    int tas_donus[TAS_TIPI_SAYISI] = {
        [0] = 1, // Uclu dik -> uclu yatay
        [1] = 0, // Uclu yatay -> uclu dik
        [2] = 2, // Dortlu
        [3] = 4, // ikili dik -> ikili yatay
        [4] = 3, // ikili yatay -> ikili dik
        [5] = 5,
        [6] = 8,
        [7] = 9,
        [8] = 7,
        [9] = 6,
        [10] =11,
        [11] =10,
    };
    int tahta[MAX_TAHTA_BOYUTU][MAX_TAHTA_BOYUTU] = {0};
    int onceki_tahta[MAX_TAHTA_BOYUTU][MAX_TAHTA_BOYUTU] = {0};
    srand(time(NULL));

    int keep_running = 1;
    while (keep_running) {

        if (state == 0) { // menu
            printf("Start Game(1) \n");
            printf("Exit(2) \n");
            printf("> ");
            int a = 0;
            scanf("%d", &a);

            if (a == 1){ // oyuna basla
                state = 1;
            } else { // oyundan cik
                keep_running = 0;
            }
        } else if (state == 1) { // dizi boyutu al
            printf("Oyun tahtasinin boyutunu giriniz, %d - %d:", MIN_TAHTA_BOYUTU, MAX_TAHTA_BOYUTU);
            scanf("%d", &boyut);
            if (boyut>=MIN_TAHTA_BOYUTU && boyut <=MAX_TAHTA_BOYUTU)
            {
                tas_tipi = rand() % TAS_TIPI_SAYISI;
                state = 2;
                skor=0;
                for(int i=0;i<boyut;i++){
                    for(int j=0;j<boyut;j++){
                        tahta[i][j]=0;
                    }
                }
            }
        } else if (state == 2) { // oyun
            printf("\nYerlestirilecek tas: \n");
            for (int i=0 ; i<3 ; i++) {
                for(int j=0 ; j<3 ; j++ ) {
                    if (tas_tipleri[tas_tipi][i][j] == 1) {
                        printf("X");
                    } else {
                        printf(" ");
                    }
                }
                printf("\n");
            }
            printf("\nOyun tahtasi: \n");
            for (int i=0;i<boyut;i++){
                for (int j=0;j<boyut;j++){
                    printf ("%4d", tahta[i][j]);

                }
                 printf("\n");
            }

            printf("\nSkor: %d En yuksek skor: %d\n", skor, en_iyi_skor);
            printf("Dondurmek icin 0 tusuna basiniz \n");
            printf("Tasi yerlestirmek icin koordinat giriniz, 1-%d \n", boyut - kontrol[tas_tipi][1] + 1);
            printf("Cikmak icin -1 tusuna basiniz \n");
            printf(">");

            int girdi;
            scanf("%d", &girdi);

            if (girdi == -1) {
                state = 0;
            } else if (girdi == 0) {
                tas_tipi = tas_donus[tas_tipi];






            } else if (girdi>= 1 && girdi<= (boyut - kontrol[tas_tipi][1] + 1))
            {
                girdi--;
                int aramayi_durdur=0; //aramayi_durdur = 1 -> cakisma , 2 -> tahta sonu
                int satir=0;
                while (aramayi_durdur==0){
                    for(int i=0; i<kontrol[tas_tipi][0];i++)
                    {
                        for(int j=0; j<kontrol[tas_tipi][1]; j++)
                        {
                            if(tahta[satir+i][girdi+j]==1 && tas_tipleri[tas_tipi][i][j]==1)
                                aramayi_durdur=1;
                        }
                    }
                    if (aramayi_durdur==0 && satir+kontrol[tas_tipi][0]==boyut)
                    {
                      aramayi_durdur=2;
                    }
                    if (aramayi_durdur==0)
                            satir++;
                }


                if (aramayi_durdur==1)
                {
                    if (satir == 0) {
                        state = 3;
                        continue;
                    }
                    satir--;
                }

                // tasi yerlestir
                for(int i=0; i<kontrol[tas_tipi][0];i++)
                {
                    for(int j=0; j<kontrol[tas_tipi][1]; j++)
                    {
                        tahta[satir+i][girdi+j] |= tas_tipleri[tas_tipi][i][j];
                    }
                }

                // satir kirma
                for (int i=boyut-1 ; i>=0 ; i--) {


                    int j=0;
                    while (tahta[i][j]==1 && j<boyut)
                    {
                      j++;
                    }
                    if (j==boyut)
                    {

                        for (int j = i; j>0 ; j--)
                        {
                            for (int k=0 ; k<boyut ; k++)
                            {
                            tahta[j][k]=tahta[j-1][k];
                            }
                        }

                        for(int j=0 ; j<boyut ; j++) {
                            tahta[0][j]=0;
                        }
                        skor++;
                        if (skor > en_iyi_skor) {
                            en_iyi_skor = skor;
                        }

                        i++;
                    }
                }

                for (int i=0; i<boyut;i++) {
                    if (tahta[0][i]==1) {
                        state = 3;
                    }
                }

                tas_tipi = rand() % TAS_TIPI_SAYISI;
            }

        } else if (state == 3)
        {
            printf("Game Over \n \n");
            printf("Tahtanin son hali:\n");

                for (int i=0;i<boyut;i++)
                    {
                for (int j=0;j<boyut;j++)
                    {
                        printf ("%4d", tahta[i][j]);
                    }
                     printf("\n");
                }


            printf("Skorunuz: %d \n" , skor);
            printf("En yuksek skor: %d \n \n", en_iyi_skor);
            printf("Devam etmek icin entera basin");
            fgetc(stdin);
            fgetc(stdin);

            state = 0;
        }
    }

    return 0;
}