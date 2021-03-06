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
map<string, vector<int> > apTime;
//map<string, vector<string> > apUser;
//map<string, vector<int> > apCatg;

typedef pair<string, set<string> > PAIR;

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs){
    return lhs.second.size() > rhs.second.size();
}

//int op(int a,int b){return a+b;}


//用于获取：每个小时每个ap的连接次数
void fact(string whichDay,string poi, string apNumFile){
      ifstream ifs2(whichDay.c_str()); // TecentData/wifi_speed/20150504/wifi_speed_sample

      ofstream ofs1(apNumFile.c_str());// bupt/apnum0316_speed
      //ofstream ofs2(apCatgFile.c_str());//catgStimeEtime

      ifstream ifs1(poi.c_str());//  bupt/bupt_poi
      string mac, lat, lon, ssid;
      string token,line;
      int count = 0;
      //vector<string> v;
      while(getline(ifs1, line)){
  		    istringstream iss(line);
  		    count=0;
          //v.clear();
  		    while(getline(iss, token, '|')){
  			      count ++;
              switch(count){
              case 1:
                  ssid = token;
                  break;
              case 2:
                  mac = token;
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
          filter[mac] = ssid;
      }
      ifs1.close();

      string end_time, guid, bssid, connect_time;
      time_t t;
      //int catalogint;
      vector< int > arry(24, 0);//初始化ap类别频次矩阵，全部值初始化为0
      int end_hour = 0, star_hour = 0;
      while(getline(ifs2, line)){
  			  istringstream iss(line);
  		    count=0;
  		    while(getline(iss, token, '|')){
  			      count ++;
              switch(count){
              case 1:
                  end_time = token;
                  char buf[128];
                  strcpy(buf,token.c_str());
                  struct tm tm_;
                  strptime(buf, "%Y-%m-%d %H:%M:%S", &tm_); //将字符串转换为tm时间

                  end_hour = int(tm_.tm_hour);
                  //cout<< end_hour<<endl;

                  break;
              case 2:
                  guid = token;
                  break;
              case 5:
                  bssid = token;
                  break;
              //case 6:
                //  connect_time = token.substr(0,10);
                //  t  = atoi(connect_time.c_str());
                //  struct tm* tm = localtime(&t);
                //  char date[50];
                  //cout<< tm->tm_hour<<endl;
                  //strftime(date, sizeof(date), "%Y-%m-%d %T", tm);
                  //connect_time = string(date);
                  //connect_time = connect_time.split(' ')
                  //connect_time = connect_time[1]
                  //connect_time = connect_time.split(':')
                //  star_hour = int(tm->tm_hour)
                //  break;
              }
  		    }
          if(filter.find(bssid)!=filter.end()){
            if(apTime.find(bssid) == apTime.end()){
                apTime[bssid] = arry;
            }

          //    catalogint = atoi(catalog.c_str()); //string to int
           // cout<<catalogint<<endl;
            apTime[bssid][end_hour] += 1;
          }
	          //    catalogint = atoi(catalog.c_str()); //string to int
             // cout<<catalogint<<endl;
	          //  userCatg[guid][catalogint-1] += 1;

  	  }
      for(map<string,vector<int> >::const_iterator it=apTime.begin(); it!=apTime.end(); ++it){
          ofs1<< it->first ;
          vector<int> ::const_iterator it2 = it->second.begin();
          for ( ; it2 != it->second.end(); it2++){
              ofs1<<','<<(*it2);
          }
          ofs1<<endl; //ofs1: 每个ap的连接次数
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
      //ofs2.close();

}

int main(int argc, char* argv[]){

   // string s2 = "/safe_wifi_connect_sample_export";
    string s1,s2,s3,s4;
   // for(int i=16;i<=22;i++)
   // {
        s1 = argv[1];//20150316/safe_wifi_connect_sample_export
        s2 = argv[2];//poi_macLatLonCatalog2
        s3 = argv[3];//userCatg
        //s4 = argv[4];//apCatg
        fact(s1,s2,s3);
   // }

}
