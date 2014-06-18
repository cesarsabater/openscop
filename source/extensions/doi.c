
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/doi.c                       **
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
#include <osl/extensions/doi.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * osl_doi_idump function:
 * this function displays an osl_doi_t structure (*doi) into a
 * file (file, possibly stdout) in a way that trends to be understandable. 
 * It includes an indentation level (level) in order to work with others
 * idump functions.
 * \param[in] file    The file where the information has to be printed.
 * \param[in] doi 		The doi_t structure to print.
 * \param[in] level   Number of spaces before printing, for each line.
 */

void osl_doi_indent(FILE * file,  int level) { 
	int j;
	for (j = 0; j < level; j++)
		fprintf(file, "|\t");
	
}
 
void osl_doi_idump(FILE * file, osl_doi_p doi, int level) {
	

  // Go to the right level.
	if (doi == NULL) { 
		osl_doi_indent(file, level);
    fprintf(file, "+-- NULL doi\n");
    return;
	}
	  
	if (doi != NULL)  { 
		// Go to the right level.
		osl_doi_indent(file, level);
		fprintf(file, "+-- osl_doi_t\n");
    osl_doi_indent(file, level+2); 
    fprintf(file, "\n");
		osl_doi_indent(file, level+1);
		fprintf(file, "+-- priority: %d\n", doi->priority);
		osl_doi_indent(file, level+2);
		fprintf(file, "\n");
		osl_doi_indent(file, level+1);
		fprintf(file, "+-- dom: %s\n", doi->dom);
		osl_doi_indent(file, level+2);
		fprintf(file, "\n");
		osl_doi_indent(file, level+1);
		if (doi->comp != NULL) 
			fprintf(file, "+-- comp: %s\n", doi->comp);
		else 
			fprintf(file, "+-- NULL comp\n");
		doi = doi->next; 
	}
	
	while (doi != NULL)  { 
		// Go to the right level.
		osl_doi_indent(file, level+1); fprintf(file, "V\n");
		osl_doi_indent(file, level);
		fprintf(file, "|   osl_doi_t\n");
    osl_doi_indent(file, level+2); fprintf(file, "\n");
		osl_doi_indent(file, level+1);
		fprintf(file, "+-- priority: %d\n", doi->priority);
		osl_doi_indent(file, level+2); fprintf(file, "\n");
		osl_doi_indent(file, level+1);
		fprintf(file, "+-- dom: %s\n", doi->dom);
		osl_doi_indent(file, level+2); fprintf(file, "\n");
		osl_doi_indent(file, level+1);
		if (doi->comp != NULL) 
			fprintf(file, "+-- comp: %s\n", doi->comp);
		else 
			fprintf(file, "+-- NULL comp\n");
		osl_doi_indent(file, level+2);
		fprintf(file, "\n");
		doi = doi->next; 
	}
  
  // The last line.
  osl_doi_indent(file, level+1);
  fprintf(file, "\n");
}

/**
 * osl_doi_dump function:
 * this function prints the content of an osl_doi_t structure
 * (*doi) into a file (file, possibly stdout).
 * \param[in] file    The file where the information has to be printed.
 * \param[in] doi The doi structure to print.
 */
void osl_doi_dump(FILE * file, osl_doi_p doi) {
  osl_doi_idump(file, doi, 0);
}

/**
 * osl_doi_sprint function:
 * this function prints the content of an osl_doi_t structure
 * (*doi) into a string (returned) in the OpenScop textual format.
 * \param[in] doi The doi structure to print.
 * \return A string containing the OpenScop dump of the doi structure.
 */
char * osl_doi_sprint(osl_doi_p doi) {
  int high_water_mark = OSL_MAX_STRING;
  char * string = NULL;
  char buffer[OSL_MAX_STRING];

	OSL_malloc(string, char *, high_water_mark * sizeof(char));

	sprintf(string, "%d\n", osl_doi_length(doi)); 
			
	while (doi != NULL) {
    sprintf(buffer, "# priority\n%d\n", doi->priority); 
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    sprintf(buffer, "# isl domain\n%s\n", doi->dom); 
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    sprintf(buffer, "# c computation\n%s\n", 
			(doi->comp != NULL) ? doi->comp : OSL_DOI_NULL);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    doi = doi->next;
  }
  // Keep only the memory space we need.
  OSL_realloc(string, char *, (strlen(string) + 1) * sizeof(char));

  return string;
}

/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/

osl_doi_p osl_doi_sread_e(char *buffer, char **input) { 
		osl_doi_p doi;

		doi = osl_doi_malloc();
		// read priority
		osl_util_sskip_blank_and_comments(input);
		osl_util_sreadl(input, buffer); 
		doi->priority = atoi(buffer);
		// read domain
		osl_util_sskip_blank_and_comments(input);
		osl_util_sreadl(input, buffer);
		doi->dom = osl_util_strdup(buffer);
		// read computation
		osl_util_sskip_blank_and_comments(input);
		osl_util_sreadl(input, buffer); 
		if (strcmp(buffer, OSL_DOI_NULL) != 0) 
			doi->comp = osl_util_strdup(buffer);
		
		return doi; 
}

/**
 * osl_doi_sread function:
 * this function reads a doi structure from a string complying to the
 * OpenScop textual format and returns a pointer to this doi structure.
 * The input parameter is updated to the position in the input string this
 * function reach right after reading the doi structure.
 * \param[in,out] input The input string where to find a doi.
 *                      Updated to the position after what has been read.
 * \return A pointer to the doi structure that has been read.
 */
osl_doi_p osl_doi_sread(char ** input) {
  osl_doi_p doi, doil;
  char buffer[OSL_MAX_STRING];
	int size;

  if (*input == NULL) {
    OSL_debug("no doi optional tag");
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
		doi = doil = osl_doi_sread_e(buffer, input);
		size--;   
	} else 
		return NULL; 
	
	while (size > 0) { 
		doi->next = osl_doi_sread_e(buffer, input); 
		doi = doi->next; 
		size--; 
	}
	
	// update the input pointer
  input += strlen(*input);

  return doil; 
}	


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/

/**
 * osl_doi_malloc function:
 * this function allocates the necessary a space for a new osl_doi
 * structure. 
 * \return A pointer to the doi structure created
 */ 
osl_doi_p osl_doi_malloc() { 
	osl_doi_p doi;
	
	OSL_malloc(doi, osl_doi_p, sizeof(osl_doi_t));
	doi->priority=-1; 
	doi->dom=NULL; 
	doi->comp=NULL;
	doi->user=NULL;
	doi->next=NULL; 
	return doi;
} 

/**
 * osl_doi_free function:
 * this function frees the allocated memory for an osl_doi_t
 * structure.User purpose pointer will not be freed.  
 * \param[in,out] doi The pointer to the doi structure to free.
 */
void osl_doi_free(osl_doi_p doi) { 
	if (doi != NULL) {
		if (doi->dom != NULL)
			free(doi->dom);
		if (doi->comp != NULL)
			free(doi->comp);
		if (doi->next != NULL) 
			osl_doi_free(doi->next);
		free(doi); 
	}
}

/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/

/**
 * osl_doi_clone_e function: 
 * this function clones the head of the doi structure
 * \param[in] d The pointer to the doi structure 
 * \return A pointer to the clone of the head of the list
 */ 
osl_doi_p osl_doi_clone_e(osl_doi_p d) {
	osl_doi_p e; 
	if (d == NULL)
		return NULL; 
	e = osl_doi_malloc();
	e->priority = d->priority;
	if (d->dom != NULL) 
		e->dom = osl_util_strdup(d->dom);
	if (d->comp != NULL)
		e->comp = osl_util_strdup(d->comp);
	return e; 
}

/**
 * osl_doi_clone function:
 * this function builds and returns a "hard copy" (not a pointer copy) of an
 * osl_doi_t data structure. User purpose pointer will not be cloned. 
 * \param[in] doi The pointer to the doi structure to clone.
 * \return A pointer to the clone of the doi structure.
 */
osl_doi_p osl_doi_clone(osl_doi_p  doi) { 
	osl_doi_p clone, di; 
	di = clone = osl_doi_clone_e(doi); 
	while (doi != NULL) { 
		doi = doi->next; 
		di->next = osl_doi_clone_e(doi);
		di = di->next;
	}
	return clone;
}


/**
 * osl_doi_equal function:
 * this function returns true if the two doi structures are the same
 * (content-wise), false otherwise. User purpose pointer will not be 
 * compared.  
 * \param[in] d1  The first doi structure.
 * \param[in] d2  The second doi structure.
 * \return 1 if d1 and d2 are the same (content-wise), 0 otherwise.
 */
int osl_doi_equal(osl_doi_p d1, osl_doi_p d2) { 
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
 * osl_doi_length function:
 * calculates the lenght of the doi list
 * \param[in] d  The doi list
 * \return An integer containing the length of the list
 */ 
int osl_doi_length(osl_doi_p d) { 
	int len = 0; 
	while (d != NULL) { 
		len++;
		d = d->next;
	}
	return len; 
}

/** 
 * osl_doi_concat function:
 * this function will concatenate two lists of dois
 * \param[in] d1  The first doi list 
 * \param[in] d2  The second doi list
 * \return A pointer to the new list
 */
osl_doi_p osl_doi_concat(osl_doi_p d1, osl_doi_p d2) {
	osl_doi_p doit;
 
	// get the last element of d1
	for (doit = d1; doit != NULL && doit->next != NULL; doit=doit->next)
		; 
	if (doit == NULL) 
		return d2; 
	// link the end of d1 with the beginning of d2
	doit->next = d2; 
	return d1; 
}
		
/**
 * osl_doi_interface function:
 * this function creates an interface structure corresponding to the doi
 * extension and returns it).
 * \return An interface structure for the doi extension.
 */
osl_interface_p osl_doi_interface() {
  osl_interface_p interface = osl_interface_malloc();
  
  OSL_strdup(interface->URI, OSL_URI_DOI);
  interface->idump  = (osl_idump_f)osl_doi_idump;
  interface->sprint = (osl_sprint_f)osl_doi_sprint;
  interface->sread  = (osl_sread_f)osl_doi_sread;
  interface->malloc = (osl_malloc_f)osl_doi_malloc;
  interface->free   = (osl_free_f)osl_doi_free;
  interface->clone  = (osl_clone_f)osl_doi_clone;
  interface->equal  = (osl_equal_f)osl_doi_equal;

  return interface;
}

