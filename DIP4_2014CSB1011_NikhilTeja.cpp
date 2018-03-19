 #include<iostream>
  #include <queue>
  #include<fstream>
  #include <cmath>
  #include <opencv2/opencv.hpp>
  #include "opencv2/highgui/highgui.hpp"
  #include "opencv2/core/core.hpp"
  #include "opencv2/core/core_c.h"
  #include "opencv2/highgui/highgui_c.h"
  #include "opencv2/imgproc/imgproc_c.h"

  using namespace cv;
  using namespace std;

    Mat image0,image1,warp0,warp1,finalMorph;

    int M_SIZE,N_SIZE;

    int TIE_POINTS=35;
    int * x1;
    int * y11;
    int * x2;
    int * y2;

    /*P AND Q for Warp Image*/
    int * pX;
    int * pY;

    int *qX;
    int *qY;

    /*L AND M FOR IMAGE 0*/
    int * lX;
    int * lY;

    int * mX;
    int * mY;

    /*L1 AND M1 FOR IMAGE 1*/
    int * l1X;
    int * l1Y;

    int * m1X;
    int * m1Y;

    /*XPRIME FOR  EACH LINE*/

    int *primeXx;
    int *primeXy;
  /*Displacei FOR  EACH LINE*/

    int *DisplaceX;
    int *DisplaceY;

  /*Dzum  FOR  EACH LINE*/

   float dSumX;float dSumY;

    /*tempX and tempY are used in addTwoPoints Subroutine*/
    int tempX[1];
    int tempY[1];

    Mat   fromImage; Mat  toImage ;
    Mat   wrapFrom; Mat wrapTo ;
    Mat   morph;

  // Caluclate the Dot Product
  //Input : the coordinates of two vectors
  //Output : the Value of the dotproduct
    int dotP(int l1, int m1 , int l2 , int m2 ){
      int result ;
      result= l1*l2 + m1*m2 ;
      return result;
    }

  //For Caluclating the mod of a line ( i.e Vector )

  float modOfP(int l , int m ){
    float result;
    result=sqrt(l*l + m* m);
    return result;
  }

  // For Addwarp0.at<uchar>(i,j)=(int)image0.at<uchar>(i,j);ing two Points
  int addTwoPoints(int l , int m , int j , int k )
  {
    tempX[0]=l+j;
    tempY[0]=m+k;
    //cout<< "addtwopoints y coordinate"<<m+k << endl;
  }
  float chimpA , chimpB; 
  float tempAdd(float l , float m , float j , float k ){
    chimpA=l+j;
    chimpB=m+k;

  }
  char lol [10];
  void read_from_file(int TIE_POINTS){

    std::fstream myfile(lol, std::ios_base::in);

    int a2,count1,i;
    float a;
    int iter=0;

    while(myfile >> a)

    {
        i=iter/8;
        count1=iter%8;

      if(count1==0){
                lX[i]=a;
                iter+=1;
                //cout << lX[i] <<endl;
                continue;
            }
       if(count1==1){
                lY[i]=a;
                iter+=1;
                continue;
            }
        if(count1==2){
                mX[i]=a;
                iter+=1;
                continue;
            }
        if(count1==3){
                mY[i]=a;
                iter+=1;
                continue;
            }
        if(count1==4){
                l1X[i]=a;
                iter+=1;
                continue;
            }
        if(count1==5){
                l1Y[i]=a;
                iter+=1;
                continue;
            }
        if(count1==6){
                m1X[i]=a;
                iter+=1;
                continue;
            }
        if(count1==7){
                m1Y[i]=a;
                //cout << m1Y[i] <<endl;
                iter+=1;
                continue;
            }




    }


  }

  void warp_calc(float t,int TIE_POINTS){
     

      for(int i=0;i<TIE_POINTS;i++){

        pX[i]=(t)*lX[i]+((1.0-t)*l1X[i]);
        pY[i]=(t)*lY[i]+((1.0-t)*l1Y[i]);
        qX[i]=(t)*mX[i]+((1.0-t)*m1X[i]);
        qY[i]=(t)*mY[i]+((1.0-t)*m1Y[i]);



      }

  }

float pointLineDistance(double u , double v  , int i , int j, int px , int py , int qx, int qy){

   if(u>=0 && u<=1){
    return abs(v);
   }
   else if(u<0){
   return  sqrt((px-i)*(px-i) + (py-j)*(py-j)) ;
   }
   else if(u>1){
    return sqrt((qx-i)*(qx-i) + (qy-j)*(qy-j)) ;
   }
  }



void display_image(){

     //namedWindow("MyWindow", WINDOW_NORMAL);

     namedWindow("image0", WINDOW_NORMAL);
     namedWindow("warp0", WINDOW_NORMAL);
     imshow("image0", image0); //display the image which is stored in the 'orginal' in the "MyWindow" window
     imshow("warp0", warp0);
     namedWindow("image1", WINDOW_NORMAL);
     namedWindow("warpOne", WINDOW_NORMAL);
     imshow("image1", image1); //display the image which is stored in the 'orginal' in the "MyWindow" window
     imshow("warpOne", warp1);
     namedWindow("final", WINDOW_NORMAL);
     imshow("final", finalMorph);
     waitKey(0); //wait infinite time for a keypress

    destroyWindow("image0");
    destroyWindow("final");
    destroyWindow("warp0");
     destroyWindow("image1");

    destroyWindow("warpOne");
    return;

}
  int main(int argc, char const *argv[])
  {
    int i,n;

      //cout << "How many numbers would you like to type? ";
      //cin >> i;
      n=35;

      pY = new (nothrow) int[n];
      pX = new (nothrow) int[n];
      qX = new (nothrow) int[n];
      qY = new (nothrow) int[n];
      lY = new (nothrow) int[n];
      lX = new (nothrow) int[n];
      mX = new (nothrow) int[n];
      mY = new (nothrow) int[n];
      l1Y = new (nothrow) int[n];
      l1X = new (nothrow) int[n];
      m1X = new (nothrow) int[n];
      m1Y = new (nothrow) int[n];
      primeXx = new (nothrow) int[n];
      primeXy = new (nothrow) int[n];
      DisplaceX= new (nothrow) int[n];
      DisplaceY= new (nothrow) int[n];
      int finalXPrimeX[1];
      int finalXPrimeY[1];
      finalXPrimeX[0]=0;
      finalXPrimeY[0]=0;
      tempX[0]=0;
      tempY[0]=0;

      // TO TAKE THE VALUES OF TIE POINTS

      //  char* im1 = argv[1];
      //char* im2 = argv[2];

      image0= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

      M_SIZE=image0.rows;
      N_SIZE=image0.cols;

      //Mat warp0(M_SIZE,N_SIZE,image0.type());
      
      image1 = imread(argv[2],CV_LOAD_IMAGE_GRAYSCALE);
      //  warp0=image1.clone();
      warp0 =   Mat::zeros(image0.size(), image0.type());
      warp1 =   Mat::zeros(image1.size(), image1.type());
     


        int M1_SIZE,N1_SIZE;
        M1_SIZE=image1.rows;
        N1_SIZE=image1.cols;
        float t;
        t=0.8;
        strcpy(lol,argv[3]);
      read_from_file(35);

      warp_calc(t,35);
      // removing garbage vals
      for (int i = 0; i < 35; ++i)
      {
        DisplaceY[i]=0;
        DisplaceX[i]=0;
      }


    int lineCount=TIE_POINTS;  // used in caluclation of x prime
    float u;  // used in caluclation of x prime
    float v ; // used in caluclation of x prime
    float length,distance ;

    float a , b ,p;double weight,weightSum; //used in weight caluclation
    a=0.5; b=1; p=0.2;
    weight=0;

    //a=0.5; b=1; p=0.2;
   dSumX=0;dSumY=0;
    //cout<<"Initial DSUM is ( "<< dSumX[0] << "," <<dSumY[0] <<")" << endl;
    weightSum = 0 ;// As in Algorithm weightsum=0;
    int lineA,lineB ,lineC ; // Coefficients of line A B and C ;
    float tempu;float tempPrime,tempv;
    float a1 , b1;   // temp variables used in (i.e after first addtwopoints to store xcord and ycord)
    int flag=0 ; // The source is image 0 and for Flag = 1 The source is image 1 ;
    int count=0;
    if (flag==0)
    {
      for (int i = 0; i < M_SIZE; ++i)
      {
        for (int j = 0; j < N_SIZE; ++j)
        { weightSum=0;dSumX=0; // As in Algorithm dsum=(0,0);
          dSumY=0;
          for (int k = 0; k < lineCount; ++k)
          {
            //cout << "entered " << endl;
              u = dotP(i-pX[k],j-pY[k],qX[k]-pX[k],qY[k]-pY[k]);
              tempu= dotP(qX[k]-pX[k],qY[k]-pY[k],qX[k]-pX[k],qY[k]-pY[k]) ;
              u = u /(float) tempu;
             // printf("u is %d \n",u);

              v = dotP(i-pX[k],j-pY[k],(-1*qY[k]+pY[k]),qX[k]-pX[k]);

              tempv=modOfP(qX[k]-pX[k],qY[k]-pY[k]);
              v=v/tempv;
                //printf("v is %d \n",v);printf("M_Size is %d \n",M_SIZE);
      //printf("N_SIZE is %d \n",N_SIZE);
              //V Caluclation Done

              tempv=modOfP(mX[k]-lX[k],mY[k]-lY[k]);
              tempPrime=v/tempv;
              tempPrime=tempPrime;
              tempAdd(u*(mX[k]-lX[k]),u*(mY[k]-lY[k]),tempPrime*(-mY[k]+lY[k]),tempPrime*(mX[k]-lX[k]));
              a1=chimpA;
              b1=chimpB;
              tempAdd(a1,b1, lX[k] , lY[k]);
              primeXx[k]=(int)(chimpA);
              primeXy[k]=(int)chimpB;
              




              //float pointLineDistance(int u , int v  , int i , int j, int px , int py , int qx, int qy)
              distance=pointLineDistance(u,v,i,j,pX[k],pY[k],qX[k],qY[k]);
             // cout<<distance<<"distance"<<endl;
              length=modOfP(qX[k]-pX[k],qY[k]-pY[k]);
              //end of distance and length


             // length=modOfP(qX[k]-pX[k],qY[k]-pY[k]);
             // printf("length is %d\n",length);
              weight= pow(length,0.2)/(0.5+distance);
              addTwoPoints(primeXx[k],primeXy[k],-i,-j); // Disp[k] = Xk - X
              DisplaceX[k]=(tempX[0]);
              DisplaceY[k]=(tempY[0]);
              //cout << "displacement is  : "<< DisplaceX[k] << endl;
            //  cout<<DisplaceY[k]<<"displaceY"<<endl;
            //  cout<<weight<< "weight"<< endl;
              //tempAdd(DisplaceX[k]*weight,DisplaceY[k]*weight,dSumX,dSumY);
              dSumX=DisplaceX[k]*weight +dSumX;

              dSumY=DisplaceY[k]*weight +dSumY;


              //cout<<dSumX[0]<<"dsumX"<<endl;
              weightSum += weight;
              //cout<<endl<<endl<<endl;

                if(i==0 && j==0  && 1)
             {  //printf("X is %d \n",primeXx[k]);
                //printf("Y is %d \n",primeXy[k]);
               // cout<<count<<" ) "<< dSumX << "  " << dSumY << endl;  
                //count++;
                //cout<<" weight "<< weight<< "  weightSum  " << weightSum<<endl;
                //cout << "DisplaceX[k]*weight" << DisplaceX[k]*weight  <<"  DisplaceY[k]*weight"<< DisplaceY[k]*weight << endl;
                 //cout<<"Displacement is ("<< DisplaceX[k] << "," << DisplaceY[k] <<")" << endl;
                //cout<<"DSUM is ("<< dSumX[0] << "," << dSumY[0] <<")" << endl;

              }
              //  cout << "X is (0,0" << endl;
               // cout<< " P is " << pX[0] <<



          } // Ending the Eachline Loop !! K indexed loop
          //addTwoPoints(i,j,round(dSumX/weightSum),round(dSumY/weightSum));
          finalXPrimeX[0]=(int)(i+(dSumX/weightSum));
          finalXPrimeY[0]=(int)(j+(dSumY/weightSum));
          if((finalXPrimeX[0]>=0&& finalXPrimeX[0]<image0.rows) && finalXPrimeY[0]>=0 && finalXPrimeY[0]<N_SIZE)
            warp0.at<uchar>(j,i)=(int)image0.at<uchar>(finalXPrimeY[0],finalXPrimeX[0]);
        }
      }
    }
    flag=1;
    if (flag==1)
    {
      for (int i = 0; i < M_SIZE; ++i)
      {
        for (int j = 0; j < N_SIZE; ++j)
        { weightSum=0;dSumX=0; // As in Algorithm dsum=(0,0);
          dSumY=0;
          for (int k = 0; k < lineCount; ++k)
          {
            //cout << "entered " << endl;
              u = dotP(i-pX[k],j-pY[k],qX[k]-pX[k],qY[k]-pY[k]);
              tempu= dotP(qX[k]-pX[k],qY[k]-pY[k],qX[k]-pX[k],qY[k]-pY[k]) ;
              u = u /(float) tempu;
             // printf("u is %d \n",u);

              v = dotP(i-pX[k],j-pY[k],(-1*qY[k]+pY[k]),qX[k]-pX[k]);

              tempv=modOfP(qX[k]-pX[k],qY[k]-pY[k]);
              v=v/tempv;
                //printf("v is %d \n",v);printf("M_Size is %d \n",M_SIZE);
      //printf("N_SIZE is %d \n",N_SIZE);
              //V Caluclation Done

              tempv=modOfP(m1X[k]-l1X[k],m1Y[k]-l1Y[k]);
              tempPrime=v/tempv;
              tempPrime=tempPrime;
              tempAdd(u*(m1X[k]-l1X[k]),u*(m1Y[k]-l1Y[k]),tempPrime*(-m1Y[k]+l1Y[k]),tempPrime*(m1X[k]-l1X[k]));
              a1=chimpA;
              b1=chimpB;
              tempAdd(a1,b1, l1X[k] , l1Y[k]);
              primeXx[k]=(int)(chimpA);
              primeXy[k]=(int)chimpB;
              




              //float pointLineDistance(int u , int v  , int i , int j, int px , int py , int qx, int qy)
              distance=pointLineDistance(u,v,i,j,pX[k],pY[k],qX[k],qY[k]);
             // cout<<distance<<"distance"<<endl;
              length=modOfP(qX[k]-pX[k],qY[k]-pY[k]);
              //end of distance and length


             // length=modOfP(qX[k]-pX[k],qY[k]-pY[k]);
             // printf("length is %d\n",length);
              weight= pow(length,0.2)/(0.5+distance);
              addTwoPoints(primeXx[k],primeXy[k],-i,-j); // Disp[k] = Xk - X
              DisplaceX[k]=(tempX[0]);
              DisplaceY[k]=(tempY[0]);
              //cout << "displacement is  : "<< DisplaceX[k] << endl;
            //  cout<<DisplaceY[k]<<"displaceY"<<endl;
            //  cout<<weight<< "weight"<< endl;
              //tempAdd(DisplaceX[k]*weight,DisplaceY[k]*weight,dSumX,dSumY);
              dSumX=DisplaceX[k]*weight +dSumX;

              dSumY=DisplaceY[k]*weight +dSumY;


              //cout<<dSumX[0]<<"dsumX"<<endl;
              weightSum += weight;
              //cout<<endl<<endl<<endl;

                if(i==0 && j==0  && 1)
             {  //printf("X is %d \n",primeXx[k]);
                //printf("Y is %d \n",primeXy[k]);
              //  cout<<count<<" ) "<< dSumX << "  " << dSumY << endl;  
               // count++;
                //cout<<" weight "<< weight<< "  weightSum  " << weightSum<<endl;
                //cout << "DisplaceX[k]*weight" << DisplaceX[k]*weight  <<"  DisplaceY[k]*weight"<< DisplaceY[k]*weight << endl;
                 //cout<<"Displacement is ("<< DisplaceX[k] << "," << DisplaceY[k] <<")" << endl;
                //cout<<"DSUM is ("<< dSumX[0] << "," << dSumY[0] <<")" << endl;

              }
              //  cout << "X is (0,0" << endl;
               // cout<< " P is " << pX[0] <<



          } // Ending the Eachline Loop !! K indexed loop
          //addTwoPoints(i,j,round(dSumX/weightSum),round(dSumY/weightSum));
          finalXPrimeX[0]=(int)(i+(dSumX/weightSum));
          finalXPrimeY[0]=(int)(j+(dSumY/weightSum));
          if((finalXPrimeX[0]>=0&& finalXPrimeX[0]<image0.rows) && finalXPrimeY[0]>=0 && finalXPrimeY[0]<N_SIZE)
            warp1.at<uchar>(j,i)=(int)image1.at<uchar>(finalXPrimeY[0],finalXPrimeX[0]);
        }
       
        }
      }
    
    finalMorph =   Mat::zeros(image1.size(), image1.type());
    for (int i = 0; i < image0.rows; ++i)
    {
      for (int j = 0; j < image0.cols; ++j)
      {
        finalMorph.at<uchar>(i,j)=(1-t)*((int)warp0.at<uchar>(i,j)) +t*((int)warp1.at<uchar>(i,j));
      }
    }

    display_image();
    //cout<< y2[3] << endl;
    return 0;
  }



