#include"User.hpp"
#include"Meeting.hpp"
#include"Date.hpp"
#include"AgendaService.hpp"
#include"Storage.hpp"
#include<iostream>
#include<list>
#include<string>
#include<functional>
#include<algorithm>
#include<vector>
using namespace std;

    AgendaService::AgendaService(){
    //m_storage = Storage::getInstance();
        startAgenda();
}

    AgendaService::~AgendaService() {
        quitAgenda();
    }

    bool AgendaService::userLogIn(const string userName, const string password){
         /*function<bool (const User&)> filter = [&]() {
            if() return 1;
            else return 0;
         };*/
         list<User> uu1 = m_storage->queryUser([&] (const User & u1) {
            return (u1.getName() == userName && u1.getPassword() == password); 
         }
         );
         if(uu1.empty()) return 0;
         else return 1; 
         /*const auto & userlo = listAllUsers();
         for(auto it5 = userlo.begin(); it5 != userlo.end(); it5++) {
            if(it5->getName() == userName && it5->getPassword() == password) return 1;
            else return 0;
         }
         return 0;*/
    }

    bool AgendaService::userRegister(const string userName, const string password, const string email, const string phone){
        /*function<bool (const User&)> filter = [&](const User u1) {
            if(u1.getName() == userName) return 1;
            else return 0;
         };
         list<User> uu1 = m_storage->queryUser(filter);
         if(uu1.size()==0) {
            User a(userName, password, email, phone);
            m_storage->createUser(a);
            return 1;
         }
         else return 0; */
          /*const auto & userlo =listAllUsers();
         for(auto it5 = userlo.begin(); it5 != userlo.end(); it5++) {
            if(it5->getName() == userName) return 0;       
         }*/
            if(m_storage->queryUser([&] (const User & u1) {
            return u1.getName() == userName; 
         }
         ).empty()) {
                 User a(userName, password, email, phone);
          m_storage->createUser(a);
         return 1;
            }
         else return 0;
    }

    bool AgendaService::deleteUser(const string userName, const string password){
         /*function<bool (const User&)> filter = [&](const User u1) {
            if(u1.getName() == userName && u1.getPassword() == password) return 1;
            else return 0;
         };
         list<User> uu1 = m_storage->queryUser(filter);
         if(uu1.size()==0) {
            return 0;
         }
         else {
            function<bool (const User&)> f1 = [&](const User u) {
            if(u.getName() == userName && u.getPassword() == password) return 1;
            else return 0;
         };
         m_storage->deleteUser(f1);
         function<bool (const Meeting&)> f = [&](const Meeting mss) {
            if(mss.getSponsor() == userName) return 1;
            else {
                vector<string> participators4 = mss.getParticipator();
                for(int jj = 0; jj < participators4.size(); jj++) {
                    if(participators4[jj] == userName)  {
                        return 1;
                        break;      
                }
            }
            return 0;
        }
         };
         m_storage->deleteMeeting(f);
         return 1;
         }*/
         const auto & userlo = listAllUsers();
         for(auto it5 = userlo.begin(); it5 != userlo.end(); it5++) {
            if(it5->getName() == userName && it5->getPassword() == password){ return (bool)(m_storage->deleteUser(
            [userName](const User & m1) -> bool{
                return (m1.getName() == userName);
         }
         )
                );
        }
}
         return 0;
    }

    list<User> AgendaService::listAllUsers(void) const{
        /*function<bool (const User&)> filter = [&](const User u1) {
            return ( u1.getName() != "\n");};
        list<User> u1 = m_storage->queryUser(filter);
        return u1;*/
        return m_storage->queryUser([&] (const User & m1) {return true;});

    }

    bool isinpar(vector<string> mee_participator, string username) {
    vector<string>::iterator it;
    for(it = mee_participator.begin(); it != mee_participator.end(); it++) {
        if(*it == username) return 1;
    }
    return 0;
   }

    bool AgendaService::createMeeting(const string userName, const string title, const string startDate, const string endDate, const vector<string> participator) {
       Date st(startDate);
       Date en(endDate);
       Date wDate;
       
       if( !Date::isValid(st)) return 0;
         if( !Date::isValid(en)) return 0;
         if(st >= en || st == wDate || en == wDate) return 0;
         if(m_storage->queryUser([&] (const User & m1) {return m1.getName() == userName;}).empty()) return 0;
         if(participator.empty()) return 0;
         for(int i = 0; i < participator.size() - 1; i++) {
            for(int j = i + 1; j < participator.size(); j++) {
                if(participator[i] == participator[j]) return 0;
            }
         }
         
         vector<string>::const_iterator iter;
         for(iter = participator.begin(); iter != participator.end(); iter++) {
            if(m_storage->queryUser([&] (const User & m1) {return m1.getName() == (*iter);}).empty()) return 0;
            list<Meeting> meelist = listAllMeetings(*iter);
            list<Meeting>::iterator it9;
            for(it9 = meelist.begin(); it9 != meelist.end(); it9++) {
            if(it9->getStartDate() >= st && it9->getStartDate() < en) return 0;
            
            
            else if(it9->getEndDate() > st && it9->getEndDate() <= en) return 0;
            else if(it9->getStartDate() <= st && it9->getEndDate() >= en) return 0;
         }
         }
         if(isinpar(participator, userName)) return 0;
         if( !m_storage->queryMeeting([&] (const Meeting & m1) {return m1.getTitle() == title;}).empty()) return 0;
         list<Meeting> meelist = listAllMeetings(userName);
         list<Meeting>::iterator it;
         for(it = meelist.begin(); it != meelist.end(); it++) {
            if(it->getStartDate() >= st && it->getStartDate() < en) return 0;
            
            
            else if(it->getEndDate() > st && it->getEndDate() <= en) return 0;
            else if(it->getStartDate() <= st && it->getEndDate() >= en) return 0;
         }
         Meeting mmm(userName, participator, st, en, title);
         m_storage->createMeeting(mmm);
         return 1;
    








       /*if(participator.empty()) return 0;
       for(int iii= 0; iii < participator.size(); iii++) 
        if(participator[iii] == userName) return 0;
       Date st = Date::stringToDate(startDate);
       Date en = Date::stringToDate(endDate);
       if(st >= en) return 0;
       if(Date::isValid(st) == 0 || Date::isValid(en) == 0) return 0;
       for(int i=0; i < participator.size(); i++) {
        auto findu = [i, participator](const User& u){ return u.getName() == participator[i];};
        list<User> temp = m_storage->queryUser(findu);
        if(temp.empty()) return false;
       }
       auto check = [title](const Meeting& m) {
            return m.getTitle() == title;
        };
        list<Meeting> same = m_storage->queryMeeting(check);
        if(same.empty() != 0) return 0;




        /*function<bool (const User&)> filter = [&](const User u1) {
            if(u1.getName() == userName) return 1;
            else {
                vector<string> participators4 = participator;
                for(int jj = 0; jj < participators4.size(); jj++) {
                    if(u1.getName()== participators4[jj]) {
                        return 1;
                        break;
                    }
                }
                return 0;
            }
         };
        list<User> uuu = m_storage->queryUser(filter);
        if(uuu.empty()) return 0;
        unsigned int value = 2;
        if(uuu.size() != value) return 0;*/
        
         /*function<bool (const Meeting&)> f1 = [&](const Meeting m1) {
            if((m1.getSponsor() == userName) && (!(m1.getStartDate() >= en ||m1.getEndDate() <= st))) return 1;
            //if((m1.getSponsor() == participator || m1.getParticipator() == participator) && (!(m1.getStartDate() >= en || m1.getEndDate() <= st))) return 1;
            if(m1.getTitle() == title) return 1;
            return 0;
         };
         list<Meeting> mmm = m_storage->queryMeeting(f1);
         if(mmm.size() != 0) return 0;
         list<Meeting>::iterator it3 = mmm.begin();
         while(it3 != mmm.end()) {
            if((en <= it3->getStartDate()) || (st >= it3->getEndDate())) it3++;
            else return 0;
         } 
         Meeting ms(userName,  participator, st, en, title);
         m_storage->createMeeting(ms);
         return 1;*/
    }

    list<Meeting> AgendaService::meetingQuery(const string userName, const string title) const{
        /*function<bool (const Meeting&)> filter = [&](const Meeting m1) {
            if(m1.getSponsor() == userName && m1.getTitle() == title) return 1;
            else return 0;
        };
        list<Meeting> mm1 = m_storage->queryMeeting(filter);
        return mm1;*/
        return m_storage->queryMeeting([&] (const Meeting & m1) {return (m1.getTitle() == title && m1.getSponsor() == userName);});
    }

    list<Meeting> AgendaService::meetingQuery(const string userName, const string startDate, const string endDate) const{
        /*function<bool (const Meeting&)> filter = [&](const Meeting m1) {
        if(m1.getSponsor() == userName  && (Date::stringToDate(startDate) <= m1.getEndDate()) && (Date::stringToDate(endDate) >= m1.getStartDate())) 
            return 1;
            else return 0;  
        };
        list<Meeting> mm1 = m_storage->queryMeeting(filter);
        return mm1;*/
        list<Meeting> ret = listAllMeetings(userName);
        list<Meeting> jieguo;
        list<Meeting>::iterator it1;
        Date st(startDate);
        Date en(endDate);
         if(st > en) return jieguo;
         for(it1 = ret.begin(); it1 != ret.end(); it1++) {
            if(it1->getStartDate() >= st && it1->getStartDate() <= en) jieguo.push_back(*it1);
            
            
            else if(it1->getEndDate() >= st && it1->getEndDate() <= en) jieguo.push_back(*it1);
            else if(it1->getStartDate() <= st && it1->getEndDate() >= en) jieguo.push_back(*it1);
         }
         return jieguo;
    }

   

    list<Meeting> AgendaService::listAllMeetings(const string userName) const{
        /*function<bool (const Meeting&)> filter = [&](const Meeting m1) {
            if(m1.getSponsor() == userName)  return 1;
            else return 0;
        };
        list<Meeting> mm1 = m_storage-> queryMeeting(filter);
        return mm1;*/
        /*return m_storage->queryMeeting(
            [userName](const Meeting & m1) -> bool{
                if(m1.getSponsor() == userName) {return 1;}
                return (m1.isParticipator(userName));
            }
            );*/
        list<Meeting> ret, ret1;

        ret = m_storage->queryMeeting([&] (const Meeting & m1) {return (m1.getSponsor() == userName);});
        ret1 = (m_storage->queryMeeting([&] (const Meeting & m1) {return (isinpar(m1.getParticipator(), userName));}));
        list<Meeting>::iterator it1;
        for(it1 = ret1.begin(); it1 != ret1.end(); it1++) {
            ret.push_back(*it1);
        }
        return ret;
    }

    list<Meeting> AgendaService::listAllSponsorMeetings(const string userName) const{
        /*function<bool (const Meeting&)> filter = [&](const Meeting m1) {
            if(m1.getSponsor() == userName) return 1;
            else return 0;
        };
        list<Meeting> mm1 = m_storage-> queryMeeting(filter);
        return mm1;*/
        return m_storage->queryMeeting([&](const Meeting & m1) {return m1.getSponsor() == userName;});
    }

    list<Meeting> AgendaService::listAllParticipateMeetings(const string userName) const{
        return m_storage->queryMeeting([&](const Meeting & m1){return (isinpar(m1.getParticipator(), userName));});
    }

    bool AgendaService::deleteMeeting(const string userName, const string title){
        /*function<bool (const Meeting&)> filter = [&](const Meeting mss) {
            if(mss.getSponsor() == userName && mss.getTitle() == title) return 1;
            else return 0;
        };
        int n = m_storage->deleteMeeting(filter);
        if(n > 0) return 1;
        else return 0;*/
        int count;
        count = m_storage->deleteMeeting([&] (const Meeting & m1) {return (m1.getSponsor() == userName && m1.getTitle() == title);});
        if(count > 0) return 1;
        else return 0;
        /*const auto & userlo = listAllMeetings(userName);
         for(auto it5 = userlo.begin(); it5 != userlo.end(); it5++) {
            if(){ return (bool)(m_storage->deleteMeeting(
            [userName](const Meeting & m1) -> bool{
                return (m1.getSponsor() == userName);
         }
         )
                );
        }
}
         return 0;*/
    }

    bool AgendaService::deleteAllMeetings(const string userName){
        int count;
        count = m_storage->deleteMeeting([&] (const Meeting & m1) {return (m1.getSponsor() == userName);});
        if(count > 0) return 1;
        else return 0;
        /*function<bool (const Meeting&)> filter = [&](const Meeting m1) {
            if(m1.getSponsor() == userName) return 1;
            else return 0;
        };
        int n = m_storage->deleteMeeting(filter);
        if(n > 0) return 1;
        else return 0;*/
    }

    void AgendaService::startAgenda(void){
        m_storage =Storage::getInstance();
    }

    void AgendaService::quitAgenda(void){
        m_storage->sync();
        m_storage = nullptr;
    }
