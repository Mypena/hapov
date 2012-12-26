#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

#define buf_sz 1024
#define t_i 0.0000001
#define A 2.0

double S_w (double x)
{
    return x<1?(3.0/4.0*A*t_i):
                sqrt(pow(A/x*(sin(3.0*x*t_i)*(5.0/4.0*cos(x*t_i/2.0)-1.0/2.0*cos(x*t_i/4.0)-1.0)+
                         3.0/4.0*(sin(x*t_i/2.0)-sin(x*t_i/4.0))*(1.0-cos(3.0*x*t_i))), 2)+
                     pow(A/x*(3.0/4.0*sin(3.0*x*t_i)*(sin(x*t_i/2.0)-sin(x*t_i/4.0))-
                         (5.0/4.0*cos(x*t_i/2.0)-1.0/2.0*cos(x*t_i/4.0)-1.0)*(1.0-cos(3.0*x*t_i))), 2)
                    );
}

/*The function will calculate value of We - effective angular frequency*/
double Calc_We (int N, double Es, double k)
{
    int w = 0;
    double E = 0;
    while ((k*Es)>E)
    {
        E += 1.0/M_PI * (N * (pow (S_w(w), 2) + pow (S_w(w+N), 2))/2.0);
        printf ("k*Es = %le, E=%le, w=%d\n", k*Es, E, w);
        w +=N;
    }
    return w;
}

int main()
{
    printf ("This program calculates effective spectrum width\n\n");
    int N =0;    /*sampling rate*/
    double We=0;    /*effective angular frequency*/
    double Es=0;    /*signal energy*/
    double k =0;    /*ratio of effective spectrum width (about 0.90-0.95)*/
    char *buf = malloc (buf_sz);
    printf ("Please input parameters as follows:\n\n");
    printf ("N=<value>,Es=<value>,k=<value>\n\n");
    printf ("N  - sampling rate(int)\n");
    printf ("Es - signal energy(double)\n");
    printf ("k  - ratio of effective spectrum width(double)\n\n");
    gets (buf);
    while ((sscanf (buf, "N=%d,Es=%le,k=%le\n", &N, &Es, &k) != 3)
           || (N<=0) || (Es<=0) || (k<=0))
    {
        printf ("\nSorry but I can't recognize entered data\n");
        printf ("Please try again or press Ctrl+C to exit\n\n");
        gets (buf);
    }
    printf ("You are entered next data: N=%d,Es=%le,k=%le\n", N, Es, k);
    printf ("Calculation of effective angular frequency in progress\n");
    We = Calc_We (N, Es, k);
    printf ("Calculation is finished. We=%le\n", We);
    free (buf);
    return 0;
}
