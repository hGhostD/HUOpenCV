//
//  EighthClass.cpp
//  HUOpenCV4
//
//  Created by jw.hu on 2020/3/26.
//  Copyright © 2020 jw.hu. All rights reserved.
//

#include "EighthClass.hpp"
#include <opencv.hpp>

using namespace cv;
using namespace std;

Mat Maze;
vector<Point>Chunk;
void MazeTrack(int r,int c);

void imreadAndWrite() {
    Mat img = imread("/Users/hujiawen/Downloads/wuwu.jpg", IMREAD_GRAYSCALE);

    if (img.empty() == true) {
        cout << "读取图片为空" << endl;
        return;
    }

    cout << img.channels() << endl;
    
    imshow("8-1", img);
    waitKey();
    
    imwrite("/Users/hujiawen/Desktop/hu/HUOpenCV/HUOpenCV4/HUOpenCV4/第八章/test.jpg", img);
}


void detectSquare() {

    Mat element = getStructuringElement(MORPH_RECT, Size(17, 17));
    Mat img = cv::imread("/Users/hujiawen/Download/wuwu.jpg");
    
    Mat video;
    dilate(img, video, element);
    erode(video, video, element);
    

    Mat frame;
    resize(video, frame, Size(video.cols / 6,video.rows / 6));
    
    
    imshow("Original", frame);

    //** convert to HSV
    Mat hsv;
    cvtColor(frame,hsv,COLOR_BGR2HSV);

    //** Find the BLACK Area
    Mat blkobj;
    //morphologyEx(hsv, hsv, MORPH_OPEN,element);
    //morphologyEx(hsv, hsv, MORPH_CLOSE,element);
    inRange(hsv,Scalar(0,0,0),Scalar(180, 255, 180), blkobj);
    
    Mat dst;
    imshow("BlackArea", blkobj);

    //** Find the BIGGEST black area
    Maze = blkobj.clone();
    vector<vector<Point> >Chunks;
    vector<Point>ChunkMax;

    int rows = Maze.rows;
    int cols = Maze.cols;

    for(int i = 0; i < rows; i++)
    {
       for(int j = 0; j < cols; j++)
       {
           if(Maze.at<uchar>(i,j)==255)//at<>(rows,cols);
           {
               MazeTrack(i,j);
               Chunks.push_back(Chunk);
               Chunk.clear();
               vector <Point>().swap(Chunk);
           }
       }
    }
    long max=0;
    for(int n=0;n<Chunks.size();n++)
    {
       if(max<Chunks[n].size())
       {
           max=Chunks[n].size();
           ChunkMax.swap(Chunks[n]);
       }
    }
    Chunks.clear();
    vector <vector<Point> >().swap(Chunks);

    //** Use RotatedRect find the minAreaRect of ChunkMax
    Point2f vertex[4];
    RotatedRect box = minAreaRect(ChunkMax);
    box.points(vertex);//the vertex of rectangle is stored in vertex[4]

    //** use the coordinate of vertex to get the high and the length of minAreaRectangle
    double rectl=sqrt(pow(vertex[0].x-vertex[1].x,2)+pow(vertex[0].y-vertex[1].y,2));
    double recth=sqrt(pow(vertex[1].x-vertex[2].x,2)+pow(vertex[1].y-vertex[2].y,2));
    double area=recth*rectl;

    //** if the ratio of ChunkMax.size() : Area of rectangle is high enough, judge it to be rectangle
    double ratio=double(ChunkMax.size())/area;
    cout<<ratio<<endl;
    if(ratio>=0.65)
    {
       for(int i=0;i<4;i++)
       {
           line(video,6*vertex[i],6*vertex[(i+1)%4],Scalar(255,0,0),2,8);
       }
    }
    resize(frame, frame, Size(frame.cols*2,frame.rows*2));
    imshow("Rect", video);

    waitKey(0);
}

void MazeTrack(int r,int c)//search for the Biggest connected area
{
    Maze.at<uchar>(r,c)=0;
    Point *p=new Point(c,r);//Attention! int Point class, x means cols, y means rows;
    Chunk.push_back(*p);
    delete p;
    
    //** if adjacent point is not black or unmarked, end the function.
    if(Maze.at<uchar>(r-1,c)==0&&Maze.at<uchar>(r+1,c)==0&&Maze.at<uchar>(r,c-1)==0&&Maze.at<uchar>(r,c+1)==0) return;
    
    //** if any of adjacent point is black and unmarked, recurse.
    if((r-1)>=0 && Maze.at<uchar>(r-1,c)==255)//up(x-1,y)
    {
        MazeTrack(r-1,c);
    }
    if((r+1)<Maze.cols && Maze.at<uchar>(r+1,c)==255)//down(x+1,y)
    {
        MazeTrack(r+1,c);
    }
    if((c-1)>=0 && Maze.at<uchar>(r,c-1)==255)//left(x,y-1)
    {
        MazeTrack(r,c-1);
    }
    if((c+1)<Maze.cols && Maze.at<uchar>(r,c+1)==255)//right(x,y+1)
    {
        MazeTrack(r,c+1);
    }
}
