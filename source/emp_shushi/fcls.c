#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "set.h"
#include "glva.h"


void alfclose(void){
	int i, is;
	
	fclose(ifp_econ);
	
	for(i=1; i<=4; i++){
		fclose(ifp10_usys[i]);
	}
	
	fclose(ifp_kyos);
	
	fclose(ifp27_tuma);
	
	fclose(ifp_nofu);
	
	fclose(ifp_kaiteb);
	
	if(Cutrfile1[0]=='0'){
		fclose(ifp_kaitea);
	}else if(Cutrfile1[0]=='1'){
		fclose(ifp_kokukaite);
	}
	
	if(Fpset!=9) fclose(ifp_wakum);
	
	if(Cutrfile1[0]=='1' && Fpset == 8){
		fclose(ifp_bas_cuta);
	}else if(Fpset == 9){
		fclose(ifp_asys_cuta);
		fclose(ifp_asys_cutb);
	}
	
	if(Fpset!=9){
		fclose(ofp_cuta);
		fclose(ofp_cutb);
		
		if(Touitu>=1){
		   fclose(ofp_cuta2);
		   fclose(ofp_cutb2);
		}
	}
	
	is=0;
	
	if(Saimu==0 || Saimu==1 || Saimu==2){
		for(i=is; i<=4; i++){
			fclose(ofp01_shushi[i]);
			if(Nenbeex2==1) fclose(ofp90_nenbe[i]);
		}
	}
	
	
	fclose(ofp_Tokutyo);
	
	fclose(ifp_Touitu);

}

