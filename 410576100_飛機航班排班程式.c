#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define SIZE 40  //��Z�̤j��
#define FSCAN fscanf(fp, "%d\t\t%c\t\t%c\t\t%d:%d\t\t%d:%d\t\t%d:%d", &flyy[i].flight_number,&flyy[i].departure_airport, &flyy[i].arrival_airport, &flyy[i].departure_time_hour, &flyy[i].departure_time_min, &flyy[i].fly_time_hour, &flyy[i].fly_time_min, &flyy[i].stay_time_hour, &flyy[i].stay_time_min) //�N���̪����e���Ӯ榡Ū�J
#define PRINT_TITLE printf("flight no\tdeparture\tarrival\t\tdeparture\tfly time\tstay time\n\t\tairport\t\tairport\t\ttime\n");  //print�X��Z���D
#define PRINT_INFO printf("%d\t\t%c\t\t%c\t\t%02d:%02d\t\t%02d:%02d\t\t%02d:%02d\n", flyy[i].flight_number, flyy[i].departure_airport, flyy[i].arrival_airport, flyy[i].departure_time_hour, flyy[i].departure_time_min, flyy[i].fly_time_hour, flyy[i].fly_time_min, flyy[i].stay_time_hour, flyy[i].stay_time_min)  //print�X��Z���

struct fly{
    int flight_number;  //��Z�s��
    char departure_airport;  //�_������
    char arrival_airport;  //��F����
    int departure_time_hour;  //�Z���ɶ�
    int departure_time_min;
    int fly_time_hour;  //����ɶ�
    int fly_time_min;
    int stay_time_hour;  //���d�ɶ�
    int stay_time_min;

}flyy[SIZE];

void main_menu();  //�D���
void add_flight();  //�s�W��Z
void reduce_flight();  //�R����Z
void search_flight();  //�d�߯�Z
void all_flight();  //�d�ݩҦ���Z
void airport_ac();  //�d�ݾ��������ƶq
void check_airport(char *a_airport);  //�����P�_�A�O�_��ABCDE
void check_time(int *h_hour, int *m_min);  //�ɶ��P�_�A�O�_�ŦX24�ɨ�
void switch_p(int *p_ac, char *p_d_airport, char *p_a_airport);  //��������e�Ǽƶq����switch
void switch_n(int *n_ac, char *n_d_airport, char *n_a_airport);  //��������e�Ǽƶq����switch

char airport_name[5] = {'A', 'B', 'C', 'D', 'E'};  //5�Ӿ������W�r
int max_ac[5] = {15, 10, 5, 5, 10};  //�U�Ӿ����̤j�e�Ƕq
int ac[5] = {6, 5, 3, 2, 5};  //�U�Ӿ����즳�����ƶq

int main()
{
    FILE *fp;
    fp = fopen("flight.txt", "r");
    if(fp == NULL){
        printf("can't open the file\n");
        exit(0);
    }

    char a[10000];
    int i = 0;
    int select;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    PRINT_TITLE;

    while(fgets(a, 10000, fp) != NULL){

        FSCAN;

        switch_p(ac, &flyy[i].departure_airport, &flyy[i].arrival_airport);  //�p��U�Ӿ����{�������ƶq

        if(flyy[i].flight_number != 0){  //print�Ҧ���Z��T
            PRINT_INFO;
            i++;
        }
    }

    printf("\n");
    for(int i=0 ; i<5 ; i++)
        printf("airport %c:  now: %d   Max: %d \n", airport_name[i], ac[i], max_ac[i]);  //print�������{�������ƶq�γ̤j�e�Ƕq

    fclose(fp);

    while(1){

        main_menu();

        choice:
        SetConsoleTextAttribute(hConsole, 0xF);
        printf("\n                                    please enter your choice:                                    \n");
        SetConsoleTextAttribute(hConsole, 0x7);
        scanf("%d", &select);

        switch(select){
        case 1: add_flight();
                break;
        case 2: reduce_flight();
                break;
        case 3: search_flight();
                break;
        case 4: all_flight();
                break;
        case 5: airport_ac();
                break;
        case 6: SetConsoleTextAttribute(hConsole, 0xF);
                printf("Thank you for using the system, see you next time!");
                SetConsoleTextAttribute(hConsole, 0xE);
                printf("\n                                                                                          �_\n");  //�n�n�����ƯZ�t�Ϊ��лx
                printf("                                                                                     .__ ( �P)<  ( bye~~ )\n");
                printf("                                                                                      \\_____)\n");
                SetConsoleTextAttribute(hConsole, 0x3);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                SetConsoleTextAttribute(hConsole, 0x7);
                return 0;
        default: goto choice;  //�p�G��J���Ʀr���O1~6�A���s��J

                break;
        }
    }
}

void main_menu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n\n");
    SetConsoleTextAttribute(hConsole, 0xE);
    printf("                                                     �_                                                    \n");  //�n�n�����ƯZ�t�Ϊ��лx
    printf("                                                .__ ( �P)>                                                  \n");
    printf("                                                 \\_____)                                                  \n");
    SetConsoleTextAttribute(hConsole, 0x3);
    printf("                                    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                    \n");
    SetConsoleTextAttribute(hConsole, 0xF);
    printf("                                    �w �� �� �� �n �n �� �� �� �Z �t ��                                    \n");  //I love duck
    printf("                                    ===================================                                    \n");
    printf("                                    ||  1. �s �W �� �Z               ||                                    \n");
    printf("                                    ||  2. �R �� �� �Z               ||                                    \n");
    printf("                                    ||  3. �d �� �� �Z               ||                                    \n");
    printf("                                    ||  4. �d �� �� �� �� �Z         ||                                    \n");
    printf("                                    ||  5. �d �� �� �� �� �� �� �q   ||                                    \n");
    printf("                                    ||  6. �� �}                     ||                                    \n");
    printf("                                    ===================================                                    \n");
    SetConsoleTextAttribute(hConsole, 0x7);
}

void add_flight()
{
    FILE *fp;
    fp = fopen("flight.txt", "a+");
    if(fp == NULL){
        printf("Open the file failure...\n");
        exit(0);
    }

    int add_number;
    char answer;
    int flag = 0, pr_flight_number;  //�Ω��˵��O�_��J���ƪ�flight number�ҥΪ��ܼ�
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("Do you want to add flight?\n");  //����ݳ]�w
    printf("Enter 'y' to continue, enter 'n' to go back: \n");
    scanf(" %c", &answer);
    if(answer == 'n')
        return;

    printf("How many flights do you want to increase?\n");
    scanf("%d", &add_number);

    fseek(fp, 0, SEEK_END);  //�qfile���̫�}�l�s�W��Z

    for(int i=0 ; i<add_number ; i++){

        printf("\n");

        printf("flight no.: ");
        scanf("%d", &pr_flight_number);
        while(1){  //�˵��O�_��J���ƪ�flight number
            for(int k=0 ; k<SIZE ; k++){
                if(pr_flight_number == flyy[k].flight_number)
                    flag++;
            }
            if(flag == 0)
                break;
            else{
                SetConsoleTextAttribute(hConsole, 0xA);
                printf("The flight number had scheduled, please enter another flight number.\n");
                printf("Enter 0 to return main menu.\n");
                SetConsoleTextAttribute(hConsole, 0x7);
                scanf("%d", &pr_flight_number);
                if(pr_flight_number == 0){
                    fclose(fp);
                    return;
                }
                flag = 0;
                continue;
            }
        }
        flyy[i].flight_number = pr_flight_number;

        printf("departure airport: ");
        scanf(" %c", &flyy[i].departure_airport);
        check_airport(&flyy[i].departure_airport);

        printf("arrival airport: ");
        scanf(" %c", &flyy[i].arrival_airport);
        check_airport(&flyy[i].arrival_airport);

        printf("departure time(hour:min): ");
        scanf("%d:%d", &flyy[i].departure_time_hour, &flyy[i].departure_time_min);
        check_time(&flyy[i].departure_time_hour, &flyy[i].departure_time_min);

        printf("fly time(hour:min): ");
        scanf("%d:%d", &flyy[i].fly_time_hour, &flyy[i].fly_time_min);
        check_time(&flyy[i].fly_time_hour, &flyy[i].fly_time_min);

        printf("stay time(hour:min): ");
        scanf("%d:%d", &flyy[i].stay_time_hour, &flyy[i].stay_time_min);
        check_time(&flyy[i].stay_time_hour, &flyy[i].stay_time_min);

        switch_p(ac, &flyy[i].departure_airport, &flyy[i].arrival_airport);  //�p��U�����{�������ƶq

        if(ac[0]>=0 && ac[1]>=0 && ac[2]>=0 && ac[3]>=0 && ac[4]>=0  && ac[0]<=15 && ac[1]<=10 && ac[2]<=5 && ac[3]<=5 && ac[4]<=10){  //�P�_�Ӿ����O�_�������B�����e�Ƕq�O���O�w�F�̤j��
            fprintf(fp, "%d\t\t%c\t\t%c\t\t%02d:%02d\t\t%02d:%02d\t\t%02d:%02d\n",
                                                            flyy[i].flight_number,
                                                            flyy[i].departure_airport,
                                                            flyy[i].arrival_airport,
                                                            flyy[i].departure_time_hour,
                                                            flyy[i].departure_time_min,
                                                            flyy[i].fly_time_hour,
                                                            flyy[i].fly_time_min,
                                                            flyy[i].stay_time_hour,
                                                            flyy[i].stay_time_min);
        }

        else{  //�p�G�s�W����Z�����ߡA�����e�Ƕq�N���|�ܰʡA�]���|�g�ifile��
            switch_n(ac, &flyy[i].departure_airport, &flyy[i].arrival_airport);  //�N���[������ƶq�Ϻ�^�h
            SetConsoleTextAttribute(hConsole, 0xC );
            printf("\n* Sorry, the airport is full/empty. *\n\n");
            SetConsoleTextAttribute(hConsole, 0x7 );
            fclose(fp);
            return add_flight();  //��^�߰ݬO�_�n�s�W��Z
        }
    }

    SetConsoleTextAttribute(hConsole, 0xB );
    printf("\n* Added successfully! *\n\n");
    SetConsoleTextAttribute(hConsole, 0x7 );

    fclose(fp);

    return ;
}

void reduce_flight()
{
    int del_flight, number;
    int flag = 0;  //�Ω�R����Z���ˬd�O�_������Z
    char a[10000], answer;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("Do you want to delete flight?\n");  //����ݳ]�w
    printf("Enter 'y' to continue, enter 'n' to go back: \n");
    scanf(" %c", &answer);
    if(answer == 'n')
        return;

    printf("How many flights do you want to delete?\n");
    scanf("%d", &number);

    for(int j=0 ; j<number ; j++){

        FILE *fp, *fr;
        fp = fopen("flight.txt", "a+");
        fr = fopen ("reduce.txt", "w+");
        if(fp==NULL || fr==NULL){
            printf("Open the file failure...\n");
            exit(0);
        }

        printf("Which flight you want to delete?\n");  //�ǥѯ�Z�s���R���ӯ�Z
        printf("Please enter the flight number:\n");
        scanf("%d", &del_flight);
        while(1){ //�ˬd�O�_������Z
            for(int k=0 ; k<SIZE ; k++){
                if(del_flight == flyy[k].flight_number)
                    flag++;
            }
            if(flag == 0){
                SetConsoleTextAttribute(hConsole, 0xA);
                printf("Couldn't find the flight number, please enter another flight number.\n");
                printf("Enter 0 to return main menu.\n");
                SetConsoleTextAttribute(hConsole, 0x7);
                scanf("%d", &del_flight);
                if(del_flight == 0)
                    break;
                flag = 0;
                continue;
            }
            else{
                SetConsoleTextAttribute(hConsole, 0xB);
                printf("\n* Deleted successfully! *\n\n");
                SetConsoleTextAttribute(hConsole, 0x7);
                break;
            }
        }

        flag = 0;  //�p�G�@���n�R���@���H�W���ܡA�ݭn�Nflag�k0

        fprintf(fr, "flight no\tdeparture\tarrival\t\tdeparture\tfly time\tstay time\n");  //�]���n���ߤ@�ӷs��file���N�ª��A�ҥH�n�����o�Ǽ��D��T
        fprintf(fr, "\t\tairport\t\tairport\t\ttime\n");

        for(int i=0 ; i<SIZE ; i++){

            FSCAN;

            if(del_flight==flyy[i].flight_number && flyy[i].flight_number!=0)
                switch_n(ac, &flyy[i].departure_airport, &flyy[i].arrival_airport);  //�N�R����������Z�Ҽv�T�������e�q�ư��Ϻ�

            if(del_flight!=flyy[i].flight_number && flyy[i].flight_number!=0){  //���F�R����������Z��ƥ~��l���s�i�s��txt�ɸ�
                fprintf(fr, "%d\t\t%c\t\t%c\t\t%02d:%02d\t\t%02d:%02d\t\t%02d:%02d\n",
                                                                flyy[i].flight_number,
                                                                flyy[i].departure_airport,
                                                                flyy[i].arrival_airport,
                                                                flyy[i].departure_time_hour,
                                                                flyy[i].departure_time_min,
                                                                flyy[i].fly_time_hour,
                                                                flyy[i].fly_time_min,
                                                                flyy[i].stay_time_hour,
                                                                flyy[i].stay_time_min);
            }
            else
                flyy[i].flight_number = 0;  //�N�R����������Ƴ]��0�A�~���|����Ū��
        }

        fclose(fp);
        fclose(fr);

        remove("flight.txt");
        rename("reduce.txt","flight.txt");
    }

    return ;
}

void search_flight()
{
    FILE *fp;
    fp = fopen("flight.txt", "r+");
    if(fp == NULL){
        printf("Open the file failure...\n");
        exit(0);
    }

    int choice;
    int flight_choice, departure_time_hour_choice, departure_time_min_choice;
    char airport_choice;
    int flag1 = 0, flag2 = 0;  //�Ω�P�_�O�_�ǥѾ���/�X�o�ɶ�����������Z(�]��������Z�s�����d�ߥ��w�u���@���A�ҥH�]flag�Ӱ��P�_)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    again:
    printf("Search by\n1: flight number\n2: airport\n3: departure time\n0: return main menu\n");  //�ǥ�1.��Z�s�� 2.���� 3.�����X�o�ɶ� �d��
    scanf("%d", &choice);

    switch(choice){
        case 1: printf("Please enter the flight number: ");
                scanf("%d", &flight_choice);

                for(int i=0 ; i<SIZE ; i++){

                    FSCAN;

                    if(flight_choice==flyy[i].flight_number && flyy[i].flight_number!=0){
                        PRINT_TITLE;
                        PRINT_INFO;
                        fclose(fp);  //�]������������Z�ᤧ��|����return�^main menu�A���|�����Ufclose���ʧ@�A�N�ɭP�{����bug�A�ҥH�o�̭n������
                        return;
                    }
                }
                SetConsoleTextAttribute(hConsole, 0xB);
                printf("\nThere is no flight.\n");
                SetConsoleTextAttribute(hConsole, 0x7);
                break;

        case 2: printf("Please enter the airport: ");
                scanf(" %c", &airport_choice);
                check_airport(&airport_choice);  //���ˬd�O�_��J���T�������W��

                for(int i=0 ; i<SIZE ; i++){

                    FSCAN;

                    if(airport_choice==flyy[i].arrival_airport && flyy[i].arrival_airport!=0 && flyy[i].flight_number!=0){
                        PRINT_TITLE;
                        PRINT_INFO;
                        flag1++;
                    }
                }

                if(flag1 == 0){
                    SetConsoleTextAttribute(hConsole, 0xB);
                    printf("\nThere is no flight.\n");
                    SetConsoleTextAttribute(hConsole, 0x7);
                }
                break;

        case 3: printf("Please enter the departure time(hour:min): ");
                scanf("%d:%d", &departure_time_hour_choice, &departure_time_min_choice);
                check_time(&departure_time_hour_choice, &departure_time_min_choice);  //���ˬd�O�_��J���T���ɶ�


                for(int i=0 ; i<SIZE ; i++){

                    FSCAN;

                    if(departure_time_hour_choice==flyy[i].departure_time_hour && departure_time_min_choice==flyy[i].departure_time_min && flyy[i].flight_number!=0){
                        PRINT_TITLE;
                        PRINT_INFO;
                        flag2++;
                    }
                }

                if(flag2 == 0){
                    SetConsoleTextAttribute(hConsole, 0xB);
                    printf("\nThere is no flight.\n");
                    SetConsoleTextAttribute(hConsole, 0x7);
                }
                break;

        case 0: fclose(fp);
                return;

        default: goto again;  //�p�G��J���Ʀr���O1~3�A���s��J
                 break;
    }

    fclose(fp);

    return ;
}

void airport_ac()
{
    for(int i=0 ; i<5 ; i++)
        printf("\nairport %c:  now: %d   Max: %d \n", airport_name[i], ac[i], max_ac[i]);

    return ;
}

void all_flight()
{
    FILE *fp;
    fp = fopen("flight.txt", "r");
    if(fp == NULL){
        printf("Open the file failure...\n");
        exit(0);
    }

    char ch;

    while((ch=getc(fp)) != EOF){
        printf("%c", ch);
    }

    fclose(fp);

    return ;
}

void check_airport(char *a_airport)
{
    char airport;
    airport = *a_airport;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(1){
        if(airport<'A' || airport>'E'){
            SetConsoleTextAttribute(hConsole, 0xC);
            printf("The airport doesn't exist.\n");
            printf("Please enter the airport again.\n");
            SetConsoleTextAttribute(hConsole, 0x7);
            scanf(" %c", &airport);
            continue;
        }
        else
            *a_airport = airport;
            break;
        }
}

void check_time(int *h_hour, int *m_min)
{
    int hour, min;
    hour = *h_hour;
    min = *m_min;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(1){
        if(hour>=24 || hour<0 || min>=60 || min<0){
            SetConsoleTextAttribute(hConsole, 0xC);
            printf("Time error.\n");
            printf("Please enter the correct time.\n");
            SetConsoleTextAttribute(hConsole, 0x7);
            scanf("%d:%d", &hour, &min);
            continue;
        }
        else{
            *h_hour = hour;
            *m_min = min;
            break;
        }
    }
}

void switch_p(int *p_ac, char *p_d_airport, char *p_a_airport)
{
    char d_airport, a_airport;
    d_airport = *p_d_airport;
    a_airport = *p_a_airport;

    switch(d_airport){
            case'A' : p_ac[0]--; break;
            case'B' : p_ac[1]--; break;
            case'C' : p_ac[2]--; break;
            case'D' : p_ac[3]--; break;
            case'E' : p_ac[4]--; break;
        }

    switch(a_airport){
            case'A' : p_ac[0]++; break;
            case'B' : p_ac[1]++; break;
            case'C' : p_ac[2]++; break;
            case'D' : p_ac[3]++; break;
            case'E' : p_ac[4]++; break;
        }
}

void switch_n(int *n_ac, char *n_d_airport, char *n_a_airport)
{
    char d_airport, a_airport;
    d_airport = *n_d_airport;
    a_airport = *n_a_airport;

    switch(d_airport){
            case'A' : n_ac[0]++; break;
            case'B' : n_ac[1]++; break;
            case'C' : n_ac[2]++; break;
            case'D' : n_ac[3]++; break;
            case'E' : n_ac[4]++; break;
        }

    switch(a_airport){
            case'A' : n_ac[0]--; break;
            case'B' : n_ac[1]--; break;
            case'C' : n_ac[2]--; break;
            case'D' : n_ac[3]--; break;
            case'E' : n_ac[4]--; break;
        }
}
