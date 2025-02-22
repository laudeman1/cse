#include "Filesys.h"

// You can use this to test your Filesys class 

int main()
{
  Filesys fsys("disk1",256,128);
  
  fsys.newfile("file1");
  
  fsys.newfile("file2");
  
  string bfile1;
  string bfile2;

  for (int i=1; i<=1024; i++)
     {
       bfile1+="1";
     }

 vector<string> blocks; 
  blocks = fsys.block(bfile1, 128); 

   int blocknumber=0;

  for (int i=0; i< blocks.size(); i++)
     {
       blocknumber=fsys.addblock("file1",blocks[i]);
     }

  fsys.delblock("file1",fsys.getfirstblock("file1"));

  for (int i=1; i<=2048; i++)
     {
       bfile2+="2";
     }

  blocks=fsys.block(bfile2,128); 

  for (int i=0; i< blocks.size(); i++)
     {
       blocknumber=fsys.addblock("file2",blocks[i]);
     }

  fsys.delblock("file2",blocknumber);
  cin.get();
}