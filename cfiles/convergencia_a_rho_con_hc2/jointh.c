/*
 * Archivo_c.c
 * 
 * Copyright 2011 Fernando Pujaico Rivera <fernando.pujaico.rivera@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

//gcc jointh.c -o jointh -lpdsit -lpdsra -lpdsba -lpdsm -lm
#include <stdio.h>
#include <stdlib.h>
#include <pds/pdsit.h>
#include <pds/pdsra.h>
#include <pds/pdsmath.h>
#include <math.h>

#include "extras.h"

int main(int argc, char** argv)
{
	double Hcond;
	double rho;
	int i;

	PdsVector  *Ps=NULL;

	double p0=0.05;
	int M=20;

	Ps=pds_vector_new(M);
	
	for(i=0;i<M;i++)
	{
		pds_vector_set_value (Ps, (PdsRaNatural)i,p0+i/(4.0*M));
	}
	printf("\nPS:\n");
	pds_vector_printf(Ps);
	printf("\n");


	////////////////////////////////////////////////////////////////////////////
	Hcond=0;
	pds_entropy_u0_omega_bsc_model(Ps,0.5,&Hcond);
	printf("H(U0|Omega)        : %e\n",Hcond);
	////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////
    pds_inv_symetric_entropy_u0_omega_bsc_model(Hcond,M,&rho);
    pds_symetric_entropy_u0_omega_bsc_model(rho,M,&Hcond);
	printf("h_C(%e,M)~ %e\n",rho,Hcond);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	rho=0;
    printf("\n");
	entropia_metodo1(Ps,&rho);
    pds_symetric_entropy_u0_omega_bsc_model(rho,M,&Hcond);
	printf("h_C(%e,M)~ %e [metodo]\n",rho,Hcond);
	////////////////////////////////////////////////////////////////////////////

	printf("\n");

	return EXIT_SUCCESS;
}
