#include <stdio.h>
#include <math.h>

#define EPS1 1.0e-12
#define EPS2 1.0e-12
#define EPS3 1.0e-12
#define EPS4 1.0e-12
//#define INFINITY 10000

#define MPI 3.1415926536
#define MPIMUL2 6.2831853072
#define MPIDIV2 1.5707963268


/***********************************************************/
double mod2pi(double angle);

/***********************************************************/
double my_atan2(double y,double x);

/***********************************************************/
double c_c_c(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double c_cc(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double csca(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double cscb(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double ccu_cuc(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double c_cucu_c(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double c_c2sca(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double c_c2scb(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double c_c2sc2_c(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double cc_c(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double csc2_ca(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double csc2_cb(double x,double y,double phi,double rs,double rc,double *t,double *u,double *v, float RADCURV);

/***********************************************************/
double reed_shepp(double x1, double y1, double t1, double x2, double y2, double t2, int *numero, double *tr, double *ur, double *vr);

/***********************************************************/
double min_length_rs(double x1,double y1,double t1,double x2,double y2,double t2,int *numero,double *t,double *u,double *v);

/***********************************************************/
int fct_curve(int ty, int orientation, double val, double *x1, double *y1, double *t1, double delta, double *pathx, double *pathy, double *patht, int n);

/***********************************************************/
int constRS(int num,double t,double u,double v,double x1,double y1,double t1,double delta,double *pathx,double *pathy,double *patht);
