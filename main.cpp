#pragma warning(disable:4996)
#include "QPSO.h"
#include"stdlib.h"
#include"time.h"
#include "stdio.h"
#include"math.h"

int cur_n;

int main(int argc, const char *argv[])
{
	double Maxfitness, Minfitness, Sumfitness, Avefitness, Maxcur_n, Mincur_n, Sumcur_n, Avecur_n, Sumtime;//���������ļ�
	FILE *fp1, *fp2;
	struct tm *newtime;
	char tmpbuffile1[128], tmpbuffile2[128], tmpbuf2file1[128], tmpbuf2file2[128];
	time_t lt1;
	lt1 = time(NULL);
	newtime = localtime(&lt1);                //�õ�����ʱ��
	int k, i; int endcur_n, Endcur_n;//�ս�ʱ�ĵ�������  
	int flag;               // ʹ��ֵ��ֻ����һ��   ��־�Ƿ񵽴���ֵ
	clock_t start, end, start3, end3;                          //start3��end3���������Ƿ���һ�����е�ʱ��
	double sumfitness1, sumfitness2, sumtime, sumcur_n;      //sumtime��ÿ�������ʱ��
	double maxfitness1, maxfitness2, minfitness1, minfitness2;                 //������Ӧ�ȣ������Ӧ��
	double maxcur_n, mincur_n;                     //���ŵ�������������������
	double avefitness1, avefitness2, avecur_n;					//ƽ����Ӧ�ȣ�ƽ����������
	int bianhao, cishu;                           //Ϊ��������ֵʱ����ѭ��        ��¼�ж��ٴδﵽ��ֵ
	double shiyingdu, wucha;
	srand((unsigned)time(NULL));
	sprintf(tmpbuffile1, "psoDIM_%dSNUM_%dITE_%d_%s%d%02d%02d_%d%02d%02d_file1.txt",
		Dim, PNum, ITE_N, FUNC_CHOICE,
		1900 + newtime->tm_year, 1 + newtime->tm_mon, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec);//�����ļ����ļ���
	sprintf(tmpbuffile2, "psoDIM_%dSNUM_%dITE_%d_%s%d%02d%02d_%d%02d%02d_file2.txt",
		Dim, PNum, ITE_N, FUNC_CHOICE,
		1900 + newtime->tm_year, 1 + newtime->tm_mon, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec);//�����ļ����ļ���
	sprintf(tmpbuf2file1, "psoDIM_%dSNUM_%dITE_%d_%s%d%02d%02d_%d%02d%02d_file1",
		Dim, PNum, ITE_N, FUNC_CHOICE,
		1900 + newtime->tm_year, 1 + newtime->tm_mon, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec);
	sprintf(tmpbuf2file2, "psoDIM_%dSNUM_%dITE_%d_%s%d%02d%02d_%d%02d%02d_file2",
		Dim, PNum, ITE_N, FUNC_CHOICE,
		1900 + newtime->tm_year, 1 + newtime->tm_mon, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec);
	fp1 = fopen(tmpbuffile1, "wt");
	fp2 = fopen(tmpbuffile2, "wt");
	fprintf(fp1, "%s\n\n\n", tmpbuf2file1);
	fprintf(fp2, "%s\n\n\n", tmpbuf2file2);
	fprintf(fp1, "����ά�ȣ�%d\n��Ⱥ��ģ:%d\n��������:%d\n���귶Χ��:%lf\n���귶Χ��:%lf\nÿ�������Ŀ:%d\n��������:%d\n���Ժ�������:%s\n\n\n", Dim, PNum, ITE_N, leftrange, rightrange, L, N, FUNC_CHOICE);   //���ļ�ͷ�����������Ϣ
	fprintf(fp2, "����ά�ȣ�%d\n��Ⱥ��ģ:%d\n��������:%d\n���귶Χ��:%lf\n���귶Χ��:%lf\nÿ�������Ŀ:%d\n��������:%d\n���Ժ�������:%s\n\n\n", Dim, PNum, ITE_N, leftrange, rightrange, L, N, FUNC_CHOICE);   //���ļ�ͷ�����������Ϣ
	Sumfitness = 0; Sumcur_n = 0; Sumtime = 0, Maxfitness = -9999999; Minfitness = 9999999; Maxcur_n = -9999999; Mincur_n = 9999999;
	for (k = 0; k < N; k++)
	{
		fprintf(fp1, "======================================================================================================================\n");
		fprintf(fp2, "======================================================================================================================\n");
		fprintf(fp1, "��%d��:\n\n", k + 1);
		fprintf(fp2, "��%d��:\n\n", k + 1);
		sumtime = 0; sumfitness1 = 0; sumfitness2 = 0; sumcur_n = 0; cishu = 0;
		maxfitness1 = -9999999; maxfitness2 = -9999999; minfitness1 = 9999999; minfitness2 = 9999999; maxcur_n = -9999999, mincur_n = 9999999;// start3 = clock();
		fprintf(fp2, "���Դ���\t�ﵽ�������ֵʱ�Ĵ���\t���ӱ��\t����ֵ\t�������\t������ֹʱ�ĵ�������\t���ӱ��\t����ֵ\t�������\n");
		fprintf(fp2, "ע���ﵽ�������ֵʱ�Ĵ��� ��������Ϊ 50ʱΪδ�������������������ҵ���������ֵ��\n");
		start = clock();
		for (i = 0; i < L; i++)
		{
			SWARM swarm;
			fprintf(fp1, "����\t���\t����ֵ\t�������\t\t����\n");
			cur_n = 0;
			flag = 1;

			swarm.RandInitofSwarm();             //��ʼ������Ⱥ
			while (++cur_n <= ITE_N)
			{
				endcur_n = cur_n;
				swarm.UpdateofVandX(); //�ٶȺ�λ�ø��£�������
				//swarm.UpdatePandGbest();    //���¸�����ʷ���Ž�P��ȫ�����Ž�GBest
				fprintf(fp1, "%d\t%d\t%E\t%E\t", cur_n, swarm.GBestIndex, ComputAFitness(swarm.GBest), ComputAFitness(swarm.GBest) - REALNUM);
				if (fabs(ComputAFitness(swarm.GBest) - REALNUM) < 1E-6&&flag == 1)
				{
					flag = 0;
					fprintf(fp1, "���﷧ֵ");
					Endcur_n = endcur_n;
					bianhao = swarm.GBestIndex;                                    //��1�������������ϵ����Ž⣬��2���ǳ���������ʱ�����Ž�
					shiyingdu = ComputAFitness(swarm.GBest);
					wucha = shiyingdu - REALNUM;
					cishu++;
				}
				/*for (int i = 0; i < Dim; i++)
				fprintf(fp1, "\t%E", swarm.GBest[i]);*/
				fprintf(fp1, "\n");

			}
			if (flag == 1)            //��δ���﷧ֵ�������
			{
				Endcur_n = endcur_n;
				bianhao = swarm.GBestIndex;
				shiyingdu = ComputAFitness(swarm.GBest);
				wucha = shiyingdu - REALNUM;
			}
			maxfitness1 = maxfitness1 > shiyingdu ? maxfitness1 : shiyingdu;
			minfitness1 = minfitness1 < shiyingdu ? minfitness1 : shiyingdu;
			maxfitness2 = maxfitness2 >  ComputAFitness(swarm.GBest) ? maxfitness2 : ComputAFitness(swarm.GBest);        //ComputAFitness(swarm.GBest)��swarm.particle[GBestIndex].fitness�ǲ�һ����
			minfitness2 = minfitness2 <  ComputAFitness(swarm.GBest) ? minfitness2 : ComputAFitness(swarm.GBest);
			maxcur_n = maxcur_n > Endcur_n ? maxcur_n : Endcur_n;
			mincur_n = mincur_n < Endcur_n ? mincur_n : Endcur_n;
			sumfitness1 += shiyingdu;
			sumfitness2 += ComputAFitness(swarm.GBest);
			sumcur_n += Endcur_n;
			if (Endcur_n < ITE_N)
			{
				fprintf(fp1, "��%-2d�β���:\n��\t%d\t������ֵ�ﵽ�����������ֵ:\t%E\t������\t%E\n", i + 1, Endcur_n, shiyingdu, wucha);
			}
			else
			{
				fprintf(fp1, "��%-2d�β���:\n��\t%d\t��ֹͣδ�����������������ҵ��������ĺ���ֵ\t����ֵ:\t%E\t������\t%E\n", i + 1, Endcur_n, shiyingdu, wucha);
			}
			fprintf(fp1, "��\t%d\t���ﵽ��ֹ��������ͷ��ı��\t%d\t����ֵ��\t%E\t�������:\t%E\n\n", ITE_N, swarm.GBestIndex, ComputAFitness(swarm.GBest), ComputAFitness(swarm.GBest) - REALNUM);
			fprintf(fp2, "%-2d\t%-5d\t%-2d\t%E\t%E\t%-5d\t%d\t%E\t%E\n", i + 1, Endcur_n, bianhao, shiyingdu, wucha, ITE_N, swarm.GBestIndex, ComputAFitness(swarm.GBest), ComputAFitness(swarm.GBest) - REALNUM);
			//fprintf(fp, "��%-2d�β���:\n�ﵽ�������ʱ�ĵ�������\t%-5d\t���ӱ��:\t%-2d\t����ֵ:\t%E\t�������:\t%E\n�ﵽ��ֹ����ʱ�ĵ�������:\t%-5d\t���ӱ��:\t%d\t����ֵ��\t%E\t������\t%E\n\n", i + 1, Endcur_n, bianhao, shiyingdu,wucha,ITE_N, swarm.GBestIndex, ComputAFitness(swarm.GBest), ComputAFitness(swarm.GBest)-REALNUM);
			printf("������%d/%d  ������%d/%dis OK!\n", k + 1, N, i + 1, L);
		}//end3 = clock();
		end = clock();
		avefitness1 = sumfitness1 / L;
		avefitness2 = sumfitness2 / L;
		avecur_n = sumcur_n / L;
		sumtime = (end - start) / CLOCKS_PER_SEC;
		if (cishu == 0)
		{
			fprintf(fp1, "δ�������޵����������ҵ��������Χ�ڵ�ֵ��\n\n");
			fprintf(fp1, "ÿ�β��Զ�������������������ͳ���������£�\n");
			fprintf(fp1, "���ź���ֵ���������:\t%E\t%E\n", minfitness2, minfitness2 - REALNUM);
			fprintf(fp1, "����ֵ���������:\t%E\t%E\n", maxfitness2, maxfitness2 - REALNUM);
			fprintf(fp1, "ƽ������ֵ���������:\t%E\t%E\n", avefitness2, avefitness2 - REALNUM);
			fprintf(fp1, "����ʱ��:\t%.3f ��\n\n", sumtime); //fprintf(fp, "%.3f", (double)(end3 - start3) / CLOCKS_PER_SEC);
			fprintf(fp1, "=======================================================================================================\n\n\n\n");
			fprintf(fp2, "\nδ�������޵����������ҵ��������Χ�ڵ�ֵ��\n\n");
			fprintf(fp2, "ÿ�β��Զ�������������������ͳ���������£�\n");
			fprintf(fp2, "���ź���ֵ���������:\t%E\t%E\n", minfitness2, minfitness2 - REALNUM);
			fprintf(fp2, "����ֵ���������:\t%E\t%E\n", maxfitness2, maxfitness2 - REALNUM);
			fprintf(fp2, "ƽ������ֵ���������:\t%E\t%E\n", avefitness2, avefitness2 - REALNUM);
			fprintf(fp2, "����ʱ��:\t%.3f ��\n\n", sumtime); //fprintf(fp, "%.3f", (double)(end3 - start3) / CLOCKS_PER_SEC);
			fprintf(fp2, "=======================================================================================================\n\n\n\n");
			printf("������%d/%dis OK\n", k + 1, N);
		}
		else
		{
			fprintf(fp1, "��\t%d\t�β����У���\t%d\t�β����ҵ�����������ֵ��������������ۺ�ͳ�����£�\n", L, cishu);
			fprintf(fp1, "���ź���ֵ���������:\t%E\t%E\n", minfitness1, minfitness1 - REALNUM);
			fprintf(fp1, "����ֵ���������:\t%E\t%E\n", maxfitness1, maxfitness1 - REALNUM);
			fprintf(fp1, "ƽ������ֵ���������:\t%E\t%E\n", avefitness1, avefitness1 - REALNUM);
			fprintf(fp1, "��С��������\t%.1f\n", mincur_n);
			fprintf(fp1, "����������\t%.1f\n", maxcur_n);
			fprintf(fp1, "ƽ����������\t%.1f\n", avecur_n);
			fprintf(fp1, "ÿ�β��Զ�������������������ͳ���������£�\n");
			fprintf(fp1, "���ź���ֵ���������:\t%E\t%E\n", minfitness2, minfitness2 - REALNUM);
			fprintf(fp1, "����ֵ���������:\t%E\t%E\n", maxfitness2, maxfitness2 - REALNUM);
			fprintf(fp1, "ƽ������ֵ���������:\t%E\t%E\n", avefitness2, avefitness2 - REALNUM);
			fprintf(fp1, "����ʱ��:\t%.3f ��\n\n", sumtime); //fprintf(fp, "%.3f", (double)(end3 - start3) / CLOCKS_PER_SEC);
			fprintf(fp1, "=======================================================================================================\n\n\n\n");
			fprintf(fp2, "\n��\t%d\t�β����У���\t%d\t�β����ҵ�����������ֵ��������������ۺ�ͳ�����£�\n", L, cishu);
			fprintf(fp2, "���ź���ֵ���������:\t%E\t%E\n", minfitness1, minfitness1 - REALNUM);
			fprintf(fp2, "����ֵ���������:\t%E\t%E\n", maxfitness1, maxfitness1 - REALNUM);
			fprintf(fp2, "ƽ������ֵ���������:\t%E\t%E\n", avefitness1, avefitness1 - REALNUM);
			fprintf(fp2, "��С��������\t%.1f\n", mincur_n);
			fprintf(fp2, "����������\t%.1f\n", maxcur_n);
			fprintf(fp2, "ƽ����������\t%.1f\n", avecur_n);
			fprintf(fp2, "ÿ�β��Զ�������������������ͳ���������£�\n");
			fprintf(fp2, "���ź���ֵ���������:\t%E\t%E\n", minfitness2, minfitness2 - REALNUM);
			fprintf(fp2, "����ֵ���������:\t%E\t%E\n", maxfitness2, maxfitness2 - REALNUM);
			fprintf(fp2, "ƽ������ֵ���������:\t%E\t%E\n", avefitness2, avefitness2 - REALNUM);
			fprintf(fp2, "����ʱ��:\t%.3f ��\n\n", sumtime); //fprintf(fp, "%.3f", (double)(end3 - start3) / CLOCKS_PER_SEC);
			fprintf(fp2, "=======================================================================================================\n\n\n\n");
			printf("������%d/%dis OK\n", k + 1, N);
		}
		Maxfitness = Maxfitness > maxfitness1 ? Maxfitness : maxfitness1;
		Minfitness = Minfitness < minfitness1 ? Minfitness : minfitness1;
		Maxcur_n = Maxcur_n > maxcur_n ? Maxcur_n : maxcur_n;
		Mincur_n = Mincur_n < mincur_n ? Mincur_n : mincur_n;
		Sumfitness += avefitness1;
		Sumcur_n += avecur_n;
		Sumtime += sumtime;
	}
	/*Avefitness = Sumfitness / N;
	Avecur_n = Sumcur_n / N;
	fprintf(fp, "\n\n\n\n\nȫ��������Ӧ��: %E\n", Minfitness);
	fprintf(fp, "ȫ�������Ӧ��: %E\n", Maxfitness);
	fprintf(fp, "ȫ��ƽ����Ӧ��: %E\n", Avefitness);
	fprintf(fp, "ȫ���������: %E\n", Minfitness-REALNUM);
	fprintf(fp, "ȫ��������: %E\n", Maxfitness-REALNUM);
	fprintf(fp, "ȫ��ƽ�����: %E\n", Avefitness-REALNUM);
	fprintf(fp, "ȫ�����ŵ���������%.1f\n", Mincur_n);
	fprintf(fp, "ȫ��������������%.1f\n", Maxcur_n);
	fprintf(fp, "ȫ��ƽ������������%.1f\n", Avecur_n);
	fprintf(fp, "ȫ������ʱ��: %.3f ��\n\n\n\n", Sumtime);
	fclose(fp);*/
	return 0;
}