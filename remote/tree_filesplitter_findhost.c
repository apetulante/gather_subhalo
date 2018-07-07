#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void write_file(FILE *out_file, double *a, double *ID, double *desc_scale, double *descID, 
  double *num_prog, double *pid, double *Upid, double *desc_pid, double *phantom, double *SAM_mvir, 
  double *mvir, double *rvir, double *r_s, double *Vrms, double *mmp, double *last_MM_scale, 
  double *Vmax, double *x_coord, double *y_coord, double *z_coord, double *x_vel, double *y_vel, 
  double *z_vel, double *x_ang, double *y_ang, double *z_ang, double *spin, double *breadth_first_ID, 
  double *depth_first_ID, double *tree_root_ID, double *orig_halo_ID, double *snap_num, 
  double *next_coprog_dep_ID, double *last_mainleaf_dep_ID, double *tidal_F, double *tidal_ID, 
  double *r_s_klyp, double *M200b_all, double *M200b_1, double *M200b_2, double *M200b_3, 
  double *M200b_4, double *Xoff, double *Voff, double *spin_bull, double *b_to_a, double *c_to_a, 
  double *A_x, double *A_y, double *A_z, double *T_U_rat, double *M_pe, double *halmass_r, 
  double *misc_54, double *misc_55, double *misc_56, double *misc_57, double *misc_58, double *misc_59, 
  double *misc_60, double *misc_61, int tree_size, int *num_subs, int tree_num, int *subs_today, 
  int *hosts_today, double *newtree_main_ids) {
     
     int b;

     newtree_main_ids[tree_num] = ID[0];

     if (Upid[0] != -1.0) {
         subs_today[*num_subs] = tree_num;
         for (b=0; b<tree_num; b++) {
             if (newtree_main_ids[b] == Upid[0]) {
                 hosts_today[*num_subs] = b;
             }
         }
         *num_subs = *num_subs + 1;
     }

     int k;
     for (k=0; k<tree_size; k++) {
        fprintf(out_file, "%lf ", a[k]); 
        fprintf(out_file, "%lf ", ID[k]);
        fprintf(out_file, "%lf ", desc_scale[k]);
        fprintf(out_file, "%lf ", descID[k]);
        fprintf(out_file, "%lf ", num_prog[k]);
        fprintf(out_file, "%lf ", pid[k]);
        fprintf(out_file, "%lf ", Upid[k]);
        fprintf(out_file, "%lf ", desc_pid[k]);
        fprintf(out_file, "%lf ", phantom[k]);
        fprintf(out_file, "%lf ", SAM_mvir[k]);
        fprintf(out_file, "%lf ", mvir[k]);
        fprintf(out_file, "%lf ", rvir[k]);
        fprintf(out_file, "%lf ", r_s[k]);
        fprintf(out_file, "%lf ", Vrms[k]);
        fprintf(out_file, "%lf ", mmp[k]);
        fprintf(out_file, "%lf ", last_MM_scale[k]);
        fprintf(out_file, "%lf ", Vmax[k]);
        fprintf(out_file, "%lf ", x_coord[k]);
        fprintf(out_file, "%lf ", y_coord[k]);
        fprintf(out_file, "%lf ", z_coord[k]);
        fprintf(out_file, "%lf ", x_vel[k]);
        fprintf(out_file, "%lf ", y_vel[k]);
        fprintf(out_file, "%lf ", z_vel[k]);
        fprintf(out_file, "%lf ", x_ang[k]);
        fprintf(out_file, "%lf ", y_ang[k]);
        fprintf(out_file, "%lf ", z_ang[k]);
        fprintf(out_file, "%lf ", spin[k]);
        fprintf(out_file, "%lf ", breadth_first_ID[k]);
        fprintf(out_file, "%lf ", depth_first_ID[k]);
        fprintf(out_file, "%lf ", tree_root_ID[k]);
        fprintf(out_file, "%lf ", orig_halo_ID[k]);
        fprintf(out_file, "%lf ", snap_num[k]);
        fprintf(out_file, "%lf ", next_coprog_dep_ID[k]);
        fprintf(out_file, "%lf ", last_mainleaf_dep_ID[k]);
        fprintf(out_file, "%lf ", tidal_F[k]);
        fprintf(out_file, "%lf ", tidal_ID[k]);
        fprintf(out_file, "%lf ", r_s_klyp[k]);
        fprintf(out_file, "%lf ", M200b_all[k]);
        fprintf(out_file, "%lf ", M200b_1[k]);
        fprintf(out_file, "%lf ", M200b_2[k]);
        fprintf(out_file, "%lf ", M200b_3[k]);
        fprintf(out_file, "%lf ", M200b_4[k]);
        fprintf(out_file, "%lf ", Xoff[k]);
        fprintf(out_file, "%lf ", Voff[k]);
        fprintf(out_file, "%lf ", spin_bull[k]);
        fprintf(out_file, "%lf ", b_to_a[k]);
        fprintf(out_file, "%lf ", c_to_a[k]);
        fprintf(out_file, "%lf ", A_x[k]);
        fprintf(out_file, "%lf ", A_y[k]);
        fprintf(out_file, "%lf ", A_z[k]);
        fprintf(out_file, "%lf ", T_U_rat[k]);
        fprintf(out_file, "%lf ", M_pe[k]);
        fprintf(out_file, "%lf ", misc_54[k]);
        fprintf(out_file, "%lf ", misc_55[k]);
        fprintf(out_file, "%lf ", misc_56[k]);
        fprintf(out_file, "%lf ", misc_57[k]);
        fprintf(out_file, "%lf ", misc_58[k]);
        fprintf(out_file, "%lf ", misc_59[k]);
        fprintf(out_file, "%lf ", misc_60[k]);
        fprintf(out_file, "%lf ", misc_61[k]);
        fprintf(out_file, "\n");
     }
}

int main(int argc, char ** argv)
{

   // check command line arguments
   if ( argc != 7 ) {
      printf("This program splits tree files into individuals, for n lines of halo data for one host\n");
      printf("Usage: ./tree_filesplitter filename (tree_treenum1_treenum2_treenum3.dat), # of lines, treenum1, treenum2, treenum3\n");
      exit(-1);
   }

   //parse input arguments
   FILE *tree_data = fopen(argv[1],"r");
   int num_lines = atoi(argv[2]);
   int file_ident_1 = atoi(argv[3]);
   int file_ident_2 = atoi(argv[4]);
   int file_ident_3 = atoi(argv[5]);
   double host_today_ID = atof(argv[6]);
   //printf("The ID we want is %lf\n", host_today_ID);
   
   int num_halos = 150000;
   //allocate arrays for all of the different parameters
   double *a = malloc(num_halos*sizeof(double));
   double *ID = malloc(num_halos*sizeof(double));
   double *desc_scale = malloc(num_halos*sizeof(double));
   double *descID = malloc(num_halos*sizeof(double));
   double *num_prog = malloc(num_halos*sizeof(double));
   double *pid = malloc(num_halos*sizeof(double));
   double *Upid = malloc(num_halos*sizeof(double));
   double *desc_pid = malloc(num_halos*sizeof(double));
   double *phantom = malloc(num_halos*sizeof(double));
   double *SAM_mvir = malloc(num_halos*sizeof(double));
   double *mvir = malloc(num_halos*sizeof(double));
   double *rvir = malloc(num_halos*sizeof(double));
   double *r_s = malloc(num_halos*sizeof(double));
   double *Vrms = malloc(num_halos*sizeof(double));
   double *mmp = malloc(num_halos*sizeof(double));
   double *last_MM_scale = malloc(num_halos*sizeof(double));
   double *Vmax = malloc(num_halos*sizeof(double));
   double *x_coord = malloc(num_halos*sizeof(double));
   double *y_coord = malloc(num_halos*sizeof(double));
   double *z_coord = malloc(num_halos*sizeof(double));
   double *x_vel = malloc(num_halos*sizeof(double));
   double *y_vel = malloc(num_halos*sizeof(double));
   double *z_vel = malloc(num_halos*sizeof(double));
   double *x_ang = malloc(num_halos*sizeof(double));
   double *y_ang = malloc(num_halos*sizeof(double));
   double *z_ang = malloc(num_halos*sizeof(double));
   double *spin = malloc(num_halos*sizeof(double));
   double *breadth_first_ID = malloc(num_halos*sizeof(double));
   double *depth_first_ID = malloc(num_halos*sizeof(double));
   double *tree_root_ID = malloc(num_halos*sizeof(double));
   double *orig_halo_ID = malloc(num_halos*sizeof(double));
   double *snap_num = malloc(num_halos*sizeof(double));
   double *next_coprog_dep_ID = malloc(num_halos*sizeof(double));
   double *last_mainleaf_dep_ID = malloc(num_halos*sizeof(double));
   double *tidal_F = malloc(num_halos*sizeof(double));
   double *tidal_ID = malloc(num_halos*sizeof(double));
   double *r_s_klyp = malloc(num_halos*sizeof(double));
   double *M200b_all = malloc(num_halos*sizeof(double));
   double *M200b_1= malloc(num_halos*sizeof(double));
   double *M200b_2 = malloc(num_halos*sizeof(double));
   double *M200b_3= malloc(num_halos*sizeof(double));
   double *M200b_4 = malloc(num_halos*sizeof(double));
   double *Xoff = malloc(num_halos*sizeof(double));
   double *Voff = malloc(num_halos*sizeof(double));
   double *spin_bull = malloc(num_halos*sizeof(double));
   double *b_to_a = malloc(num_halos*sizeof(double));
   double *c_to_a = malloc(num_halos*sizeof(double));
   double *A_x = malloc(num_halos*sizeof(double));
   double *A_y = malloc(num_halos*sizeof(double));
   double *A_z = malloc(num_halos*sizeof(double));
   double *T_U_rat = malloc(num_halos*sizeof(double));
   double *M_pe = malloc(num_halos*sizeof(double));
   double *halfmass_r = malloc(num_halos*sizeof(double));
   double *misc_54 = malloc(num_halos*sizeof(double));
   double *misc_55 = malloc(num_halos*sizeof(double));
   double *misc_56 = malloc(num_halos*sizeof(double));
   double *misc_57 = malloc(num_halos*sizeof(double));
   double *misc_58 = malloc(num_halos*sizeof(double));
   double *misc_59 = malloc(num_halos*sizeof(double));
   double *misc_60 = malloc(num_halos*sizeof(double));
   double *misc_61 = malloc(num_halos*sizeof(double));

   double *newtree_main_ids = malloc(num_halos*sizeof(double));
   int *subs_today = malloc(num_halos*sizeof(int));
   int *hosts_today = malloc(num_halos*sizeof(int));

  int i = 0;
  int j;
  double current_scale;
  int tree_num = 0;
  int tree_size = 0;
  int num_subs = 0;
  int print_next = 0;
  for (j=0; j<num_lines; j++) {
        if (i > num_halos) {
            i++;
            a = realloc(a, i*sizeof(double));
            ID = realloc(ID, i*sizeof(double));
            desc_scale = realloc(desc_scale, i*sizeof(double));
            descID = realloc(descID, i*sizeof(double));
            num_prog = realloc(num_prog, i*sizeof(double));
            pid = realloc(pid, i*sizeof(double));
            Upid = realloc(Upid, i*sizeof(double));
            desc_pid = realloc(desc_pid, i*sizeof(double));
            phantom = realloc(phantom, i*sizeof(double));
            SAM_mvir = realloc(SAM_mvir, i*sizeof(double));
            mvir = realloc(mvir, i*sizeof(double));
            rvir = realloc(rvir, i*sizeof(double));
            r_s = realloc(r_s, i*sizeof(double));
            Vrms = realloc(Vrms, i*sizeof(double));
            mmp = realloc(mmp, i*sizeof(double));
            last_MM_scale = realloc(last_MM_scale, i*sizeof(double));
            Vmax = realloc(Vmax, i*sizeof(double));
            x_coord = realloc(x_coord, i*sizeof(double));
            y_coord = realloc(y_coord, i*sizeof(double));
            z_coord = realloc(z_coord, i*sizeof(double));
            x_vel = realloc(x_vel, i*sizeof(double));
            y_vel = realloc(y_vel, i*sizeof(double));
            z_vel = realloc(z_vel, i*sizeof(double));
            x_ang = realloc(x_ang, i*sizeof(double));
            y_ang = realloc(y_ang, i*sizeof(double));
            z_ang = realloc(z_ang, i*sizeof(double));
            spin = realloc(spin, i*sizeof(double));
            breadth_first_ID = realloc(breadth_first_ID, i*sizeof(double));
            depth_first_ID = realloc(depth_first_ID, i*sizeof(double));
            tree_root_ID = realloc(tree_root_ID, i*sizeof(double));
            orig_halo_ID = realloc(orig_halo_ID, i*sizeof(double));
            snap_num = realloc(snap_num, i*sizeof(double));
            next_coprog_dep_ID = realloc(next_coprog_dep_ID, i*sizeof(double));
            last_mainleaf_dep_ID = realloc(last_mainleaf_dep_ID, i*sizeof(double));
            tidal_F = realloc(tidal_F, i*sizeof(double));
            tidal_ID = realloc(tidal_ID, i*sizeof(double));
            r_s_klyp = realloc(r_s_klyp, i*sizeof(double));
            M200b_all = realloc(M200b_all, i*sizeof(double));
            M200b_1= realloc(M200b_1, i*sizeof(double));
            M200b_2 = realloc(M200b_2, i*sizeof(double));
            M200b_3= realloc(M200b_3, i*sizeof(double));
            M200b_4 = realloc(M200b_4, i*sizeof(double));
            Xoff = realloc(Xoff, i*sizeof(double));
            Voff = realloc(Voff, i*sizeof(double));
            spin_bull = realloc(spin_bull, i*sizeof(double));
            b_to_a = realloc(b_to_a, i*sizeof(double));
            c_to_a = realloc(c_to_a, i*sizeof(double));
            A_x = realloc(A_x, i*sizeof(double));
            A_y = realloc(A_y, i*sizeof(double));
            A_z = realloc(A_z, i*sizeof(double));
            T_U_rat = realloc(T_U_rat, i*sizeof(double));
            M_pe = realloc(M_pe, i*sizeof(double));
            halfmass_r = realloc(halfmass_r, i*sizeof(double));
            misc_54 = realloc(misc_54, i*sizeof(double));
            misc_55 = realloc(misc_55, i*sizeof(double));
            misc_56 = realloc(misc_56, i*sizeof(double));
            misc_57 = realloc(misc_57, i*sizeof(double));
            misc_58 = realloc(misc_58, i*sizeof(double));
            misc_59 = realloc(misc_59, i*sizeof(double));
            misc_60 = realloc(misc_60, i*sizeof(double));
            misc_61 = realloc(misc_61, i*sizeof(double));
            i--;
        }
        fscanf(tree_data, "%lf", &a[i]);
        current_scale = a[i];
	// current_ID = ID[i];
        // printf("Working on line: %d, scale is: %lf\n", j, current_scale);
        if (current_scale == 1.0000) {
           if (j > 0) {
              tree_num++;
              if (print_next == 1) {
              FILE *out_file;
              char *filename = malloc(30*sizeof(char));
              snprintf(filename, sizeof(char) * 30, "tree_%d_%d_%d_MainHalo.txt",file_ident_1,file_ident_2,file_ident_3); 
              out_file = fopen(filename, "w");
              write_file(out_file, a, ID, desc_scale, descID, num_prog, pid, Upid, desc_pid, phantom, SAM_mvir, 
                mvir, rvir, r_s, Vrms, mmp, last_MM_scale, Vmax, x_coord, y_coord, z_coord, x_vel, y_vel, z_vel, 
                x_ang, y_ang, z_ang, spin, breadth_first_ID, depth_first_ID, tree_root_ID, orig_halo_ID, snap_num, 
                next_coprog_dep_ID, last_mainleaf_dep_ID, tidal_F, tidal_ID, r_s_klyp, M200b_all, M200b_1, M200b_2, 
                M200b_3, M200b_4, Xoff, Voff, spin_bull, b_to_a, c_to_a, A_x, A_y, A_z, T_U_rat, M_pe, halfmass_r, 
                misc_54, misc_55, misc_56, misc_57, misc_58, misc_59, misc_60, misc_61, tree_size, &num_subs,
                tree_num, subs_today, hosts_today, newtree_main_ids);
              fclose(out_file);
	      break;
	      free(filename);
	      }
              tree_size = 0;
              i = 0;
	      }
        }
	fscanf(tree_data, "%lf", &ID[i]);
	//printf("This is: %lf, want: %lf\n", ID[i], desired_ID);
	if (ID[i] == host_today_ID) {
	    //printf("This is: %lf, want: %lf\n", ID[i], host_today_ID);
	    print_next=1;
	}
        fscanf(tree_data, "%lf", &desc_scale[i]);
        fscanf(tree_data, "%lf", &descID[i]);
        fscanf(tree_data, "%lf", &num_prog[i]);
        fscanf(tree_data, "%lf", &pid[i]);
        fscanf(tree_data, "%lf", &Upid[i]);
        fscanf(tree_data, "%lf", &desc_pid[i]);
        fscanf(tree_data, "%lf", &phantom[i]);
        fscanf(tree_data, "%lf", &SAM_mvir[i]);
        fscanf(tree_data, "%lf", &mvir[i]);
        fscanf(tree_data, "%lf", &rvir[i]);
        fscanf(tree_data, "%lf", &r_s[i]);
        fscanf(tree_data, "%lf", &Vrms[i]);
        fscanf(tree_data, "%lf", &mmp[i]);
        fscanf(tree_data, "%lf", &last_MM_scale[i]);
        fscanf(tree_data, "%lf", &Vmax[i]);
        fscanf(tree_data, "%lf", &x_coord[i]);
        fscanf(tree_data, "%lf", &y_coord[i]);
        fscanf(tree_data, "%lf", &z_coord[i]);
        fscanf(tree_data, "%lf", &x_vel[i]);
        fscanf(tree_data, "%lf", &y_vel[i]);
        fscanf(tree_data, "%lf", &z_vel[i]);
        fscanf(tree_data, "%lf", &x_ang[i]);
        fscanf(tree_data, "%lf", &y_ang[i]);
        fscanf(tree_data, "%lf", &z_ang[i]);
        fscanf(tree_data, "%lf", &spin[i]);
        fscanf(tree_data, "%lf", &breadth_first_ID[i]);
        fscanf(tree_data, "%lf", &depth_first_ID[i]);
        fscanf(tree_data, "%lf", &tree_root_ID[i]);
        fscanf(tree_data, "%lf", &orig_halo_ID[i]);
        fscanf(tree_data, "%lf", &snap_num[i]);
        fscanf(tree_data, "%lf", &next_coprog_dep_ID[i]);
        fscanf(tree_data, "%lf", &last_mainleaf_dep_ID[i]);
        fscanf(tree_data, "%lf", &tidal_F[i]);
        fscanf(tree_data, "%lf", &tidal_ID[i]);
        fscanf(tree_data, "%lf", &r_s_klyp[i]);
        fscanf(tree_data, "%lf", &M200b_all[i]);
        fscanf(tree_data, "%lf", &M200b_1[i]);
        fscanf(tree_data, "%lf", &M200b_2[i]);
        fscanf(tree_data, "%lf", &M200b_3[i]);
        fscanf(tree_data, "%lf", &M200b_4[i]);
        fscanf(tree_data, "%lf", &Xoff[i]);
        fscanf(tree_data, "%lf", &Voff[i]);
        fscanf(tree_data, "%lf", &spin_bull[i]);
        fscanf(tree_data, "%lf", &b_to_a[i]);
        fscanf(tree_data, "%lf", &c_to_a[i]);
        fscanf(tree_data, "%lf", &A_x[i]);
        fscanf(tree_data, "%lf", &A_y[i]);
        fscanf(tree_data, "%lf", &A_z[i]);
        fscanf(tree_data, "%lf", &T_U_rat[i]);
        fscanf(tree_data, "%lf", &M_pe[i]);
        fscanf(tree_data, "%lf", &misc_54[i]);
        fscanf(tree_data, "%lf", &misc_55[i]);
        fscanf(tree_data, "%lf", &misc_56[i]);
        fscanf(tree_data, "%lf", &misc_57[i]);
        fscanf(tree_data, "%lf", &misc_58[i]);
        fscanf(tree_data, "%lf", &misc_59[i]);
        fscanf(tree_data, "%lf", &misc_60[i]);
        fscanf(tree_data, "%lf", &misc_61[i]);
        i++;
        tree_size++;
   }

   tree_num++;

   fclose(tree_data); 
   free(subs_today);
   free(hosts_today);

   free(a);
   free(ID);
   free(desc_scale);
   free(descID);
   free(num_prog);
   free(pid);
   free(Upid);
   free(desc_pid);
   free(phantom);
   free(SAM_mvir);
   free(mvir);
   free(rvir);
   free(r_s);
   free(Vrms);
   free(mmp);
   free(last_MM_scale);
   free(Vmax);
   free(x_coord);
   free(y_coord);
   free(z_coord);
   free(x_vel);
   free(y_vel);
   free(z_vel);
   free(x_ang);
   free(y_ang);
   free(z_ang);
   free(spin);
   free(breadth_first_ID);
   free(depth_first_ID);
   free(tree_root_ID);
   free(orig_halo_ID);
   free(snap_num);
   free(next_coprog_dep_ID);
   free(last_mainleaf_dep_ID);
   free(tidal_F);
   free(tidal_ID);
   free(r_s_klyp);
   free(M200b_all);
   free(M200b_1);
   free(M200b_2);
   free(M200b_3);
   free(M200b_4);
   free(Xoff);
   free(Voff);
   free(spin_bull);
   free(b_to_a);
   free(c_to_a);
   free(A_x);
   free(A_y);
   free(A_z);
   free(T_U_rat);
   free(M_pe);
   free(halfmass_r);
   free(misc_54);
   free(misc_55);
   free(misc_56);
   free(misc_57);
   free(misc_58);
   free(misc_59);
   free(misc_60);
   free(misc_61);   

   return 0;     
}
