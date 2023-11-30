#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 20

int comparisons = 0; // 비교 횟수
int moves = 0;      // 이동 횟수

int com = 0;
int swaps = 0;

static void print_array(int list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");
}

static void swap(int list[], int a, int b)
{
    int temp = list[a];
    list[a] = list[b];
    list[b] = temp;
    moves++; // 이동 횟수 증가
}

static int partition(int list[], int low, int high)
{
    int pivot = list[high]; // 피봇을 선택
    int i = (low - 1);    // 작은 요소들을 위한 인덱스

    for (int j = low; j <= high - 1; j++)
    {
        // 현재 요소가 피봇보다 작거나 같으면 교환
        if (list[j] <= pivot)
        {
            i++;
            swap(list, i, j);
        }
        comparisons++; // 비교 횟수 증가
    }

    swap(list, i + 1, high); // 피봇 위치 교환
    return (i + 1);
}

//재귀적 방법의 퀵 정렬
static void quick_sort(int list[], int left, int right, int k)
{
    if (left < right)
    {
        // 분할 위치를 찾아서 분할
        int q = partition(list, left, right);

        // 분할된 부분 배열에 대해 재귀적으로 퀵 정렬 수행
        quick_sort(list, left, q - 1, k);
        quick_sort(list, q + 1, right, k);

        //정렬과정 출력
        if (k == 0)
        {
            print_array(list, MAX_SIZE);
        }
    }
}   

static void reapted_quick_sort(int list[], int low, int high, int k)
{
    low = 0; high = MAX_SIZE - 1;
    int stack[MAX_SIZE]{}; // 스택을 사용하여 분할 위치 저장
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0)
    {
        high = stack[top--];
        low = stack[top--];

        int pi = partition(list, low, high);

        if (pi - 1 > low)
        {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        if (pi + 1 < high)
        {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }

        if (k == 0)
        {
            print_array(list, MAX_SIZE);
        }
    }
}

int main()
{
    int i= 0, n = MAX_SIZE;
    int list[MAX_SIZE]{};
    srand(time(NULL));

    //20번 반복
    for (int i = 0; i < 20; i++)
    {
        //배열 생성
        for (int i = 0; i < MAX_SIZE; i++)
        {
            list[i] = rand() % 100;
        }

        if (i == 0)
        {
            //초기 배열 출력
            printf("초기 배열\n");
            print_array(list, MAX_SIZE);
            printf("\n");
        }

        comparisons = 0;
        moves = 0;
        //quick_sort(list, 0, MAX_SIZE - 1, i);
        reapted_quick_sort(list, 0, MAX_SIZE - 1, i);

        com += comparisons;
        swaps += moves;
    }

    printf("평균 이동 횟수: %d\n", swaps / 20);
    printf("평균 비교 횟수: %d\n", com / 20);
  
    return 0;
}