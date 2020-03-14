#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 10, 100, 1000, 10000, 100000 };

void fill_increasing(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = i; //Raczej działa
    }
}

void fill_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = n - i; //Raczej działa
    }
}

void fill_vshape(int *t, unsigned int n) {
  for (int i = 0; i<n; i++){
    t[i]=0;
}
for (int i = 0; i<=n;){
        int x;
if(i == 0){
    x=0;
}
    if( i < n/2){
        t[i]=1+n-(i*2+1);
        i++;
        continue;
    }
    if(i==n/2){
        if(t[i] != 0){
            break;
        }else{
            t[i]=1;
            i=n;
        }
    }
    if(i>n/2){
        t[i]=t[x-1]-1;
        i--;
        x++;
        continue;
    }
}
}

void selection_sort(int *t, unsigned int n) {
    for(int i = 0; i < n - 1; i++)
    {
        int min = i;
        int pierw = i;
        for(int x = i + 1; x < n; x++)
        {
            if(t[min] > t[x])
            {
                min = x;
            }
        }
        if(t[pierw] > t[min])
        {
          int temp = t[pierw];
          t[pierw] = t[min];
          t[min] = temp;
        }
    }
}

void insertion_sort(int *t, unsigned int n) {
    // TODO: implement
}
void quick_sort_rekurencja(int *t, int left, int right){
    int pivot, temp, x_prog, y_prog;
    pivot = t[right];
    x_prog = left;
    y_prog = right;
    do{
        while(t[x_prog]<pivot) x_prog++;
        while(t[y_prog]>pivot) y_prog--;
        if(x_prog<=y_prog){
            temp=t[x_prog];
            t[x_prog]=t[y_prog];
            t[y_prog]=temp;
            x_prog++;
            y_prog--;
        }
    }while(x_prog<=y_prog);
    if(y_prog>left) quick_sort_rekurencja(t, left, y_prog);
    if(x_prog<right) quick_sort_rekurencja(t, x_prog, right);
}
void quick_sort(int *t, unsigned int n) {
    int left;
    left=0;
    quick_sort_rekurencja(t, left, n);
}

void heap_sort(int *t, unsigned int n) {
    // TODO
}

void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}
