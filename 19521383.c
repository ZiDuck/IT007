#include<stdlib.h>
#include<stdio.h>
#include <stdbool.h>
void Xuat(int a[], int frame, int n, int fault[],int **arr_2D, int chon)
{
    int count = 0;
    printf("\n---Page Replacement algotrithm---\n");
    if(chon == 1)
        printf("============ FIFO ===========\n");
    else if (chon == 2)
        printf("============ OPT ===========\n");
    else
        printf("============ LRU ===========\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    for(int i = 0; i < frame; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(arr_2D[i][j] == -1)
                printf("  ");
            else
                printf("%d ", arr_2D[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < n; i++)
    {
        if(fault[i] == 0)
            printf("  ");
        else
        {
            printf("* ");
            count++;
        }
    }
    printf("\nNumber of Page Fault: %d", count);
}

void FIFO(int a[], int frame, int n, int chon)
{
    int available;
    int fault[100];
    int next = 0;
    int count = 0;
    int **arr_2D = malloc(sizeof(int *) * (frame));
	for (int i = 0; i < frame; i++)
	{
		arr_2D[i] = malloc(sizeof(int) * n);
		for (int j = 0; j < n; j++)
			arr_2D[i][j] = -1;
	}
    for(int i = 0; i < n; i++)
    {
        fault[i] = 0;
    }
    for(int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            fault[0] = 1;
            arr_2D[0][0] = a[i];
            next = (next + 1) % frame;
            continue;
        }
		bool found = false;
		for (int j = 0; j < frame; j++)
		{
			arr_2D[j][i] = arr_2D[j][i - 1];
			if (arr_2D[j][i] == a[i])
				found = true;
		}
		if (found == false)
		{
			fault[i] = 1;
			//int t = a[i];
			arr_2D[next][i] = a[i];
			next = (next + 1) % frame;
		}
    }
    Xuat(a, frame, n, fault, arr_2D, chon);
}
void OPT(int a[], int frame, int n, int chon)
{
    int i, j;
	int **arr_2D = malloc(sizeof(int *) * frame);
	for (i = 0; i < frame; i++)
	{
		arr_2D[i] = malloc(sizeof(int) * n);
		for (j = 0; j < n; j++)
			arr_2D[i][j] = -1;
	}
	int *fault = malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		fault[i] = 0;
	//-------------------------------
	int cnt = 0;
	for (j = 0; j < n; j++)
	{
		if (j == 0)
		{
			fault[0] = 1;
			arr_2D[0][0] = a[0];
			cnt = 1;
			continue;
		}
 
		bool found = false;
		for (i = 0; i < frame; i++)
		{
			arr_2D[i][j] = arr_2D[i][j - 1];
			if (arr_2D[i][j] == a[j])
				found = true;
		}
		if (found == false)
		{
			fault[j] = 1;
 
			if (cnt < frame)
			{
				arr_2D[cnt][j] = a[j];
				cnt += 1;
				continue;
			}
 
			else
			{
				int max = j;
				int alter = 0;
				for (i = 0; i < frame; i++)
				{
					int h;
					for (h = j + 1; h < n; h++)
						if (a[h] == arr_2D[i][j])
						{
							if (h > max)
							{
								max = h;
								alter = i;
							}
							break;
						}
					if (h == n)
					{
						alter = i;
						break;
					}
				}
				arr_2D[alter][j] = a[j];
			}
		}
	}
	Xuat(a, frame, n, fault, arr_2D, chon);
}
void LRU(int a[], int frame,int n, int chon)
{
	int i, j;
	int **arr_2D = malloc(sizeof(int *) * frame);
	for (i = 0; i < frame; i++)
	{
		arr_2D[i] = malloc(sizeof(int) * n);
		for (j = 0; j < n; j++)
			arr_2D[i][j] = -1;
	}
	int *fault = malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		fault[i] = 0;
	//-------------------------------
	int cnt = 0;
	for (j = 0; j < n; j++)
	{
		//first page
		if (j == 0)
		{
			fault[0] = 1;
			arr_2D[0][0] = a[0];
			cnt = 1;
			continue;
		}
 
		int x = a[j];
		bool found = false;
		for (i = 0; i < frame; i++)
		{
			arr_2D[i][j] = arr_2D[i][j - 1];
			if (arr_2D[i][j] == a[j])
				found = true;
		}
		if (found == false)
		{
			fault[j] = 1;
 
			if (cnt < frame)
			{
				arr_2D[cnt][j] = a[j];
				cnt += 1;
				continue;
			}
 
			else
			{
				int min = j;
				int alter = 0;
				for (i = 0; i < frame; i++)
				{
					int h;
					for (h = j - 1; h >= 0; h--)
						if (a[h] == arr_2D[i][j])
						{
							if (h < min)
							{
								min = h;
								alter = i;
							}
							break;
						}
					if (h == -1)
					{
						alter = i;
						break;
					}
				}
				arr_2D[alter][j] = a[j];
			}
		}
	}
	Xuat(a, frame, n, fault, arr_2D, chon);
}
int main()
{
    int a[100]; // Mảng chứa danh sách các trang
    int frame; // số khung trang
    int n; // số trang
    int select; // option
    int arr[] = {1, 9, 5, 2, 1, 3, 8, 3, 0, 0, 7}; // Mảng chứa danh sách các trang mặc định
    int default_frame = 11; // số trang mặc định
    system("@cls||clear"); // lệnh xóa màn hình
	printf("\n---Page Replacement algotrithm---");
	printf("\n1. Default referenced sequence\n2. Manual input sequence");
    do
	{
		printf("\nYour option: ");
		scanf("%d", &select);
	} while (select <= 0 || select > 2);

    if (select == 2)
	{
		int i;
		printf("\nLenght of sequence: ");
		scanf("%d", &n);
 
		printf("\nInput sequence: ");
		for (i = 0; i < n; i++)
		{
			scanf("%d", &a[i]);
		}
		a[i] = '\0';
	}
	else
	{
		int i, tam = 11;
		for (i = 0; i < tam; i++)
		{
			a[i] = arr[i];
		}
		a[tam] = '\0';
		n = tam;
	}
    //-------------------------------
	system("@cls||clear");
	printf("\n---Page Replacement algotrithm---");
	do
	{
		printf("\nInput page frames: ");
		scanf("%d", &frame);
	} while (frame <= 0);
 
	//-------------------------------
	system("@cls||clear");
	printf("\n---Page Replacement algotrithm---");
	printf("\n1. FIFO algorithm\n2. OPT algorithm\n3. LRU algorithm\n4. All algorithm");
	do
	{
		printf("\nYour option: ");
		scanf("%d", &select);
	} while (select <= 0 || select > 4);
	system("@cls||clear"); 
	int chon;
	switch (select)
	{
	case 1:
	    chon = 1;
		FIFO(a, frame, n, chon);
		break;
	case 2:
	    chon = 2;
		OPT(a, frame, n, chon);
		break;
	case 3:
	    chon = 3;
		LRU(a, frame, n, chon);
		break;
	case 4:
	    chon = 1;
		FIFO(a, frame, n, chon);
		chon = 2;
		OPT(a, frame, n, chon);
		chon = 3;
		LRU(a, frame, n, chon);
		break;
	}
}
