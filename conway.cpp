#include<time.h>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<unistd.h>
#include<fstream>
using namespace std;
class conway
{
   private:  vector<vector<int> > state;
	     vector<vector<int> > next_state;
		int w;
		int h;

   public:  conway();
//	  void state_entry(int [][3],int ,int);
	  void setheight_width(int,int);
	  void random_state(void);
	  void next_state1(void);
	  void  sur_neigh(int,int);
	  void load_file(void);
	  void render(void);
	  
};
conway::conway()
 {
    
    w=0;
    h=0;
 }
 void conway::setheight_width(int height,int width)
    {
    // cout<<"entered w n h"<<endl;
     w=width;h=height;
     state.resize(h);
    next_state.resize(h); 
  for(int i=0;i<h;i++)
   {
    next_state[i].resize(w);
    state[i].resize(w);
    
   }
   
  for(int i=0;i<h;i++)
    {
	for(int j=0;j<w;j++)
           {
	     next_state[i][j]=0;
  	     state[i][j]=0;
           }
    }
  }
     

 void conway::load_file(void)
  {
    ifstream fin;
  fin.open("gosper.txt",ios::in);
  vector<int> states;
   vector<vector<int>> final_states;
  int lines=0;
  int width=0; 
  int number;
  int height=0;
  char ch;
  while(!fin.eof()){
       fin.get(ch);
       number=ch-48;
     if(number==(-38))
       {
	height++;
	continue;
       }
     states.push_back(number);
      width++;
    
  }
  
 
  height=height-1;
  width=width/height;
    //cout<<"started copying"<<endl;
    setheight_width(height,width);
    for(int i=0;i<height;i++)
      {
       for(int j=0;j<width;j++)
        {
	//cout<<state[i][j]<<" ";
         state[i][j]=states[lines];
       // cout<<state[i][j]<<endl;
	lines++;
       }
  //  cout<<"outside for loop"<<endl;
      }
  // cout<<"after copying";
   
  }  
  
  

void conway::random_state(void)
    {
	cout<<"enter width and height";
	int wi,he;
	cin>>wi>>he;
	setheight_width(he,wi);
//	cout<<"creating random states"<<endl;
        srand(time(NULL)); 
	for(int i=0;i<h;i++)
	  {
	    for(int j=0;j<w;j++)
		{
		int ran=rand()%10;
		if(ran>5)
			state[i][j]=1;
		else
			state[i][j]=0;
		}
	 }
    // cout<<"after creation"<<endl;
    }
 void conway::sur_neigh(int x,int y)
   {
	//cout<<"entered this function "<<endl;	
     int sum=0;
    for(int i=x-1;i<=x+1;i++)
	{
	  if((i<0)||(i>=h))
		continue;
	for(int j=y-1;j<=y+1;j++)
	    {
		if((j<0)||(j>=w))
			continue;
		if((i==x)&&(j==y))
			continue;
	       if(state[i][j]==1)
                   sum=sum+1;
	    }
	}
      //cout<<"out form loop"<<endl;
     if(state[x][y]==1)
	{
	 if(sum<=1)
	    next_state[x][y]=0;
	else  if(sum<=3)
	    next_state[x][y]=1;
	else 
	    next_state[x][y]=0;
	}
      else
	{
	  if(sum==3)
		next_state[x][y]=1;
	  else
		next_state[x][y]=0;
	}
//   cout<<"out of function"<<endl; 
   }
	    

void conway::next_state1(void)
    {
     
	for(int i=0;i<h;i++)
	  {
	   for(int j=0;j<w;j++)
	      {
		sur_neigh(i,j);
	      }
	  }
        for(int i=0;i<h;i++)
	  {	
	   for(int j=0;j<w;j++)
	       state[i][j]=next_state[i][j];
	  }
    }

void conway::render(void)
   {
    cout<<"\033c";
     for(int i=0;i<h;i++)
      {
	for(int j=0;j<w;j++)
	{
  	if(state[i][j]==1)
		cout<<"\u25A0";
	else 
		cout<<" ";
 	}
	cout<<endl;
      }
    
   // cout<<"\n------------------------------------------------------------------"<<endl;
  }

int main()
 {
  conway life;
 // int arr[3][3]={{0,0,1},{0,1,1},{0,0,0}};
 // life.state_entry(arr,3,3);
  life.load_file();
 // life.random_state();
  life.render();
  life.next_state1();
  life.render();
  for(;;)
   {
    sleep(1);
    life.next_state1();
    life.render();
    
   }
 return 0;
 }
