#include"AgendaUI.hpp"
#include"AgendaService.hpp"
#include<iomanip>
#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

    AgendaUI::AgendaUI(){
        startAgenda();
    }
    void AgendaUI::OperationLoop(void){
        string a = getOperation();
        if(!executeOperation(a)) {
            cout<<"ERROR: No such operation, please input again!"<<endl;
            OperationLoop();
        }
    }

    void AgendaUI::startAgenda(void){
        if(m_userName.size() == 0) {
            cout<<"---------------------Agenda-------------------------"<<endl;
            cout<<"Action :"<<endl;
            cout<<"l  - log in Agenda by user name and password"<<endl;
            cout<<"r  - register an Agenda account"<<endl;
            cout<<"q  - quit Agenda"<<endl;
            cout<<"----------------------------------------------------"<<endl<<endl;
            cout<<"Agenda : ~$";
            OperationLoop();
        }
        else {
            cout<<"---------------------Agenda-------------------------"<<endl;
            cout<<"Action :"<<endl;
            cout<<"o   - log out Agenda"<<endl;
            cout<<"dc  - delete Agenda account"<<endl;
            cout<<"lu  - list all Agenda user"<<endl;
            cout<<"cm  - create a meeting"<<endl;
            cout<<"la  - list all meetings"<<endl;
            cout<<"las - list all sponsor meetings"<<endl;
            cout<<"lap - list all participate meetings"<<endl;
            cout<<"qm  - query meeting by title"<<endl;
            cout<<"qt  - query meeting by time interval"<<endl;
            cout<<"dm  - delete meeting by title"<<endl;
            cout<<"da  - delete all meetings"<<endl;
            cout<<"----------------------------------------------------"<<endl<<endl;
            cout<<"Agenda@"<<m_userName<<" : #";
            OperationLoop();
        }
    }

    string AgendaUI::getOperation(){
        string aa;
        cin>>aa;
        return aa;
    }

    bool AgendaUI::executeOperation(string t_operation){
        if(t_operation == "l") {
            userLogIn();
            return 1;
        }
        else if(t_operation == "r") {
            userRegister();
            return 1;
        }
        else if(t_operation == "q") {
            quitAgenda();
            return 1;
        }
        else if(t_operation == "o") {
            userLogOut();
            return 1;
        }
        else if(t_operation == "dc") {
            deleteUser();
            return 1;
        }
        else if(t_operation == "lu") {
            listAllUsers();
            return 1;
        }
        else if(t_operation == "cm") {
            createMeeting();
            return 1;
        }
        else if(t_operation == "la") {
            listAllMeetings();
            return 1;
        }
        else if(t_operation == "las") {
            listAllSponsorMeetings();
            return 1;
        }
        else if(t_operation == "lap") {
            listAllParticipateMeetings();
            return 1;
        }
        else if(t_operation == "qm") {
            queryMeetingByTitle();
            return 1;
        }
        else if(t_operation == "qt") {
            queryMeetingByTimeInterval();
            return 1;
        }
        else if(t_operation == "dm") {
            deleteMeetingByTitle();
            return 1;
        }
        else if(t_operation == "da") {
            deleteAllMeetings();
            return 1;
        }
        else return 0;
    }

    void AgendaUI::userLogIn(void){
        cout<<endl;
        if(m_userName.size() != 0) {
            cout<<"You have logged in!"<<endl;
            startAgenda();
        }
        else {
            cout<<"[log in] [user name] [password]"<<endl;
            cout<<"[log in]";
            cin>>m_userName;
            cin>>m_userPassword;
            if(m_agendaService.userLogIn(m_userName, m_userPassword)){
                cout<<"[log in] succeed!"<<endl;
            }
            else {
                cout<<"[error] log in fail!"<<endl;
                m_userName.clear();
            }
            startAgenda();
        }
    }

    void AgendaUI::userRegister(void){
        cout<<endl;
        if(m_userName.size() != 0) {
            cout<<"You can't register!"<<endl;
            startAgenda();
        }
        else {
            cout<<"[register] [user name] [password] [email] [phone]"<<endl;
            cout<<"[register]";
            string a, b, c, d;
            cin>>a;
            cin>>b;
            cin>>c;
            cin>>d;
            if(m_agendaService.userRegister(a, b, c, d)) {
                cout<<"[register] succeed!"<<endl;
            }
            else {
                cout<<"[register] register fail!"<<endl;
            }
            startAgenda();
        }
    }

    void AgendaUI::quitAgenda(void){
        m_agendaService.quitAgenda();
        cout<<endl;
        if(m_userName.size() != 0) {
            cout<<"You should log out!"<<endl;
            startAgenda();
        }
        else {
            cout<<"You have quited Agenda!"<<endl;
            exit(0);
        }
    }

    void AgendaUI::userLogOut(void){
        cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else {
            m_userName.clear();
            startAgenda();
        }
    }

    void AgendaUI::deleteUser(void){
        cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else {
            if(m_agendaService.deleteUser(m_userName, m_userPassword)) {
                cout<<"[delete agenda account] succeed!"<<endl;
                m_userName.clear();
                m_userPassword.clear();
                startAgenda();
            }
        }
    }

    void AgendaUI::listAllUsers(void){
        cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else {
            cout<<"[list all users]"<<endl;
            cout<<setw(10)<<"name"<<setw(15)<<"email"<<setw(15)<<"phone"<<endl;
            list<User> u = m_agendaService.listAllUsers();
            list<User>::iterator uit = u.begin();
            while(uit != u.end()) {
                cout<<setw(10)<<(*uit).getName()<<setw(15)<<(*uit).getEmail()<<setw(15)<<(*uit).getPhone()<<endl;
                uit++;
            }
            startAgenda();
        }
    }

    void AgendaUI::createMeeting(void){
         cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else{
            vector<string> participators2;
            cout<<"[create meeting] [the number of participators]"<<endl;
            cout<<"[create meeting] ";
            int n, i;
            cin>>n;
            cout<<endl;
            for(i = 1; i <= n; i++) {
                cout<<"[create meeting] [please enter the participator "<<i<<" ]"<<endl;
               cout<<"[create meeting] ";
               string aaa;
               cin>>aaa;
               participators2.push_back(aaa);
            }
          cout<<"[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"<<endl;
          cout<<"[create meeting] ";
          string bbb, ccc, ddd;
          cin>>bbb;
          cin>>ccc;
          cin>>ddd;
          if(m_agendaService.createMeeting(m_userName, bbb, ccc, ddd, participators2)){
            cout<<"[create meeting] succeed!"<<endl;
          }
          else {
            cout<<"[create meeting] error!"<<endl;
          }
          startAgenda();
        }
    }

    void AgendaUI::listAllMeetings(void){
        cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else {
            list<Meeting> m =m_agendaService.listAllMeetings(m_userName);
            if(m.size() == 0){
                cout<<"No meeting!"<<endl;
            }
            else {
                cout<<"[list all meetings]"<<endl;
                cout<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(20)<<"start time"<<setw(20)<<"end time"<<setw(15)<<"participators"<<endl;
                printMeetings(m);
            }
            startAgenda();
        }
    }

    void AgendaUI::listAllSponsorMeetings(void){
        cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else {
            list<Meeting> m =m_agendaService.listAllSponsorMeetings(m_userName);
            if(m.size() == 0){
                cout<<"No Sponsormeeting!"<<endl;
            }
            else {
                cout<<"[list all sponsor meetings]"<<endl;
                cout<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(20)<<"start time"<<setw(20)<<"end time"<<setw(15)<<"participators"<<endl;
                printMeetings(m);
            }
            startAgenda();
        }
    }

    void AgendaUI::listAllParticipateMeetings(void){
        cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else {
            list<Meeting> m =m_agendaService.listAllParticipateMeetings(m_userName);
            if(m.size() == 0){
                cout<<"No Participatormeeting!"<<endl;
            }
            else {
                cout<<"[list all participator meetings]"<<endl;
                cout<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(20)<<"start time"<<setw(20)<<"end time"<<setw(15)<<"participators"<<endl;
                printMeetings(m);
            }
            startAgenda();
        }
    }

    void AgendaUI::queryMeetingByTitle(void){
        cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else {
            cout<<"[query meeting] [title]"<<endl;
            cout<<"[]query meeting] ";
            string eee;
            cin>>eee;
            list<Meeting> m =m_agendaService.meetingQuery(m_userName, eee);
            if(m.size() == 0) {
                cout<<"No meeting!"<<endl;
            }
            else {
                cout<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(20)<<"start time"<<setw(20)<<"end time"<<setw(15)<<"participators"<<endl;
                list<Meeting>::iterator mit = m.begin();
                while(mit != m.end()) {
                    printMeetings(m);
                    mit++;
               }
            }
            startAgenda();
        }
    }

    void  AgendaUI::queryMeetingByTimeInterval(void){
        cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else {
            cout<<"[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"<<endl;
            cout<<"[query meeting] ";
            string st, en;
            cin>>st;
            cin>>en;
            cout<<endl;
            list<Meeting> m = m_agendaService.meetingQuery(m_userName, st, en);
            if(m.size() == 0) {
                cout<<"No meeting!"<<endl;
            }
            else {
                cout<<"[query meeting]"<<endl;
                cout<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(20)<<"start time"<<setw(20)<<"end time"<<setw(15)<<"participators"<<endl;
                printMeetings(m);
            }
            startAgenda();
        }
    }

    void AgendaUI::deleteMeetingByTitle(void){
        cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else {
            cout<<"[delete meeting] [title]"<<endl;
            cout<<"[delete meeting] ";
            string til;
            cin>>til;
            if(m_agendaService.deleteMeeting(m_userName, til)) {
                cout<<endl;
                cout<<"[delete meeting] succeed!"<<endl;
            }
            else {
                cout<<"[delete meeting] delete meeting fail!"<<endl;
            }
            startAgenda();
        }
    }

    void AgendaUI::deleteAllMeetings(void){
        cout<<endl;
        if(m_userName.size() == 0) {
            cout<<"You should log in first!"<<endl;
            startAgenda();
        }
        else {
            if(m_agendaService.deleteAllMeetings(m_userName)) {
                cout<<"[delete all meetings] succeed!"<<endl;
                startAgenda();
            }
            else {
                cout<<"[delete all meetings] fail!"<<endl;
                startAgenda();
            }
        }
    }

    void AgendaUI::printMeetings(list<Meeting> t_meetings){
        cout<<left;
        list<Meeting>::iterator mit = t_meetings.begin();
        while(mit != t_meetings.end()) {
            cout<<setw(15)<<(*mit).getTitle()<<setw(15)<<(*mit).getSponsor()<<setw(20)<<Date::dateToString((*mit).getStartDate())<<setw(20)<<Date::dateToString((*mit).getEndDate());
            vector<string> participators1 = mit->getParticipator();
            for(int j = 0; j < participators1.size(); j++) {
                cout<<participators1[j];
                if(j != participators1.size() - 1) cout<<",";
            }
            cout<<endl;
            mit++;
        }
        cout<<right;
    }


