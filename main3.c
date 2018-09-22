#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

double to_nest(double x, double r, double n){
  return r * ( 1. - pow( fabs(2*x-1), n) );
}

double* nester(int step, double r, double n){
  double* ans = (double*) malloc(sizeof(double) * step);
  ans[0] = 0.5;
  for(int i=1; i<step; i++){
    ans[i] = to_nest(ans[i-1], r, n);
  }
  return ans;
}

double** all_r(int step, int n_step, double r, double max_n){
  double** ans = (double**) malloc(sizeof(double*) * n_step);
  for(int i=0; i<n_step; i++){
    ans[i] = nester(step, r, ((double)i)/n_step*max_n);
  }
  return ans;
}

int ploter(double** data, int step, int n_step, int fore_step, char* file_name, int image_size){
  FILE* fp = fopen(file_name, "wb");
  fprintf(fp, "P1\n%d %d\n" ,n_step, image_size);
  //unsigned char image[image_size][n_step];
  unsigned char (*image)[n_step] = (unsigned char (*)[n_step]) malloc(sizeof(unsigned char)*n_step*image_size);
  memset(image, 0, image_size*n_step*sizeof(unsigned char));
  for(int i=0;i<n_step;i++){
    for(int j=fore_step;j<step;j++){
      int x = i;
      int y = (int)((1-data[i][j])*image_size);
      if((0<=y)&&(y<image_size)){
        image[y][x] = 1;
      }
    }
  }
  for(int i = 0; i<image_size;i++){
    for(int j = 0; j<n_step;j++){
      fprintf(fp, "%d ", image[i][j]);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

int main(int argc, char** argv){
  double r=0.998;
  char filename[]="long.pgm";
  double max_n=20;
  int step = 2000;
  int n_step = max_n*1000;
  int fore_step = 200;
  double ** data = all_r(step, n_step, r, max_n);
  /*for(int i=0;i<n_step;i++){
    for(int j=step-10;j<step;j++)
      printf("%f ", data[i][j]);
    printf("\n");
  }*/
  ploter(data, step, n_step, fore_step, filename, 1000);
  return 0;
}
