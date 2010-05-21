h29033
s 00000/00000/00068
d D 2.1 93/02/03 15:25:10 suprem45 2 1
c Initial IV.GS release
e
s 00068/00000/00000
d D 1.1 93/02/03 15:24:16 suprem45 1 0
c date and time created 93/02/03 15:24:16 by suprem45
e
u
U
f e 0
t
T
I 1
static char sccsid[]="panic.c 5.1  7/3/91 08:41:10";
/*----------------------------------------------------------------------
 *
 * panic - remedial action attempted
 *
 * Copyright c 1985 The board of trustees of the Leland Stanford
 *                  Junior University. All rights reserved.
 * This subroutine may not be used outside of the SUPREM4 computer
 * program without the prior written consent of Stanford University.
 *
 * Original: CSR
 *---------------------------------------------------------------------*/

#include <stdio.h>
#include "global.h"
#include "constant.h"
#include "geom.h"
#include "material.h"
#include "impurity.h"
#include "diffuse.h"
#include "shell.h"
#include "sysdep.h"

panic (s)
    char *s;
{
    fprintf(stderr,"suprem4 panic: %s\n",s);
    if( (!strcmp( s, "nocore")) || (!strcmp( s, "Out of memory")))
	goto outtahere;
    
    fprintf( stderr, "Writing structure to panic.str..."); fflush(stderr);
    if( (ig2_write("panic.str", 0, 1.0)) < 0)
	fprintf(stderr, "Failed\n");
    else
	fprintf(stderr, "Succeeded\n");

#ifdef SUPPORT
    fprintf( stderr, "Submitting bug report..."); fflush(stderr);

    /* Let's try not to confuse the shell too badly. */
    /* People who run csh here lose big because it balks at quoted newlines */
    for (t=s; *t; t++)
	if (*t == '\'' || *t=='\\')
	    *t = '#';
    sprintf( cmdbuf, "mail -s 'suprem4 panic: %s\nExecuting command: %s\nTotal time: %e' %s %s&",
	    s, buffer, total, SUPPORT, (ier<0)? "</dev/null": "<panic.str");
    
    if(system( cmdbuf))
	fprintf( stderr, "Failed\n");
    else
	fprintf( stderr, "Succeeded\n");
#endif
    outtahere:
    
    fprintf(stderr, "Better luck next time.\n");
    fflush(stdout);
    fflush(stderr);
    abort();
}

		
/*-----------------GridSave---------------------------------------------
 * Store a valid grid before anything bad happens.
 *----------------------------------------------------------------------*/
GridSave ()
{
}

E 1