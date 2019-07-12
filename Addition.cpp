#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1000000; // we support 1000000 digits

int a[maxn+10];
int b[maxn+10];

int main()
{
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	
    int N, M;
	scanf("%d", &N);
	for (int i = 0; i <= N; i++)
		scanf("%d", a + i);
	scanf("%d", &M);
	for (int i = 0; i <= M; i++)
		scanf("%d", b + i);
	
	int P = std::max(N, M);
	for (int i = 0; i <= P; i++)
		a[i] += b[i];

	printf("The sum is:\n");
	printf("%d ", P);
	for (int i = 0; i <= P; i++)
		printf("%d ", a[i]);
	printf("\n");

    return 0;
}