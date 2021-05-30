#include<stdio.h>
#include<stdlib.h>
void main()
{
    //Mo file
	FILE *fi = fopen("input.txt", "r");
	FILE *fo = fopen("output.txt", "w");

	//Kiem tra file co ton tai hay khong
	if (fi == NULL){
		printf("File not exist!");
		return;
	}

    int pn[10];
    int bur[10], star[10], finish[10], tat[10], wt[10], bur_tam[10], i, n, qt;
    int tam[10], arr[10];
    int time = 0, tong_bur = 0, flag1[10], flag2[10];
    int totwt = 0, tottat = 0;


    fscanf(fi, "%d%d", &n, &qt);

    for (i = 0; i < n; i++)
    {
        fscanf(fi, "%d%d", &pn[i], &bur[i]);
        bur_tam[i] = bur[i];
    }
    for (i = 0; i < n; i++)
    {
        tong_bur += bur[i];
    }
    for (i = 0; i < n; i++)
    {
        flag1[i] = 0;
        flag2[i] = 0;
        arr[i] = 0;
        wt[i] = 0;
    }
    i = 0;

    while (time != tong_bur)
    {
        if (bur_tam[i] <= qt && bur_tam[i] > 0) // Lần thực hiện cuối cùng
        {
            fprintf(fo, "%d %d ", pn[i], time);
            wt[i] += time - tam[i];
            time += bur_tam[i];
            bur_tam[i] = 0;
            flag1[i] = 1;
            finish[i] = time;
            fprintf(fo, "%d\n", time);
        }
        else if (bur_tam[i] > 0 && flag2[i] == 0) // Lần thực hiện đầu tiên của mỗi tiến trình 
        {
            fprintf(fo, "%d %d ", pn[i], time);
            star[i] = time;
            bur_tam[i] -= qt;
            time += qt;
            flag2[i] = 1;
            tam[i] = time;
            fprintf(fo, "%d\n", time);
        }
        else if (bur_tam[i] > 0 && flag2[i] != 0) // Các lần thực hiện tiếp theo
        {
            fprintf(fo, "%d %d ", pn[i], time);
            wt[i] += time - tam[i];
            bur_tam[i] -= qt;
            time += qt;
            tam[i] = time;
            fprintf(fo, "%d\n", time);
        }
        if (bur_tam[i] == 0 && flag1[i] == 1) 
        {
            totwt += wt[i];
            tat[i] = finish[i] - arr[i];
            tottat += tat[i];
            flag1[i] = 0;
        }

        if (i == n - 1)
            i = 0;
        else
            i++;
    }
    for (i = 0; i < n; i++) // mặc định arrival time của các tiến trình là = 0 lúc khởi tạo nên thời gian chờ cần phải cộng thêm thời gian từ lúc vào đến lúc lần đầu thực hiện tiến trình
    {
        //wt[i] += star[i] - arr[i];
        totwt += star[i];
    }
    fprintf(fo, "%.2f\n%.2f", (float)totwt/n, (float)tottat/n);
    fclose(fi);
	fclose(fo);
}
