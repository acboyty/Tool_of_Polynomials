#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100000000;

int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

struct tFraction
{
    int numer;
    int denomin;
    tFraction(int x = 0)
    {
        numer = x;
        denomin = 1;
    }
    tFraction operator + (const tFraction &y) const
    {
        tFraction ans;
        int temp = gcd(denomin, y.denomin);
        ans.denomin = denomin / temp * y.denomin;
        ans.numer = y.denomin/temp*numer + denomin/temp*y.numer;
        temp = gcd(abs(ans.numer), ans.denomin);
        ans.numer /= temp;
        ans.denomin /= temp;
        return ans;
    }
    tFraction operator - (const tFraction &y) const
    {
        tFraction ans;
        int temp = gcd(denomin, y.denomin);
        ans.denomin = denomin / temp * y.denomin;
        ans.numer = y.denomin/temp*numer - denomin/temp*y.numer;
        temp = gcd(abs(ans.numer), ans.denomin);
        ans.numer /= temp;
        ans.denomin /= temp;
        return ans;
    }
    tFraction operator * (const int &y) const
    {
        tFraction ans(*this);
        ans.numer *= y;
        int temp = gcd(abs(ans.numer), ans.denomin);
        ans.numer /= temp;
        ans.denomin /= temp;
        return ans;
    }
    tFraction operator / (const int &y) const
    {
        tFraction ans(*this);
        if (y < 0)
            ans.numer = -ans.numer;
        ans.denomin *= abs(y);
        int temp = gcd(abs(ans.numer), ans.denomin);
        ans.numer /= temp;
        ans.denomin /= temp;
        return ans;
    }
    void show()
    {
        printf("The fraction is: ");
        printf("%d / %d\n", numer, denomin);
    }
};

struct tPolyFrac
{
    int mmax;
    tFraction coeffi[20];
    tPolyFrac()
    {
        mmax = -1;
        for (int i = 0; i < 20; i++)
            coeffi[i] = tFraction(0);
    }
    void show()
    {
        printf("The PolyFrac is: ");
        printf("%d ", mmax);
        for (int i = 0; i <= mmax; i++)
            printf("%d/%d ", coeffi[i].numer, coeffi[i].denomin);
        printf("\n");
    }
};

struct tPolyInt
{
    int mmax;
    tFraction overall;
    int coeffi[20];
    tPolyInt()
    {
        mmax = -1;
        overall = tFraction(0);
        for (int i = 0; i < 20; i++)
            coeffi[i] = 0;
    }
    tPolyInt(tPolyFrac &rhs)
    {
        mmax = rhs.mmax;
        int mul = 1;
        for (int i = 0; i <= mmax; i++)
            mul *= rhs.coeffi[i].denomin;
        for (int i = 0; i <= mmax; i++)
            coeffi[i] = mul / rhs.coeffi[i].denomin * rhs.coeffi[i].numer;
        int temp1 = abs(coeffi[0]);
        for (int i = 1; i <= mmax; i++)
            temp1 = gcd(temp1, abs(coeffi[i]));
        for (int i = 0; i <= mmax; i++)
            coeffi[i] /= temp1;
        overall.numer = temp1;
        overall.denomin = mul;
        int temp2 = gcd(overall.numer, overall.denomin);
        overall.numer /= temp2;
        overall.denomin /= temp2;
    }
    int getValue(int x)
    {
        int tempx = 1, sum = 0;
        for (int i = 0; i <= mmax; i++)
        {
            sum += tempx * coeffi[i];
            tempx *= x;
        }
        return sum;
    }
    void show()
    {
        printf("Your Polynomial is: ");
        printf("%d ", mmax);
        for (int i = 0; i <= mmax; i++)
            printf("%d ", coeffi[i]);
        printf("\n");
		printf("The factors are:\n");
    }
};

tPolyInt polyInt;
int varX[15], varY[15], varCnt = 1;
int factY[15][10000], factCnt[15];
int numSet[15];
tFraction differ[15][15];
FILE *fpFactor;

void getDiffer(int limit)
{
    for (int i = 1; i <= limit; i++)
        differ[i][i] = (tFraction){numSet[i]};
    for (int len = 2; len <= limit; len++)
    {
        for (int l = 1, r; ; l++)
        {
            r = len + l - 1;
            if (r > limit)
                break;
            differ[l][r] = (differ[l][r-1] - differ[l+1][r]) / (varX[l] - varX[r]);
        }
    }
}

void getCoeffi(tPolyFrac &p, int number, int times, int depth, int limit)
{
    if (depth == limit)
    {
        p.mmax = std::max(p.mmax, times);
        p.coeffi[times] = p.coeffi[times] + differ[1][limit] * number;
        return;
    }
    getCoeffi(p, number, times+1, depth+1, limit);
    getCoeffi(p, number*(-varX[depth]), times, depth+1, limit);
}

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
    int result[20], cnt = -1;
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

void dfs(int depth, int limit)
{
    if (depth == limit+1)
    {
        // printf("One numSet is: ");
        // for (int i = 1; i <= limit; i++) printf("%d ", numSet[i]);
        // printf("\n");
        getDiffer(limit);
        tPolyFrac polyFrac;
        for (int i = 1; i <= limit; i++)
        {
            getCoeffi(polyFrac, 1, 0, 1, i);
        }
        tPolyInt polyInt1(polyInt), polyInt2(polyFrac);
        // polyInt1.show(); polyInt2.show();
        int times = 0;
        while (true)
        {
            if (exactDivision(polyInt1, polyInt2))
            {
                polyInt = polyInt1;
                times++;
            }
            else
            {
                if (times > 0)
                {
                    printf("%d ", polyInt2.mmax);
                    for (int i = 0; i <= polyInt2.mmax; i++)
                        printf("%d ", polyInt2.coeffi[i]);
                    printf("%d\n", times);
                }
                break;
            }
        }
        return;
    }
    for (int i = 1; i <= factCnt[depth]-1; i++)
    {
        numSet[depth] = factY[depth][i];
        dfs(depth+1, limit);
    }
}

int main() {
    /*
     * get primitive polynomial
     */
    scanf("%d", &polyInt.mmax);
    polyInt.overall = (tFraction)1;
    for (int i = 0; i <= polyInt.mmax; i++)
        scanf("%d", &polyInt.coeffi[i]);
    polyInt.show();

    /*
     * Kronecker Polynomial Decomposition
     */
    int maxTimes = polyInt.mmax/2 + 1;
    for (int i = 1, temp; varCnt <= maxTimes; i++)
    {
        temp = polyInt.getValue(i);
        if (temp != 0)
        {
            varX[varCnt] = i;
            varY[varCnt++] = abs(temp);
        }
    }
    for (int i = 1, temp; i <= varCnt-1; i++)
    {
        factCnt[i] = 1;
        temp = varY[i];
        for (int j = 1; 1LL*j*j <= 1LL*temp; j++)
        {
            if (temp % j == 0)
            {
                factY[i][factCnt[i]++] = j; factY[i][factCnt[i]++] = -j;
                factY[i][factCnt[i]++] = temp/j; factY[i][factCnt[i]++] = -temp/j;
            }
        }
        // printf("the factor of %d is: ", varY[i]);
        // for (int j = 1; j <= factCnt[i]-1; j+=2) printf("%d ", factY[i][j]);
        // printf("\n");
    }
    for (int i = 2; i <= maxTimes; i++)
    {
        if (polyInt.mmax == 0 || i-1 >= polyInt.mmax)
            break;
        dfs(1, i);
    }
    if (polyInt.mmax > 0)
    {
        printf("%d ", polyInt.mmax);
        for (int i = 0; i <= polyInt.mmax; i++)
            printf("%d ", polyInt.coeffi[i]);
        printf("%d\n", 1);
    }
    else if (polyInt.coeffi[0] != 1)
    {
        printf("0 %d 1", polyInt.coeffi[0]);
    }

    return 0;
}
