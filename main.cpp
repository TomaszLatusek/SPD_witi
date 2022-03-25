#include <iostream>
#include <fstream>
#include <math.h>

struct task
{
	int id;
	int p;
	int w;
	int d;
};

struct perm
{
	int lastItemId;
	int previousSet;
};

void getPermutation(perm P[], int i)
{
	if (P[i].previousSet < 0)
	{
		return;
	}
	else
	{
		getPermutation(P, P[i].previousSet);
	}

	std::cout << P[i].lastItemId << " ";

	return;
}

int main()
{
	task tab[100];
	std::ifstream data("data.txt");
	int n, c;
	std::string tmp;
	std::string set[11] = {"data.10:", "data.11:", "data.12:", "data.13:", "data.14:", "data.15:", "data.16:", "data.17:", "data.18:", "data.19:", "data.20:"};

	for (int setNumber = 0; setNumber < 11; setNumber++)
	{
		while (tmp != set[setNumber])
		{
			data >> tmp;
		}

		data >> n;

		for (int i = 0; i < n; i++)
		{
			data >> tab[i].p >> tab[i].w >> tab[i].d;
			tab[i].id = i + 1;
		}

		int N = pow(2, n);
		int *F = new int[N];
		F[0] = 0;
		perm *P = new perm[N];
		P[0].lastItemId = -1, P[0].previousSet = -1;

		int permutation[n];

		for (int x = 1; x < N; x++)
		{
			c = 0;
			for (int i = 0, b = 1; i < n; i++, b *= 2)
			{
				if (x & b)
				{
					c += tab[i].p;
				}
			}

			F[x] = INT32_MAX;

			for (int i = 0, b = 1; i < n; i++, b *= 2)
			{
				if (x & b)
				{
					if (F[x - b] + tab[i].w * std::max(c - tab[i].d, 0) <= F[x])
					{
						P[x].lastItemId = tab[i].id;
						P[x].previousSet = x - b;
						F[x] = F[x - b] + tab[i].w * std::max(c - tab[i].d, 0);
					}
				}
			}
		}
		std::cout << set[setNumber] << " " << F[N - 1] << std::endl;
		getPermutation(P, N - 1);
		std::cout << std::endl
				  << std::endl;

		delete[] F;
		delete[] P;
	}
	data.close();
}
