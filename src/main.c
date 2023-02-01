#include "myBmpGris.c"
#include<math.h>
#include<time.h>
#define IMAGE1 "img/1carre_rond.bmp"    
#define IMAGE2 "img/2carre_rond.bmp"


/* CREER UNE STRUCTURE DE MATRICE QUI CONTIENT */
/* LE CONTENUE EST LES DIMENSTIONDE LA MATRICE */

typedef struct doubleMat_s doubleMat;
struct doubleMat_s {
  unsigned int dimX;
  unsigned int dimY;
  double** Mat;
};

/* Si on souhaite réitialiser la matrice a 0 */
  void initMat(doubleMat mat){
    unsigned int i,j;
    for(i=0;i<mat.dimX;i++){
      for(j=0;j<mat.dimY;j++){
        mat.Mat[i][j]=0;
      }
    }
  }

doubleMat createMat(int dimX,int dimY){
      doubleMat mat ;
      unsigned int i;
      mat.dimX = dimX;
      mat.dimY = dimY;
      mat.Mat  = malloc(dimX*sizeof(double*));
      for(i=0;i<dimX;i++){
        mat.Mat[i] = calloc(dimY,sizeof(double));
      }
      initMat(mat);
      return mat;
}

 void freeDoubleMat(doubleMat* mat) {
     if( mat->Mat != NULL){ 
         unsigned int i;
         for(i=0;i<mat->dimX;i++){
            free(mat->Mat[i]);
         }
         free(mat->Mat);
      }
    if(mat->Mat == NULL )printf("hellofree\n");// ENLEVE
    mat->Mat = NULL;
    if(mat->Mat == NULL )printf("hellofree\n");// ENLEVE
 }
    
   double mPixel(doubleMat mat,int i, int j){ 
   //moyenne des 8 pixels entourant le pixel (i,j)
   double moyenne=0;
    int n,m,nb=0;
    for(n=-1;n<=1;n++){
      for(m=-1;m<=1;m++){   
        if( (i+n >= 0) && (i+n < mat.dimX ) ){
          if( (j+m >= 0) && (j+m < mat.dimY ) ){
            moyenne += mat.Mat[i+n][j+m];
            nb++;
          }
        }  
      }
    }
   return  (moyenne - mat.Mat[i][j])/(nb-1);
   }

  double norm(doubleMat mat){
    double res = 0;
    unsigned int i,j; 
    for(i=0;i<mat.dimX;i++){
       for(j=0;j<mat.dimY;j++){
        res += mat.Mat[i][j]*mat.Mat[i][j];
       }
     }
     return sqrt(res);
  }
  

  void copyMat(doubleMat matOrig, doubleMat* matDest){
    int i, j;
    int dimXO = matOrig.dimX;
    int dimYO = matOrig.dimY;
    int dimXC = matDest->dimX;
    int dimYC = matDest->dimY;
    
    if( (dimXO == dimXC) && (dimYO == dimYC) ) {
      for(i=0;i<dimXC;i++){
        for(j=0;j<dimYC;j++){
          matDest->Mat[i][j] = matOrig.Mat[i][j];
        }
      }
    }
  }

// void initRandMat(doubleMat mat){
//     int i,j;
//     for(i=0;i<mat.dimX;i++){
//       for(j=0;j<mat.dimY;j++){
//         mat.Mat[i][j] = (rand()%1000)/100;
//       }
//     }
//   }
  
  void  writeFILE(char* name,doubleMat* mat){
    FILE* fw = fopen(name,"w"); 
    int i,j;
    if(fw != NULL){
      fprintf(fw,"%d %d\n",mat->dimX,mat->dimY);
      for( i = 0 ; i < mat->dimX ; i++ ){
        for( j = 0 ; j < mat->dimY ; j++){
          fprintf(fw,"%.10f,",mat->Mat[i][j]); 
        }
     fprintf(fw,"\n"); 
      }
    fclose(fw);  
    }  
  }

  void writeInBmp(doubleMat* mat,char* name){
    BmpImg BmpMat = createBmpImg(name,mat->dimX,mat->dimY);
    int i,j;
    for(i=0;i<mat->dimX;i++){
      for(j=0;j<mat->dimY;j++){
        BmpMat.img[i][j] = mat->Mat[i][j];
      }
    }
    writeBmpImage(name,&BmpMat);
  }

  double minMat(doubleMat mat){
    double min =  mat.Mat[0][0];
    for(int i=0;i<mat.dimX;i++){
      for(int j=0;j<mat.dimY;j++){
        if(mat.Mat[i][j] < min)min =mat.Mat[i][j];
      } 
    }
    return min;
  }

  double maxMat(doubleMat mat){
    double max =  mat.Mat[0][0];
    for(int i=0;i<mat.dimX;i++){
      for(int j=0;j<mat.dimY;j++){
        if(mat.Mat[i][j] > max)max =mat.Mat[i][j];
      } 
    }
    return max;
  }
  double mPixel2(BmpImg image,int deg,int i,int j){
    int x,y;
    double somme = 0;
    for(x=0;x<deg;x++){
      for(y=0;y<deg;y++){
	      if( (i+x >= 0) && (i+x < image.dimX) ) {
		      if( (j+y >= 0) && (j+y < image.dimY) ) {
              somme = somme + image.img[i+x][i+y];
          }
        }
      } //= malloc(3*siz
    }
    return somme/(deg*deg);
  }

  void Pyramida(BmpImg* pyramide,BmpImg *img){
    int dimX=img->dimX,dimY=img->dimY;
    int dimx1=((*img).dimX-1)/2+1,dimy1=((*img).dimY-1)/2+1;
    int dimx2=((*img).dimX-1)/4+1,dimy2=((*img).dimY-1)/4+1;
    pyramide[0] = *img;
    pyramide[1] = createBmpImg("ech/2",dimx1,dimy1);
    pyramide[2] = createBmpImg("ech/4",dimx2,dimy2);
  }

  // BmpImg** Pyramida2(BmpImg *img){
    // BmpImg pyramide[3];
    // int dimX=img->dimX,dimY=img->dimY;
    // int dimx1=((*img).dimX-1)/2-1,dimy1=((*img).dimY-1)/2+1;
    // int dimx2=((*img).dimX-1)/4-1,dimy2=((*img).dimY-1)/4+1;
    // BmpImg mat2 = (createBmpImg("ech/2",dimx1,dimy1));
    // BmpImg mat4 = (createBmpImg("ech/4",dimx2,dimy2));
    // pyramide[0] = img;
    // pyramide[1] = &mat2;
    // pyramide[2] = &mat4;
    // return pyramide;
  // }

  void freepyramide(BmpImg * pyrmd){
    int i;
  for(i=0;i<3;i++){
    freeBmpImg(&pyrmd[i]);
    printf("Boucle free");
  }
  free(pyrmd);
  }

 
int main(){
 
  /* [> LECTURE DES DEUX IMAGES  <] */

   BmpImg img1 = readBmpImage(IMAGE1);
   BmpImg img2 = readBmpImage(IMAGE2);
   
    
   doubleMat Iy = createMat(img1.dimX,img1.dimY);
   doubleMat Ix = createMat(img1.dimX,img1.dimY);
   doubleMat It = createMat(img1.dimX,img1.dimY);

   
  doubleMat u      = createMat(img1.dimX,img1.dimY);
  doubleMat v      = createMat(img1.dimX,img1.dimY);
  doubleMat v_prec = createMat(img1.dimX,img1.dimY);
  doubleMat dv     = createMat(img1.dimX,img1.dimY);
  doubleMat ku     = createMat(img1.dimX,img1.dimY);
  double vn,un;
  
  // Pour la solution  matricielle 
  //BmpImg ** py = pyramide(img1);
   

  unsigned int i,j;
   int dimx = img1.dimX, dimy = img1.dimY,k=0;
   double alpha =1, eps = 0.000001;
   
   BmpImg py[3];
   Pyramida(py,&img1);


   /* BmpImg * py = Pyramida2(&img1); */
    // Alors on creer un tableau de doubleMat de taille 3;

/*               dimY
 *      o------------------>
 *      |
 *      |
 *      |
 * dimX |
 *      |
 *      |
 *      |
 *      v
 *  */
   // Calcul de It 
   
  for(i=0;i<dimx;i++){
      for(j=0;j<dimy;j++){
        It.Mat[i][j] =(double)(img2.img[i][j] - img1.img[i][j])*60;
      }
   }
  // Calcul de Ix
   
   for(i=0;i<dimx;i++){
      for(j=0;j<dimy;j++){
        if(i == 0){
        Iy.Mat[i][j] = (double) (getPixel(img1,i+1,j) - getPixel(img2,i,j)); 
        }
        else if (i == dimx-1){
        Iy.Mat[i][j] = (double) (getPixel(img1,i,j)-getPixel(img1,i-1,j));
        }
        else { 
        Iy.Mat[i][j] = (double) (getPixel(img1,i+1,j) - getPixel(img1,i-1,j))/2;
        }
      }
  }
    // Calcul de Iy
   for(i=0;i<dimx;i++){
      for(j=0;j<dimy;j++){
        if(j == 0){
        Ix.Mat[i][j] = (double) (getPixel(img1,i,j+1) - getPixel(img1,i,j)); 
        }
        else if (j == dimy-1){
        Ix.Mat[i][j] = (double) (getPixel(img1,i,j) - getPixel(img1,i,j-1));
        }
        else { 
        Ix.Mat[i][j] = (double) (getPixel(img1,i,j+1) - getPixel(img1,i,j-1))/2;
        }
      }
  } 
    
   
   initMat(u);
   initMat(v);

    for(i=0;i<dimx;i++){
      for(j=0;j<dimy;j++){
        if(Iy.Mat[i][j] != 0){
          v.Mat[i][j] = (-It.Mat[i][j] - u.Mat[i][j]*Ix.Mat[i][j])/Iy.Mat[i][j];
        }
        if(Ix.Mat[i][j] != 0){
          u.Mat[i][j] = (-It.Mat[i][j] - v.Mat[i][j]*Iy.Mat[i][j])/Ix.Mat[i][j];
        }
      }
   }

    // Calucul de u et v 

   do{
    copyMat(v,&v_prec);
     for(i=0;i<dimx;i++){
       for(j=0;j<dimy;j++){
        un =  mPixel(u,i,j);
        vn =  mPixel(v,i,j);
        u.Mat[i][j]  = un - ((Ix.Mat[i][j]*un + Iy.Mat[i][j]*vn + It.Mat[i][j])*Ix.Mat[i][j])/(alpha + pow(Iy.Mat[i][j],2) + pow(Ix.Mat[i][j],2));
        v.Mat[i][j]  = vn - ((Ix.Mat[i][j]*un + Iy.Mat[i][j]*vn + It.Mat[i][j])*Iy.Mat[i][j])/(alpha + pow(Iy.Mat[i][j],2) + pow(Ix.Mat[i][j],2));
        dv.Mat[i][j] = v.Mat[i][j] - v_prec.Mat[i][j];
       }
    }
    k++;
    printf("%d %lf\n",k,norm(dv));
   }while(norm(dv) > eps );
  
    // Methode de Multi-resolution 
  //  writeFILE("sous_ech2.txt",pyrmd[1]);
  //writeFILE("sous_ech4.txt",py[2]);
    
   // printf("\nla taille de l'image sous ech : ( %d ; %d)\n\n",img1.dimX,img1.dimY);
   // printf("\nla taille de l'image sous ech : ( %d ; %d)\n\n",(py[0]).dimX,(py[0]).dimY);
   // printf("\nla taille de l'image sous ech : ( %d ; %d)\n\n",(py[1]).dimX,(py[1]).dimY);
   // printf("\nla taille de l'image sous ech : ( %d ; %d)\n\n",(py[2]).dimX,(py[2]).dimY);
   

   
   printf("\nla taille de l'image sous ech : ( %d ; %d)\n\n",img1.dimX,img1.dimY);
   printf("\nla taille de l'image sous ech : ( %d ; %d)\n\n",(py[0]).dimX,(py[0]).dimY);
   printf("\nla taille de l'image sous ech : ( %d ; %d)\n\n",(py[1]).dimX,(py[1]).dimY);
   printf("\nla taille de l'image sous ech : ( %d ; %d)\n\n",(py[2]).dimX,(py[2]).dimY);



   // writeBmpImage("ssech2",py[1]);
  
   // writeInBmp(&Iy,"Iy.bmp");
  // writeInBmp(&Ix,"Ix.bmp");
  // writeInBmp(&It,"It.bmp");
  
   writeFILE("u.txt",&u);
   writeFILE("v.txt",&v);

  freeDoubleMat(&Iy);
  freeDoubleMat(&Ix);
  freeDoubleMat(&It);
  freeDoubleMat(&u);
  freeDoubleMat(&v);  
  freeDoubleMat(&v_prec);
  freeDoubleMat(&dv);

//  freeBmpImg(py[0]);
//  freeBmpImg(py[1]);
//  freepyramide(py);
  freepyramide(py);
  freeDoubleMat(&ku);
  //freeBmpImg(&mat2);
  freeBmpImg(&img1);
  freeBmpImg(&img2);
  
  return 0;
}
