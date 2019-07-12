#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 10000000; // actually we only support 1000000 digits
const double PI = acos(-1.0);

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

struct tComplex
{
    double x, y;
    tComplex(double xx = 0, double yy = 0)
    {
        x = xx; y = yy;
    }
};
tComplex a[maxn+10];
tComplex b[maxn+10];

tComplex operator + (const tComplex &a, const tComplex &b)
{
    return tComplex(a.x + b.x, a.y + b.y);
}

tComplex operator - (const tComplex &a, const tComplex &b)
{
    return tComplex(a.x - b.x, a.y - b.y);
}

tComplex operator * (const tComplex &a, const tComplex &b)
{
    return tComplex(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x);
}

int l, r[maxn+10];
int limit = 1;

void FFT(tComplex A[], int type)
{
    for (int i = 0; i < limit; i++)
    {
        if (i < r[i])
            std::swap(A[i], A[r[i]]);
    }
    for (int mid = 1; mid < limit; mid <<= 1) // enumerate half of the interval len
    {
        tComplex Wn(cos(PI/mid), type * sin(PI/mid));
        for (int R = mid << 1, j = 0; j < limit; j += R)
        {
            tComplex w(1, 0);
            for (int k = 0; k < mid; k++, w = w * Wn)
            {
                tComplex x = A[j+k], y = w * A[j+mid+k];
                A[j+k] = x + y;
                A[j+mid+k] = x - y;
            }
        }
    }
}

int main()
{
    int N, M;
    scanf("%d", &N);
    for (int i = 0; i <= N; i++)
        scanf("%lf", &a[i].x);
    scanf("%d", &M);
    for (int i = 0; i <= M; i++)
        scanf("%lf", &b[i].x);

    while (limit <= N + M)
    {
        limit <<= 1, l++;
    }
    //get reverse order 0..limit-1
    for (int i = 0; i < limit; i++)
        r[i] = (r[i>>1] >> 1) | ((i&1) << (l-1));

    FFT(a, 1); FFT(b, 1);
    for (int i = 0; i < limit; i++)
        a[i] = a[i] * b[i];
    FFT(a, -1);

	printf("The product is:\n");
    printf("%d ", N + M);
    for (int i = 0; i <= N + M; i++)
    {
        double temp = a[i].x / limit + 0.5;
        if (temp > 0)
            printf("%lld ", (LL)temp);
        else
            printf("%lld ", (LL)(temp - 1));
    }
    printf("\n");

    return 0;
}