

int entropia_metodo1(const PdsVector *V, double *rho)
{
	double h0,p0;
	int j,i,N=V->Nel;

    PdsVector *v=pds_vector_new_vector(V);
    //pds_vector_printf(v);
    for(j=0;j<(2*log2(N));j++)
    {
	    for(i=0;i<round(N/2.0);i++)
	    {   //printf("[%d,%d-%d]\n",i,N,i);
		    h0=pds_hc2_func(v->V[i],v->V[N-i-1]);
		    p0=pds_hc2s_invfunc(h0,1.0/1000000);
            v->V[i]=p0;
            v->V[N-i-1]=p0;
	    }
        //printf("RAW: ");pds_vector_printf(v);
        pds_vector_asc_order(v);
        //printf("ORD: ");pds_vector_printf(v);
        //printf("\n");
    }
    //pds_vector_printf(v);
    PdsRaReal m;
    pds_vector_mean_vector (v,&m);
	*rho=m;
    printf("E[rho]=%e\t",m);
    pds_vector_std_vector (v,&m);
    printf("Sigma[rho]=%e\n",m);
    pds_vector_free(v);
    return TRUE;
}
