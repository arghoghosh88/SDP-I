#include<bits/stdc++.h>
using namespace std;
class student
{
private:
    string student_name;
    int student_id;
    const string intake = "56";
    const string section = "5";
public:
    student()
    {

    }
    //Setting name and id of student with setter method
    void set_student_name(string name)
    {
        student_name = name;
    }
    void set_student_id(int id)
    {
        student_id = id;
    }
    //Getting name and id with getter method
    string get_student_name()
    {
        return student_name;
    }
    int get_student_id()
    {
        return student_id;
    }

    //Input and set Student details
    void Take_student_details()
    {
        string name;
        cout<<"Enter your name please : ";
        getline(cin,name);

        set_student_name(name);

        int id;
        cout<<"Enter your student ID : ";
        cin>>id;

        set_student_id(id);

    }

    // Showing student details
    void show_student_details()
    {
        cout<<"Student name : "<< student_name <<endl;
        cout<<"Student ID : "  << student_id   <<endl;
        cout<<"Intake : "      << intake       <<endl;
        cout<<"Section : "     <<section       <<endl;
    }
};

class Faculty
{

    private:
    string course;
    string faculty_name;
    string designation;
    string phone_num;
    string email;
    string desk;
     int mark;
    Faculty()
    {

    }
    void set_course(string c)
    {
        course = c;
    }
    string get_course()
    {
        return course;
    }
    void set_faculty_name(string n)
    {
        faculty_name = n;
    }
    string get_faculty_name()
    {
        return faculty_name;
    }
    void set_designation(string d)
    {
        designation = d;
    }
    string get_designation()
    {
        return designation;
    }
    void set_phone_number(string ph)
    {
        phone_num = ph;
    }
    string get_phone_number()
    {
        return phone_num;
    }
    void set_email(string e)
    {
        email = e;
    }
    string get_email()
    {
        return email;
    }
    void set_desk(string d)
    {
        desk = d;
    }
    string get_desk()
    {
        return desk;
    }
    void show_faculty_setails()
    {
        cout<<"Course : "<<course<<endl;
        cout<<"Faculty Name : "<<faculty_name<<endl;
        cout<<"E-Mail : "<<email<<endl;
        cout<<"Desk Info : "<<desk<<endl;
    }
    void set_daculty_info()
    {

        string course_name;
        cout<<"Enter course name : ";
        getline(cin, course_name);
        cin.ignore();


        set_course(course_name);

        string name;
        cout<<"Enter Faculty name : ";
        getline(cin, name);

        set_faculty_name(name);

        string deg;
        cout<<"Enter designation of the faculty : ";
        getline(cin,deg);

        set_designation(deg);

        string phone_N;
        cout<<"Enter Faculty's Phone number : ";
        cin>>phone_N;

        set_phone_number(phone_N);
        string email;
        cout<<"Enter faculty email : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(cin, email);

        set_email(email);

        string desk;
        cout<<"Enter the Desk of the faculty : ";
        getline(cin, desk);

        set_desk(desk);
    }
};
 void Routine()
    {
        time_t t;
        time(&t);
        tm *d = localtime(&t);
        cout<<"*************************************************"<<endl;
        cout<<"--------------Routine of CSE-56/5----------------"<<endl;
        cout<<"================================================="<<endl;


        string day[]= {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday",};
        if(day[d->tm_wday]=="Sunday")
        {
            cout<<"CSE-221"<<" "<<"[  9:45 Am - 11:15 Am]"<<" "<<"Room no: 710{B2}"<<endl;
            cout<<"================================================="<<endl;
            cout<<"EEE-211"<<" "<<"[ 11:15 Am - 12:45 Pm]"<<" "<<"Room no: 710{B2}"<<endl;

        }
        else if(day[d->tm_wday]=="Monday")
        {
            cout<<"CSE-222"<<" "<<"[  8:15 Am -  9:45 Am]"<<" "<<"Room no: 417{B2}"<<endl;
            cout<<"================================================="<<endl;
            cout<<"CSE-222"<<" "<<"[  9:45 Am - 11:15 Am]"<<" "<<"Room no: 417{B2}"<<endl;
            cout<<"================================================="<<endl;
            cout<<"EEE-211"<<" "<<"[ 11:15 Am - 12:45 Pm]"<<" "<<"Room no: 317{B2}"<<endl;
            cout<<"================================================="<<endl;
            cout<<"|----<Break>-----  [12:45 Pm - 1:15 Pm] --------|"<<endl;
            cout<<"================================================="<<endl;
            cout<<"CSE-215"<<" "<<"[  1:15 Pm -  2:45 Pm]"<<" "<<"Room no: 319{B2}"<<endl;
            cout<<"================================================="<<endl;
        }
        else if(day[d->tm_wday]=="Tuesday")
        {
            cout<<"EEE-212"<<" "<<"[ 11:15 Am - 12:45 Pm]"<<" "<<"Room no: 505{B3}"<<endl;
            cout<<"================================================="<<endl;
            cout<<"|----<Break>-----  [12:45 Pm - 1:15 Pm] --------|"<<endl;
            cout<<"================================================="<<endl;
            cout<<"EEE-212"<<" "<<"[  1:15 Pm -  2:45 Pm]"<<" "<<"Room no: 505{B3}"<<endl;
            cout<<"================================================="<<endl;
        }
        else if(day[d->tm_wday]=="Wednesday")
        {
            cout<<"CSE-221"<<" "<<"[ 1:15 Pm - 2:45 Pm]"<<" "<<"Room no: 906{B2}"<<endl;
            cout<<"================================================="<<endl;
            cout<<"MAT-221"<<" "<<"[ 2:45 Am - 4:15 Pm]"<<" "<<"Room no: 906{B2}"<<endl;
            cout<<"================================================="<<endl;
        }
        else if(day[d->tm_wday]=="Thursday")
        {
            cout<<"CSE-215"<<" "<<"[ 1:15 Pm - 2:45 Pm]"<<" "<<"Room no: 906{B2}"<<endl;
            cout<<"================================================="<<endl;
            cout<<"MAT-221"<<" "<<"[ 2:45 Am - 4:15 Pm]"<<" "<<"Room no: 906{B2}"<<endl;
            cout<<"================================================="<<endl;
        }
        else if(day[d->tm_wday]=="Saturday"||day[d->tm_wday]=="Friday")
        {
            cout<<"You have no class today!"<<endl;
            cout<<"================================================="<<endl;
            cout<<"Enjoy your day!"<<endl;
            cout<<"================================================="<<endl;
        }
        cout<<"*************************************************"<<endl;

    }
int main()
{
    Routine();
}
