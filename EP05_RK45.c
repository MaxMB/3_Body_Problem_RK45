// MAP5725 - EP03 - 07/02/2019
// Marcelo Monari Baccaro - 8989262
// 3-body problem with RK45

#include <stdio.h>
#include <math.h>
int n = 18; // system dimension
double G = 1000; // gravitational constant
double m[3] = {100,100,100}; // mass vector

// 3-body problem
void f (double t, double y[n], double v[n]) {
    int i;
    double d[3]; // distance^3

    d[0] = pow(pow(y[0]-y[3],2)+pow(y[1]-y[4],2)+pow(y[2]-y[5],2),1.5); // d12
    d[1] = pow(pow(y[0]-y[6],2)+pow(y[1]-y[7],2)+pow(y[2]-y[8],2),1.5); // d13
    d[2] = pow(pow(y[3]-y[6],2)+pow(y[4]-y[7],2)+pow(y[5]-y[8],2),1.5); // d23

    for (i=0;i<n/2;i++) v[i] = y[i+n/2];

    v[n/2] = G * (m[1]*(y[3]-y[0])/d[0] + m[2]*(y[6]-y[0])/d[1]); // v1x
    v[n/2+1] = G * (m[1]*(y[4]-y[1])/d[0] + m[2]*(y[7]-y[1])/d[1]); // v1y
    v[n/2+2] = G * (m[1]*(y[5]-y[2])/d[0] + m[2]*(y[8]-y[2])/d[1]); // v1z

    v[n/2+3] = G * (m[0]*(y[0]-y[3])/d[0] + m[2]*(y[6]-y[3])/d[2]); // v2x
    v[n/2+4] = G * (m[0]*(y[1]-y[4])/d[0] + m[2]*(y[7]-y[4])/d[2]); // v2y
    v[n/2+5] = G * (m[0]*(y[2]-y[5])/d[0] + m[2]*(y[8]-y[5])/d[2]); // v2z

    v[n/2+6] = G * (m[0]*(y[0]-y[6])/d[1] + m[1]*(y[3]-y[6])/d[2]); // v3x
    v[n/2+7] = G * (m[0]*(y[1]-y[7])/d[1] + m[1]*(y[4]-y[7])/d[2]); // v3y
    v[n/2+8] = G * (m[0]*(y[2]-y[8])/d[1] + m[1]*(y[5]-y[8])/d[2]); // v3z
}

void rk45 (double t, double h, double y[n]) {
    int i;
    double k1[n], k2[n], k3[n], k4[n], k5[n], v[n];
    f(t,y,k1);
    for (i=0;i<n;i++) v[i] = y[i] + h*k1[i]/4;
    f(t+h/4,v,k2);
    for (i=0;i<n;i++) v[i] = y[i] + h*(k1[i]*3/32 + k2[i]*9/32);
    f(t+h*3/8,v,k3);
    for (i=0;i<n;i++) v[i] = y[i] + h*(k1[i]*1932/2197 - k2[i]*7200/2197 + k3[i]*7296/2197);
    f(t+h*12/13,v,k4);
    for (i=0;i<n;i++) v[i] = y[i] + h*(k1[i]*439/216 - k2[i]*8 + k3[i]*3680/513 - k4[i]*845/4104);
    f(t+h,v,k5);
    for (i=0;i<n;i++) y[i] = y[i] + h*(k1[i]*25/216 + k3[i]*1408/2565 + k4[i]*2197/4104 - k5[i]/5);
}

int main() {
    int i;
    double w[18] = {3,0,0,0,3,0,0,0,3,0,100,0,0,0,100,100,0,0}; // p(x,y,z) | v(x,y,z)
    double h=0.0001, tf=0.1, t=0;
    FILE *f = fopen("solution.txt","w");

    /*
    printf("\n3-body problem with RK45 method\n\n");
    prinf("Mass m1 m2 m3 = ");
    scanf(" %lf %lf %lf",&m[0],&m[1],&m[2]);
    printf("Initial x1 y1 z1 vx1 vy1 vz1 = ");
    scanf(" %lf %lf %lf %lf %lf %lf",&w[0],&w[1],&w[2],&w[9],&w[10],&w[11]);
    printf("Initial x2 y2 z2 vx2 vy2 vz2 = ");
    scanf(" %lf %lf %lf %lf %lf %lf",&w[3],&w[4],&w[5],&w[12],&w[13],&w[14]);
    printf("Initial x3 y3 z3 vx3 vy3 vz3 = ");
    scanf(" %lf %lf %lf %lf %lf %lf",&w[6],&w[7],&w[8],&w[15],&w[16],&w[17]);
    printf("Value of G = ");
    scanf(" %lf",&G);
    printf("Time step: h = ");
    scanf(" %lf",&h);
    printf("Final time: tf = ");
    scanf(" %lf",&tf);
    */

    fprintf(f,"%f", t);
    for (i=0;i<18;i++) fprintf(f," %f", w[i]);
    fprintf(f,"\n");

    while (t < tf) {
        t = t + h;
        rk45(t,h,w);
        fprintf(f,"%f", t);
        for (i=0;i<18;i++) fprintf(f," %f", w[i]);
        fprintf(f,"\n");
    }
    printf("\nDONE!\n");
    return 0;
}
