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
//End of header section

using namespace std;

// ================= Forward Class Declarations =================

class student;
class Faculty;

// ================= Function Prototypes =================

bool AdminLogin();
bool StudentLogin(student&);
bool FacultyLogin(Faculty&);

void copy_File(string file1, string file2);
void FixStudentNames(string filename);

bool isMarksGiven(const string&);
bool allMarksGiven();
bool isResultGiven(const string&);

void LoginMenu(Faculty&, student&);
void AdminMenu(Faculty&, student&);
void StudentMenu(student&);
void FacultyMenu(Faculty&, student&);
void Enter_course_marks();

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

    void ShowCGPAResults(const string &filename = "CGPA_ThirdSemester.txt")
    {
        ifstream fin(filename);
        if(!fin)
        {
            cout<<"CGPA file not found: "<<filename<<endl;
            return;
        }

        string id, name;
        double cgpa;

        //setw() is used to set the minimum width for the next output value, so the table columns stay properly aligned.
        cout <<left<<setw(12)<<"ID"  // Aligns "ID" to the left and reserves 12 spaces
             <<setw(25)<<"Name"
             <<setw(8)<<"CGPA"<<endl;
        cout << "---------------------------------------------" << endl;

        string header;
        getline(fin, header);

        while(fin>>id)
        {
            fin>>ws;
            getline(fin,name,' ');
            fin>>cgpa;

            cout << left<<setw(12)<<id
                 << setw(25)<<name
                 << setw(8)<<fixed<<setprecision(2)<<cgpa
                 << endl;
        }

        fin.close();
    }

    void ShowCGPAResults_Own(const string &filename = "CGPA_ThirdSemester.txt")
    {
        ifstream fin(filename);

        if(!fin)
        {
            cout<<"CGPA file not found: "<<filename<<endl;
            return;
        }

        string ownId;
        cout<<"Enter your ID to see your CGPA"<<endl;
        cout<<"ID : ";
        cin>>ownId;

        string id, name;
        double cgpa;
        bool found = false;

        // setw() is used to set the minimum width for the next output value,
        // so the table columns stay properly aligned.
        cout<<left<<setw(12)<<"ID"
            <<setw(25)<<"Name"
            <<setw(8)<<"CGPA"<<endl;

        cout<< "---------------------------------------------" << endl;

        string header;
        getline(fin, header);   // Skip the header line

        while(fin >> id)
        {
            fin>>ws;
            getline(fin,name,' ');

            if(!(fin>>cgpa))
            {
                cout<<"Your CGPA is not found or not given."<<endl;
                return;
            }

            if(id == ownId)
            {
                found = true;

                cout<<left<<setw(12)<<id
                    <<setw(25)<<name
                    <<setw(8)<<fixed<<setprecision(2)<<cgpa
                    <<endl;
                break;
            }
        }

        if(!found)
        {
            cout<<"Your ID was not found."<<endl;
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

                ifstream course_pass("Course&Password");

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
                        if(hashPassword(password) == stored_pass)
                        {
                            course_pass.close();

                            Enter_course_marks();

                            return;
                        }
                        else
                        {
                            throw "Invalid Password";
                        }
                    }
                }

                if(!found)
                {
                    cout<<"Set your course code ans password then try again <..>"<<endl;
                    Set_Course_Password();
                }

                course_pass.close();

                throw "Course code not found!";
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

    void Enter_course_marks()
    {

    }

    void Set_Course_Password()
    {
        ofstream fout("Course&Password.txt",ios::app);

        if(!fout)
        {
            cout<<"File could not Find or opened!"<<endl;
            return;
        }
        cout<<"Enter Course Name : ";
        string course_name;
        getline(cin,course_name);

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

        while(attempt>0)
        {
            cout<<"Enter Password Again : ";

            char ch;
            while((ch =_getch())!='\r')
            {
                confirmed_password += ch;
                cout<<".";

            }
            if(temp_password == confirmed_password)
            {
                password = confirmed_password;
                break;
            }
            attempt--;

            cout<<"Invalid Password!"<<endl;
            cout<<"Try Again!"<<endl;

            cout<<"Chance Remaining : "<<attempt<<endl;



        }

        password = hashPassword(password);

        fout<<course_name<<" "<<password<<endl;

        fout<<"================================================="<<endl;

        fout.close();

        cout<<endl;

        cout<<"Course name and Password are saved successfully!"<<endl;
    }

};


// ================= ADMIN CLASS =================

class Admin : public student,public Faculty
{
public:
    void Admin_Menu()
    {
        int choice;
        while(true)
        {
            cout << "\n====== ADMIN MENU ======\n";
            cout<<"0. EXIT"<<endl;
            cout<<"1. Show Student Details "<<endl;
            cout<<"2. Show Faculty Details "<<endl;
            cout<<"3. Set Files for Course teachers"<<endl;
            cout<<"---------------------------------"<<endl;
            cout<<endl<<"Enter your choice : ";

            cin>>choice;

            if(choice == 0)
            {
                cout<<"Exit"<<endl;
                break;
            }
            else if(choice == 3)
            {

            }
        }
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

void Student_Menu(student &s)
{
    int choice;
    while(true)
    {

        cout << "\n----- STUDENT MENU -----\n";
        cout<<"1. Set Student Details "<<endl;
        cout<<"2. View Today's Routine "<<endl;
        cout<<"3. View FULL Routine "<<endl;
        cout<<"4. View Personal CGPA "<<endl;
        cout<<"5. View All Students Details"<<endl;
        cout<<"0. EXIT"<<endl;

        cout<<"Enter choice: ";
        cin>>choice;
        if(choice == 1)
        {
            s.set_student_details();
        }
        else if(choice == 2)
        {
            s.Today_Routine();
        }
        else if(choice == 3)
        {
            s.Total_week_Routine();
        }
        else if(choice == 4)
        {
            s.ShowCGPAResults_Own();
        }
        else if(choice == 5)
        {
            s.show_Student_details();
        }
        else if(choice == 0)
        {
            cout<<"EXIT"<<endl;
            return ;
        }
        else
        {
            cout<<"Invalid Choice!"<<endl;
            cout<<"Try Again"<<endl;
        }
    }
}

// Faculty Menu

void Faculty_Menu(Faculty &f)
{
    int choice;
    while(true)
    {
        cout << "\n----- FACULTY MENU -----\n";

        cout<<"1. Set Faculty Details"<<endl;
        cout<<"2. Enter Marks"<<endl;
        cout<<"0. EXIT"<<endl;

        cout<<"Enter your Choice : ";
        cin>>choice;

        if(choice == 1)
        {
            f.set_Faculty_Info();
        }
        else if(choice == 2)
        {
//            f.Enter_Marks();
        }
        else if(choice == 0)
        {
            return;
        }
        else
        {
            cout<<"Invalid Input"<<endl;
            cout<<"Try Again"<<endl;

        }
    }
}
int main()
{
    student s;
    Faculty f;
    Admin a;
//    a.set_course_files();
    return 0;
}


