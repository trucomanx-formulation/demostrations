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
	double Hjoint;
	double Hjoint2;
	double Hcond;
	double Hcond2;
	double rho;
	double rho0;
	int i,N;

	PdsVector  *Ps=NULL;
	PdsBVector *B =NULL;
	double p0=0.15;
	double p,S,h;
	int M=3;
	PdsBaNatural n;

	Ps=pds_vector_new(M);
	B =pds_bvector_new(M);
	
	for(i=0;i<M;i++)
	{
		pds_vector_set_value (Ps, (PdsRaNatural)i,p0);//+i/(4.0*M));
	}
	printf("\nPS:\n");
	pds_vector_printf(Ps);
	printf("\n");

	////////////////////////////////////////////////////////////////////////////
	pds_symetric_entropy_u0_omega_bsc_model (p0,M,&Hcond);
	printf("H(U0|Omega) :\t%f\n",Hcond);
	////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////
	Hcond=0;
	pds_entropy_u0_omega_bsc_model(Ps,0.5,&Hcond);
	printf("H(U0|Omega) :\t%f\n",Hcond);
	////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////
	N=(int)pow(2,M);
	S=0;
	for(i=0;i<N;i++)
	{
		pds_bvector_set_natural(B,i);		//pds_bvector_printf(B);
		pds_bvector_weight_bvector(B,&n);	//printf("%d\n",n);
	
		p=0;
		probabilidad(B,Ps,&p);				//printf("%f\n\n",p);
		h=pds_hb(p);						//printf("%f\n\n",h);

		S=S+pow(-1,n+1)*h;
	}
	printf("H(U0|Omega) :\t%f\n",S);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	Hcond=0;
	entropia_metodo1(Ps,&Hcond);
	printf("H(U0|Omega) :\t%f\n",Hcond);
	////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////
	Hcond=0;
	pds_joint_entropy_bsc_model(Ps,0.5,&Hcond);
	printf("H(Omega) :\t%f\n",Hcond);
	////////////////////////////////////////////////////////////////////////////

	printf("\n");

	return EXIT_SUCCESS;
}
