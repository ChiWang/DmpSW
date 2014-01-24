#include "../include/IniReader.h"
#include <iostream>

#include<fstream>
#include <string>




char* IniReadString(char* szFileName, char* szKey, char* sDefault)
{

  std::string line="";  
  std::string myline="";
  std::string str_szKey( szKey );
  std::ifstream myfile(szFileName); 
  int ck = 0;
  if (myfile.is_open())
    {
      while ( myfile.good() )
	{
	  getline (myfile,line);
	  std::size_t founds = line.find("##");
	  if(founds!=-1){
	    continue;
	  }
	  //std::cout<<line<< std::endl;
	  std::size_t found = line.find(szKey);
	  if(found!=-1){	    
	    myline=line.substr(str_szKey.length(),line.length());
	    myline.erase(remove(myline.begin(),myline.end(),' '),myline.end());
	    myline.erase(remove(myline.begin(),myline.end(),'='),myline.end());
	    myline.erase(remove(myline.begin(),myline.end(),':'),myline.end());
	    myline.erase(remove(myline.begin(),myline.end(),'"'),myline.end());
	    
	    //std::cout << myline << std::endl;
	  }
	}
      myfile.close();
    }

  
  else std::cout << "Unable to open file:" << szFileName << " to search " << szKey <<std::endl; 
  char *Sout;
  if(myline.length()==0){
    Sout = sDefault;
  }
  else{
    Sout = new char[myline.length() + 1];
    std::strcpy(Sout,myline.c_str());
  }
  return Sout;
}

int IniReadInt(char* szFileName, char* szKey, int iDefault)
{

  std::string line="";  
  std::string myline="";
  std::string str_szKey( szKey );
  std::ifstream myfile(szFileName); 
  if (myfile.is_open())
    {
      while ( myfile.good() )
	{
	  getline (myfile,line);
	  std::size_t founds = line.find("##");
	  if(founds!=-1){
	    continue;
	  }
	  //std::cout<<line<< std::endl;
	  std::size_t found = line.find(szKey);
	  if(found!=-1){	    
	    myline=line.substr(str_szKey.length(),line.length());
	    myline.erase(remove(myline.begin(),myline.end(),' '),myline.end());
	    myline.erase(remove(myline.begin(),myline.end(),'='),myline.end());
	    myline.erase(remove(myline.begin(),myline.end(),':'),myline.end());
	    //std::cout << myline << std::endl;
	  }
	}
      myfile.close();
    }

  else std::cout << "Unable to open file:" << szFileName << " to search " << szKey <<std::endl;   
  int Iout;
  if(myline.length()==0){
    Iout = iDefault;
  }
  else{
  Iout = atoi(myline.c_str());
  }
  return Iout;
}


double IniReadDouble(char* szFileName, char* szKey, double dDefault)
{

  std::string line="";  
  std::string myline="";
  std::string str_szKey( szKey );
  std::ifstream myfile(szFileName); 
  if (myfile.is_open())
    {
      while ( myfile.good() )
	{
	  getline (myfile,line);
	  std::size_t founds = line.find("##");
	  if(founds!=-1){
	    continue;
	  }
	  //std::cout<<line<< std::endl;
	  std::size_t found = line.find(szKey);
	  if(found!=-1){	    
	    myline=line.substr(str_szKey.length(),line.length());
	    myline.erase(remove(myline.begin(),myline.end(),' '),myline.end());
	    myline.erase(remove(myline.begin(),myline.end(),'='),myline.end());
	    myline.erase(remove(myline.begin(),myline.end(),':'),myline.end());
	    //std::cout << myline << std::endl;
	  }
	}
      myfile.close();
    }

  else std::cout << "Unable to open file:" << szFileName << " to search " << szKey <<std::endl;   
  double Dout;
  if(myline.length()==0){
  
    Dout = dDefault;
  }
  else{
    Dout = (double)atof(myline.c_str());
  }
  return Dout;
}


bool string2bool (const std::string & v)
{
    return !v.empty () &&
        (strcasecmp (v.c_str (), "true") == 0 ||
         atoi (v.c_str ()) != 0);
}

bool IniReadBool(char* szFileName, char* szKey, bool bDefault)
{

  std::string line="";  
  std::string myline="";
  std::string str_szKey( szKey );
  std::ifstream myfile(szFileName); 
  if (myfile.is_open())
    {
      while ( myfile.good() )
	{
	  getline (myfile,line);
	  std::size_t founds = line.find("##");
	  if(founds!=-1){
	    continue;
	  }
	  //std::cout<<line<< std::endl;
	  std::size_t found = line.find(szKey);
	  if(found!=-1){	    
	    myline=line.substr(str_szKey.length(),line.length());
	    myline.erase(remove(myline.begin(),myline.end(),' '),myline.end());
	    myline.erase(remove(myline.begin(),myline.end(),'='),myline.end());
	    myline.erase(remove(myline.begin(),myline.end(),':'),myline.end());
	    //std::cout << myline << std::endl;
	  }
	}
      myfile.close();
    }

  else std::cout << "Unable to open file:" << szFileName << " to search " << szKey <<std::endl;   
  bool Bout;
 if(myline.length()==0){
    Bout = bDefault;
  }
  else{
    Bout =string2bool(myline);
  }
  return Bout;
}

