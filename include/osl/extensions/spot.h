
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/spot.h                            **
     **-----------------------------------------------------------------**
     **                   First version: 22/05/2014                     **
     **-----------------------------------------------------------------**

 
 *****************************************************************************
 * OpenScop: Structures and formats for polyhedral tools to talk together    *
 *****************************************************************************
 *    ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,                *
 *    /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,             *
 *   /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\             *
 *  |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \            *
 *  | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\           *
 *  | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\          *
 *  | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \         *
 *  | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \        *
 *  | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \       *
 *  | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \      *
 *  | T | |   |   |   |   | |   | |   |   |   | |   | |   | |    \  \  \     *
 *  | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \    *
 *  | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \   *
 *  | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /   *
 *  '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'    *
 *                                                                           *
 * Copyright (C) 2008 University Paris-Sud 11 and INRIA                      *
 *                                                                           *
 * (3-clause BSD license)                                                    *
 * Redistribution and use in source  and binary forms, with or without       *
 * modification, are permitted provided that the following conditions        *
 * are met:                                                                  *
 *                                                                           *
 * 1. Redistributions of source code must retain the above copyright notice, *
 *    this list of conditions and the following disclaimer.                  *
 * 2. Redistributions in binary form must reproduce the above copyright      *
 *    notice, this list of conditions and the following disclaimer in the    *
 *    documentation and/or other materials provided with the distribution.   *
 * 3. The name of the author may not be used to endorse or promote products  *
 *    derived from this software without specific prior written permission.  *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR      *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.   *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,          *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.         *
 *                                                                           *
 * OpenScop Library, a library to manipulate OpenScop formats and data       *
 * structures. Written by:                                                   *
 * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr> and                         *
 * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                          *
 *                                                                           *
 *****************************************************************************/


#ifndef OSL_SPOT_H
# define OSL_SPOT_H

# include <stdio.h>
# include <osl/interface.h>
# include <osl/util.h>

# if defined(__cplusplus)
extern "C"
  {
# endif


# define OSL_URI_SPOT      "spot"

# define OSL_SPOT_NULL			"NULL"

 
/**
 * The osl_spot structure stores a an extention to handle a list of
 * Domains of Interest that modify how the computation is done for 
 * some subspaces of the original domain
 */

struct osl_spot { 
	int priority;  					/** Prioriy among other domains of interest. */ 
	char * dom;      				/** Domain codified in polihedral equations  */ 
	char * comp;        		/** Computation that should be done in the domain */ 
	void * user; 							/** User purpose pointer */ 
	struct osl_spot * next;	/** If there are muliple SPOTs, the next SPOT  */
	
}; 

typedef struct osl_spot   osl_spot_t;
typedef struct osl_spot * osl_spot_p;


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void            osl_spot_idump(FILE *, osl_spot_p, int);
void            osl_spot_dump(FILE *, osl_spot_p);
char *          osl_spot_sprint(osl_spot_p);


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/
osl_spot_p   osl_spot_sread_e(char *, char **);
osl_spot_p   osl_spot_sread(char **);


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
osl_spot_p   	osl_spot_malloc();
osl_spot_p					osl_spot_malloc();
void            	osl_spot_free(osl_spot_p);


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
osl_spot_p  	osl_spot_clone_e(osl_spot_p);
osl_spot_p  	osl_spot_clone(osl_spot_p);
int             	osl_spot_equal(osl_spot_p, osl_spot_p);
int 							osl_spot_length(osl_spot_p);
osl_spot_p 		osl_spot_concat(osl_spot_p, osl_spot_p);
osl_interface_p osl_spot_interface();


# if defined(__cplusplus)
  }
# endif

#endif /* define OSL_SPOT_H */
