
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/spot.c                       **
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <osl/macros.h>
#include <osl/util.h>
#include <osl/interface.h>
#include <osl/extensions/spot.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * osl_spot_idump function:
 * this function displays an osl_spot_t structure (*spot) into a
 * file (file, possibly stdout) in a way that trends to be understandable. 
 * It includes an indentation level (level) in order to work with others
 * idump functions.
 * \param[in] file    The file where the information has to be printed.
 * \param[in] spot 		The spot_t structure to print.
 * \param[in] level   Number of spaces before printing, for each line.
 */

void osl_spot_indent(FILE * file,  int level) { 
	int j;
	for (j = 0; j < level; j++)
		fprintf(file, "|\t");
	
}
 
void osl_spot_idump(FILE * file, osl_spot_p spot, int level) {
	

  // Go to the right level.
	if (spot == NULL) { 
		osl_spot_indent(file, level);
    fprintf(file, "+-- NULL spot\n");
    return;
	}
	  
	if (spot != NULL)  { 
		// Go to the right level.
		osl_spot_indent(file, level);
		fprintf(file, "+-- osl_spot_t\n");
    osl_spot_indent(file, level+2); 
    fprintf(file, "\n");
		osl_spot_indent(file, level+1);
		fprintf(file, "+-- priority: %d\n", spot->priority);
		osl_spot_indent(file, level+2);
		fprintf(file, "\n");
		osl_spot_indent(file, level+1);
		fprintf(file, "+-- dom: %s\n", spot->dom);
		osl_spot_indent(file, level+2);
		fprintf(file, "\n");
		osl_spot_indent(file, level+1);
		if (spot->comp != NULL) 
			fprintf(file, "+-- comp: %s\n", spot->comp);
		else 
			fprintf(file, "+-- NULL comp\n");
		spot = spot->next; 
	}
	
	while (spot != NULL)  { 
		// Go to the right level.
		osl_spot_indent(file, level+1); fprintf(file, "V\n");
		osl_spot_indent(file, level);
		fprintf(file, "|   osl_spot_t\n");
    osl_spot_indent(file, level+2); fprintf(file, "\n");
		osl_spot_indent(file, level+1);
		fprintf(file, "+-- priority: %d\n", spot->priority);
		osl_spot_indent(file, level+2); fprintf(file, "\n");
		osl_spot_indent(file, level+1);
		fprintf(file, "+-- dom: %s\n", spot->dom);
		osl_spot_indent(file, level+2); fprintf(file, "\n");
		osl_spot_indent(file, level+1);
		if (spot->comp != NULL) 
			fprintf(file, "+-- comp: %s\n", spot->comp);
		else 
			fprintf(file, "+-- NULL comp\n");
		osl_spot_indent(file, level+2);
		fprintf(file, "\n");
		spot = spot->next; 
	}
  
  // The last line.
  osl_spot_indent(file, level+1);
  fprintf(file, "\n");
}

/**
 * osl_spot_dump function:
 * this function prints the content of an osl_spot_t structure
 * (*spot) into a file (file, possibly stdout).
 * \param[in] file    The file where the information has to be printed.
 * \param[in] spot The spot structure to print.
 */
void osl_spot_dump(FILE * file, osl_spot_p spot) {
  osl_spot_idump(file, spot, 0);
}

/**
 * osl_spot_sprint function:
 * this function prints the content of an osl_spot_t structure
 * (*spot) into a string (returned) in the OpenScop textual format.
 * \param[in] spot The spot structure to print.
 * \return A string containing the OpenScop dump of the spot structure.
 */
char * osl_spot_sprint(osl_spot_p spot) {
  int high_water_mark = OSL_MAX_STRING;
  char * string = NULL;
  char buffer[OSL_MAX_STRING];

	OSL_malloc(string, char *, high_water_mark * sizeof(char));

	sprintf(string, "%d\n", osl_spot_length(spot)); 
			
	while (spot != NULL) {
    sprintf(buffer, "# priority\n%d\n", spot->priority); 
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    sprintf(buffer, "# isl domain\n%s\n", spot->dom); 
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    sprintf(buffer, "# c computation\n%s\n", 
			(spot->comp != NULL) ? spot->comp : OSL_SPOT_NULL);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    spot = spot->next;
  }
  // Keep only the memory space we need.
  OSL_realloc(string, char *, (strlen(string) + 1) * sizeof(char));

  return string;
}

/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/

osl_spot_p osl_spot_sread_e(char *buffer, char **input) { 
		osl_spot_p spot;

		spot = osl_spot_malloc();
		// read priority
		osl_util_sskip_blank_and_comments(input);
		osl_util_sreadl(input, buffer); 
		spot->priority = atoi(buffer);
		// read domain
		osl_util_sskip_blank_and_comments(input);
		osl_util_sreadl(input, buffer);
		spot->dom = osl_util_strdup(buffer);
		// read computation
		osl_util_sskip_blank_and_comments(input);
		osl_util_sreadl(input, buffer); 
		if (strcmp(buffer, OSL_SPOT_NULL) != 0) 
			spot->comp = osl_util_strdup(buffer);
		
		return spot; 
}

/**
 * osl_spot_sread function:
 * this function reads a spot structure from a string complying to the
 * OpenScop textual format and returns a pointer to this spot structure.
 * The input parameter is updated to the position in the input string this
 * function reach right after reading the spot structure.
 * \param[in,out] input The input string where to find a spot.
 *                      Updated to the position after what has been read.
 * \return A pointer to the spot structure that has been read.
 */
osl_spot_p osl_spot_sread(char ** input) {
  osl_spot_p spot, spotl;
  char buffer[OSL_MAX_STRING];
	int size;

  if (*input == NULL) {
    OSL_debug("no spot optional tag");
    return NULL;
  }
  
  if (strlen(*input) > OSL_MAX_STRING) 
    OSL_error("the input is too long");

	// Read list size
	osl_util_sskip_blank_and_comments(input);
  osl_util_sreadl(input, buffer);
  size = atoi(buffer); 
	// scan the list
	if (size > 0) {
		spot = spotl = osl_spot_sread_e(buffer, input);
		size--;   
	} else 
		return NULL; 
	
	while (size > 0) { 
		spot->next = osl_spot_sread_e(buffer, input); 
		spot = spot->next; 
		size--; 
	}
	
	// update the input pointer
  input += strlen(*input);

  return spotl; 
}	


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/

/**
 * osl_spot_malloc function:
 * this function allocates the necessary a space for a new osl_spot
 * structure. 
 * \return A pointer to the spot structure created
 */ 
osl_spot_p osl_spot_malloc() { 
	osl_spot_p spot;
	
	OSL_malloc(spot, osl_spot_p, sizeof(osl_spot_t));
	spot->priority=-1; 
	spot->dom=NULL; 
	spot->comp=NULL;
	spot->user=NULL;
	spot->next=NULL; 
	return spot;
} 

/**
 * osl_spot_free function:
 * this function frees the allocated memory for an osl_spot_t
 * structure.User purpose pointer will not be freed.  
 * \param[in,out] spot The pointer to the spot structure to free.
 */
void osl_spot_free(osl_spot_p spot) { 
	if (spot != NULL) {
		if (spot->dom != NULL)
			free(spot->dom);
		if (spot->comp != NULL)
			free(spot->comp);
		if (spot->next != NULL) 
			osl_spot_free(spot->next);
		free(spot); 
	}
}

/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/

/**
 * osl_spot_clone_e function: 
 * this function clones the head of the spot structure
 * \param[in] d The pointer to the spot structure 
 * \return A pointer to the clone of the head of the list
 */ 
osl_spot_p osl_spot_clone_e(osl_spot_p d) {
	osl_spot_p e; 
	if (d == NULL)
		return NULL; 
	e = osl_spot_malloc();
	e->priority = d->priority;
	if (d->dom != NULL) 
		e->dom = osl_util_strdup(d->dom);
	if (d->comp != NULL)
		e->comp = osl_util_strdup(d->comp);
	return e; 
}

/**
 * osl_spot_clone function:
 * this function builds and returns a "hard copy" (not a pointer copy) of an
 * osl_spot_t data structure. User purpose pointer will not be cloned. 
 * \param[in] spot The pointer to the spot structure to clone.
 * \return A pointer to the clone of the spot structure.
 */
osl_spot_p osl_spot_clone(osl_spot_p  spot) { 
	osl_spot_p clone, di; 
	di = clone = osl_spot_clone_e(spot); 
	while (spot != NULL) { 
		spot = spot->next; 
		di->next = osl_spot_clone_e(spot);
		di = di->next;
	}
	return clone;
}


/**
 * osl_spot_equal function:
 * this function returns true if the two spot structures are the same
 * (content-wise), false otherwise. User purpose pointer will not be 
 * compared.  
 * \param[in] d1  The first spot structure.
 * \param[in] d2  The second spot structure.
 * \return 1 if d1 and d2 are the same (content-wise), 0 otherwise.
 */
int osl_spot_equal(osl_spot_p d1, osl_spot_p d2) { 
	if (d1 == d2) { 
		return 1; 
	}
	while (d1 != NULL && d2 != NULL) { 
		if (! ((d1->priority == d2->priority) 
					&& (osl_util_safe_strcmp(d1->dom, d2->dom) == 0)
					&& (osl_util_safe_strcmp(d1->comp, d2->comp) == 0)  ))	  
			return 0;
			
		d1 = d1->next; 
		d2 = d2->next; 
	}
	
	if (d1 != d2) 
		return 0; // one of them is larger 
		
	return 1;  
}

/** 
 * osl_spot_length function:
 * calculates the lenght of the spot list
 * \param[in] d  The spot list
 * \return An integer containing the length of the list
 */ 
int osl_spot_length(osl_spot_p d) { 
	int len = 0; 
	while (d != NULL) { 
		len++;
		d = d->next;
	}
	return len; 
}

/** 
 * osl_spot_concat function:
 * this function will concatenate two lists of spots
 * \param[in] d1  The first spot list 
 * \param[in] d2  The second spot list
 * \return A pointer to the new list
 */
osl_spot_p osl_spot_concat(osl_spot_p d1, osl_spot_p d2) {
	osl_spot_p spott;
 
	// get the last element of d1
	for (spott = d1; spott != NULL && spott->next != NULL; spott=spott->next)
		; 
	if (spott == NULL) 
		return d2; 
	// link the end of d1 with the beginning of d2
	spott->next = d2; 
	return d1; 
}
		
/**
 * osl_spot_interface function:
 * this function creates an interface structure corresponding to the spot
 * extension and returns it).
 * \return An interface structure for the spot extension.
 */
osl_interface_p osl_spot_interface() {
  osl_interface_p interface = osl_interface_malloc();
  
  OSL_strdup(interface->URI, OSL_URI_SPOT);
  interface->idump  = (osl_idump_f)osl_spot_idump;
  interface->sprint = (osl_sprint_f)osl_spot_sprint;
  interface->sread  = (osl_sread_f)osl_spot_sread;
  interface->malloc = (osl_malloc_f)osl_spot_malloc;
  interface->free   = (osl_free_f)osl_spot_free;
  interface->clone  = (osl_clone_f)osl_spot_clone;
  interface->equal  = (osl_equal_f)osl_spot_equal;

  return interface;
}

