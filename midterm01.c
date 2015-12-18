#include <math.h>
#include <stdio.h>
#include "adjust.c"
#include "timer.c"


double pi_leibniz (int n);
double pi_leibniz (int n)//Uses the Leibniz series for pi 
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += 4 * pow(-1, i) / (2.*i + 1.);
    }
    return sum;
}

double pi_bbp (int n);
double pi_bbp (int n)//Uses the Bailey-Borwein-Plouffe series for pi
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += ((4. / (8.*i + 1.)) - (2. / (8.*i +4.)) - (1. / (8.*i +5.)) - (1. / (8.*i +6.))) / (pow(16,i));
    }
    return sum;
}

int main ()
{
    double pi = 0;
    printf("Leibniz:\nIndex        Pi Value              Abs Error\n");
    for (int i = 1; fabs(pi - M_PI) > pow(10,-6); i *= 2)//loops over value of i from i=1 and doubles i every iteration. Takes value of Leibniz series up to points equal to i.
    {//stops when absolute error is less than 10^-6
        pi = pi_leibniz(i);
        printf("%8d  %20.15f  %20.15f\n", i, pi, fabs(pi - M_PI));
    }    
    pi = 0;
    printf("\nBBP:\nIndex        Pi Value              Abs Error\n");
    for (int i = 1; fabs(pi - M_PI) > pow(10,-6); i *= 2)//loops over value of i from i=1 and doubles i every iteration. Takes value of BBP series up to points equal to i.
    {
        pi = pi_bbp(i);
        printf("%8d  %20.15f  %20.15f\n", i, pi, fabs(pi - M_PI));
    }
    pi = 0;
    timer_start();//measuring time in one Leibniz call
    pi = pi_leibniz(1048576);
    double t_leibniz = timer_stop();
    double t_bbp = 0;
    for (int k = 1; k <= 100; k++)
    {//BBP is too fast to effectively measure the time of one iteration, so we ran it for 100 iterations and counted up the total time.
	timer_start();
        pi = pi_bbp(4);
        t_bbp += timer_stop();
    }
    int count_leibniz = adjust_rep_count(1, t_leibniz, 1., 2.);//this function returns how many times to iterate a function so that the total time is between 1 and 2 seconds.
    int count_bbp = adjust_rep_count(5, t_bbp, 1., 2.);//using this to measure time per function call with greater precision. With great precision comes great responsibility.    
    for (int k = 1; k <= count_leibniz; k++)
    {
        timer_start();
        pi = pi_leibniz(1048576);
        t_bbp += timer_stop();
    }
    for (int k = 1; k <= count_bbp; k++)
    {
        timer_start();
        pi = pi_bbp(4);
        t_bbp += timer_stop();
    }
    double ratio_leibniz = t_leibniz / count_leibniz;
    double ratio_bbp = t_bbp / count_bbp;
    printf("\nLeibniz time per function call:  %e\nBBP time per function call:  %e\nRatio of Leibniz to BBP:  %e\n", ratio_leibniz, ratio_bbp, ratio_leibniz / ratio_bbp);
}
