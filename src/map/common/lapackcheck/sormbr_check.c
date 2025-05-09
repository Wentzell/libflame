#include "FLA_lapack2flame_return_defs.h"
#include "FLA_f2c.h"
static int c__1 = 1;
static int c_n1 = -1;

int sormbr_check(char *vect, char *side, char *trans, int *m, int *n, int *k, float *a, int *lda, float *tau, float *c__, int *ldc, float *work, int *lwork, int *info)
{
    /* System generated locals */
    int a_dim1, a_offset, c_dim1, c_offset, i__1, i__2;
    char ch__1[2] = {'\0','\0'};

    /* Local variables */
    int nb, nq, nw;
    logical left;
    logical notran, applyq;
    int lwkopt;
    logical lquery;

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;
    /* Function Body */
    *info = 0;
    applyq = lsame_(vect, "Q");
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");
    lquery = *lwork == -1;
    /* NQ is the order of Q or P and NW is the minimum dimension of WORK */
    if (left)
    {
        nq = *m;
        nw = *n;
    }
    else
    {
        nq = *n;
        nw = *m;
    }
    if (! applyq && ! lsame_(vect, "P"))
    {
        *info = -1;
    }
    else if (! left && ! lsame_(side, "R"))
    {
        *info = -2;
    }
    else if (! notran && ! lsame_(trans, "T"))
    {
        *info = -3;
    }
    else if (*m < 0)
    {
        *info = -4;
    }
    else if (*n < 0)
    {
        *info = -5;
    }
    else if (*k < 0)
    {
        *info = -6;
    }
    else /* if(complicated condition) */
    {
        /* Computing MAX */
        i__1 = 1;
        i__2 = min(nq,*k); // , expr subst
        if (applyq && *lda < max(1,nq) || ! applyq && *lda < max(i__1,i__2))
        {
            *info = -8;
        }
        else if (*ldc < max(1,*m))
        {
            *info = -11;
        }
        else if (*lwork < max(1,nw) && ! lquery)
        {
            *info = -13;
        }
    }
    if (*info == 0)
    {
        if (applyq)
        {
            if (left)
            {
                i__1 = *m - 1;
                i__2 = *m - 1;
                nb = ilaenv_(&c__1, "SORMQR", ch__1, &i__1, n, &i__2, &c_n1);
            }
            else
            {
                i__1 = *n - 1;
                i__2 = *n - 1;
                nb = ilaenv_(&c__1, "SORMQR", ch__1, m, &i__1, &i__2, &c_n1);
            }
        }
        else
        {
            if (left)
            {
                i__1 = *m - 1;
                i__2 = *m - 1;
                nb = ilaenv_(&c__1, "SORMLQ", ch__1, &i__1, n, &i__2, &c_n1);
            }
            else
            {
                i__1 = *n - 1;
                i__2 = *n - 1;
                nb = ilaenv_(&c__1, "SORMLQ", ch__1, m, &i__1, &i__2, &c_n1);
            }
        }
        lwkopt = max(1,nw) * nb;
        work[1] = (float) lwkopt;
    }
    if (*info != 0)
    {
        i__1 = -(*info);
        xerbla_("SORMBR", &i__1);
        return LAPACK_FAILURE;
    }
    else if (lquery)
    {
        return LAPACK_QUERY_RETURN;
    }
    /* Quick return if possible */
    work[1] = 1.f;
    if (*m == 0 || *n == 0)
    {
        return LAPACK_QUICK_RETURN;
    }
    return LAPACK_SUCCESS;
}
