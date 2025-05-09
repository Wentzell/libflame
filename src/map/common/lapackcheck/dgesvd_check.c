#include "FLA_lapack2flame_return_defs.h"
#include "FLA_f2c.h"
static int c__6 = 6;
static int c__0 = 0;
static int c_n1 = -1;

int dgesvd_check(char *jobu, char *jobvt, int *m, int *n, double *a, int *lda, double *s, double *u, int * ldu, double *vt, int *ldvt, double *work, int *lwork, int *info)
{
    /* System generated locals */
    int a_dim1, a_offset, u_dim1, u_offset, vt_dim1, vt_offset, i__2, i__3;
    char ch__1[2] = {'\0','\0'};
    /* Local variables */
    double dum[1];
    int ierr, lwork_dgebrd__, lwork_dgelqf__, lwork_dgeqrf__;
    int minmn, wrkbl, mnthr;
    logical wntua, wntva, wntun, wntuo, wntvn, wntvo, wntus, wntvs;
    int bdspac;
    extern int 
      dgebrd_(int *, int *, double *, int *, double *, double *, double *, double *, double *, int *, int *),
      dgelqf_(int *, int *, double *, int *, double *, double *, int *, int *), 
      dgeqrf_(int *, int *, double *, int *, double *, double *, int *, int *), 
      dorgbr_(char *, int *, int *, int *, double *, int *, double *, double *, int *, int *),
      dorglq_(int *, int *, int *, double *, int *, double *, double *, int *, int *), 
      dorgqr_(int *, int *, int *, double *, int *, double *, double *, int *, int *);
    int minwrk, maxwrk;
    logical lquery, wntuas, wntvas;
    int lwork_dorgbr_p__, lwork_dorgbr_q__, lwork_dorglq_m__, lwork_dorglq_n__, lwork_dorgqr_m__, lwork_dorgqr_n__;

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --s;
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1;
    u -= u_offset;
    vt_dim1 = *ldvt;
    vt_offset = 1 + vt_dim1;
    vt -= vt_offset;
    --work;
    /* Function Body */
    *info = 0;
    minmn = min(*m,*n);
    wntua = lsame_(jobu, "A");
    wntus = lsame_(jobu, "S");
    wntuas = wntua || wntus;
    wntuo = lsame_(jobu, "O");
    wntun = lsame_(jobu, "N");
    wntva = lsame_(jobvt, "A");
    wntvs = lsame_(jobvt, "S");
    wntvas = wntva || wntvs;
    wntvo = lsame_(jobvt, "O");
    wntvn = lsame_(jobvt, "N");
    lquery = *lwork == -1;
    if (! (wntua || wntus || wntuo || wntun))
    {
        *info = -1;
    }
    else if (! (wntva || wntvs || wntvo || wntvn) || wntvo && wntuo)
    {
        *info = -2;
    }
    else if (*m < 0)
    {
        *info = -3;
    }
    else if (*n < 0)
    {
        *info = -4;
    }
    else if (*lda < max(1,*m))
    {
        *info = -6;
    }
    else if (*ldu < 1 || wntuas && *ldu < *m)
    {
        *info = -9;
    }
    else if (*ldvt < 1 || wntva && *ldvt < *n || wntvs && *ldvt < minmn)
    {
        *info = -11;
    }
    /* Compute workspace */
    /* (Note: Comments in the code beginning "Workspace:" describe the */
    /* minimal amount of workspace needed at that point in the code, */
    /* as well as the preferred amount for good performance. */
    /* NB refers to the optimal block size for the immediately */
    /* following subroutine, as returned by ILAENV.) */
    if (*info == 0)
    {
        minwrk = 1;
        maxwrk = 1;
        if (*m >= *n && minmn > 0)
        {
            /* Compute space needed for DBDSQR */
            mnthr = ilaenv_(&c__6, "DGESVD", ch__1, m, n, &c__0, &c__0);
            bdspac = *n * 5;
            /* Compute space needed for DGEQRF */
            dgeqrf_(m, n, &a[a_offset], lda, dum, dum, &c_n1, &ierr);
            lwork_dgeqrf__ = (int) dum[0];
            /* Compute space needed for DORGQR */
            dorgqr_(m, n, n, &a[a_offset], lda, dum, dum, &c_n1, &ierr);
            lwork_dorgqr_n__ = (int) dum[0];
            dorgqr_(m, m, n, &a[a_offset], lda, dum, dum, &c_n1, &ierr);
            lwork_dorgqr_m__ = (int) dum[0];
            /* Compute space needed for DGEBRD */
            dgebrd_(n, n, &a[a_offset], lda, &s[1], dum, dum, dum, dum, &c_n1, &ierr);
            lwork_dgebrd__ = (int) dum[0];
            /* Compute space needed for DORGBR P */
            dorgbr_("P", n, n, n, &a[a_offset], lda, dum, dum, &c_n1, &ierr);
            lwork_dorgbr_p__ = (int) dum[0];
            /* Compute space needed for DORGBR Q */
            dorgbr_("Q", n, n, n, &a[a_offset], lda, dum, dum, &c_n1, &ierr);
            lwork_dorgbr_q__ = (int) dum[0];
            if (*m >= mnthr)
            {
                if (wntun)
                {
                    /* Path 1 (M much larger than N, JOBU='N') */
                    maxwrk = *n + lwork_dgeqrf__;
                    /* Computing MAX */
                    i__2 = maxwrk;
                    i__3 = *n * 3 + lwork_dgebrd__; // , expr subst
                    maxwrk = max(i__2,i__3);
                    if (wntvo || wntvas)
                    {
                        /* Computing MAX */
                        i__2 = maxwrk;
                        i__3 = *n * 3 + lwork_dorgbr_p__; // , expr subst
                        maxwrk = max(i__2,i__3);
                    }
                    maxwrk = max(maxwrk,bdspac);
                    /* Computing MAX */
                    i__2 = *n << 2;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntuo && wntvn)
                {
                    /* Path 2 (M much larger than N, JOBU='O', JOBVT='N') */
                    wrkbl = *n + lwork_dgeqrf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n + lwork_dorgqr_n__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    /* Computing MAX */
                    i__2 = *n * *n + wrkbl;
                    i__3 = *n * *n + *m * *n + *n; // , expr subst
                    maxwrk = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = *n * 3 + *m;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntuo && wntvas)
                {
                    /* Path 3 (M much larger than N, JOBU='O', JOBVT='S' or */
                    /* 'A') */
                    wrkbl = *n + lwork_dgeqrf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n + lwork_dorgqr_n__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    /* Computing MAX */
                    i__2 = *n * *n + wrkbl;
                    i__3 = *n * *n + *m * *n + *n; // , expr subst
                    maxwrk = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = *n * 3 + *m;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntus && wntvn)
                {
                    /* Path 4 (M much larger than N, JOBU='S', JOBVT='N') */
                    wrkbl = *n + lwork_dgeqrf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n + lwork_dorgqr_n__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = *n * *n + wrkbl;
                    /* Computing MAX */
                    i__2 = *n * 3 + *m;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntus && wntvo)
                {
                    /* Path 5 (M much larger than N, JOBU='S', JOBVT='O') */
                    wrkbl = *n + lwork_dgeqrf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n + lwork_dorgqr_n__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = (*n << 1) * *n + wrkbl;
                    /* Computing MAX */
                    i__2 = *n * 3 + *m;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntus && wntvas)
                {
                    /* Path 6 (M much larger than N, JOBU='S', JOBVT='S' or */
                    /* 'A') */
                    wrkbl = *n + lwork_dgeqrf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n + lwork_dorgqr_n__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = *n * *n + wrkbl;
                    /* Computing MAX */
                    i__2 = *n * 3 + *m;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntua && wntvn)
                {
                    /* Path 7 (M much larger than N, JOBU='A', JOBVT='N') */
                    wrkbl = *n + lwork_dgeqrf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n + lwork_dorgqr_m__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = *n * *n + wrkbl;
                    /* Computing MAX */
                    i__2 = *n * 3 + *m;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntua && wntvo)
                {
                    /* Path 8 (M much larger than N, JOBU='A', JOBVT='O') */
                    wrkbl = *n + lwork_dgeqrf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n + lwork_dorgqr_m__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = (*n << 1) * *n + wrkbl;
                    /* Computing MAX */
                    i__2 = *n * 3 + *m;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntua && wntvas)
                {
                    /* Path 9 (M much larger than N, JOBU='A', JOBVT='S' or */
                    /* 'A') */
                    wrkbl = *n + lwork_dgeqrf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n + lwork_dorgqr_m__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *n * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = *n * *n + wrkbl;
                    /* Computing MAX */
                    i__2 = *n * 3 + *m;
                    minwrk = max(i__2,bdspac);
                }
            }
            else
            {
                /* Path 10 (M at least N, but not much larger) */
                dgebrd_(m, n, &a[a_offset], lda, &s[1], dum, dum, dum, dum, & c_n1, &ierr);
                lwork_dgebrd__ = (int) dum[0];
                maxwrk = *n * 3 + lwork_dgebrd__;
                if (wntus || wntuo)
                {
                    dorgbr_("Q", m, n, n, &a[a_offset], lda, dum, dum, &c_n1, &ierr);
                    lwork_dorgbr_q__ = (int) dum[0];
                    /* Computing MAX */
                    i__2 = maxwrk;
                    i__3 = *n * 3 + lwork_dorgbr_q__; // , expr subst
                    maxwrk = max(i__2,i__3);
                }
                if (wntua)
                {
                    dorgbr_("Q", m, m, n, &a[a_offset], lda, dum, dum, &c_n1, &ierr);
                    lwork_dorgbr_q__ = (int) dum[0];
                    /* Computing MAX */
                    i__2 = maxwrk;
                    i__3 = *n * 3 + lwork_dorgbr_q__; // , expr subst
                    maxwrk = max(i__2,i__3);
                }
                if (! wntvn)
                {
                    /* Computing MAX */
                    i__2 = maxwrk;
                    i__3 = *n * 3 + lwork_dorgbr_p__; // , expr subst
                    maxwrk = max(i__2,i__3);
                }
                maxwrk = max(maxwrk,bdspac);
                /* Computing MAX */
                i__2 = *n * 3 + *m;
                minwrk = max(i__2,bdspac);
            }
        }
        else if (minmn > 0)
        {
            /* Compute space needed for DBDSQR */
            mnthr = ilaenv_(&c__6, "DGESVD", ch__1, m, n, &c__0, &c__0);
            bdspac = *m * 5;
            /* Compute space needed for DGELQF */
            dgelqf_(m, n, &a[a_offset], lda, dum, dum, &c_n1, &ierr);
            lwork_dgelqf__ = (int) dum[0];
            /* Compute space needed for DORGLQ */
            dorglq_(n, n, m, dum, n, dum, dum, &c_n1, &ierr);
            lwork_dorglq_n__ = (int) dum[0];
            dorglq_(m, n, m, &a[a_offset], lda, dum, dum, &c_n1, &ierr);
            lwork_dorglq_m__ = (int) dum[0];
            /* Compute space needed for DGEBRD */
            dgebrd_(m, m, &a[a_offset], lda, &s[1], dum, dum, dum, dum, &c_n1, &ierr);
            lwork_dgebrd__ = (int) dum[0];
            /* Compute space needed for DORGBR P */
            dorgbr_("P", m, m, m, &a[a_offset], n, dum, dum, &c_n1, &ierr);
            lwork_dorgbr_p__ = (int) dum[0];
            /* Compute space needed for DORGBR Q */
            dorgbr_("Q", m, m, m, &a[a_offset], n, dum, dum, &c_n1, &ierr);
            lwork_dorgbr_q__ = (int) dum[0];
            if (*n >= mnthr)
            {
                if (wntvn)
                {
                    /* Path 1t(N much larger than M, JOBVT='N') */
                    maxwrk = *m + lwork_dgelqf__;
                    /* Computing MAX */
                    i__2 = maxwrk;
                    i__3 = *m * 3 + lwork_dgebrd__; // , expr subst
                    maxwrk = max(i__2,i__3);
                    if (wntuo || wntuas)
                    {
                        /* Computing MAX */
                        i__2 = maxwrk;
                        i__3 = *m * 3 + lwork_dorgbr_q__; // , expr subst
                        maxwrk = max(i__2,i__3);
                    }
                    maxwrk = max(maxwrk,bdspac);
                    /* Computing MAX */
                    i__2 = *m << 2;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntvo && wntun)
                {
                    /* Path 2t(N much larger than M, JOBU='N', JOBVT='O') */
                    wrkbl = *m + lwork_dgelqf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m + lwork_dorglq_m__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    /* Computing MAX */
                    i__2 = *m * *m + wrkbl;
                    i__3 = *m * *m + *m * *n + *m; // , expr subst
                    maxwrk = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = *m * 3 + *n;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntvo && wntuas)
                {
                    /* Path 3t(N much larger than M, JOBU='S' or 'A', */
                    /* JOBVT='O') */
                    wrkbl = *m + lwork_dgelqf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m + lwork_dorglq_m__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    /* Computing MAX */
                    i__2 = *m * *m + wrkbl;
                    i__3 = *m * *m + *m * *n + *m; // , expr subst
                    maxwrk = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = *m * 3 + *n;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntvs && wntun)
                {
                    /* Path 4t(N much larger than M, JOBU='N', JOBVT='S') */
                    wrkbl = *m + lwork_dgelqf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m + lwork_dorglq_m__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = *m * *m + wrkbl;
                    /* Computing MAX */
                    i__2 = *m * 3 + *n;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntvs && wntuo)
                {
                    /* Path 5t(N much larger than M, JOBU='O', JOBVT='S') */
                    wrkbl = *m + lwork_dgelqf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m + lwork_dorglq_m__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = (*m << 1) * *m + wrkbl;
                    /* Computing MAX */
                    i__2 = *m * 3 + *n;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntvs && wntuas)
                {
                    /* Path 6t(N much larger than M, JOBU='S' or 'A', */
                    /* JOBVT='S') */
                    wrkbl = *m + lwork_dgelqf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m + lwork_dorglq_m__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = *m * *m + wrkbl;
                    /* Computing MAX */
                    i__2 = *m * 3 + *n;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntva && wntun)
                {
                    /* Path 7t(N much larger than M, JOBU='N', JOBVT='A') */
                    wrkbl = *m + lwork_dgelqf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m + lwork_dorglq_n__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = *m * *m + wrkbl;
                    /* Computing MAX */
                    i__2 = *m * 3 + *n;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntva && wntuo)
                {
                    /* Path 8t(N much larger than M, JOBU='O', JOBVT='A') */
                    wrkbl = *m + lwork_dgelqf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m + lwork_dorglq_n__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = (*m << 1) * *m + wrkbl;
                    /* Computing MAX */
                    i__2 = *m * 3 + *n;
                    minwrk = max(i__2,bdspac);
                }
                else if (wntva && wntuas)
                {
                    /* Path 9t(N much larger than M, JOBU='S' or 'A', */
                    /* JOBVT='A') */
                    wrkbl = *m + lwork_dgelqf__;
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m + lwork_dorglq_n__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dgebrd__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_p__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    /* Computing MAX */
                    i__2 = wrkbl;
                    i__3 = *m * 3 + lwork_dorgbr_q__; // , expr subst
                    wrkbl = max(i__2,i__3);
                    wrkbl = max(wrkbl,bdspac);
                    maxwrk = *m * *m + wrkbl;
                    /* Computing MAX */
                    i__2 = *m * 3 + *n;
                    minwrk = max(i__2,bdspac);
                }
            }
            else
            {
                /* Path 10t(N greater than M, but not much larger) */
                dgebrd_(m, n, &a[a_offset], lda, &s[1], dum, dum, dum, dum, & c_n1, &ierr);
                lwork_dgebrd__ = (int) dum[0];
                maxwrk = *m * 3 + lwork_dgebrd__;
                if (wntvs || wntvo)
                {
                    /* Compute space needed for DORGBR P */
                    dorgbr_("P", m, n, m, &a[a_offset], n, dum, dum, &c_n1, & ierr);
                    lwork_dorgbr_p__ = (int) dum[0];
                    /* Computing MAX */
                    i__2 = maxwrk;
                    i__3 = *m * 3 + lwork_dorgbr_p__; // , expr subst
                    maxwrk = max(i__2,i__3);
                }
                if (wntva)
                {
                    dorgbr_("P", n, n, m, &a[a_offset], n, dum, dum, &c_n1, & ierr);
                    lwork_dorgbr_p__ = (int) dum[0];
                    /* Computing MAX */
                    i__2 = maxwrk;
                    i__3 = *m * 3 + lwork_dorgbr_p__; // , expr subst
                    maxwrk = max(i__2,i__3);
                }
                if (! wntun)
                {
                    /* Computing MAX */
                    i__2 = maxwrk;
                    i__3 = *m * 3 + lwork_dorgbr_q__; // , expr subst
                    maxwrk = max(i__2,i__3);
                }
                maxwrk = max(maxwrk,bdspac);
                /* Computing MAX */
                i__2 = *m * 3 + *n;
                minwrk = max(i__2,bdspac);
            }
        }
        maxwrk = max(maxwrk,minwrk);
        work[1] = (double) maxwrk;
        if (*lwork < minwrk && ! lquery)
        {
            *info = -13;
        }
    }
    if (*info != 0)
    {
        i__2 = -(*info);
        xerbla_("DGESVD", &i__2);
        return LAPACK_FAILURE;
    }
    else if (lquery)
    {
        return LAPACK_QUERY_RETURN;
    }
    /* Quick return if possible */
    if (*m == 0 || *n == 0)
    {
        return LAPACK_QUICK_RETURN;
    }

    return LAPACK_SUCCESS;
}
