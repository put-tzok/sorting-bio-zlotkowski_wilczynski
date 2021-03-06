#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

void fill_increasing(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = i+1;
    }
}

void fill_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = n - i;
    }
}

void fill_vshape(int *t, unsigned int n) {
  int x = 0;
for(int i = 0; i<=n;){
    if( i < n/2){
        t[i]=1+n-(i*2+1);
        i++;
        continue;
    }
    if(i==n/2){
        if(x != 0){
            break;
        }else{
            t[i]=1;
            i=n-1;
        }
    }
    if(i>n/2){
        t[i]=t[x]-1;
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

void insertion_sort(int *t, int n)
{
    int j, temp;
    for (int i = 1; i <= n - 1; i++)
    {
        temp = t[i];
        j = i - 1;
        while (j >= 0 && t[j] > temp)
        {
            t[j + 1] = t[j];
            j--;
        }
        t[j + 1] = temp;
    }
}
void quick_sort_rekurencja(int *t, int lewy, int prawy)
{
int v=t[(lewy+prawy)/2];
int i,j,x;
i=lewy;
j=prawy;
do{
while (t[i]<v) i++;
while (t[j]>v) j--;
if (i<=j){
x=t[i];
t[i]=t[j];
t[j]=x;
i++; j--;
}
}while (i<=j);
if (j>lewy) quick_sort_rekurencja(t,lewy, j);
if (i<prawy) quick_sort_rekurencja(t, i, prawy);
}
void quick_sort(int *t, unsigned int n) {
    int lewy;
    lewy=n-n;
    quick_sort_rekurencja(t, lewy, n-1);
    return;
}
void heap_porz(int *heap, int i)
{
    if(heap[i] < heap[(i-1)/2])
    {
        int temp;
        temp = heap[(i-1)/2];
        heap[(i-1)/2] = heap[i];
        heap[i] = temp;
        heap_porz(heap, (i-1)/2);
    }
}
void heap_balans(int *heap, int x, int n, int i)
{
    int temp;
    if((2*x + 2) >= (n - i))
    {
        if((2*x + 1) >= (n - i))
        {
            return;
        }
        else
        {
            temp = heap[2*x + 1];
            heap[2*x + 1] = heap[x];
            heap[x] = temp;
            heap_balans(heap, 2*x + 1, n, i);
        }
    }
    else{
    if(heap[x] > heap[2*x + 1] || heap[x] > heap[2*x + 2])
    {
        if(heap[2*x + 1] < heap[2*x + 2])
        {
            temp = heap[2*x + 1];
            heap[2*x + 1] = heap[x];
            heap[x] = temp;
            heap_balans(heap, 2*x + 1, n, i);
        }
        else
        {
            temp = heap[2*x + 2];
            heap[2*x + 2] = heap[x];
            heap[x] = temp;
            heap_balans(heap, 2*x + 2, n, i);
        }
    }
    }
}
void heap_sort(int *t,  int n){
int heap[n];
heap[0] = t[0];
for(int i = 1; i < n; i ++)//wypełnianie kopca
{
    heap[i] = t[i];
    heap_porz(heap, i);
}
for(int i = 0; i < n; i++)//przenosimy kopiec do tablicy t
{
    t[i] = heap[0];
    heap[0] = heap[n-(i+1)];
    heap_balans(heap, 0, n, i);
}
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
        /*assert(t[i] >= t[i - 1]);*/
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
