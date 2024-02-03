#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char nama[50];
    char phone[50];
    char akun[50];
    char password[50];
    float saldo;
};

void cek_saldo();
void deposit();
void tarik();
void transfer();
void ubah_pword();

struct user usr, usr1;
FILE *fp;
char akun[50],pword[50];
float nominal;

int main(){
    printf("======================================================= \n");
    printf("***************** WELCOME TO BANK YUANTA ************** \n");
    printf("======================================================= \n");

    int pilihan1, pilihan2, pil;
    char cont = 'y';

    start:
    printf("\nApa yang ingin anda lakukan?\n");
    printf("\n1.Registrasi akun");
    printf("\n2.Login ke akun");

    printf("\n\nPilihan Anda : ");
    scanf("%d", &pilihan1);

    switch(pilihan1){
        case 1:
            system("clear");
            printf("Nama Anda \t\t\t: ");
            scanf("%s", &usr.nama);
            printf("Masukkan nomor akun Anda\t: ");
            scanf("%s", &usr.akun);
            printf("Masukkan nomor telepon Anda\t: ");
            scanf("%s", &usr.phone);
            printf("Masukkan password Anda\t\t: ");
            scanf("%s", &usr.password);
            usr.saldo = 0;
            fp = fopen(strcat(usr.akun,".dat"),"w");
            fwrite(&usr,sizeof(struct user),1,fp);
            if(fwrite!=NULL){
                printf("\n\nAkun Anda berhasil diregistrasi");
            }
            else{
                printf("\n\nTerdapat kesalahan. Coba lagi");
            }
        break;

        case 2:
            login:
            system("clear");
            printf("\nNomor akun\t: ");
            scanf("%s", &akun);
            printf("Password\t: ");
            scanf("%s", &pword);
            fp = fopen(strcat(akun,".dat"),"r");
            if(fp == NULL){
                printf("\nNomor akun belum teregistrasi\n");
            }
            else{
                fread(&usr,sizeof(struct user),1,fp);
                fclose(fp);
                system("clear");
                menu:
                if(!strcmp(usr.password,pword)){
                    printf("\nSelamat Datang, %s\n",usr.nama);
                    printf("\nApa yang ingin Anda lakukan?\n");
                    while(cont == 'y'){
                        printf("\nTekan 1 untuk cek saldo");
                        printf("\nTekan 2 untuk deposit");
                        printf("\nTekan 3 untuk tarik");
                        printf("\nTekan 4 untuk transfer saldo");
                        printf("\nTekan 5 untuk ubah password");
                        printf("\n\nPilihan Anda\t: ");
                        scanf("%d", &pilihan2);

                        switch(pilihan2){
                            case 1:
                                cek_saldo();
                                break;
                            case 2:
                                deposit();
                                break;
                            case 3:
                                tarik();
                                break;
                            case 4:
                                transfer();
                                break;
                            case 5:
                                ubah_pword();
                                break;
                            default:
                                system("clear");
                                printf("Inputan tidak memenuhi\n");
                                goto menu;
                        }
                        printf("\n\n\nApakah Anda ingin melanjutkan transaksi? [y/n]");
                        scanf("%s", &cont);
                    }
                }
                else{
                    printf("\nPassword salah\nTekan 1 untuk coba lagi atau tekan 0 untuk keluar\n");
                    printf("Pilihan Anda : ");
                    scanf("%d", &pil);
                    if(pil==1){
                        goto login;
                    }
                    else return 0;
                }
            }
            break;

        default:
            system("clear");
            printf("Inputan tidak memenuhi");
            goto start;
    }
}

void cek_saldo(){
    system("clear");
    printf("---------- CEK SALDO ----------\n\n");
    printf("Saldo Anda : Rp%.2f", usr.saldo);
}
void deposit(){
    system("clear");
    printf("---------- DEPOSIT ----------\n\n");
    printf("Ketik nominal : ");
    scanf("%f", &nominal);
    usr.saldo=usr.saldo+nominal;
    fp = fopen(usr.akun,"w");
    fwrite(&usr,sizeof(struct user),1,fp);
    if(fwrite!=NULL){
        printf("\nDeposit berhasil");
        printf("\n\nSisa saldo Anda : Rp%.2f", usr.saldo);
    }
    fclose(fp);
}
void tarik(){
    system("clear");
    printf("---------- TARIK UANG ----------\n\n");
    printf("Ketik nominal : ");
    scanf("%f", &nominal);
    if(nominal>usr.saldo)
        printf("Saldo Anda tidak mencukupi");
    else{
        usr.saldo=usr.saldo-nominal;
        fp = fopen(usr.akun,"w");
        fwrite(&usr,sizeof(struct user),1,fp);
        if(fwrite!=NULL){
            printf("\nAnda telah menarik uang sejumlah %.2f", nominal);
            printf("\n\nSisa saldo Anda : Rp%.2f", usr.saldo);
        }
        fclose(fp);
    }
}
void transfer(){
    system("clear");
    printf("---------- TRANSFER ----------\n\n");
    printf("Ketik nomor akun tujuan : ");
    scanf("%s", &akun);
    printf("\nKetik nominal transfer   : ");
    scanf("%f", &nominal);
    fp = fopen(strcat(akun,".dat"),"r");
    if(fp == NULL)
        printf("\nNomor akun belum teregistrasi");
    else{
        fread(&usr1,sizeof(struct user),1,fp);

        fclose(fp);
        if(nominal>usr.saldo)
            printf("\nSaldo Anda tidak mencukupi");
        else{
            fp = fopen(akun,"w");
            usr1.saldo = usr1.saldo+nominal;
            fwrite(&usr1,sizeof(struct user),1,fp);

            fclose(fp);
            if(fwrite!=NULL){
                printf("Anda telah berhasil melakukan transfer sebesar Rp%.2f ke %s", nominal, usr1.nama);
                fp = fopen(usr.akun,"w");
                usr.saldo = usr.saldo-nominal;
                fwrite(&usr,sizeof(struct user),1,fp);
                fclose(fp);
                printf("\n\nSisa saldo Anda : Rp%.2f", usr.saldo);
            }
        }
    }
}
void ubah_pword()
{
    system("clear");
    printf("---------- UBAH PASSWORD ----------\n\n");
    printf("Ketik password baru Anda : ");
    scanf("%s", &pword);
    fp= fopen(usr.akun,"w");
    strcpy(usr.password,pword);
    fwrite(&usr,sizeof(struct user),1,fp);
    if(fwrite!=NULL)
        printf("\n\nPassword Anda berhasil diperbarui");
    fclose(fp);
}


