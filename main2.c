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

/*
double** all_r(int step, int r_step, double n){
  double** ans = (double**) malloc(sizeof(double*) * r_step);
  for(int i=0; i<r_step; i++){
    ans[i] = nester(step, ((double)i)/r_step, n);
  }
  return ans;
}
*/

double** all_r(int step, int r_step, double n){
  double** ans = (double**) malloc(sizeof(double*) * r_step);
  for(int i=0; i<r_step; i++){
    ans[i] = nester(step, n, ((double)i)/r_step*4);
  }
  return ans;
}

int printer(double** data, int step, int r_step, int fore_step){
  for(int i=0;i<r_step;i++){
    double r = ((double)i)/r_step;
    for(int j=fore_step;j<step;j++){
      printf("%f ", data[i][j]);
    }
    printf("\n");
  }
  return 0;
}

int ploter(double** data, int step, int r_step, int fore_step, char* file_name, int image_size){
  FILE* fp = fopen(file_name, "wb");
  fprintf(fp, "P1\n%d %d\n", image_size, image_size);
  unsigned char image[image_size][image_size];
  memset(image, 0, image_size*image_size*sizeof(unsigned char));
  for(int i=0;i<r_step;i++){
    double r = ((double)i)/r_step;
    for(int j=fore_step;j<step;j++){
      int x = (int)(r*image_size);
      int y = (int)((1-data[i][j])*image_size);
      if((0<=x)&&(x<image_size)&&(0<=y)&&(y<image_size)){
        image[y][x] = 1;
      }
    }
  }
  for(int i = 0; i<image_size;i++){
    for(int j = 0; j<image_size;j++){
      fprintf(fp, "%d ", image[i][j]);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

int main(int argc, char** argv){
  double n;
  char filename[100];
  sscanf(argv[1], "%lf", &n);
  sprintf(filename, "result2/%s.pgm", argv[1]);
  int step = 600;
  int r_step = 1000;
  int fore_step = 200;
  double ** data = all_r(step, r_step, n);
  ploter(data, step, r_step, fore_step, filename, 1000);
  return 0;
}
