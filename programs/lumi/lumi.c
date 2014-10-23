#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(int argc, char** argv){
  int  i,j;
  int  found,notfound;
  int verb;
  int cut;
  char* verbmode;
  char* lumilist;
  char* runlist;
  char* runnew;
  char slumical[10];
  char slumispc[10];
  char srun[15];
  float lumical;
  float lumicalsum;
  float lumispc;
  float lumispcsum;
  float lumidiff;
  char srunrun[15];
  int  run;
  int  runrun;
  FILE* file_lumilist;
  FILE* file_runlist;
  FILE* file_runnew;
  char  file_lumi_arr[1001];
  char  file_run_arr[1001];
  char  file_tmp_arr[1003];
  int   maximumrun;
  float maximumlumical;
  float maximumlumispc;
  char* pos;
/*   long int  cutpos; */
  
  lumicalsum=0;
  lumispcsum=0;
  verb=1;
  cut=0;
  if (argc<2) {
    printhelp();
    exit(0);
  }
  if (argc>=2){
    verbmode=argv[1];
    if ((strcmp(verbmode, "-h")==0 ||strcmp(verbmode, "--help")==0) || !(argc >= 3)) {
      printhelp();
      exit(0);
    }
  }
  if (argc ==3) {
    lumilist=argv[1];
    runlist=argv[2];
  }
  if (argc == 4 ||argc == 5 ) {
    verbmode=argv[1];
    if (strcmp(verbmode, "-v")==0 ||strcmp(verbmode, "--verbose")==0)
      verb=1;
    else if(strcmp(verbmode, "-q")==0 ||strcmp(verbmode, "--quiet")==0)
      verb=0;
    if(strcmp(verbmode, "-c")==0 ||strcmp(verbmode, "--cut")==0 ) {
      cut=1;
    }
    lumilist=argv[2];
    runlist=argv[3];
/*     strcpy(runnew,"x"); */
/*     strcat(runnew, runlist); */
/*     strcat(runnew, ".new"); */
  }
  if (argc == 4 && cut==1) {
    printhelp();
    exit(0);
  }
  else if (argc==5)
    runnew=argv[4];    
  if (verb) printf("verbose mode\n");
  if (verb) printf("lumilist: %s\n", lumilist);
  if (verb) printf("runlist: %s\n", runlist);
  if (cut) {
    /*     runnew=strcat(runlist, ".new"); */
    /*     sprintf(runnew,"card.new"); */
    printf("modified runlist: %s\n", runnew);  
    file_runnew = fopen(runnew, "w");
    if (file_runnew==NULL) {
      printf("could not create file!\n");    
      exit(0);
    }
  }
  file_runlist = fopen(runlist, "r");
  file_lumilist = fopen(lumilist, "r");
  if (file_runlist==NULL || file_lumilist==NULL) {
    printf("file not found!\n");    
    exit(0);
  }
  if (verb) printf("\n");
  if (verb) printf("--------------------------\n");
  while (fgets(file_run_arr, 1000, file_runlist)) {
    sscanf(file_run_arr,"%12s", &srunrun);
    found=1;
    if (strcmp(srunrun, "ZEUSIO-INFI")==0){
      pos =strstr(file_run_arr, "/r0");
      runrun=atoi(pos+2);
      /*     sscanf(file_arr,"%6s", &srunrun); */
      /*       sscanf(file_arr,"%*11s %*20s %6s", &srunrun); */
      /*       runrun=atoi(srunrun); */
      if (runrun!=0) {
	if (verb) printf("run in runlist=%d\t",runrun);
	found=0;
	rewind(file_lumilist); 
	while (fgets(file_lumi_arr, 1000, file_lumilist)){
	  sscanf(file_lumi_arr,"%*1s %6s", &srun);
	  sscanf(file_lumi_arr,"%*1s %*5s %*10s %8s", &slumical);
	  sscanf(file_lumi_arr,"%*1s %*5s %*10s %*8s %8s", &slumispc);
	  lumical=atof(slumical);
	  lumispc=atof(slumispc);
	  run=atoi(srun);
	  if (run==runrun) {
	    if (verb) printf("run=%5d  lumical=%5.2f lumispc=%5.2f",run,lumical,lumispc);
	    found=1;
	    if (lumical==0 || lumispc==0) {
	      lumical=(lumical>lumispc)?lumical:lumispc;
	      lumispc=lumical;
	    }
	    lumicalsum+=lumical;
	    lumispcsum+=lumispc;
	    if (maximumlumical<lumical){
	      maximumlumical=lumical;
	      maximumrun=run;
	      maximumlumispc=lumispc;
	    }
	    /* 	printf("\t lumical so far=%f",lumicalsum); */
	    if (verb) printf("\n");
	    break;
	  }
	}
      }
    }
    if (!found) {
      printf("run %d not found!!!\n", runrun);
      if (cut) {
	strcpy(file_tmp_arr, "C Not a validrun ");
	strcat(file_tmp_arr, &file_run_arr[0]);
	fprintf(file_runnew,file_tmp_arr);
      }  
    }
    else if (cut){
      fprintf(file_runnew,file_run_arr);      
    }
  }
  fclose(file_lumilist);
  fclose(file_runlist);
  if (cut) {
    fclose(file_runnew);
  }
  printf("--------------------------\n");
  printf("Lumi:\n");
  printf("CAL-biased=%6.2f\t",lumicalsum);
  printf("SPC-biased=%6.2f\t",lumispcsum);
  lumidiff=200*fabs(lumicalsum-lumispcsum)/(lumicalsum+lumispc);
  printf("difference: %4.2f %\n",lumidiff);
  if (verb) printf("\n");
  if (verb) printf("And the winning run was: %d (CAL:%-5.2f nb^-1  SPC:%-5.2f nb^-1)\n",maximumrun,maximumlumical,maximumlumispc);
}

int printhelp(){
  printf("Usage: lumi.exe [OPTION] lumi_filename runlist_filename [runlist_cutfile]\n");
  printf("Options: \n");
  printf("  -v, --verbose                some output/default\n");
  printf("  -q, --quiet                  less output\n");
  printf("  -c, --cut                    comment out from runlist file all events\n");
  printf("                               that are not found in lumi file\n");
  printf("                               write new runlist to runlist_cutfile\n");
  printf("  -h, --help                   gives this help\n");
}
