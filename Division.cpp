#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 10000; // we support 10000 digits

struct tPolyInt
{
    int mmax;
    int coeffi[maxn+10];
    tPolyInt()
    {
        mmax = -1;
        memset(coeffi, 0, sizeof(coeffi));
    }
};

bool exactDivision(tPolyInt &x, tPolyInt y)
{
    tPolyInt xx(x);
    if (x.mmax < y.mmax)
        return false;
    while (xx.coeffi[0] == 0 && y.coeffi[0] == 0)
    {
        for (int i = 0; i <= xx.mmax-1; i++)
            xx.coeffi[i] = xx.coeffi[i+1];
        for (int i = 0; i <= y.mmax-1; i++)
            y.coeffi[i] = y.coeffi[i+1];
        xx.mmax--; y.mmax--;
    }
    if (y.coeffi[0] == 0)
        return false;
    int result[maxn+10], cnt = -1;
    for (int i = 0; i <= xx.mmax-y.mmax; i++)
    {
        if (xx.coeffi[i] % y.coeffi[0] != 0)
            return false;
        else
        {
            result[++cnt] = xx.coeffi[i] / y.coeffi[0];
            for (int j = 0; j <= y.mmax; j++)
                xx.coeffi[i+j] -= y.coeffi[j]*result[cnt];
        }
    }
    for (int i = 0; i <= xx.mmax; i++)
    {
        if (xx.coeffi[i] != 0)
            return false;
    }
    x.mmax = cnt;
    for (int i = 0; i <= cnt; i++)
        x.coeffi[i] = result[i];
    return true;
}

int main()
{
    tPolyInt Poly1, Poly2;
    scanf("%d", &Poly1.mmax);
    for (int i = 0; i <= Poly1.mmax; i++)
        scanf("%d", &Poly1.coeffi[i]);
    scanf("%d", &Poly2.mmax);
    for (int i = 0; i <= Poly2.mmax; i++)
        scanf("%d", &Poly2.coeffi[i]);

    if (exactDivision(Poly1, Poly2))
    {
        printf("Divided exactly.\n");
        printf("The quotient is:\n");
        printf("%d ", Poly1.mmax);
        for (int i = 0; i <= Poly1.mmax; i++)
            printf("%d ", Poly1.coeffi[i]);
        printf("\n");
    }
    else
    {
        printf("Couldn't divide exactly.\n");
    }

    return 0;
}
