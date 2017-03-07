#include"Storage.hpp"
#include"User.hpp"
#include"Meeting.hpp"
#include"Date.hpp"
#include"Path.hpp"
#include<iostream>
#include<string>
#include<list>
#include<functional>
#include<fstream>
using namespace std;

shared_ptr<Storage> Storage::m_instance = nullptr;

Storage::Storage(){
      m_dirty = false;
      readFromFile();
  }
//Storage::Storage(const Storage & t_another) = delete;
//void Storage::operator=(const Storage & t_another) = delete;

vector<string> pai(string str, char ch) {
  //int len = str.size();
  int flag = 0, i;
  vector<string> paixu;
  for(i = 0; i < str.size(); i++) {
    if(str[i] == ch) {
      string s1 = str.substr(flag, i - flag);
      flag = i + 1;
      paixu.push_back(s1);
    }
  }
  string s1 = str.substr(flag, str.size() - flag);
  paixu.push_back(s1);
  return paixu;
}

bool Storage::readFromFile(void){
      ifstream inu(Path::userPath, ios::in);
      if(!inu) return 0;
      else {
        while(!inu.eof()) {
          string s;
        getline(inu, s);
        if(s.size() <= 3) break;
        vector<string> v = pai(s, ',');
       for(int i= 0; i < 4; i++) {
        int size1 = v[i].size();
        string str2 = v[i].substr(1, size1 - 2);
        v[i] = str2;
      }      
       User u(v[0], v[1], v[2], v[3]);
          m_userList.push_back(u);
      }
    }
    inu.close();

    ifstream inm(Path::meetingPath, ios::in);
    if(!inm) return 0;
    else {
      while(!inm.eof()) {
          string s7;
        getline(inm, s7);
        if(s7.size() <= 3) break;
        vector<string> v6 = pai(s7, ',');
       for(int i= 0; i < 5; i++) {
        int size6 = v6[i].size();
        string str21 = v6[i].substr(1, size6 - 2);
        v6[i] = str21;
      } 
      vector<string> participators = pai(v6[1], '&');
      Date startTi(v6[2]);
      Date endTi(v6[3]);
      Meeting m(v6[0], participators, startTi, endTi, v6[4]);
          m_meetingList.push_back(m);
        }
      }
      inm.close();
      return 1;
    }

       /*for(int i= 0; i < 4; i++) {
        int size1 = v[i].size();
        string str2 = v[i].substr(1, size1 - 2);
        v[i] = str2;
      }      
       User u(v[0], v[1], v[2], v[3]);
          m_userList.push_back(u);     
       User u(v[0], v[1], v[2], v[3]);
          m_userList.push_back(u);
      }
    }

      
      string ss[1000];
      int value = 0;
      int start;
      for(int l = 1; l < i; l++) {
        if(s[l].length() < 2) break;
        int k = 0, end = 0;
        start = 0;
        int mm = -1, cc = -1;
        for(unsigned int j = 0; j < s[l].size(); j++) {
          if(s[l][j] == '"') {
            k++;
            mm = 0;
          }
          if(k % 2 != 0 && mm == 0) {
            mm = 1;
            start = j;
          }
          if(k % 2 == 0 && mm == 0) {
            mm = cc = 1;
            end = j;
          }
          if(end - start > 0 && cc == 1) {
            char sa[1000];
            for(int a = 0; a < end - start - 1; a++) {
              sa[a] = s[l][start + a + 1];
            }
            sa[end - start - 1] = '\0';
            cc = 0;
            ss[value] = sa;
            value++; 
          }
        }
      }
      for(int v = 0; v < value; v++) {
        if((v + 1) % 4 == 0) {
          
        }
      }
      in.close();
      
      if(!in1) return 0;
      string r[1000];
      int i1 = 0;
      while(!in1.eof()) {
        getline(in1, r[i1], '\n');
        i1++;
      }
      string ss1[1000];
      int value1 = 0;
      for(int l1 = 1; l1 < i1; l1++) {
        if(r[l1].length() < 2) break;
        int k1 = 0, start1 = 0, end1 = 0;
        int mm1 = -1, cc1 = -1;
        for(unsigned int j1 = 0; j1 < r[l1].size(); j1++) {
          if(r[l1][j1] == '"') {
            k1++;
            mm1 = 0;
          }
          if(k1 % 2 != 0 && mm1 == 0) {
            mm1 = 1;
            start1 = j1;
          }
          if(k1 % 2 == 0 && mm1 == 0) {
            mm1 = cc1 = 1;
            end1 = j1;
          }
          if(end1 - start1 > 0 && cc1 == 1) {
            char rr[1000];
            for(int b = 0; b < end1 - start1 - 1; b++) {
              rr[b] = r[l1][start1 + b + 1];
            }
            rr[end1 - start1 - 1] = '\0';
            cc1 = 0;
            ss1[value1] = rr;
            value1++; 
          }
        }
      }
      Date d1, d2;
      for(int v1 = 0; v1 < value1; v1++) {
        if((v1 + 1) % 3 == 0) {
          d1 = Date::stringToDate(ss1[v1]);
        }
        if((v1 + 1) % 4 == 0) {
          d2 = Date::stringToDate(ss1[v1]);
        }
        if((v1 + 1) % 5 == 0) 
{          vector<string> v;
          string h;
          int sizes = ss1[v1 - 3].size();
          int starts = 0, i;
          for(int leng = 0; leng < sizes; leng++) {
            if(ss1[v1 - 3][leng] == '&') {
              h = ss1[v1 - 3].substr(starts, 1 - start);
              starts = value1 + 1;
              v.push_back(h);
            }
          }
          h = ss1[v1 - 3].substr(starts, value1 - start);
          starts = value1 + 1;
          v.push_back(h);
          
        }
      }
      in1.close();
      return 1;
  }*/
bool Storage::writeToFile(void){
       ofstream outu(Path::userPath, ios::out);
       if( !outu) return false;
       else {
        list<User>::iterator i;
        for(auto i = m_userList.begin(); i != m_userList.end(); i++) {
        outu<<"\"" << i->getName()<< "\",\"" << i->getPassword()<< "\",\"" << i->getEmail()<< "\",\"" <<i->getPhone()<< "\"" <<endl;

       }
       }
       outu.close();

       ofstream outm(Path::meetingPath, ios::out);
       if( !outm) return false;
       else {
        vector<string> participator;
        list<Meeting>::iterator i;
        for(auto i = m_meetingList.begin(); i != m_meetingList.end(); i++) {
          participator = (*i).getParticipator();
        outm << "\"" << i->getSponsor()<< "\",\"";
        vector<string>::iterator vit = participator.begin();
        for(int i= 0; i <participator.size() - 1; i++) {
          outm<<(*vit++)<<"&";
        }
        outm<<(*vit);
        outm<<"\",\"" << Date::dateToString(i->getStartDate())<< "\",\"" <<Date::dateToString(i->getEndDate())<< "\",\"" <<i->getTitle()<<"\""<<endl;

      }
       }
       outm.close();
       return true;
     }
       /*int i;
       if(outu) outu.close();
       if(outm) outm.close();
       for(i = 0; i < ATIMES; i++) {
        outu.open(Path::userPath, fstream::out | fstream::trunc);
        if(outu) break;
       }
       if(i == ATIMES) return 0;
       for(i = 0; i < ATIMES; i++) {
        outm.open( fstream::out | fstream::trunc);
        if(outm) break;
       }
       if(i == ATIMES) return 0;
       
       
      outu.close();
      outm.close();
      return 1;*/
    /*try {
      ofstream out();
      list<User>::iterator it1 = m_userList.begin();
      while(it1 != m_userList.end()) {
        out << 
        it1++;
      }
      out.close();
      out.open(Path::meetingPath, ios::out | ios::trunc);
      list<Meeting>::iterator it2 = m_meetingList.begin();
      while(it2 != m_meetingList.end()) {
        
      out.close();
      return 1;
    }
    catch(...) {
      return false;
    }*/

shared_ptr<Storage> Storage::getInstance(void){
  if(m_instance == nullptr)
      m_instance.reset(new Storage());
      return m_instance;
  }

Storage::~Storage(){
     writeToFile();
     m_instance.reset();

  }

void Storage::createUser(const User & t_user){
    m_userList.push_back(t_user);
    m_dirty = true;
    sync();
  }

list<User> Storage::queryUser(function<bool(const User &)> filter) const{
      list<User> uu;
      list<User>::iterator it1;
      for(auto it1 = m_userList.begin(); it1 != m_userList.end(); it1++) {
        if(filter(*it1)) {
          uu.push_back(*it1);
        }
      }
      return uu;
      /*list<User> uu;
      for(auto i : m_userList) {
     if(filter(i)) uu.push_back(i);
   }
   return uu;*/
  }
int Storage::updateUser(function<bool(const User &)> filter, function<void(User &)> switcher){
    list<User>::iterator it1;
    int n = 0;
    for(auto it1 = m_userList.begin(); it1 != m_userList.end(); it1++) {
      if(filter(*it1)) {
        switcher(*it1);
        n += 1;
      }
    }
    m_dirty = true;
    sync();
    return n;
}

int Storage::deleteUser(function<bool(const User &)> filter){
    list<User>::iterator it1;
    int n = 0;
    for(auto it1 = m_userList.begin(); it1 != m_userList.end(); it1++) {
      if(filter(*it1)) {
        it1 = m_userList.erase(it1);
        n += 1;
      }
    }
    m_dirty = true;
    sync();
    return n;
}

void Storage::createMeeting(const Meeting & t_meeting){
    m_meetingList.push_back(t_meeting);
    m_dirty = true;
    sync();
}

list<Meeting> Storage::queryMeeting(function<bool(const Meeting &)> filter) const{
   list<Meeting> mm;
   list<Meeting>::iterator it2; 
   for(auto it2 = m_meetingList.begin(); it2 != m_meetingList.end(); it2++) {
    if(filter(*it2)) {
      mm.push_back(*it2);
    }
   }
   return mm;
   /*list<Meeting> mm;
   for(auto i : m_meetingList) {
     if(filter(i)) mm.push_back(i);
   }
   return mm;*/
}
int Storage::updateMeeting(function<bool(const Meeting &)> filter, function<void(Meeting &)> switcher){
  list<Meeting>::iterator it2 = m_meetingList.begin();
  int n = 0;
  while(it2 != m_meetingList.end()) {
    if(filter(*it2)) {
      switcher(*it2);
      n += 1;
    }
    else { it2++;}
  }
  m_dirty = true;
  sync();
  return n;
}
int Storage::deleteMeeting(function<bool(const Meeting &)> filter){
  list<Meeting>::iterator it2 = m_meetingList.begin();
  int n = 0;
  while(it2 != m_meetingList.end()) {
    if(filter(*it2)) {
      it2 = m_meetingList.erase(it2);
      n += 1;
    }
    else { it2++;}
  }
  m_dirty = true;
  sync();
  return n;
}
bool Storage::sync(void){
  /*if(m_dirty) {
    writeToFile();
    m_dirty = false;
  }*/
  return writeToFile();
}
