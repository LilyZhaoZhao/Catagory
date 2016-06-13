#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
#include <ctime>

using namespace std;
map<string, string> filter;
map<string, vector<int> > userCatg;
//map<string, vector<string> > apUser;
//map<string, vector<int> > apCatg;

typedef pair<string, set<string> > PAIR;

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs){
    return lhs.second.size() > rhs.second.size();
}

//int op(int a,int b){return a+b;}

//用于LDA主题模型，未完工！！！
//用于获取：每个小时每种类别ap的连接次数
void fact(string whichDay,string poi, string userCatgFile, string apCatgFile){
      ifstream ifs2(whichDay.c_str()); // 0316/safe_wifi_connect_sample_export

      ofstream ofs1(userCatgFile.c_str());//userCatgvector
      ofstream ofs2(apCatgFile.c_str());//catgStimeEtime

      ifstream ifs1(poi.c_str());//shenzhen_macCatalogint
      string mac, lat, lon, catalog;
      string token,line;
      int count = 0;
      //vector<string> v;
      while(getline(ifs1, line)){
  		    istringstream iss(line);
  		    count=0;
          //v.clear();
  		    while(getline(iss, token, ';')){
  			      count ++;
              switch(count){
              case 1:
                  mac = token;
                  break;
              case 2:
                  catalog = token;
                  break;
            /*  case 2:
                  lat = token;
                  break;
              case 3:
                  lon = token;
                  break;
              case 4:
                  catalog = token;
                  break;
              */
              }
          }
          //v.push_back(lat);
          //v.push_back(lon);
          //v.push_back(catalog);
          filter[mac] = catalog;
      }
      ifs1.close();

      string end_time, guid, bssid, connect_time;
      time_t t;
      int catalogint;
      vector< int > arry(16, 0);//初始化ap类别频次矩阵，全部值初始化为1
      int end_hour = 0, star_hour = 0;
      while(getline(ifs2, line)){
  			  istringstream iss(line);
  		    count=0;
  		    while(getline(iss, token, '|')){
  			      count ++;
              switch(count){
              case 1:
                  end_time = token;
                  //end_time = end_time.split(' ')
                  //end_time = end_time[1]
                  //end_time = end_time.split(':')
                  //end_hour = int(end_time[0])
                  break;
              case 2:
                  guid = token;
                  break;
              case 4:
                  bssid = token;
                  break;
              case 6:
                  connect_time = token.substr(0,10);
                  t  = atoi(connect_time.c_str());
                  struct tm* tm = localtime(&t);
                  char date[50];
                  strftime(date, sizeof(date), "%Y-%m-%d %T", tm);
                  connect_time = string(date);
                  //connect_time = connect_time.split(' ')
                  //connect_time = connect_time[1]
                  //connect_time = connect_time.split(':')
                  //star_hour = int(connect_time[0])
                  break;
              }
  		    }
          if(filter.find(bssid)!=filter.end()){
              if(userCatg.find(guid) == userCatg.end()){
                  userCatg[guid] = arry;//?????
              }
	             catalog = filter[bssid];
	              catalogint = atoi(catalog.c_str()); //string to int
             // cout<<catalogint<<endl;
	            userCatg[guid][catalogint-1] += 1;

              ofs2<<catalog<<','<<connect_time <<','<<end_time<<endl; //ofs2: ap类别，开始时间，结束时间

          }
  	  }

      for(map<string,vector<int> >::const_iterator it=userCatg.begin(); it!=userCatg.end(); ++it){
          ofs1<< it->first ;
          vector<int> ::const_iterator it2 = it->second.begin();
          for ( ; it2 != it->second.end(); it2++){
            ofs1<<','<<(*it2);
          }
          ofs1<<endl; //ofs1: 每个用户对不同类别ap的连接次数
      }

      //int op(int a,int b){return a+b;}
      /*
      string u, ap;
      vector<int> sumVec(16,0), addVec(16,0), tmpVec;
      //sumVec.resize(16);
      vector<string> ::const_iterator it2;
      vector<int> ::const_iterator it3;

      for(map<string,vector<string> >::const_iterator it=apUser.begin(); it!=apUser.end(); ++it){
          ap = it->first;
          for (it2 = it->second.begin(); it2 != it->second.end(); it2++){
              u = *it2;
              tmpVec = userCatg[u];
              transform(tmpVec.begin(),tmpVec.end(),addVec.begin(),sumVec.begin(),op);
              addVec = sumVec;
          }
          ofs2<< ap ;
          for (it3 = sumVec.begin() ; it3 != sumVec.end(); it3++){
            ofs2<<','<<(*it3);
          }
          ofs2<<endl;

      }
      */
      ifs2.close();
      ofs1.close();
      ofs2.close();

}

int main(int argc, char* argv[]){

   // string s2 = "/safe_wifi_connect_sample_export";
    string s1,s2,s3,s4;
   // for(int i=16;i<=22;i++)
   // {
        s1 = argv[1];//20150316/safe_wifi_connect_sample_export
        s2 = argv[2];//poi_macLatLonCatalog2
        s3 = argv[3];//userCatg
        s4 = argv[4];//apCatg
        fact(s1,s2,s3,s4);
   // }

}
