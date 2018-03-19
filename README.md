# Face_morphing
*This work was done as part of Digital Image Analysis lab work.

*We have morphed 2 images by using the [Beier-Neely Morphing](https://www.cs.princeton.edu/courses/archive/fall00/cs426/papers/beier92.pdf) technique. 

*This lab was done in a group of two by Nikhil Teja and Vamsi V 

## This is the lab description of the exercise.

--------------------------------------------------------------------------------------------------------------------------------
Morphing, short for metamorphosing, refers to an animation technique in which one image is gradually turned into another.  Its a transformation of one image to another by the gradual distortion of corresponding points.

In this lab you need to implement : 
* Image Morphing between 2 images
  Input: Given 2 images and  .txt file that specifies the tie points between these two images
  Output: .gif image (exhibiting Image morphing between two images)

Some basic concepts were already discussed and you may refer to the Shared-folder for some some ppts/content on this topic. Also, you may refer to following links: https://www.cs.princeton.edu/courses/archive/fall00/cs426/papers/beier92.pdf

There are several ways to do image morphing. If you are using Delaunay's  triangulation, you may refer to these http://www-2.cs.cmu.edu/~quake/triangle.html. And you are allowed to use their subroutines for generating the grid topology 
(delaunay triangulation one)

---------------------------------------------------------------------------------------------------------------------------------

## To compile and run the code


-----------------------------------------------------------------------------------------------------------------------------
Compile : 
In order to compile the code type the following statements in the terminal:
1) cmake .
2) make

Run :

./DIP4_2014CSB1011_NikhilTeja 1a.jpg 1b.jpg 1p.txt

since i have already given the tie points it's better to give the sample images 

you can give command line input for img1 src as argv[1]  img0 src as argv[2] tipoints source text file as argv[3]

---------------------------------------------------------------------------------------------------------------------------------
