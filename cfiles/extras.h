int probabilidad(const PdsBVector *B,const PdsVector *V, double *val)
{
	int i,N;
	PdsBaBit m;

	if(B==NULL)	return FALSE;
	if(V==NULL)	return FALSE;

	if(B->Nel!=V->Nel)	return FALSE;

	N=V->Nel;
	*val=0;	

	for(i=0;i<N;i++)
	{
		pds_bvector_get_bit (B,i,&m);
		if(m==1)
		{
			*val=V->V[i]+(*val)-2*(*val)*V->V[i];
		}
	}
	return TRUE;
}


int entropia_metodo1(const PdsVector *V, double *val)
{
	double h0,p0;
	int i;

	h0=pds_hb(V->V[0]);
	p0=V->V[0];

	for(i=1;i<V->Nel;i++)
	{
		h0=pds_hb(V->V[i])+h0-pds_hb(V->V[i]+p0-2*p0*V->V[i]);
		p0=pds_hbinv(h0);
	}
	*val=h0;
}
