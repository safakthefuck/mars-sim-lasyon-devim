//
//  main.c
//  mars similasyon ödevim safak
//
//  Created by Şafak Balcı on 10.10.2026.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int saglik = 100;
    int enerji = 100;
    int oksijen = 100;
    int su = 30;
    int yedekParca = 5;
    int modulHasari = 10;
    int kilitMuhurlu = 0;

    int gun = 1;
    int tur = 0;
    int oyunDevam = 1;

    int firtinaSuresi = 3;
    int firtinaHasarCarpan = 1;
    int esikAvantaji = 15;

    char zorlukSecimi;
    int gecerliZorluk = 0;

    srand((unsigned int)time(NULL));

    
    printf("   MARS KOLONISI YASAM DESTEK SIMULATORUNE HOS GELDINIZ!        \n");
    printf("   Kizil Gezegende 15 Gun Boyunca Hayatta Kalmayi Basarin!      \n");
    

    do {
        printf("Lutfen bir zorluk seviyesi seciniz:\n");
        printf("  [K] Kolay  : Bol kaynak, kisa firtinalar\n");
        printf("  [N] Normal : Standart Mars gorev kosullari\n");
        printf("  [Z] Zor    : Dusuk kaynak, siddetli firtinalar, zorlu arazi\n");
        printf("Seciminiz (K/N/Z): ");
        scanf(" %c", &zorlukSecimi);

        switch (zorlukSecimi) {
            case 'k':
            case 'K':
                saglik = 100;
                enerji = 100;
                oksijen = 100;
                su = 30;
                yedekParca = 5;
                modulHasari = 10;
                firtinaSuresi = 3;
                firtinaHasarCarpan = 1;
                esikAvantaji = 15;
                gecerliZorluk = 1;
                printf("\n>>> KOLAY Seviye Secildi. Hayatta kalma sansiniz yuksek!\n\n");
                break;

            case 'n':
            case 'N':
                saglik = 100;
                enerji = 90;
                oksijen = 90;
                su = 20;
                yedekParca = 3;
                modulHasari = 25;
                firtinaSuresi = 5;
                firtinaHasarCarpan = 1;
                esikAvantaji = 0;
                gecerliZorluk = 1;
                printf("\n>>> NORMAL Seviye Secildi. Standart Mars protokolleri devrede.\n\n");
                break;

            case 'z':
            case 'Z':
                saglik = 90;
                enerji = 80;
                oksijen = 80;
                su = 10;
                yedekParca = 1;
                modulHasari = 40;
                firtinaSuresi = 7;
                firtinaHasarCarpan = 2;
                esikAvantaji = -15;
                gecerliZorluk = 1;
                printf("\n>>> ZOR Seviye Secildi. Ekstrem kosullarda cok dikkatli olmalisiniz!\n\n");
                break;

            default:
                printf("\n[HATA] Gecersiz bir zorluk seviyesi girdiniz! Lutfen tekrar deneyiniz.\n\n");
                gecerliZorluk = 0;
                break;
        }
    } while (!gecerliZorluk);

    do {
        char komut;
        int komutGecerliVeZamanHarcar = 0;

        
        printf("[GUN: %d | TUR: %d] Komutlar: [G] Kesif | [O] Oksijen | [T] Tamir\n", gun, tur);
        printf("                          [D] Durum | [U] Uyu | [K] Firtina | [H] Kilit | [Q] Cikis\n");
        printf("Komutunuzu giriniz: ");
        scanf(" %c", &komut);
        

        switch (komut) {
            case 'g':
            case 'G': {
                if (enerji < 15) {
                    printf("[UYARI] Kesfe cikmak icin yeterli enerjiniz yok (Gereken: 15, Mevcut: %d)!\n", enerji);
                    printf("Komut iptal edildi, tur harcanmadi.\n");
                    break;
                }
                if (oksijen < 10) {
                    printf("[UYARI] Kesfe cikmak icin yeterli oksijeniniz yok (Gereken: 10, Mevcut: %d)!\n", oksijen);
                    printf("Komut iptal edildi, tur harcanmadi.\n");
                    break;
                }

                enerji -= 15;
                oksijen -= 10;
                komutGecerliVeZamanHarcar = 1;

                int esik;
                if (enerji > 40 && oksijen > 30) {
                    esik = 40 - esikAvantaji;
                } else {
                    esik = 65 - esikAvantaji;
                }

                int zar = rand() % 100;
                printf("[ZAR ATILDI] Zar: %d / Esik: %d -> ", zar, esik);

                if (zar < 10 || modulHasari > 70) {
                    int hasarKaybi = 15;
                    saglik -= hasarKaybi;
                    printf("TEHLIKE!\n[YARALANMA] Mars arazisinde kaza gecirdiniz! Saglik -%d azaldi.\n", hasarKaybi);
                }

                if (zar >= esik) {
                    int bulunanSu = 10 + (rand() % 10);
                    su += bulunanSu;
                    printf("BASARILI!\nBuzul katmaninda zengin su kaynagi kesfettiniz! (+%d Birim Su)\n", bulunanSu);
                } else if (zar >= 25) {
                    int bulunanParca = 1 + (rand() % 2);
                    yedekParca += bulunanParca;
                    printf("KISMI BASARILI!\nTerk edilmis eski bir sondaj aracindan parca soktunuz! (+%d Yedek Parca)\n", bulunanParca);
                } else {
                    printf("BASARISIZ!\nKizil kum tepelerinde saatlerce dolastiniz fakat kayda deger bir sey bulamadiniz.\n");
                }
                break;
            }

            case 'o':
            case 'O': {
                if (enerji < 10) {
                    printf("[UYARI] Oksijen jeneratorunu calistirmak icin en az 10 enerji gerekir (Mevcut: %d)!\n", enerji);
                    printf("Komut iptal edildi, tur harcanmadi.\n");
                    break;
                }
                if (su < 2) {
                    printf("[UYARI] Oksijen uretmek icin en az 2 birim su gereklidir (Mevcut: %d birim)!\n", su);
                    printf("Komut iptal edildi, tur harcanmadi.\n");
                    break;
                }

                int istenenSu;
                printf("Oksijen uretimi icin harcamak istediginiz su miktarini giriniz (Mevcut: %d birim): ", su);
                scanf("%d", &istenenSu);

                if (istenenSu <= 0) {
                    printf("[HATA] Gecersiz su miktari girdiniz. Islem iptal edildi.\n");
                    break;
                }
                if (istenenSu > su) {
                    printf("[HATA] Deponuzda o kadar su yok! (Istenen: %d, Mevcut: %d)\n", istenenSu, su);
                    break;
                }

                int kullanilanSu;
                if (istenenSu % 2 == 0) {
                    kullanilanSu = istenenSu;
                } else {
                    kullanilanSu = istenenSu - 1;
                    printf("[BILGI] Girdiginiz miktar tek sayi oldugu icin 1 birim su depoda artik olarak kaldi.\n");
                }

                if (kullanilanSu < 2) {
                    printf("[UYARI] Kullanilabilir su miktari 2 birimden az oldugu icin uretim yapilamadi.\n");
                    break;
                }

                int uretilenOksijen = (kullanilanSu / 2) * 3;

                su -= kullanilanSu;
                oksijen += uretilenOksijen;
                enerji -= 10;
                komutGecerliVeZamanHarcar = 1;

                printf("[URETIM BASARILI] %d birim su harcandi -> +%d birim Oksijen uretildi! (-10 Enerji)\n",
                       kullanilanSu, uretilenOksijen);
                break;
            }

            case 't':
            case 'T': {
                if (yedekParca <= 0) {
                    printf("[UYARI] Tamir yapabilmek icin elinizde yedek parca bulunmalidir (Mevcut: 0)!\n");
                    printf("Komut iptal edildi, tur harcanmadi.\n");
                    break;
                }
                if (modulHasari <= 0) {
                    printf("[BILGI] Modul hasari zaten %%0! Istasyon kusursuz durumda, tamire gerek yok.\n");
                    break;
                }

                if (modulHasari <= 30) {
                    if (enerji < 10) {
                        printf("[UYARI] Hafif tamir icin en az 10 enerji gereklidir (Mevcut: %d)!\n", enerji);
                        break;
                    }
                    yedekParca -= 1;
                    enerji -= 10;
                    modulHasari -= 20;
                    komutGecerliVeZamanHarcar = 1;
                    printf("[KADEME 1: HAFIF ONARIM] 1 yedek parca ve 10 enerji harcandi. Hasar 20 azaltildi.\n");

                } else if (modulHasari <= 70) {
                    if (yedekParca < 2) {
                        printf("[UYARI] Orta hasarli modulu onarmak icin en az 2 yedek parca gerekir (Mevcut: %d)!\n", yedekParca);
                        break;
                    }
                    if (enerji < 15) {
                        printf("[UYARI] Orta onarim icin en az 15 enerji gereklidir (Mevcut: %d)!\n", enerji);
                        break;
                    }
                    yedekParca -= 2;
                    enerji -= 15;
                    modulHasari -= 35;
                    komutGecerliVeZamanHarcar = 1;
                    printf("[KADEME 2: ORTA ONARIM] 2 yedek parca ve 15 enerji harcandi. Hasar 35 azaltildi.\n");

                } else {
                    if (yedekParca < 3) {
                        printf("[UYARI] Kritik agir hasari onarmak icin en az 3 yedek parca gerekir (Mevcut: %d)!\n", yedekParca);
                        break;
                    }
                    if (enerji < 20) {
                        printf("[UYARI] Agir onarim icin en az 20 enerji gereklidir (Mevcut: %d)!\n", enerji);
                        break;
                    }
                    yedekParca -= 3;
                    enerji -= 20;
                    modulHasari -= 50;
                    komutGecerliVeZamanHarcar = 1;
                    printf("[KADEME 3: AGIR ONARIM] 3 yedek parca ve 20 enerji harcandi. Hasar 50 azaltildi.\n");
                }
                break;
            }

            case 'd':
            case 'D': {
               
                printf("  Mevcut Gun       : %d / 15\n", gun);
                printf("  Gecen Toplam Tur : %d\n", tur);
                printf("  Saglik Durumu    : %%%d\n", saglik);
                printf("  Enerji Seviyesi  : %%%d\n", enerji);
                printf("  Oksijen Seviyesi : %%%d\n", oksijen);
                printf("  Su Rezervi       : %d birim\n", su);
                printf("  Yedek Parca      : %d adet\n", yedekParca);
                printf("  Modul Hasari     : %%%d\n", modulHasari);
                printf("  Hava Kilidi      : %s\n", kilitMuhurlu ? "MUHURLU (Guvenli)" : "ACIK (Riskli)");
                

                if (oksijen < 25) {
                    printf("  [KRITIK UYARI] Oksijen seviyesi %%25 altina dustu! Bogulma riski!\n");
                }
                if (saglik < 30) {
                    printf("  [KRITIK UYARI] Saglik durumu %%30 altina dustu! Tibbi mudahale gerekli!\n");
                }
                if (modulHasari > 70) {
                    printf("  [KRITIK UYARI] Modul hasari %%70 uzerinde! Her gun basinda can kaybi riski!\n");
                }

                if (oksijen >= 25 && saglik >= 30 && modulHasari <= 70) {
                    printf("  >>> TUM SISTEMLER NORMAL <<<\n");
                }
                
                komutGecerliVeZamanHarcar = 0;
                break;
            }

            case 'u':
            case 'U': {
                enerji += 30;
                oksijen -= 5;
                komutGecerliVeZamanHarcar = 1;

                printf("[DINLENME] Yatak unitesine gectiniz. Enerji depolandi (+30 Enerji, -5 Oksijen).\n");

                if (oksijen < 20) {
                    saglik -= 10;
                    printf("[TEHLIKE] Oksijen 20'nin altinda olduğu icin uykuda bogulma tehlikesi atlattiniz! (Saglik -10)\n");
                } else {
                    saglik += 15;
                    printf("[RAHATLAMA] Temiz oksijen ve derin dinlenme sayesinde sagliginiz iyilesti (+15 Saglik).\n");
                }
                break;
            }

            case 'k':
            case 'K': {
                printf("\n>>> DIKKAT! SIDDETLI MARS KUM FIRTINASI BASLADI! <<<\n");
                printf("Firtina Suresi: %d Tur boyunca istasyonu sarsacak!\n\n", firtinaSuresi);

                int hasarAlinanTurSayisi = 0;
                int toplamKaybedilenSaglik = 0;
                int toplamKaybedilenOksijen = 0;

                for (int fTur = 1; fTur <= firtinaSuresi; fTur++) {
                    int zar = rand() % 100;
                    int hasarCarpani = firtinaHasarCarpan;

                    if (fTur % 2 == 0) {
                        hasarCarpani = hasarCarpani * 2;
                        printf("--> [Tur %d] Ruzgar siddetini ikiye katladi! (Hasar Carpani: %d)\n", fTur, hasarCarpani);
                    } else {
                        printf("--> [Tur %d] Normal ruzgar siddeti. (Hasar Carpani: %d)\n", fTur, hasarCarpani);
                    }

                    if (zar < 25) {
                        int canKaybi = 8 * hasarCarpani;
                        saglik -= canKaybi;
                        toplamKaybedilenSaglik += canKaybi;
                        hasarAlinanTurSayisi++;
                        printf("    [Zar: %d / Esik: 25] Enkaz parcalari pencereye carpti! (Saglik -%d)\n", zar, canKaybi);

                    } else if (zar < 50) {
                        if (kilitMuhurlu == 1) {
                            printf("    [Zar: %d / Esik: 50] Hava kilidi daha once muhurlendigi icin oksijen sizintisi ENGELLENDI!\n", zar);
                            continue;
                        }
                        int oksijenKaybi = 10 * hasarCarpani;
                        oksijen -= oksijenKaybi;
                        toplamKaybedilenOksijen += oksijenKaybi;
                        hasarAlinanTurSayisi++;
                        printf("    [Zar: %d / Esik: 50] Basinc subabi patladi! Oksijen sizintisi! (Oksijen -%d)\n", zar, oksijenKaybi);

                    } else if (zar < 75) {
                        int yapisalHasar = 12 * hasarCarpani;
                        modulHasari += yapisalHasar;
                        hasarAlinanTurSayisi++;
                        printf("    [Zar: %d / Esik: 75] Radyasyon kalkanlari hasar gordu! (Modul Hasari +%d)\n", zar, yapisalHasar);

                    } else {
                        printf("    [Zar: %d / Esik: 75] Barinak firtinaya basariyla direndi, hasar alinmadi.\n", zar);
                    }

                    if (saglik <= 0 || oksijen <= 0) {
                        printf("\n[KRITIK DURUM] Yasam destek uniteleri iflas etti! Firtina dongusu sonlandiriliyor!\n");
                        break;
                    }
                }

                printf("\n FIRTINA SONUC OZETI \n");
                printf("  Hasar Alinan Tur Sayisi  : %d\n", hasarAlinanTurSayisi);
                printf("  Toplam Saglik Kaybi      : -%d\n", toplamKaybedilenSaglik);
                printf("  Toplam Oksijen Kaybi     : -%d\n", toplamKaybedilenOksijen);
             

                komutGecerliVeZamanHarcar = 1;
                break;
            }

            case 'h':
            case 'H': {
                if (kilitMuhurlu == 1) {
                    printf("[BILGI] Hava kilidi zaten basariyla muhurlenmis durumda! Tekrar isleme gerek yok.\n");
                    break;
                }
                if (enerji < 5) {
                    printf("[UYARI] Hava kilidi konsolunu calistirmak icin en az 5 enerji gereklidir!\n");
                    break;
                }

                char sifre = (char)('A' + (gun % 26));
                int denemeSayisi = 0;
                char tahmin = ' ';

                printf("\n>>> HAVA KILIDI MUHURLEME SISTEMI <<<\n");
                printf("IPUCU: Sifre, Ingiliz alfabesinde 'A' harfinden bugunun gun sayisi (%d) kadar ilerideki harftir.\n", gun);
                printf("Toplam 3 deneme hakkiniz vardir. Her hatali deneme 5 enerji harcar.\n");

                do {
                    printf("Tahmininizi giriniz (%d/3): ", denemeSayisi + 1);
                    scanf(" %c", &tahmin);

                    if (tahmin >= 'a' && tahmin <= 'z') {
                        tahmin = (char)(tahmin - ('a' - 'A'));
                    }

                    denemeSayisi++;

                    if (tahmin == sifre) {
                        printf("[KOD KABUL EDILDI] Sifre dogrulandi! Hava kilidi manyetik olarak muhurlendi.\n");
                    } else {
                        enerji -= 5;
                        if (enerji < 0) enerji = 0;
                        printf("[HATALI SIFRE] Enerji -5 azaldi (Kalan Enerji: %d). ", enerji);

                        if (tahmin < sifre) {
                            printf("Ipucu: Alfabede daha ILERI gitmelisiniz.\n");
                        } else {
                            printf("Ipucu: Alfabede daha GERI gitmelisiniz.\n");
                        }
                    }
                } while (tahmin != sifre && denemeSayisi < 3);

                if (tahmin == sifre) {
                    kilitMuhurlu = 1;
                } else {
                    modulHasari += 20;
                    printf("\n[SISTEM ALARMI] 3 deneme de basarisiz oldu! Konsol kilitlendi ve asiri yuklemeden kilit patladi! (Modul Hasari +20)\n");
                }

                komutGecerliVeZamanHarcar = 1;
                break;
            }

            case 'q':
            case 'Q': {
                printf("\n[CIKIS PROTOKOLU] Gorevi sonlandirma talebinde bulundunuz.\n");
                oyunDevam = 0;
                komutGecerliVeZamanHarcar = 0;
                break;
            }

            default: {
                printf("\n[GECERSIZ KOMUT] '%c' tanimsiz bir komuttur! Lutfen gecerli bir komut giriniz.\n", komut);
                printf("Tur ve kaynak harcanmadi.\n");
                komutGecerliVeZamanHarcar = 0;
                break;
            }
        }

        if (saglik > 100)      saglik = 100;
        if (saglik < 0)        saglik = 0;
        if (enerji > 100)      enerji = 100;
        if (enerji < 0)        enerji = 0;
        if (oksijen > 100)     oksijen = 100;
        if (oksijen < 0)       oksijen = 0;
        if (modulHasari > 100) modulHasari = 100;
        if (modulHasari < 0)   modulHasari = 0;

        if (komutGecerliVeZamanHarcar) {
            tur++;

            if (tur % 3 == 0) {
                gun++;
              
                printf(">>> 3 Tur Tamamlandi! YENI BIR MARS GUNU BASLADI: GUN %d <<<\n", gun);
              

                oksijen -= 8;
                if (oksijen < 0) oksijen = 0;
                printf("- Yasam destek unitesi gunluk baz tuketimi: Oksijen -8 azaldi.\n");

                if (modulHasari > 70) {
                    saglik -= 5;
                    if (saglik < 0) saglik = 0;
                    printf("- TEHLIKE: Modul hasari kritik seviyede (%%70 uzeri)! Zehirli sizinti nedeniyle 5 can kaybettiniz.\n");
                }
             
            }
        }

        if (saglik <= 0 || oksijen <= 0) {
            oyunDevam = 0;
        } else if (gun > 15) {
            oyunDevam = 0;
        }

    } while (oyunDevam);

    int hayattaKalinanGun = (gun > 15) ? 15 : gun;
    int puan = (hayattaKalinanGun * 100) + saglik + oksijen - modulHasari;

    printf("\n\n");
   
    printf("                MARS GOREVI SONUC RAPORU                        \n");
 

    if (saglik <= 0) {
        printf("DURUM: >> GOREV BASARISIZ (KAYBETTINIZ) <<\n");
        printf("NEDEN: Saglik rezerviniz tukendi ve Mars yuzeyinde hayatinizi kaybettiniz.\n");
    } else if (oksijen <= 0) {
        printf("DURUM: >> GOREV BASARISIZ (KAYBETTINIZ) <<\n");
        printf("NEDEN: Yasam destek unitesinde oksijen tukendi ve boguldunuz.\n");
    } else if (gun > 15) {
        printf("DURUM: >> GOREV BASARILI! TEBRIKLER KAZANDINIZ! <<\n");
        printf("NEDEN: 15 cetin Mars gunu boyunca hayatta kalmayi basardiniz.\n");
        printf("       Dunya'dan yola cikan Ares Kurtarma Gemisi istasyona inis yapti!\n");
    } else {
        printf("DURUM: >> GOREV YARIDA BIRAKILDI (CIKIS YAPILDI) <<\n");
        printf("NEDEN: Kendi isteginizle tahliye kapsulune gectiniz.\n");
    }

    
    printf("  Hayatta Kalinan Gun Sayisi : %d\n", hayattaKalinanGun);
    printf("  Tamamlanan Toplam Tur      : %d\n", tur);
    printf("  Kalan Saglik               : %%%d\n", saglik);
    printf("  Kalan Enerji               : %%%d\n", enerji);
    printf("  Kalan Oksijen              : %%%d\n", oksijen);
    printf("  Kalan Su Miktari           : %d birim\n", su);
    printf("  Kalan Yedek Parca          : %d adet\n", yedekParca);
    printf("  Istasyon Modul Hasari      : %%%d\n", modulHasari);
    printf("  Hava Kilidi Durumu         : %s\n", kilitMuhurlu ? "Muhurlu" : "Acik");
   
    printf("  HESAPLANAN TOPLAM SKOR     : %d PUAN\n", puan);
    printf("  (Formul: Gun*100 + Saglik + Oksijen - ModulHasari)\n");
   

    return 0;
}
