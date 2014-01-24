namespace IGRFf2c {
   typedef float real;
   typedef long int integer;
   typedef long int logical;
   typedef int ftnlen;
   typedef double doublereal;
   typedef char address;
   int igrf_sub__(real *xlat, real *xlong, real *year, 
                  real *height, real *xl, integer *icode,
                  real *dip, real *dec, address *DataPath);
   int findb0_(real *stps, real *bdel, logical *value, 
               real *bequ, real *rr0);
   int shellg_(real *glat, real *glon, real *alt, real *dimo, 
               real *fl, integer *icode, real *b0);
   int shellc_(real *v, real *fl, real *b0);
   int feldg_(real *glat, real *glon, real *alt, 
              real *bnorth, real *beast, real *bdown, 
              real *babs, real *bx, real *by, real *bz);
   int feldc_(real *v, real *b);
   int feldi_();
   int feldcof_(real *year, real *dimo, address *DataPath);
   int initize_();


   int feldg_0_(int n__, real *glat, real *glon, real *alt, 
                real *bnorth, real *beast, real *bdown, 
                real *babs, real *bx, real *by, real *bz, real *v, real *b);
   int shellg_0_(int n__, real *glat, real *glon, 
                 real *alt, real *dimo, real *fl, 
                 integer *icode, real *b0, real *v);
   int stoer_(real *p, real *bq, real *r__);
   int intershc_(real *date, real *dte1, integer *nmax1, 
                 real *gh1, real *dte2, integer *nmax2, 
                 real *gh2, integer *nmax, real *gh);
   int extrashc_(real *date, real *dte1, integer *nmax1, 
                 real *gh1, integer *nmax2, real *gh2, 
                 integer *nmax, real *gh);
   int getshc_(integer *iu, char *fspec, integer *nmax, 
               real *erad, real *gh, integer *ier, 
               ftnlen fspec_len);
}
