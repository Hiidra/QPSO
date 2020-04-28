#pragma warning(disable:4996)
#include "iostream"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "QPSO.h"

double GPu(double x, double a, double k, double m) {
	if (x > a)
		return k * pow((x - a), m);
	else if (x<-a) {
		return k * pow((-x - a), m);
	}
	else
		return 0;
}
double GPy(double x) {
	return 1 + 0.25 * (x + 1);
}
void mul_matrix(double z[Dim], double M[Dim][Dim]) {
	double z2[Dim];
	int i = 0, j = 0;
	//memcpy(z2, z, sizeof(z));
	for (int i = 0; i < Dim; i++)
	{
		z2[i] = z[i];
		z[i] = 0.0;
	}
	//memset(z, 0, sizeof(z));

	for (j = 0; j < Dim; j++)
	{
		for (i = 0; i < Dim; i++)
		{
			z[j] += z2[i] * M[i][j];
		}
	}
}

double ComputAFitness(double X[]) {
#if six_hump_camel_back_function
	//����ֵ�ձ��������ú�����6���ֲ���С��,����ȫ����С�� F��-0.0898��0.7126��=F��0.0898��-0.7126��=-1.031628
	return (4.0 - 2.1*X[0] * X[0] + (1.0 / 3.0)*X[0] * X[0] * X[0] * X[0])*X[0] * X[0] + X[0] * X[1] + (4 * X[1] * X[1] - 4)*X[1] * X[1];
#endif

#if Martin_and_Gaddy
	//Martin and Gaddy��������СֵΪ0.00000����ռ�Xi����[-20 20]
	return (X[0] - X[1])*(X[0] - X[1]) + ((X[0] + X[1] - 10) / 3.0)* ((X[0] + X[1] - 10) / 3.0);
#endif

#if Goldstein_and_Price
	return (1 + (X[0] + X[1] + 1)*(X[0] + X[1] + 1)*(19 - 14 * X[0] + 3 * X[0] * X[0] - 14 * X[1] + 6 * X[0] * X[1] + 3 * X[1] * X[1]))*(30 + (2 * X[0] - 3 * X[1])*(2 * X[0] - 3 * X[1])*(18 - 32 * X[0] + 12 * X[0] * X[0] + 48 * X[1] - 36 * X[0] * X[1] + 27 * X[1] * X[1]));
#endif
#if Demo
	double y = 0;
	y = X[0] * sin(10 * PI*X[0]) + 2.0;
	return y;
#endif

	//���Ե�Nά����
#if Sphere
	double f = 0;
	for (int i = 0; i < Dim; i++)
	{
		f = f + X[i] * X[i];
	}
	return f;
#endif

#if Sphere_Shifted
	double f = 0;
	extern double Sh_O[100];
	double z[Dim];
	for (int i = 0; i < Dim; i++) {
		z[i] = X[i] - Sh_O[i];
	}
	for (int i = 0; i < Dim; i++)
	{
		f = f + z[i] * z[i];
	}
	return f + -450.0;
#endif

#if Rastrigin
	double f = 0;
	for (int i = 0; i < Dim; i++)
	{
		f = f + (X[i] * X[i] - 10 * cos(2 * PI*X[i]) + 10);
	}
	return f;
#endif

#if Rastrigin_Shifted
	double f = 0;
	extern double Ra_O[100];
	double z[Dim];
	for (int i = 0; i < Dim; i++) {
		z[i] = X[i] - Ra_O[i];
	}
	for (int i = 0; i < Dim; i++)
	{
		f = f + (z[i] * z[i] - 10 * cos(2 * PI*z[i]) + 10);
	}
	return f + -330;
#endif


#if Rastrigin_Shifted_Rotated
	//	fp = fopen( "wt");
	double f = 0;
	extern double Ra_O[100];
	extern double Ra_M10[10][10], Ra_M30[30][30], Ra_M50[50][50];
	double z[Dim];
	for (int i = 0; i < Dim; i++) {
		//printf("%e\n", X[i]);
		z[i] = X[i] - Ra_O[i];
	}
#if Dim == 10
	mul_matrix(z, Ra_M10);
#endif
#if Dim == 30
	mul_matrix(z, Ra_M30);
#endif
#if Dim == 50
	mul_matrix(z, Ra_M50);
#endif
	for (int i = 0; i < Dim; i++) {
		f = f + (z[i] * z[i] - 10 * cos(2 * PI*z[i]) + 10);
	}
	return f - 330.0;
#endif

#if Schwefel
	double  f = 0;

	for (int i = 0; i < Dim; i++)
	{
		f = f + (X[i] * sin(sqrt(fabs(X[i]))) + 418.9829);
	}
	//f = f + DIM*418.9829;
	return f;
#endif
#if Ackley
	double result;
	double f1 = 0, f2 = 0;
	for (int i = 0; i < Dim; i++)
	{
		f1 += X[i] * X[i];
		f2 += cos(2 * PI * X[i]);
	}
	result = -20 * exp(-0.2*sqrt((1.0 / Dim) * f1)) - exp((1.0 / Dim) * f2) + exp(1) + 20;
	return result;
#endif
#if Ackley_Shifted_Rotated
	double result;
	double f1 = 0, f2 = 0;
	extern double Ac_O[100];
	extern double Ac_M10[10][10], Ac_M30[30][30], Ac_M50[50][50];
	double z[Dim];
	for (int i = 0; i < Dim; i++) {
		z[i] = X[i] - Ac_O[i];
	}
#if Dim == 10
	mul_matrix(z, Ac_M10);
#endif
#if Dim == 30
	mul_matrix(z, Ac_M30);
#endif
#if Dim == 50
	mul_matrix(z, Ac_M50);
#endif
	for (int i = 0; i < Dim; i++)
	{
		f1 += z[i] * z[i];
		f2 += cos(2 * PI * z[i]);
	}
	result = -20 * exp(-0.2*sqrt((1.0 / Dim) * f1)) - exp((1.0 / Dim) * f2) + exp(1) + 20;
	return result + -140.0;
#endif

#if Griewank
	double result;
	double f1 = 0, f2 = 1;
	for (int i = 0; i < Dim; i++)
	{
		f1 += X[i] * X[i] / 4000;
		f2 *= cos(X[i] / sqrt(i + 1));
	}
	result = f1 - f2 + 1;
	return result;
#endif
#if Rosenbrock
	double result;
	double f1 = 0;
	for (int i = 0; i < Dim - 1; i++)
	{
		f1 += 100 * (X[i] * X[i] - X[i + 1]) * (X[i] * X[i] - X[i + 1]) + (X[i] - 1) * (X[i] - 1);
	}
	result = f1;
	return result;
#endif
#if Generalized_Penalized_1
	double result;
	double f1 = 0, f2 = 0;
	for (int i = 0; i < Dim - 1; i++)
	{
		f1 += ((GPy(X[i]) - 1)*(GPy(X[i]) - 1)*(1 + 10 * (sin(PI*GPy(X[i + 1]))) * (sin(PI*GPy(X[i + 1])))));
		f2 += GPu(X[i], 10, 100, 4);
	}
	f2 += GPu(X[Dim - 1], 10, 100, 4);
	result = PI / Dim * (10 * sin(PI*GPy(X[0]))*sin(PI*GPy(X[0])) + f1 + (GPy(X[Dim - 1]) - 1) * (GPy(X[Dim - 1]) - 1)) + f2;
	return result;
#endif
#if Generalized_Penalized_2
	double result;
	double f1 = 0, f2 = 0;
	for (int i = 0; i < Dim - 1; i++)
	{
		f1 += ((X[i] - 1)*(X[i] - 1)*(1 + 10 * (sin(PI*X[i + 1] * 3)) * (sin(PI*X[i + 1] * 3))));
		f2 += GPu(X[i], 5, 100, 4);
	}
	f2 += GPu(X[Dim - 1], 5, 100, 4);
	result = 0.1*(sin(3 * PI*X[0])*sin(3 * PI*X[0]) + f1 + (X[Dim - 1] - 1) * (X[Dim - 1] - 1) * (1 + (sin(2 * PI*X[Dim - 1]))*(sin(2 * PI*X[Dim - 1])))) + f2;
	return result;
#endif
#if Axis_parallel_hyper_ellipsoid
	double f = 0;
	for (int i = 0; i < Dim; i++) {
		f = f + X[i] * X[i] * (i + 1);
	}
	return f;
#endif
}

double mbest[Dim];
double C[PNum][Dim];

//��ʼ����Ⱥ
void SWARM::RandInitofSwarm()
{
	int i, j, i1, j1;
	C1 = 2.0;
	C2 = 2.0;
	for (j = 0; j < Dim; j++)
	{
		Xdown[j] = leftrange;    //�����ռ䷶Χ
		Xup[j] = rightrange;
	}

	for (i = 0; i < PNum; i++)
	{
		for (j = 0; j < Dim; j++)
		{
			Particle[i].X[j] = rand() / (double)RAND_MAX * (Xup[j] - Xdown[j]) + Xdown[j];	//-Xdown~Xup
			Particle[i].P[j] = Particle[i].X[j];//��ʼ�����弫ֵ
		}
		Particle[i].Fitness = ComputAFitness(Particle[i].X);
	}
	GBestIndex = 0;
	for (i1 = 1; i1 < PNum; i1++)
		if (ComputAFitness(Particle[i1].P) < ComputAFitness(Particle[GBestIndex].P))
			GBestIndex = i1;
	for (j1 = 0; j1 < Dim; j1++)
	{
		GBest[j1] = Particle[GBestIndex].P[j1];
	}
}

//update  X
void SWARM::UpdateofVandX(void)
{
	int i, j;
	double beta, fai, k, u;
	beta = 0.5*(ITE_N - cur_n) / ITE_N + 0.5;//��1.0���Եݼ���0.5
	//����mbest
	for (int n = 0; n<Dim; n++)
	{
		mbest[n] = 0.0;
		for (int m = 0; m<PNum; m++)
			mbest[n] += Particle[m].P[n];
		mbest[n] /= PNum;
	}
	for (i = 0; i < PNum; i++)
	{
		for (int j = 0; j < Dim; j++)
		{
			fai = (double)(rand() / (double)RAND_MAX);
			C[i][j] = fai * Particle[i].P[j] + (1 - fai)*GBest[j];

			k = (double)(rand() / (double)RAND_MAX);
			u = (double)(rand() / (double)RAND_MAX);
			if (k >= 0.5)
				Particle[i].X[j] = C[i][j] + beta * fabs(mbest[j] - Particle[i].P[j])*log(1.0 / u);
			else
				Particle[i].X[j] = C[i][j] - beta * fabs(mbest[j] - Particle[i].P[j])*log(1.0 / u);
			if (Particle[i].X[j] > Xup[j])
				Particle[i].X[j] = Xup[j];
			else if (Particle[i].X[j] < Xdown[j])
				Particle[i].X[j] = Xdown[j];
			
			//printf("%d��,scope:%E������%d,ά��%d\n", cur_n,beta* fabs(mbest[j] - Particle[i].X[j]), i, j);
		}

		
		Particle[i].Fitness = ComputAFitness(Particle[i].X);
		/**/
		if (Particle[i].Fitness < ComputAFitness(Particle[i].P))
			for (j = 0; j < Dim; j++)
				Particle[i].P[j] = Particle[i].X[j];

		for (int m = 0; m < PNum; m++)
			if (ComputAFitness(Particle[m].P) < ComputAFitness(Particle[GBestIndex].P))
				GBestIndex = m;
		for (int n = 0; n < Dim; n++)
		{
			GBest[n] = Particle[GBestIndex].P[n];
		}

	}
}




void SWARM::UpdatePandGbest(void)
{
	int i, j;
	//update of P if the X is bigger than current P
	for (i = 0; i < PNum; i++)
	{
		if (Particle[i].Fitness < ComputAFitness(Particle[i].P))
		{
			for (j = 0; j < Dim; j++)
			{
				Particle[i].P[j] = Particle[i].X[j];
			}
		}
	}
	//update of GBest
	for (i = 0; i < PNum; i++)
		if (ComputAFitness(Particle[i].P) < ComputAFitness(Particle[GBestIndex].P))
			GBestIndex = i;
	for (j = 0; j < Dim; j++)
	{
		GBest[j] = Particle[GBestIndex].P[j];
	}

}