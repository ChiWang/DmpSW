

#ifndef GLAST_slew_estimate_h
#define GLAST_slew_estimate_h

#ifdef __cplusplus
extern "C" {
#endif
double GLAST_slew_estimate ( double ra_s, double dec_s, // sun coordinates (radians)
			     double ra_i, double dec_i, // initial pointing
			     double ra_f, double dec_f // final pointing
			     );






#ifdef __cplusplus
}
#endif


#endif
