// Header section
//#include<bits/stdc++.h>
#include<iostream>
#include<conio.h>
#include<ctime>
#include<cmath>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<map>
#include<sstream>
#include<algorithm>
#include<functional>
#include<limits>
//End of header section

using namespace std;

// ================= Forward Class Declarations =================

class student;
class Faculty;
class Admin;

// ================= Function Prototypes =================



void Log_in_menu();

void Student_Menu(student&);
void Faculty_Menu(Faculty&);

void copy_File(string file1, string file2);
void FixStudentNames(string filename);

bool isMarksGiven(const string&);
bool allMarksGiven();
bool isResultGiven(const string&);;

// Converting string to hashing;
string hashPassword(string password)
{
    hash<string> h;
    return to_string(h(password));
}

// ================= STUDENT CLASS =================

class student
{
private:
    string name;
    string id;
    const string intake = "56";
    const string section = "5";
public:
    int cse221 = 0;
    int cse222 = 0;
    int cse215 = 0;
    int eee221 = 0;
    int eee222 = 0;
    int mat221 = 0;

    student()
    {

    }
    void set_name(string n)
    {
        name = n;
    }
    string get_name()
    {
        return name;
    }
    void set_ID(string i)
    {
        id = i;
    }
    string get_ID()
    {
        return id;
    }

    //Setting student details

    void set_student_details()
    {
        string name;
        cout<<"Enter your name : ";
        getline(cin, name);

        set_name(name);

        string i;
        cout<<"Enter your ID : ";
        cin>>i;

        set_ID(i);

        //Setting student details to file..
        Save_StudentDetailsTo_file();
    }

    // Showing student details.
    void show_Student_details()
    {
        cout<<"Name : "<<name<<endl;
        cout<<"ID : "<<id<<endl;
        cout<<"Intake : "<<intake<<endl;
        cout<<"Section : "<<section<<endl;

    }
    void Save_StudentDetailsTo_file()
    {
        ofstream fout("Set_Student.txt", ios::app);

        fout << get_ID() << " " << get_name() << endl;

        fout.close();

        cout << "Name and ID Saved to file successfully!" << endl;
    }

    bool LoginfromFile_Student()
    {
        string sid;
        cout<<"Enter ID: ";
        cin>>sid;

        ifstream fin("Student.txt");
        string fid, fname;

        while(fin>>fid>>fname)
        {
            if(fid==sid)
            {
                id=fid;
                name=fname;
                fin.close();
                return true;
            }
        }

        fin.close();
        return false;
    }
    //Showing students CGPA if given

    void ShowCGPAResults(const string &filename = "SGPA_Result.txt")
    {
        ifstream fin(filename);

        if(!fin)
        {
            cout<<"CGPA file not found: "<<filename<<endl;
            return;
        }

        cout<<endl;
        cout<<"================================================="<<endl;
        cout<<"                 ALL STUDENT CGPA               "<<endl;
        cout<<"================================================="<<endl;

        cout<<left
            <<setw(15)<<"ID"
            <<setw(30)<<"Name"
            <<setw(10)<<"CGPA"<<endl;

        cout<<"-------------------------------------------------"<<endl;

        string line;

        // Skip header if there is one
        getline(fin,line);

        bool foundData = false;

        while(getline(fin,line))
        {
            if(line.empty())
            {
                continue;
            }

            stringstream ss(line);

            string student_id;
            string student_name;
            double cgpa;

            ss>>student_id;

            if(student_id.empty())
            {
                continue;
            }

            // Read name until the last numeric value (CGPA)
            vector<string> nameParts;
            string word;

            while(ss>>word)
            {
                try
                {
                    size_t pos;
                    double temp = stod(word,&pos);

                    // If entire word is a number, this is CGPA
                    if(pos == word.length())
                    {
                        cgpa = temp;
                        break;
                    }
                    else
                    {
                        nameParts.push_back(word);
                    }
                }
                catch(...)
                {
                    nameParts.push_back(word);
                }
            }

            if(nameParts.empty())
            {
                continue;
            }

            student_name = nameParts[0];

            for(int i=1; i<nameParts.size(); i++)
            {
                student_name += " ";
                student_name += nameParts[i];
            }

            cout<<left
                <<setw(15)<<student_id
                <<setw(30)<<student_name
                <<setw(10)<<fixed<<setprecision(2)<<cgpa
                <<endl;

            foundData = true;
        }

        cout<<"================================================="<<endl;

        if(!foundData)
        {
            cout<<"No CGPA result found!"<<endl;
        }

        fin.close();
    }


//    void ShowCGPAResults_Own(const string &filename = "CGPA_ThirdSemester.txt")
//    {
//        ifstream fin(filename);
//
//        if(!fin)
//        {
//            cout<<"CGPA file not found: "<<filename<<endl;
//            return;
//        }
//
//        string ownId;
//        cout<<"Enter your ID to see your CGPA"<<endl;
//        cout<<"ID : ";
//        cin>>ownId;
//
//        string id, name;
//        double cgpa;
//        bool found = false;
//
//        // setw() is used to set the minimum width for the next output value,
//        // so the table columns stay properly aligned.
//        cout<<left<<setw(12)<<"ID"
//            <<setw(25)<<"Name"
//            <<setw(8)<<"CGPA"<<endl;
//
//        cout<< "---------------------------------------------" << endl;
//
//        string header;
//        getline(fin, header);   // Skip the header line
//
//        while(fin >> id)
//        {
//            fin>>ws;
//            getline(fin,name,' ');
//
//            if(!(fin>>cgpa))
//            {
//                cout<<"Your CGPA is not found or not given."<<endl;
//                return;
//            }
//
//            if(id == ownId)
//            {
//                found = true;
//
//                cout<<left<<setw(12)<<id
//                    <<setw(25)<<name
//                    <<setw(8)<<fixed<<setprecision(2)<<cgpa
//                    <<endl;
//                break;
//            }
//        }
//
//        if(!found)
//        {
//            cout<<"Your ID was not found."<<endl;
//        }
//
//        fin.close();
//    }
    void ShowCGPAResults_Own(const string &filename = "SGPA_Result.txt")
    {
        ifstream fin(filename);

        if(!fin)
        {
            cout<<"CGPA file not found: "<<filename<<endl;
            return;
        }

        string ownId;

        cout<<endl;
        cout<<"=============================================="<<endl;
        cout<<"             VIEW PERSONAL CGPA               "<<endl;
        cout<<"=============================================="<<endl;

        cout<<"Enter your ID : ";
        cin>>ownId;

        string line;

        // Skip header
        getline(fin,line);

        bool found = false;

        while(getline(fin,line))
        {
            if(line.empty())
            {
                continue;
            }

            stringstream ss(line);

            string student_id;
            string student_name;
            double cgpa;

            ss>>student_id;

            if(student_id != ownId)
            {
                continue;
            }

            vector<string> nameParts;
            string word;

            while(ss>>word)
            {
                try
                {
                    size_t pos;
                    double temp = stod(word,&pos);

                    if(pos == word.length())
                    {
                        cgpa = temp;
                        break;
                    }
                    else
                    {
                        nameParts.push_back(word);
                    }
                }
                catch(...)
                {
                    nameParts.push_back(word);
                }
            }

            if(nameParts.empty())
            {
                cout<<"Your CGPA is not found or not given."<<endl;
                fin.close();
                return;
            }

            student_name = nameParts[0];

            for(int i=1; i<nameParts.size(); i++)
            {
                student_name += " ";
                student_name += nameParts[i];
            }

            cout<<endl;

            cout<<left
                <<setw(15)<<"ID"
                <<setw(30)<<"Name"
                <<setw(10)<<"CGPA"<<endl;

            cout<<"-------------------------------------------------"<<endl;

            cout<<left
                <<setw(15)<<student_id
                <<setw(30)<<student_name
                <<setw(10)<<fixed<<setprecision(2)<<cgpa
                <<endl;

            cout<<"================================================="<<endl;

            found = true;
            break;
        }

        if(!found)
        {
            cout<<endl;
            cout<<"Your ID was not found in the CGPA result!"<<endl;
        }

        fin.close();
    }
    void Today_Routine()
    {
        time_t t;
        time(&t);

        tm *d = localtime(&t);

        string day[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

        cout<<"*************************************************"<<endl;
        cout<<"--------------Routine of CSE-56/5----------------"<<endl;
        cout<<"*************************************************"<<endl;

        cout<<"Today is: "<<day[d->tm_wday]<<endl;
        cout<<"================================================="<<endl;

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

            cout<<"|----<Break>----- [12:45 Pm - 1:15 Pm] --------|"<<endl;

            cout<<"================================================="<<endl;

            cout<<"CSE-215"<<" "<<"[  1:15 Pm -  2:45 Pm]"<<" "<<"Room no: 319{B2}"<<endl;
        }

        else if(day[d->tm_wday]=="Tuesday")
        {
            cout<<"EEE-212"<<" "<<"[ 11:15 Am - 12:45 Pm]"<<" "<<"Room no: 505{B3}"<<endl;

            cout<<"================================================="<<endl;

            cout<<"|----<Break>----- [12:45 Pm - 1:15 Pm] --------|"<<endl;

            cout<<"================================================="<<endl;

            cout<<"EEE-212"<<" "<<"[  1:15 Pm -  2:45 Pm]"<<" "<<"Room no: 505{B3}"<<endl;
        }

        else if(day[d->tm_wday]=="Wednesday")
        {
            cout<<"CSE-221"<<" "<<"[  1:15 Pm - 2:45 Pm]"<<" "<<"Room no: 906{B2}"<<endl;

            cout<<"================================================="<<endl;

            cout<<"MAT-221"<<" "<<"[  2:45 Pm - 4:15 Pm]"<<" "<<"Room no: 906{B2}"<<endl;
        }

        else if(day[d->tm_wday]=="Thursday")
        {
            cout<<"CSE-215"<<" "<<"[  1:15 Pm - 2:45 Pm]"<<" "<<"Room no: 906{B2}"<<endl;

            cout<<"================================================="<<endl;

            cout<<"MAT-221"<<" "<<"[  2:45 Pm - 4:15 Pm]"<<" "<<"Room no: 906{B2}"<<endl;
        }

        else if(day[d->tm_wday]=="Friday"||day[d->tm_wday]=="Saturday")
        {
            cout<<"You have no class today!"<<endl;

            cout<<"================================================="<<endl;

            cout<<"Enjoy your day!"<<endl;
        }

        cout<<"================================================="<<endl;
        cout<<"*************************************************"<<endl;
    }
    void Total_week_Routine()
    {
        cout<<"*************************************************"<<endl;
        cout<<"--------------Routine of CSE-56/5----------------"<<endl;
        cout<<"*************************************************"<<endl;

        cout<<"--------------------Sunday-----------------------"<<endl;
        cout<<"CSE-221"<<" "<<"[  9:45 Am - 11:15 Am]"<<" "<<"Room no: 710{B2}"<<endl;
        cout<<"================================================="<<endl;
        cout<<"EEE-211"<<" "<<"[ 11:15 Am - 12:45 Pm]"<<" "<<"Room no: 710{B2}"<<endl;

        cout<<"*************************************************"<<endl;

        cout<<"--------------------Monday-----------------------"<<endl;
        cout<<"CSE-222"<<" "<<"[  8:15 Am -  9:45 Am]"<<" "<<"Room no: 417{B2}"<<endl;
        cout<<"================================================="<<endl;
        cout<<"CSE-222"<<" "<<"[  9:45 Am - 11:15 Am]"<<" "<<"Room no: 417{B2}"<<endl;
        cout<<"================================================="<<endl;
        cout<<"EEE-211"<<" "<<"[ 11:15 Am - 12:45 Pm]"<<" "<<"Room no: 317{B2}"<<endl;
        cout<<"================================================="<<endl;
        cout<<"|----<Break>----- [12:45 Pm - 1:15 Pm] --------|"<<endl;
        cout<<"================================================="<<endl;
        cout<<"CSE-215"<<" "<<"[  1:15 Pm -  2:45 Pm]"<<" "<<"Room no: 319{B2}"<<endl;

        cout<<"*************************************************"<<endl;

        cout<<"--------------------Tuesday----------------------"<<endl;
        cout<<"EEE-212"<<" "<<"[ 11:15 Am - 12:45 Pm]"<<" "<<"Room no: 505{B3}"<<endl;
        cout<<"================================================="<<endl;
        cout<<"|----<Break>----- [12:45 Pm - 1:15 Pm] --------|"<<endl;
        cout<<"================================================="<<endl;
        cout<<"EEE-212"<<" "<<"[  1:15 Pm -  2:45 Pm]"<<" "<<"Room no: 505{B3}"<<endl;

        cout<<"*************************************************"<<endl;

        cout<<"-------------------Wednesday---------------------"<<endl;
        cout<<"CSE-221"<<" "<<"[  1:15 Pm - 2:45 Pm]"<<" "<<"Room no: 906{B2}"<<endl;
        cout<<"================================================="<<endl;
        cout<<"MAT-221"<<" "<<"[  2:45 Pm - 4:15 Pm]"<<" "<<"Room no: 906{B2}"<<endl;

        cout<<"*************************************************"<<endl;

        cout<<"--------------------Thursday---------------------"<<endl;
        cout<<"CSE-215"<<" "<<"[  1:15 Pm - 2:45 Pm]"<<" "<<"Room no: 906{B2}"<<endl;
        cout<<"================================================="<<endl;
        cout<<"MAT-221"<<" "<<"[  2:45 Pm - 4:15 Pm]"<<" "<<"Room no: 906{B2}"<<endl;

        cout<<"*************************************************"<<endl;

        cout<<"----------------------Friday---------------------"<<endl;
        cout<<"You have no class!"<<endl;
        cout<<"================================================="<<endl;
        cout<<"Enjoy your day!"<<endl;

        cout<<"*************************************************"<<endl;

        cout<<"--------------------Saturday---------------------"<<endl;
        cout<<"You have no class!"<<endl;
        cout<<"================================================="<<endl;
        cout<<"Enjoy your day!"<<endl;

        cout<<"*************************************************"<<endl;
    }
};


// ================= FACULTY CLASS =================
class Faculty
{
private:
    string course;
    string faculty_name;
    string designation;
    string phone_num;
    string E_Mail;
    string Desk;
public:
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
    void set_PhoneNumber(string ph)
    {
        phone_num = ph;
    }
    string get_phoneNumber()
    {
        return phone_num;
    }
    void set_email(string e)
    {
        E_Mail = e;
    }
    string get_email()
    {
        return E_Mail;
    }
    void set_Desk(string d)
    {
        Desk = d;
    }
    string get_Desk()
    {
        return Desk;
    }

    // Checking the phone number is valid or not

    bool isValidPhone(string phone_N)
    {
        if(phone_N.length()!=11)
        {
            return false;
        }

        if(phone_N[0]!='0' || phone_N[1]!='1')
        {
            return false;
        }

        for(int i=0; i<phone_N.length(); i++)
        {
            if(phone_N[i]<'0' || phone_N[i]>'9')
            {
                return false;
            }
        }

        return true;
    }

// Checking the email is valid or not

    bool isValidEmail(string email)
    {
        int at = email.find('@');
        int dot = email.find('.',at);

        if(at==string::npos || dot==string::npos)
        {
            return false;
        }

        if(at==0 || dot==at+1 || dot==email.length()-1)
        {
            return false;
        }

        if(email.find('@',at+1)!=string::npos)
        {
            return false;
        }

        if(email.find("..")!=string::npos)
        {
            return false;
        }

        return true;
    }

// Setting faculty info

    void set_Faculty_Info()
    {
        int chance = 0;

        try
        {
            // Course Name
            string Course_name;

            while(chance<3)
            {
                cout<<"Enter course name : ";
                getline(cin,Course_name);

                if(Course_name.empty())
                {
                    chance++;
                    cout<<"Invalid course name! Chance left: "<<3-chance<<endl;
                }
                else
                {
                    break;
                }
            }

            if(chance==3)
            {
                throw "Maximum attempts exceeded!";
            }

            set_course(Course_name);


            // Faculty Name
            chance = 0;

            string name;

            while(chance<3)
            {
                cout<<"Enter Faculty name : ";
                getline(cin,name);

                if(name.empty())
                {
                    chance++;
                    cout<<"Invalid faculty name! Chance left: "<<3-chance<<endl;
                }
                else
                {
                    break;
                }
            }

            if(chance==3)
            {
                throw "Maximum attempts exceeded!";
            }

            set_faculty_name(name);


            // Designation
            chance = 0;

            string deg;

            while(chance<3)
            {
                cout<<"Enter designation of the faculty : ";
                getline(cin,deg);

                if(deg.empty())
                {
                    chance++;
                    cout<<"Invalid designation! Chance left: "<<3-chance<<endl;
                }
                else
                {
                    break;
                }
            }

            if(chance==3)
            {
                throw "Maximum attempts exceeded!";
            }

            set_designation(deg);


            // Phone Number
            chance = 0;

            string phone_N;

            while(chance<3)
            {
                cout<<"Enter Faculty's Phone number : ";
                cin>>phone_N;

                if(!isValidPhone(phone_N))
                {
                    chance++;
                    cout<<"Invalid phone number!"<<endl;
                    cout<<"Phone number must start with 01 and contain 11 digits."<<endl;
                    cout<<"Chance left: "<<3-chance<<endl;
                }
                else
                {
                    break;
                }
            }

            if(chance==3)
            {
                throw "Maximum attempts exceeded!";
            }

            set_PhoneNumber(phone_N);


            // Email
            chance = 0;

            string email;

            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            while(chance<3)
            {
                cout<<"Enter faculty email : ";
                getline(cin,email);

                if(!isValidEmail(email))
                {
                    chance++;
                    cout<<"Invalid email format!"<<endl;
                    cout<<"Chance left: "<<3-chance<<endl;
                }
                else
                {
                    break;
                }
            }

            if(chance==3)
            {
                throw "Maximum attempts exceeded!";
            }

            set_email(email);


            // Desk
            chance = 0;

            string desk;

            while(chance<3)
            {
                cout<<"Enter the Desk of the faculty : ";
                getline(cin,desk);

                if(desk.empty())
                {
                    chance++;
                    cout<<"Invalid desk!"<<endl;
                    cout<<"Chance left: "<<3-chance<<endl;
                }
                else
                {
                    break;
                }
            }

            if(chance==3)
            {
                throw "Maximum attempts exceeded!";
            }

            set_Desk(desk);

            // Saving faculty information to file....

            Save_Faculty_Info_To_File();

            cout<<"Faculty information saved successfully!"<<endl;
        }

        catch(const char* error)
        {
            cout<<"Error : "<<error<<endl;
        }

    }

    void Save_Faculty_Info_To_File()
    {
        ofstream fout("Faculty_info.txt",ios::app);

        if(!fout)
        {
            cout<<"File could not be opened!"<<endl;
            return;
        }

        fout<<"Course : "<<get_course()<<endl;
        fout<<"Faculty Name : "<<get_faculty_name()<<endl;
        fout<<"Designation : "<<get_designation()<<endl;
        fout<<"Phone Number : "<<get_phoneNumber()<<endl;
        fout<<"Email : "<<get_email()<<endl;
        fout<<"Desk : "<<get_Desk()<<endl;

        fout<<"================================================="<<endl;

        fout.close();

        cout<<"Faculty information saved successfully!"<<endl;
    }

    // Showing faculty information...
    void Show_Faculty_Details()
    {
        cout<<"Course : "      <<course      <<endl;
        cout<<"Faculty Name : "<<faculty_name<<endl;
        cout<<"E-Mail : "      <<E_Mail      <<endl;
        cout<<"Desk Info : "   <<Desk        <<endl;
    }

//    void Enter_to_Marksfile()
//    {
//        cout<<"Give course code .|."<<endl;
//        cout<<"You have 3 attempts only !"<<endl;
//
//        cout<<endl;
//        cout<<"Be aware for this : "<<endl;
//        cout<<"Course code format : 'XYZ-123' "<<endl;
//
//        int chance = 0;
//
//        string course_code;
//
//        while(chance < 3)
//        {
//            cout<<"Attempts Left : "<<3-chance<<endl;
//
//            cout<<"Enter Course Code : ";
//            getline(cin,course_code);
//
//            try
//            {
//                if(course_code.length() != 7)
//                {
//                    throw "Length must be 7";
//                }
//
//                if(!isupper(course_code[0]) ||
//                        !isupper(course_code[1]) ||
//                        !isupper(course_code[2]))
//                {
//                    throw "First 3 characters must be capital!";
//                }
//
//                if(course_code[3] != '-')
//                {
//                    throw "4th character must be '-' ";
//                }
//
//                if(!isdigit(course_code[4]) ||
//                        !isdigit(course_code[5]) ||
//                        !isdigit(course_code[6]))
//                {
//                    throw "Last 3 characters must be digit!";
//                }
//
//                cout<<"Course code is valid!"<<endl;
//
//                cout<<"Enter the course password now  "<<endl;
//
//                cout<<"Enter Password : ";
//
//                string password;
//
//                char ch;
//
//                while((ch = _getch()) != '\r')
//                {
//                    password += ch;
//                    cout<<"$";
//                }
//                cout<<endl;
//
//                ifstream course_pass("Course&Password");
//
//                if(!course_pass)
//                {
//                    throw "Course password file not found!";
//                }
//
//                string stored_course;
//                string stored_pass;
//
//                bool found = false;
//                while(course_pass>>stored_course>>stored_pass)
//                {
//                    if(course_code == stored_course)
//                    {
//                        found = true;
//                        if(hashPassword(password) == stored_pass)
//                        {
//                            course_pass.close();
//
//                            Enter_course_marks();
//
//                            return;
//                        }
//                        else
//                        {
//                            throw "Invalid Password";
//                        }
//                    }
//                }
//
//                if(!found)
//                {
//                    cout<<"Set your course code ans password then try again <..>"<<endl;
//                    Set_Course_Password();
//                }
//
//                course_pass.close();
//
//                throw "Course code not found!";
//            }
//            catch(const char* error)
//            {
//                cout<<"Error! "<<error<<endl;
//                cout<<"Try Again"<<endl;
//
//                chance++;
//            }
//        }
//
//        if(chance == 3)
//        {
//            cout<<"Maximum attempt exceeded!"<<endl;
//        }
//    }
//
//    void Enter_course_marks()
//    {
//
//    }

    void Enter_to_Marksfile()
    {
        cout<<"Give course code .|."<<endl;
        cout<<"You have 3 attempts only !"<<endl;

        cout<<endl;
        cout<<"Be aware for this : "<<endl;
        cout<<"Course code format : 'XYZ-123' "<<endl;

        int chance = 0;

        string course_code;

        while(chance < 3)
        {
            cout<<"Attempts Left : "<<3-chance<<endl;

            cout<<"Enter Course Code : ";
            getline(cin,course_code);

            try
            {
                if(course_code.length() != 7)
                {
                    throw "Length must be 7";
                }

                if(!isupper(course_code[0]) ||
                        !isupper(course_code[1]) ||
                        !isupper(course_code[2]))
                {
                    throw "First 3 characters must be capital!";
                }

                if(course_code[3] != '-')
                {
                    throw "4th character must be '-' ";
                }

                if(!isdigit(course_code[4]) ||
                        !isdigit(course_code[5]) ||
                        !isdigit(course_code[6]))
                {
                    throw "Last 3 characters must be digit!";
                }

                cout<<"Course code is valid!"<<endl;

                ifstream course_pass("Course&Password.txt");

                if(!course_pass)
                {
                    throw "Course password file not found!";
                }

                string stored_course;
                string stored_pass;

                bool found = false;

                while(course_pass>>stored_course>>stored_pass)
                {
                    if(course_code == stored_course)
                    {
                        found = true;

                        cout<<"Enter the course password now  "<<endl;

                        cout<<"Enter Password : ";

                        string password;

                        char ch;

                        while((ch = _getch()) != '\r')
                        {
                            password += ch;
                            cout<<"$";
                        }

                        cout<<endl;

                        if(hashPassword(password) == stored_pass)
                        {
                            course_pass.close();

                            Enter_course_marks(course_code);

                            return;
                        }
                        else
                        {
                            course_pass.close();

                            throw "Invalid Password";
                        }
                    }
                }

                course_pass.close();

                if(!found)
                {
                    cout<<"Course code not found!"<<endl;
                    cout<<"This course has not been set by Admin yet!"<<endl;

                    throw "Course not found";
                }
            }

            catch(const char* error)
            {
                cout<<"Error! "<<error<<endl;
                cout<<"Try Again"<<endl;

                chance++;
            }
        }

        if(chance == 3)
        {
            cout<<"Maximum attempt exceeded!"<<endl;
        }
    }


//    void Set_Course_Password()
//    {
//        ofstream fout("Course&Password.txt",ios::app);
//
//        if(!fout)
//        {
//            cout<<"File could not Find or opened!"<<endl;
//            return;
//        }
//        cout<<"Enter Course Name : ";
//        string course_name;
//        getline(cin,course_name);
//
//        cout<<"Enter the course Password : ";
//        string password;
//        string temp_password;
//
//        char ch;
//
//        while((ch = _getch()) != '\r')
//        {
//            temp_password += ch;
//            cout<<"*";
//        }
//        cout<<endl;
//
//        cout<<"Confirm the password!"<<endl;
//        cout<<"3 Attempts only!"<<endl;
//
//        int attempt = 3;
//        string confirmed_password;
//
//        while(attempt>0)
//        {
//            cout<<"Enter Password Again : ";
//
//            char ch;
//            while((ch =_getch())!='\r')
//            {
//                confirmed_password += ch;
//                cout<<".";
//
//            }
//            if(temp_password == confirmed_password)
//            {
//                password = confirmed_password;
//                break;
//            }
//            attempt--;
//
//            cout<<"Invalid Password!"<<endl;
//            cout<<"Try Again!"<<endl;
//
//            cout<<"Chance Remaining : "<<attempt<<endl;
//
//
//
//        }
//
//        password = hashPassword(password);
//
//        fout<<course_name<<" "<<password<<endl;
//
//        fout<<"================================================="<<endl;
//
//        fout.close();
//
//        cout<<endl;
//
//        cout<<"Course name and Password are saved successfully!"<<endl;
//    }

    void Enter_course_marks(string course_code)
    {
        cout<<endl;
        cout<<"=============================================="<<endl;
        cout<<"              ENTER COURSE MARKS              "<<endl;
        cout<<"=============================================="<<endl;

        string student_id;
        int total_marks;

        cout<<"Course Code : "<<course_code<<endl;

        cout<<endl;

        cout<<"Enter Student ID : ";
        cin>>student_id;

        if(student_id.length() != 11)
        {
            cout<<"Invalid Student ID!"<<endl;
            return;
        }

        for(char ch : student_id)
        {
            if(!isdigit(ch))
            {
                cout<<"Invalid Student ID!"<<endl;
                return;
            }
        }

        cout<<"Enter Total Marks : ";
        cin>>total_marks;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');

            cout<<"Invalid Marks!"<<endl;
            return;
        }

        if(total_marks < 0 || total_marks > 100)
        {
            cout<<"Marks must be between 0 and 100!"<<endl;
            return;
        }

        cin.ignore(1000,'\n');

        string filename = course_code + ".txt";

        ifstream check_file(filename);

        if(!check_file)
        {
            cout<<"Course file not found!"<<endl;
            cout<<"Please contact Admin."<<endl;

            return;
        }

        check_file.close();

        ofstream fout(filename,ios::app);

        if(!fout)
        {
            cout<<"Course file could not be opened!"<<endl;
            return;
        }

        fout<<student_id<<" "<<total_marks<<endl;

        fout.close();

        cout<<endl;
        cout<<"Marks saved successfully!"<<endl;

        cout<<"Student ID : "<<student_id<<endl;
        cout<<"Course Code : "<<course_code<<endl;
        cout<<"Total Marks : "<<total_marks<<endl;
    }

    void Set_Course_Password()
    {
        ofstream fout("Course&Password.txt",ios::app);

        if(!fout)
        {
            cout<<"File could not Find or opened!"<<endl;
            return;
        }

        cout<<"Enter Course Code : ";

        string course_code;

        getline(cin,course_code);

        cout<<"Enter the course Password : ";

        string password;
        string temp_password;

        char ch;

        while((ch = _getch()) != '\r')
        {
            temp_password += ch;
            cout<<"*";
        }

        cout<<endl;

        cout<<"Confirm the password!"<<endl;
        cout<<"3 Attempts only!"<<endl;

        int attempt = 3;

        string confirmed_password;

        bool matched = false;

        while(attempt > 0)
        {
            confirmed_password.clear();

            cout<<"Enter Password Again : ";

            while((ch = _getch()) != '\r')
            {
                confirmed_password += ch;
                cout<<".";
            }

            cout<<endl;

            if(temp_password == confirmed_password)
            {
                matched = true;
                break;
            }

            attempt--;

            cout<<"Invalid Password!"<<endl;

            if(attempt > 0)
            {
                cout<<"Try Again!"<<endl;
                cout<<"Chance Remaining : "<<attempt<<endl;
            }
        }

        if(!matched)
        {
            cout<<"Maximum attempt exceeded!"<<endl;

            fout.close();

            return;
        }

        password = hashPassword(confirmed_password);

        fout<<course_code<<" "<<password<<endl;

        fout.close();

        cout<<endl;

        cout<<"Course code and Password are saved successfully!"<<endl;
    }

};


// ================= ADMIN CLASS =================

class Admin : public student,public Faculty
{
public:

    string Calculate_Grade(int marks)
    {
        if(marks >= 80)
        {
            return "A+";
        }
        else if(marks >= 75)
        {
            return "A";
        }
        else if(marks >= 70)
        {
            return "A-";
        }
        else if(marks >= 65)
        {
            return "B+";
        }
        else if(marks >= 60)
        {
            return "B";
        }
        else if(marks >= 55)
        {
            return "B-";
        }
        else if(marks >= 50)
        {
            return "C+";
        }
        else if(marks >= 45)
        {
            return "C";
        }
        else if(marks >= 40)
        {
            return "D";
        }
        else
        {
            return "F";
        }
    }
    void Calculate_Grade_point()
    {

        cout<<"=============================================="<<endl;
        cout<<"              Generate Result                 "<<endl;
        cout<<"=============================================="<<endl;

        cout<<"Enter Course Code : ";

        string course_code;

        getline(cin,course_code);

        string course_file = course_code + ".txt";

        ifstream fin(course_file);

        if(!fin)
        {
            cout<<"Course file not found!"<<endl;
            return;
        }

        string result_file = course_code + "_Result.txt";

        ofstream fout(result_file);

        if(!fout)
        {
            cout<<"Result file could not be opened!"<<endl;

            fin.close();

            return;
        }

        string student_id;
        int marks;

        while(fin>>student_id>>marks)
        {
            string student_name = "Unknown";

            ifstream student_file("Student.txt");

            if(student_file)
            {
                string stored_id;
                string stored_name;

                while(student_file>>stored_id>>stored_name)
                {
                    if(student_id == stored_id)
                    {
                        student_name = stored_name;

                        break;
                    }
                }

                student_file.close();
            }

            string grade = Calculate_Grade(marks);

            fout<<student_id<<" "
                <<student_name<<" "
                <<grade<<endl;
        }

        fin.close();

        fout.close();

        cout<<endl;

        cout<<"Result generated successfully!"<<endl;

        cout<<"Course Code : "<<course_code<<endl;

        cout<<"Result File : "<<result_file<<endl;
    }

    double Grade_Point(string grade)
    {
        if(grade == "A+")
        {
            return 4.00;
        }
        else if(grade == "A")
        {
            return 3.75;
        }
        else if(grade == "A-")
        {
            return 3.50;
        }
        else if(grade == "B+")
        {
            return 3.25;
        }
        else if(grade == "B")
        {
            return 3.00;
        }
        else if(grade == "B-")
        {
            return 2.75;
        }
        else if(grade == "C+")
        {
            return 2.50;
        }
        else if(grade == "C")
        {
            return 2.25;
        }
        else if(grade == "D")
        {
            return 2.00;
        }
        else
        {
            return 0.00;
        }
    }
    void Generate_SGPA_Result()
    {
        cout<<endl;
        cout<<"=============================================="<<endl;
        cout<<"             GENERATE SGPA RESULT             "<<endl;
        cout<<"=============================================="<<endl;

        string course_name[] =
        {
            "CSE-221",
            "CSE-222",
            "EEE-221",
            "EEE-222",
            "MAT-221",
            "CSE-215",
            "CSE-100"
        };

        double credit[] =
        {
            3.00,
            1.50,
            3.00,
            1.50,
            3.00,
            3.00,
            0.75
        };

        int course_count = 7;

        string student_id[100];
        string student_name[100];

        string grades[100][7];

        int student_count = 0;

        // ================= READ ALL RESULT FILES =================

        for(int i=0; i<course_count; i++)
        {
            string filename = course_name[i] + "_Result.txt";

            ifstream fin(filename);

            if(!fin)
            {
                cout<<filename<<" not found!"<<endl;
                continue;
            }

            string id;
            string name;
            string grade;

            while(fin>>id>>name>>grade)
            {
                int index = -1;

                // Search existing student
                for(int j = 0; j < student_count; j++)
                {
                    if(student_id[j] == id)
                    {
                        index = j;
                        break;
                    }
                }

                // New student
                if(index == -1)
                {
                    index = student_count;

                    student_id[index] = id;
                    student_name[index] = name;

                    for(int j = 0; j < course_count; j++)
                    {
                        grades[index][j] = "";
                    }

                    student_count++;
                }

                grades[index][i] = grade;
            }

            fin.close();
        }

        // ================= CREATE SGPA FILE =================

        ofstream fout("SGPA_Result.txt");

        if(!fout)
        {
            cout<<"SGPA Result file could not be opened!"<<endl;
            return;
        }

        // ================= CALCULATE SGPA =================

        for(int i = 0; i < student_count; i++)
        {
            bool failed = false;

            double total_grade_point = 0;

            double total_credit = 0;

            for(int j = 0; j < course_count; j++)
            {
                // Course result missing
                if(grades[i][j] == "")
                {
                    failed = true;
                    break;
                }

                // If student has F
                if(grades[i][j] == "F")
                {
                    failed = true;
                    break;
                }

                double point = Grade_Point(grades[i][j]);

                total_grade_point =
                    total_grade_point + (credit[j] * point);

                total_credit =
                    total_credit + credit[j];
            }

            // If any course has F or result missing
            if(failed)
            {
                continue;
            }

            double sgpa = total_grade_point / total_credit;

            fout<<student_name[i]<<" "
                <<student_id[i]<<" "
                <<fixed<<setprecision(2)
                <<sgpa<<endl;
        }

        fout.close();

        cout<<endl;
        cout<<"SGPA Result generated successfully!"<<endl;
        cout<<"File Name : SGPA_Result.txt"<<endl;
    }
//    void Admin_Menu()
//    {
//        int choice;
//        while(true)
//        {
//            cout << "\n====== ADMIN MENU ======\n";
//            cout<<"0. EXIT"<<endl;
//            cout<<"1. Mange Students "<<endl;
//            cout<<"2. Manage Faculty "<<endl;
//            cout<<"3. Manage Courses "<<endl;
//            cout<<"5. Marks Management"<<endl;
//            cout<<"6. Result Management"<<endl;
//
//            cout<<"---------------------------------"<<endl;
//            cout<<endl<<"Enter your choice : ";
//
//            cin>>choice;
//
//            switch(choice)
//            {
//            case 0:
//                return;
//
//            case 1:
//                manage_students();
//                break;
//
//            case 2:
//                manage_faculty();
//                break;
//
//            case 3:
//                manage_courses();
//                break;
//
//            case 4:
//                marks_managements();
//                break;
//
//            case 5:
//                result_managements();
//                break;
//
//            default:
//                cout<<"Invalid Input!!"<<endl;
//            }
//        }
//    }

void Admin_Menu()
{
    int choice;

    while(true)
    {
        cout<<endl;
        cout<<"=============================================="<<endl;
        cout<<"                 ADMIN MENU                   "<<endl;
        cout<<"=============================================="<<endl;

        cout<<"0. EXIT"<<endl;
        cout<<"1. Set Course Password"<<endl;
        cout<<"2. Set Course File"<<endl;
        cout<<"3. Generate Course Result"<<endl;
        cout<<"4. Generate SGPA Result"<<endl;

        cout<<"----------------------------------------------"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;

        switch(choice)
        {
        case 0:
            cout<<"Exiting Admin Panel..."<<endl;
            return;

        case 1:
            cin.ignore();
            Set_Course_Password();
            break;

        case 2:
            cin.ignore();
            set_course_files();
            break;

        case 3:
            cin.ignore();
            Calculate_Grade_point();
            break;

        case 4:
            Generate_SGPA_Result();
            break;

        default:
            cout<<"Invalid Choice!!"<<endl;
            cout<<"Try Again."<<endl;
        }
    }
}
    void add_student()
    {

    }
    void search_student()
    {

    }
    void  update_student()
    {

    }
    void delete_student()
    {

    }
    void view_all_students()
    {

    }
    void manage_students()
    {
        int choice;



        while(true)
        {

            cout<<"======< Manage Students >======"<<endl;

            cout<<"0. Exit "<<endl;

            cout<<"1. Add Student"<<endl;

            cout<<"2. Search Student"<<endl;

            cout<<"3. Update Student"<<endl;

            cout<<"4. Delete Student"<<endl;

            cout<<"5. View All Students"<<endl;

            cout<<"Enter your choice : ";

            cin>>choice;

            switch(choice)
            {
            case 0:
                return;
            case 1:
                add_student();
                break;
            case 2:
                search_student();
                break;
            case 3:
                update_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                view_all_students();
                break;
            default:
                cout<<"Invalid choice!!!"<<endl;
            }

        }
    }
    void add_faculty()
    {

    }

    void update_faculty()
    {


    }

    void delete_faculty()
    {

    }

    void view_all_faculty()
    {

    }


    void  manage_faculty()
    {
        int choice;

        while(true)
        {
            cout<<"======< MANAGE FACULTY >======"<<endl;

            cout<<"0. EXIT"<<endl;

            cout<<"1. Add Faculty"<<endl;

            cout<<"2. Update Faculty"<<endl;

            cout<<"3. Delete Faculty"<<endl;

            cout<<"4. View All Faculty"<<endl;

            cout<<"Enter your choice : ";

            cin>>choice;

            switch(choice)
            {
            case 0:
                return;

            case 1:
                add_faculty();
                break;

            case 2:
                update_faculty();
                break;

            case 3:
                delete_faculty();
                break;

            case 4:
                view_all_faculty();
                break;

            default:
                cout<<"Invalid Choice!!"<<endl;
                cout<<"Try Again"<<endl;

            }
        }
    }


    void add_course()
    {


    }

    void search_course()
    {


    }

    void update_course()
    {

    }

    void delete_course()
    {


    }

    void view_all_courses()
    {

    }


    void manage_courses()
    {
        int choice;

        while(true)
        {


            cout<<"======< MANAGE COURSES >======="<<endl;

            cout<<"0. EXIT"<<endl;

            cout<<"1. Add Course"<<endl;

            cout<<"2. Search Course"<<endl;

            cout<<"3. Update Course"<<endl;

            cout<<"4. Delete course"<<endl;

            cout<<"5. View All courses "<<endl;

            switch(choice)
            {
            case 0:
                return;

            case 1:
                add_course();
                break;

            case 2:
                search_course();
                break;

            case 3:
                update_course();
                break;

            case 4:
                delete_course();
                break;

            case 5:
                view_all_courses();
                break;

            default:
                cout<<"Invalid Choice<..>"<<endl;


            }
        }
    }


    void marks_managements()
    {
        int choice;

        while(true)
        {

            cout<<"0. EXIT"<<endl;

            cout<<"1. View Marks"<<endl;

            cout<<"2. Update Marks"<<endl;

            cout<<"3. Delete Marks"<<endl;

            cout<<"4. Search Student Result"<<endl;


            cout<<"Enter Your Choice : ";
            cin>>choice;


            switch(choice)
            {
            case 0:
                return;

            case 1:
                view_marks();
                break;

            case 2:
                update_marks();
                break;

            case 3:
                delete_marks();
                break;

            case 4:
                search_student_result();
                break;

            default:
                cout<<"Invalid Choice!!"<<endl;


            }
        }
    }

    void view_marks()
    {

    }

    void update_marks()
    {


    }

    void delete_marks()
    {

    }

    void search_student_result()
    {

    }


    void result_managements()
    {

        int choice;

        while(true)
        {

            cout<<"==========< RESULT MANAGEMENT >========="<<endl;

            cout<<"0. EXIT"<<endl;

            cout<<"1. View Course Result"<<endl;

            cout<<"2. Calculate SGPA"<<endl;

            cout<<"3. View Pass/Fail Statistics"<<endl;

            cout<<"Enter your choice : ";

            cin>>choice;

            switch(choice)
            {
            case 0:
                return;

            case 1:
                view_course_result();
                break;

            case 2:
                calculate_sgpa();
                break;

            case 3:
                view_pass_fail();
                break;

            default:
                cout<<"Invalid choice"<<endl;

            }
        }
    }


    void view_course_result()
    {

    }


    void calculate_sgpa()
    {

    }


    void view_pass_fail()
    {


    }


    void set_course_files()
    {
        cout<<"Enter course name to create the file for course teacher "<<endl;

        string course_name;

        cout<<"Enter course code : ";

        getline(cin,course_name);

        ifstream student_file("Student.txt");

        string file_name = course_name + ".txt";

        ofstream course_file(file_name);

        if(!student_file)
        {
            cout<<"File not found !"<<endl;
            return;
        }

        if(!course_file)
        {
            cout<<"Course file could not be created !"<<endl;
            return;
        }

        string line;

        course_file<<"The students of "<<course_name<<endl;

        while(getline(student_file,line))
        {
            course_file<<line<<endl;
        }

        student_file.close();
        course_file.close();

        cout<<"Course file set successfully!"<<endl;
    }
    void Admin_log_in()
    {
        string username, password;
        string storedUsername, storedPassword;

        ifstream file("Admin.txt");

        if(!(file >> storedUsername >> storedPassword))
        {
            file.close();
            cout<<"Enter Admin Username: ";
            cin>>username;
            cout<<"Enter Password: ";
            string temp_pass;

            char ch;

            while((ch = _getch()) != '\r')
            {
                temp_pass += ch;
                cout<<"*";
            }
            cout<<endl;

            cout<<"You have 3 times to confirm your password!"<<endl;

            for(int i=0; i<3; i++)
            {
                cout<<"Confirm Password : ";
                string confirm_pass;
                char ch1;

                while((ch1 = _getch()) != '\r')
                {
                    confirm_pass += ch1;
                    cout<<"*";
                }
                if(temp_pass == confirm_pass)
                {
                    password = confirm_pass;
                    break;
                }
                cout<<"Invalid Password !"<<endl;
                cout<<"Try again!"<<endl;
            }
            password = hashPassword(password);

            ofstream out("Admin.txt");

            out<<username<<" "<<password;

            out.close();
            cout<<endl;
            cout<<"Admin Information Saved!"<<endl;

        }
        else
        {
            int chance = 3;

            while(chance > 0)
            {
                try
                {
                    cout<<"Enter Password: ";
                    cin>>password;

                    password = hashPassword(password);

                    if(password != storedPassword)
                    {
                        throw "Wrong Password!";
                    }

                    cout<<"Login Successful!"<<endl;
                    //Entering admin menu;
                    Admin_Menu();
                    return;
                }

                catch(const char *msg)
                {
                    chance--;

                    cout<<msg<<endl;
                    cout<<"Remaining Chance: "<<chance<<endl;
                }
            }

            cout<<"Login Failed!"<<endl;
        }

    }
};

//Student Menu
//
//void Student_Menu(student &s)
//{
//    int choice;
//    while(true)
//    {
//
//        cout << "\n----- STUDENT MENU -----\n";
//        cout<<"1. Set Student Details "<<endl;
//        cout<<"2. View Today's Routine "<<endl;
//        cout<<"3. View FULL Routine "<<endl;
//        cout<<"4. View Personal CGPA "<<endl;
//        cout<<"5. View All Students Details"<<endl;
//        cout<<"0. EXIT"<<endl;
//
//        cout<<"Enter choice: ";
//        cin>>choice;
//        if(choice == 1)
//        {
//            s.set_student_details();
//        }
//        else if(choice == 2)
//        {
//            s.Today_Routine();
//        }
//        else if(choice == 3)
//        {
//            s.Total_week_Routine();
//        }
//        else if(choice == 4)
//        {
//            s.ShowCGPAResults_Own();
//        }
//        else if(choice == 5)
//        {
//            s.show_Student_details();
//        }
//        else if(choice == 0)
//        {
//            cout<<"EXIT"<<endl;
//            return ;
//        }
//        else
//        {
//            cout<<"Invalid Choice!"<<endl;
//            cout<<"Try Again"<<endl;
//        }
//    }
//}
void Student_Menu(student &s)
{
    int choice;

    while(true)
    {
        cout<<endl;
        cout<<"=============================================="<<endl;
        cout<<"                STUDENT MENU                 "<<endl;
        cout<<"=============================================="<<endl;

        cout<<"1. Set Student Details"<<endl;
        cout<<"2. View Today's Routine"<<endl;
        cout<<"3. View Full Routine"<<endl;
        cout<<"4. View Personal CGPA"<<endl;
        cout<<"5. View My Details"<<endl;
        cout<<"0. EXIT"<<endl;

        cout<<"----------------------------------------------"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;

        switch(choice)
        {
        case 0:
            cout<<"Exiting Student Panel..."<<endl;
            return;

        case 1:
            s.set_student_details();
            break;

        case 2:
            s.Today_Routine();
            break;

        case 3:
            s.Total_week_Routine();
            break;

        case 4:
            s.ShowCGPAResults_Own();
            break;

        case 5:
            s.show_Student_details();
            break;

        default:
            cout<<"Invalid Choice!"<<endl;
            cout<<"Try Again."<<endl;
        }
    }
}
// Faculty Menu
//
//void Faculty_Menu(Faculty &f)
//{
//    int choice;
//    while(true)
//    {
//        cout << "\n----- FACULTY MENU -----\n";
//
//        cout<<"1. Set Faculty Details"<<endl;
//        cout<<"2. Enter Marks"<<endl;
//        cout<<"0. EXIT"<<endl;
//
//        cout<<"Enter your Choice : ";
//        cin>>choice;
//
//        if(choice == 1)
//        {
//            f.set_Faculty_Info();
//        }
//        else if(choice == 2)
//        {
////            f.Enter_Marks();
//        }
//        else if(choice == 0)
//        {
//            return;
//        }
//        else
//        {
//            cout<<"Invalid Input"<<endl;
//            cout<<"Try Again"<<endl;
//
//        }
//    }
//}

void Faculty_Menu(Faculty &f)
{
    int choice;

    while(true)
    {
        cout<<endl;
        cout<<"=============================================="<<endl;
        cout<<"                FACULTY MENU                 "<<endl;
        cout<<"=============================================="<<endl;

        cout<<"1. Set Faculty Details"<<endl;
        cout<<"2. Enter Course Marks"<<endl;
        cout<<"0. EXIT"<<endl;

        cout<<"----------------------------------------------"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;

        switch(choice)
        {
        case 0:
            cout<<"Exiting Faculty Panel..."<<endl;
            return;

        case 1:
            cin.ignore();
            f.set_Faculty_Info();
            break;

        case 2:
            cin.ignore();
            f.Enter_to_Marksfile();
            break;

        default:
            cout<<"Invalid Input!"<<endl;
            cout<<"Try Again."<<endl;
        }
    }
}
void Log_in_menu()
{
    student s;
    Faculty f;
    Admin a;

    int choice;

    while(true)
    {
        cout<<endl;
        cout<<"=============================================="<<endl;
        cout<<"        STUDENT RESULT MANAGEMENT SYSTEM      "<<endl;
        cout<<"=============================================="<<endl;

        cout<<"1. Admin Login"<<endl;
        cout<<"2. Student Login"<<endl;
        cout<<"3. Faculty Login"<<endl;
        cout<<"0. Exit"<<endl;

        cout<<"----------------------------------------------"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            a.Admin_log_in();
            break;

        case 2:
            Student_Menu(s);
            break;

        case 3:
            Faculty_Menu(f);
            break;

        case 0:
            cout<<"Thank you for using SRAMS!"<<endl;
            return;

        default:
            cout<<"Invalid Choice!"<<endl;
            cout<<"Try Again!"<<endl;
        }
    }
}


int main()
{



    Log_in_menu();


    return 0;
}
