#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int wynik_dodawania[256];
int wynik_odejmowania[256];
int wynik_mnozenia[256];

void scan_string(char tab[]) {
   char z;
   while (isspace(z = getchar()));
   int i = 0;
   while (z != '\n') {
      tab[i] = z;
      i++;
      z = getchar();
   }
   tab[i] = '\0';
}

void char2int(char char_tab[], int int_tab[]) {
   if (char_tab[0] == '-') {
      int_tab[0] = 1;
      int_tab[1] = strlen(char_tab) - 1;
   } else if (char_tab[0] == '+') {
      int_tab[0] = 0;
      int_tab[1] = strlen(char_tab) - 1;
   } else {
      int_tab[0] = 0;
      int_tab[1] = strlen(char_tab);
   }

   int i = 2, h = strlen(char_tab) - 1;
   while ((i - 2) < int_tab[1]) {
      int_tab[i] = char_tab[h] - 48;
      i++;
      h--;
   }
}

int find_max(int a[], int b[]) {
   for (int i = 255; i > 1; i--) {
      if (a[i] > b[i])
         return 0;
      else if (b[i] > a[i])
         return 1;
   }
   return 0;
}

void dodawanie_single(int l1[], int wynik[]) {
   for (int i = 2; i < l1[1] + 2; i++) {
      int r = (wynik[i] + l1[i]);
      int j = i;
      wynik[i] = r % 10;
      r /= 10;
      while (r > 0) {
         j++;
         wynik[j] += r % 10;
         r /= 10;
      }
   }
}

void odejmowanie_single(int l1[], int wynik[]) {
   int mode = find_max(l1, wynik);
   int pomoc[256] = {0};
   if (mode == 0) {
      wynik[0] = (wynik[0] + 1) % 2;
      for (int i = 2; i < l1[1] + 2; i++) {
         int r = l1[i] - wynik[i] - pomoc[i];
         if (r < 0) {
            r += 10;
            int j = i + 1;
            do {
               pomoc[j] -= 1;
               j++;
            } while ((l1[j] - pomoc[j] - 1) < 0);
         }
         wynik[i] = r;
      }
   } else {
      for (int i = 2; i < l1[1] + 2; i++) {
         int r = wynik[i] - l1[i] - pomoc[i];
         if (r < 0) {
            r += 10;
            int j = i + 1;
            do {
               pomoc[j] -= 1;
               j++;
            } while ((wynik[j] - pomoc[j] - 1) < 0);
         }
         wynik[i] = r;
      }
   }
}

void dodawanie(int l1[], int l2[], int wynik[]) {
   for (int i = 0; i < 256; i++)
      wynik[i] = l1[i];

   if ((l2[0] == 0 && wynik[0] == 0) || (l2[0] == 1 && wynik[0] == 1))
      dodawanie_single(l2, wynik);
   else
      odejmowanie_single(l2, wynik);
}

void odejmowanie(int l1[], int l2[], int wynik[]) {
   for (int i = 0; i < 256; i++)
      wynik[i] = l1[i];

   if ((l2[0] == 0 && wynik[0] == 0) || (l2[0] == 1 && wynik[0] == 1))
      odejmowanie_single(l2, wynik);
   else
      dodawanie_single(l2, wynik);
}

void mnozenie(int l1[], int l2[], int wynik[]) {
   wynik[0] = (l1[0] + l2[0]) % 2;
   int mode = find_max(l1, l2);

   for (int i = 2; i < 255; i++) {
      for (int j = 2; j < 255; j++) {
         int pomoc[512] = {
            0
         };
         pomoc[1] = 252;
         if (mode == 0) {
            int r = l1[j] * l2[i];
            pomoc[j + i - 2] = r % 10;
            r /= 10;
            pomoc[j + i - 1] = r;
            dodawanie_single(pomoc, wynik);
         } else {
            int r = l1[i] * l2[j];
            pomoc[j + i - 2] = r % 10;
            r /= 10;
            pomoc[j + i - 1] = r;
            dodawanie_single(pomoc, wynik);
         }
      }
   }
}

int main(void) {
   char liczba_1[256];
   char liczba_2[256];
   int liczba_1_num[256] = {0};
   int liczba_2_num[256] = {0};

   scan_string(liczba_1);
   scan_string(liczba_2);
   char2int(liczba_1, liczba_1_num);
   char2int(liczba_2, liczba_2_num);

   dodawanie(liczba_1_num, liczba_2_num, wynik_dodawania);

   printf("Wynik dodawania:  ");
   int czy = 0, l = 255;
   while (l > 1) {
      if (czy == 0 && wynik_odejmowania[l] != 0)
         czy = 1;
      l--;
   }

   if (wynik_dodawania[0] == 1 && czy == 1)
      printf("-");

   czy = 0, l = 255;
   while (l > 1) {
      if (czy == 1)
         printf("%d", wynik_dodawania[l]);
      else if (czy == 0 && wynik_dodawania[l] != 0) {
         czy = 1;
         printf("%d", wynik_dodawania[l]);
      }
      l--;
   }
   if (czy == 0)
      printf("0");
   printf("\n");

   odejmowanie(liczba_1_num, liczba_2_num, wynik_odejmowania);

   printf("Wynik odejmowania:  ");

   czy = 0, l = 255;
   while (l > 1) {
      if (czy == 0 && wynik_odejmowania[l] != 0)
         czy = 1;
      l--;
   }

   if (wynik_odejmowania[0] == 1 && czy == 1)
      printf("-");
   czy = 0, l = 255;
   while (l > 1) {
      if (czy == 1)
         printf("%d", wynik_odejmowania[l]);
      else if (czy == 0 && wynik_odejmowania[l] != 0) {
         czy = 1;
         printf("%d", wynik_odejmowania[l]);
      }
      l--;
   }
   if (czy == 0)
      printf("0");
   printf("\n");

   mnozenie(liczba_1_num, liczba_2_num, wynik_mnozenia);

   printf("Wynik mnożenia:  ");
   if (wynik_mnozenia[0] == 1)
      printf("-");
   czy = 0, l = 255;
   while (l > 1) {
      if (czy == 1)
         printf("%d", wynik_mnozenia[l]);
      else if (czy == 0 && wynik_mnozenia[l] != 0) {
         czy = 1;
         printf("%d", wynik_mnozenia[l]);
      }
      l--;
   }
   if (czy == 0)
      printf("0");
   printf("\n");
   return 0;
}