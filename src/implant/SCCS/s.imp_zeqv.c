h39699
s 00000/00000/00060
d D 2.1 93/02/03 15:10:36 suprem45 2 1
c Initial IV.GS release
e
s 00060/00000/00000
d D 1.1 93/02/03 15:08:32 suprem45 1 0
c date and time created 93/02/03 15:08:32 by suprem45
e
u
U
f e 0
t
T
I 1
/* date: 05 jul 85 (mje)
 *
 * "zeqv" : Find the equivalent dose through a given depth.
 *
 * calling sequence:
 *	double
 *	zeqv(dose, dx, kp)
 *
 * where:
 *	<return>	- (double) depth over which Dose extends.
 *	dose		- (double) Dose over which to find an 'zeqiv'
 *	dx		- (double) Delta x to use in calculations.
 *	kp		- (double []) Pearson constants.
 *
 * notes:
 *	> What happens if the target dose is too large for the implantation
 *	  parameters?
 *
 * written: Michael Eldredge (apr 85)
 *
 * imp_zeqv.c	5.1	7/3/91	12:08:46
 */

#include <math.h>
#define  abs(V) ((V) < 0.? -(V) : (V))

/* Offsets to the Pearson-IV constants array */
#include "global.h"
#include "constant.h"
#include "implant.h"

double
zeqv(dose, qtot, dx, bt, data)
	double	 dose ;
	double	 qtot ;
	double	 dx ;
	double bt;
	struct imp_info	 *data ;
	{

	double	 x , val, ov ;
	double	 q = 0.0 ;	/* Accumulating dose */
	double	 qtarg ;	/* target dose */

	qtarg = (dose / qtot) * data->area / dx * 1e4 ;

	ov = imp_vert(0.0, data);
	for (x = dx ; x < data->maxz ; x += dx) {
		val = imp_vert( x , data );

		q += 0.5 * (val + ov) ;
		if (q >= qtarg) {
		    x -= dx * (q - qtarg) / val ;
			break ;
			}
		ov = val;
		}

	return ( x ) ;
	}
E 1