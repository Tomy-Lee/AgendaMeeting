#include"Date.hpp"
#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

static int day1[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int day2[12]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 Date::Date(){
  	m_year=0;
  	m_month=0;
  	m_day=0;
  	m_hour=0;
  	m_minute=0;
  }
 Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute){
    m_year=t_year;
  	m_month=t_month;
  	m_day=t_day;
  	m_hour=t_hour;
  	m_minute=t_minute;
  }
 Date::Date(string dateString){
    *this = stringToDate(dateString);
 }
 int Date::getYear(void) const{ return m_year;}
 void Date::setYear(const int t_year){ m_year=t_year;}
 int Date::getMonth(void) const{ return m_month;}
 void Date::setMonth(const int t_month){ m_month=t_month;}
 int Date::getDay(void) const{ return m_day;}
 void Date::setDay(const int t_day){ m_day=t_day;}
 int Date::getHour(void) const{ return m_hour;}
 void Date::setHour(const int t_hour){ m_hour=t_hour;}
 int Date::getMinute(void) const{return m_minute;}
 void Date::setMinute(const int t_minute){ m_minute=t_minute;}
 bool Date::isValid(const Date t_date){
 	if(t_date.m_year<1000 || t_date.m_year>9999 || t_date.m_month<=0 || t_date.m_month>12 || t_date.m_day<=0 || t_date.m_minute<0 || t_date.m_minute>59 || t_date.m_hour<0 || t_date.m_hour>23)
 		return false;
 	if((t_date.m_year%4==0 && t_date.m_year%100 != 0) || t_date.m_year%400 == 0){
 		if(t_date.m_day > day2[t_date.m_month-1]) return false;
 	}
 	else {
 		if(t_date.m_day > day1[t_date.m_month-1]) return false;
    }
    return true;
}
/*bool isValidstring(const string dateString) {
  int chang = dateString.size();
  int nian = dateString[3] - '0' + (dateString[2] - '0') * 10 + (dateString[1] - '0') * 100 + (dateString[0] - '0') * 1000;
  int yue = dateString[6] - '0' + (dateString[5] - '0') * 10;
  int ri = dateString[9] - '0' + (dateString[8] - '0') * 10;
  int shi = dateString[12] - '0' + (dateString[11] - '0') * 10;
  int fen = dateString[15] - '0' + (dateString[14] - '0') * 10;
  if(nian < 1000 || nian > 9999 || yue <= 0 || yue > 12 || ri <= 0 || shi < 0 || shi > 23 ||fen < 0 || fen > 59 ) return 0;
  if((nian % 4==0 && nian % 100 != 0) || nian % 400 == 0){
    if(ri > day2[yue - 1]) return 0;
  }
  else {
    if(ri > day1[yue - 1]) return 0;
    }
   if(chang != 16 || dateString[4] != '-' || dateString[7] != '-' || dateString[10] != '/' || dateString[13] != ':')  return 0;
   return 1;
}*/
Date Date::stringToDate(const string t_dateString){
      Date newdate2;
      int lent = t_dateString.length();
      if(lent != 16) {
        newdate2.m_year = newdate2.m_month = newdate2.m_day = newdate2.m_hour = newdate2.m_minute = 0;
      }
      else if((t_dateString[0] > '0' && t_dateString[0] <= '9') && (t_dateString[1] >= '0' && t_dateString[1] <= '9') && (t_dateString[2] >= '0' && t_dateString[2] <= '9') && 
        (t_dateString[3] >= '0' && t_dateString[3] <= '9') && t_dateString[4] == '-' && (t_dateString[5] >= '0' && t_dateString[5] <= '1') && (t_dateString[6] >= '0' && t_dateString[6] <= '9') &&
        t_dateString[7] == '-' && (t_dateString[8] >= '0' && t_dateString[8] <= '9') && (t_dateString[9] >= '0' && t_dateString[9] <= '9') &&
        t_dateString[10] == '/' && (t_dateString[11] >= '0' && t_dateString[11] <= '9') && (t_dateString[12] >= '0' && t_dateString[12] <= '9') &&
        t_dateString[13] == ':' && (t_dateString[14] >= '0' && t_dateString[14] <= '9') && (t_dateString[15] >= '0' && t_dateString[15] <= '9')) {
        newdate2.m_year = (t_dateString[3] - '0') + (t_dateString[2] - '0') * 10 + (t_dateString[1] - '0') * 100 + (t_dateString[0] - '0') * 1000;
        newdate2.m_month = (t_dateString[6] - '0') + (t_dateString[5] - '0') * 10;
        newdate2.m_day = (t_dateString[9] - '0') + (t_dateString[8] - '0') * 10;
        newdate2.m_hour = (t_dateString[12] - '0') + (t_dateString[11] - '0') * 10;
        newdate2.m_minute = (t_dateString[15] - '0') + (t_dateString[14] - '0') * 10;
      }
      else {
        newdate2.m_year = newdate2.m_month = newdate2.m_day = newdate2.m_hour = newdate2.m_minute = 0;
      }
      return newdate2;
     /*int len = t_dateString.size(); 
     Date newdate;
     if(len != 16 || t_dateString[4] != '-' || t_dateString[7] != '-' || t_dateString[10] != '/' || t_dateString[13] != ':') {
         newdate.m_year = newdate.m_month = newdate.m_day = newdate.m_hour = newdate.m_minute = 0;
     }
     else {
      
     }  
     return newdate;*/
     /*int nian, yue, ri, shi, fen;
     if(isValidstring(t_dateString)) {
      int j, i=0, count = 1;
      int changdu = t_dateString.size();
      while(i != changdu) {
        if(i != 0) i++;
        if(i == 0) {
          j = 4;
          nian = stoi(t_dateString.substr(i, j));
          count++;
        }
        else {
          j = 2;
          if(count == 5) {
            fen = stoi(t_dateString.substr(i, j));
          }
          else if(count == 4) shi = stoi(t_dateString.substr(i, j));
          else if(count == 3) ri = stoi(t_dateString.substr(i, j));
          else if(count == 2) yue = stoi(t_dateString.substr(i, j));
          count++;
        }
        i = i + j;
      }
      return Date(nian, yue, ri, shi, fen);
     }
     else return Date();*/
 }
string Date::dateToString(Date t_date){
      char day[17];
      Date newdate1 = t_date;
      if(! isValid(t_date)) {
        return "0000-00-00/00:00";
      }
      else {
        int i;
      for(i = 3; i >= 0; i--) {
        day[i] = newdate1.m_year % 10 + '0';
        newdate1.m_year /= 10;  
      }
      for(i = 6; i>= 5; i--) {
        day[i] = newdate1.m_month % 10 + '0';
        newdate1.m_month /= 10;
      }
      for(i = 9; i>= 8; i--) {
        day[i] = newdate1.m_day % 10 + '0';
        newdate1.m_day /= 10;
      }
      for(i = 12; i>= 11; i--) {
        day[i] = newdate1.m_hour % 10 + '0';
        newdate1.m_hour /= 10;
      }
      for(i = 15; i>= 14; i--) {
        day[i] = newdate1.m_minute % 10 + '0';
        newdate1.m_minute /= 10;
      }
      day[4] = day[7] = '-';
      day[10] = '/';
      day[13] = ':';
      day[16] = '\0';
      string str(day);
      return str;
      }
      
 }
 Date& Date::operator=(const Date &t_date){
 	m_year = t_date.m_year;
 	m_month = t_date.m_month;
 	m_day = t_date.m_day;
 	m_hour = t_date.m_hour;
 	m_minute = t_date.m_minute;
 	return *this;
 }
 bool Date::operator==(const Date &t_date) const{
 	if(m_year == t_date.m_year && m_month == t_date.m_month && m_day == t_date.m_day && m_hour == t_date.m_hour && m_minute == t_date.m_minute) 
 		return true;
 	return false;
 }
 bool Date::operator>(const Date &t_date) const{
 	if(m_year > t_date.m_year) return true;
 	else if(m_year == t_date.m_year && m_month > t_date.m_month) return true;
 	else if(m_year == t_date.m_year && m_month == t_date.m_month && m_day > t_date.m_day) return true;
 	else if(m_year == t_date.m_year && m_month == t_date.m_month && m_day == t_date.m_day && m_hour > t_date.m_hour) return true;
 	else if(m_year == t_date.m_year && m_month == t_date.m_month && m_day == t_date.m_day && m_hour == t_date.m_hour && m_minute > t_date.m_minute) return true;
 	return false;
 }
 bool Date::operator<(const Date &t_date) const{
 	if(m_year < t_date.m_year) return true;
 	else if(m_year == t_date.m_year && m_month < t_date.m_month) return true;
 	else if(m_year == t_date.m_year && m_month == t_date.m_month && m_day < t_date.m_day) return true;
 	else if(m_year == t_date.m_year && m_month == t_date.m_month && m_day == t_date.m_day && m_hour < t_date.m_hour) return true;
 	else if(m_year == t_date.m_year && m_month == t_date.m_month && m_day == t_date.m_day && m_hour == t_date.m_hour && m_minute < t_date.m_minute) return true;
 	return false;
 }
 bool Date::operator>=(const Date &t_date) const{
 	return(*this > t_date || *this == t_date);
 }
 bool Date::operator<=(const Date &t_date) const{
 	return(*this < t_date || *this == t_date);
 }
