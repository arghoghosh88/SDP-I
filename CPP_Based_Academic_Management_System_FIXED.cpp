//#include <bits/stdc++.h>
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


// ================= STUDENT CLASS =================

class student
{
private:
    string name;
    string id;
    const string intake = "56";
    const string section = "5";
public:
    int cse111 = 0;
    int cse112 = 0;
    int cse103 = 0;
    int eee101 = 0;
    int eee102 = 0;
    int mat103 = 0;

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
    void show_Student_details()
    {
        cout<<"Name : "<<name<<endl;
        cout<<"ID : "<<id<<endl;
        cout<<"Intake : "<<intake<<endl;
        cout<<"Section : "<<section<<endl;
    }
    void ShowCGPAResults(const string &filename = "CGPA_ThirdSemester.txt")
    {
        ifstream fin(filename);
        if(!fin)
        {
            cout<<"CGPA file not found: " << filename<<endl;
            return;
        }

        string id, name;
        double cgpa;

        cout <<left<<setw(10)<<"ID"
             <<setw(25)<<"Name"
             <<setw(8)<<"CGPA"<<endl;
        cout << "---------------------------------------------" << endl;

        // Read the header of the file and skip it.
        string header;
        getline(fin, header);

        while(fin >> id)
        {
            fin >> ws;// Read all the whitespaces
            getline(fin, name, ' ');//Read the line until it get any space at the end.
            fin >> cgpa;

            cout << left << setw(10) << id
                 << setw(25) << name
                 << setw(8) << fixed << setprecision(2) << cgpa
                 << endl;
        }

        fin.close();
    }


    void Edit_Info()
    {
        string rid, rname;
        cout << "Enter your Wrong Id in file : ";
        cin >> rid;

        cin.ignore();

        cout<<"Enter your wrong name in file : ";
        getline(cin, rname);

        string eid,ename;
        cout<<"Enter your Edited ID : ";
        cin >> eid;

        cin.ignore();

        cout<<"Enter your Edited name : ";
        getline(cin, ename);

        ifstream fin("Student.txt");
        ofstream fout("temp.txt");

        string fid, fnm;
        int matches = 0;

        while(fin>>fid>>fnm)
        {
            if(rid == fid && rname == fnm)
            {
                fout << eid << " " << ename << endl;
                matches++;
            }
            else
            {
                fout << fid << " " << fnm << endl;
            }
        }

        fin.close();
        fout.close();

        remove("Student.txt");
        rename("temp.txt","Student.txt");

        // FIX: previously gave no feedback at all if the old ID/name didn't
        // match anything, so a typo would silently do nothing.
        if(matches > 0)
            cout << "Record updated successfully!" << endl;
        else
            cout << "No matching record found — nothing was changed." << endl;
    }




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
    }

    // Initializes / syncs a course roster file ("<course>.txt") from
    // Student.txt.
    // FIX: previously this appended the whole roster EVERY time it was
    // called (once per Enter_Marks() call), duplicating students on every
    // run and eventually corrupting the mark parsing. Now it only ADDS
    // students who aren't already in the course file (by ID), so it's
    // safe to call repeatedly and still picks up newly-added students
    // without duplicating or touching existing marks.
    void Copy_Student_details(string s)
    {
        static const vector<string> validSubjects =
        {
            "CSE-111","CSE-112","CSE-103","EEE-101","EEE-102","MAT-111"
        };

        if(find(validSubjects.begin(), validSubjects.end(), s) == validSubjects.end())
        {
            cout << "Unknown course code: " << s << endl;
            return;
        }

        string filename = s + ".txt";

        // Load IDs already present in the course file so we don't duplicate.
        vector<string> existingIds;
        {
            ifstream existing(filename);
            string line;
            while(getline(existing, line))
            {
                if(line.empty()) continue;
                istringstream iss(line);
                string fid;
                iss >> fid;
                existingIds.push_back(fid);
            }
        }

        ifstream fin("Student.txt");
        if(!fin)
        {
            cout << "Student.txt not found!" << endl;
            return;
        }

        ofstream fout(filename, ios::app); // only NEW lines get appended
        string fn, fid;
        int added = 0;
        while(fin >> fid)
        {
            getline(fin, fn);
            if(find(existingIds.begin(), existingIds.end(), fid) == existingIds.end())
            {
                fout << fid << " " << fn << endl;
                added++;
            }
        }
        fin.close();
        fout.close();

        if(added > 0)
            cout << filename << ": added " << added << " new student(s) to the roster.\n";
    }
    void Save_StudentDetailsTo_file()
    {
        ofstream fout("Student.txt",ios::app);
        int snum;
        cout<<"How many students ? : ";
        cin>>snum;
        for(int i=0; i<snum; i++)
        {
            string n;
            cout<<"Enter student name ";
            cin.ignore();
            getline(cin, name);
            cout<<"Enter the ID : ";
            string iD;
            cin>>iD;
            fout<<iD<<" "<<name<<endl;


        }

        fout.close();
        cout<<"Name and ID Saved"<<endl;
    }


    double calculateGradePoint(double marks)
    {
        if (marks >= 80)
        {
            return 4.00;       // A+

        }

        else if (marks >= 75)
        {
            return 3.75;  // A
        }

        else if (marks >= 70)
        {
            return 3.50;  // A-
        }

        else if (marks >= 65)
        {
            return 3.25;  // B+
        }

        else if (marks >= 60)
        {
            return 3.00;  // B
        }

        else if (marks >= 55)
        {
            return 2.75;  // B-
        }

        else if (marks >= 50)
        {
            return 2.50;  // C+
        }

        else if (marks >= 45)
        {
            return 2.25;  // C
        }

        else
        {
            return 0.0;                     // Fail

        }

    }

    void CalculateCGPA()
    {
        struct Subject
        {
            string filename;
            double credit;
        };

        Subject subject[]=
        {
            {"CSE-111.txt",3},
            {"CSE-112.txt",1.5},
            {"CSE-103.txt",3},
            {"EEE-101.txt",3},
            {"EEE-102.txt",1.5},
            {"MAT-111.txt",3}

        };

        double totalgp = 0;

        for(auto it: subject)
        {
            totalgp += it.credit;
        }

        map<string,string>name;
        map<string,double>cg;

        for(auto it:subject)
        {
            ifstream fin(it.filename);

            string fid,fnm;
            int mark;
            while(fin>>fid>>fnm>>mark)
            {
                name[fid] = fnm;
                cg[fid]+= calculateGradePoint(mark) * it.credit;
            }
            fin.close();

        }

        ofstream fout("CGPA_SecondSemester.txt");
        fout<<"ID\tName\tCGPA"<<endl;

        for(auto it: cg)
        {
            double cgpa = it.second / totalgp;
            fout<<it.first<<" "<<name[it.first]<<" "<<setprecision(2)<<cgpa<<endl;

        }
        fout.close();
        cout<<"CGPA of all students saved in CGPA_SecondSemester.txt" << endl;

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
    void Routine()
    {
        time_t t;
        time(&t);
        tm *d = localtime(&t);
        cout<<"Routine of CSE-56/5"<<endl;

        string day[]= {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday",};
        if(day[d->tm_wday]=="Sunday")
        {
            cout<<"CSE-103"<<" "<<"[ 9:45 Am - 11:15 Am]"<<" "<<"Room no: 905{B3}"<<endl;
            cout<<"EEE-102"<<" "<<"[11:15 Am - 12:45 Pm]"<<" "<<"Room no: 505{B3}"<<endl;
            cout<<"-----<Break>-----  [12:45 Pm - 1:15 Pm]"<<endl;
            cout<<"EEE-102"<<" "<<"[ 1:15 Pm -  2:45 Pm]"<<" "<<"Room no: 505{B3}"<<endl;
        }
        else if(day[d->tm_wday]=="Monday")
        {
            cout<<"MAT-111"<<" "<<"[ 8:15 Am -  9:45 Am]"<<" "<<"Room no: 905{B2}"<<endl;
            cout<<"CSE-111"<<" "<<"[ 9:15 Am - 11:15 Am]"<<" "<<"Room no: 905{B2}"<<endl;
        }
        else if(day[d->tm_wday]=="Tuesday")
        {
            cout<<"MAT-111"<<" "<<"[ 1:15 Pm -  2:45 Pm]"<<" "<<"Room no: 709{B2}"<<endl;
            cout<<"CSE-112"<<" "<<"[ 2:45 Pm -  4:15 Pm]"<<" "<<"Room no: 417{B2}"<<endl;

            cout<<"CSE-112"<<" "<<"[ 4:15 Pm -  5:45 Pm]"<<" "<<"Room no: 417{B2}"<<endl;
        }
        else if(day[d->tm_wday]=="Wednesday")
        {
            cout<<"EEE-101"<<" "<<"[ 8:15 Am -  9:45 Am]"<<" "<<"Room no: 709{B2}"<<endl;
            cout<<"CSE-103"<<" "<<"[ 9:15 Am - 11:15 Am]"<<" "<<"Room no: 709{B2}"<<endl;
        }
        else if(day[d->tm_wday]=="Thursday")
        {
            cout<<"CSE-111"<<" "<<"[11:15 Am - 12:45 Pm]"<<" "<<"Room no: 709{B2}"<<endl;
            cout<<"-----<Break>-----  [12:45 Pm - 1:15 Pm]"<<endl;
            cout<<"EEE-101"<<" "<<"[ 1:15 Pm -  2:45 Pm]"<<" "<<"Room no: 505{B3}"<<endl;
        }
        else if(day[d->tm_wday]=="Saturday"||day[d->tm_wday]=="Friday")
        {
            cout<<"You have no class today!"<<endl;
            cout<<"Enjoy your day!"<<endl;
        }
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
    void Show_Faculty_Details()
    {
        cout<<"Course : "<<course<<endl;
        cout<<"Faculty Name : "<<faculty_name<<endl;
        cout<<"E-Mail : "<<E_Mail<<endl;
        cout<<"Desk Info : "<<Desk<<endl;
    }
    void set_Faculty_Info()
    {

        string Course_name;
        cout<<"Enter course name : ";
        getline(cin, Course_name);
        cin.ignore();


        set_course(Course_name);

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

        set_PhoneNumber(phone_N);
        string email;
        cout<<"Enter faculty email : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(cin, email);

        set_email(email);

        string desk;
        cout<<"Enter the Desk of the faculty : ";
        getline(cin, desk);

        set_Desk(desk);
    }


//vector<string> split(const string &s) {
//    vector<string> tokens;
//    string temp = "";
//    for (char c : s) {
//        if (c == ' ') {
//            if (!temp.empty()) {
//                tokens.push_back(temp);
//                temp = "";
//            }
//        } else {
//            temp += c;
//        }
//    }
//    if (!temp.empty()) tokens.push_back(temp);
//    return tokens;
//}
//
//    void showFromFile()
//    {
//        ifstream fin("Faculty.txt");
//        if (!fin)
//        {
//            cout << "File not found!" << endl;
//            return;
//        }
//
//        string line;
//        while (getline(fin, line))
//        {
//            if (line.empty()) continue;
//
//            vector<string> words = split(line);
//            if (words.size() < 4) continue; // invalid line
//
//            string course = words[0];                       // first word
//            string desk = words.back();                      // last word
//            string email = words[words.size() - 2];         // second last
//            string designation = words[words.size() - 3];   // third last
//
//            // name is everything in between
//            string name = "";
//            for (size_t i = 1; i < words.size() - 3; i++)
//            {
//                name += words[i] + " ";
//            }
//            if (!name.empty() && name.back() == ' ') name.pop_back();
//
//            // print nicely
//            cout << "Course: " << course << endl;
//            cout << "Name: " << name << endl;
//            cout << "Designation: " << designation << endl;
//            cout << "Email: " << email << endl;
//            cout << "Desk: " << desk << endl;
//            cout << "-----------------------------" << endl;
//        }
//
//        fin.close();
//    }



//    void SaveFacultyDetails_File()
//    {
//
//        set_Faculty_Info();
//
//        ofstream fout("Faculty.txt",ios::app);
//
//        fout<<"||Course ||     Name ||          ||Email||               || Desk ||"<<endl;
//        fout<<"-----------------------------------------------------------------------"<<endl;
//
//        fout<<course<< " "<<faculty_name<<" , "<<designation <<" "<<phone_num<< " "<< E_Mail<< " "<<Desk<<endl;
//
//        fout.close();
//    }

    bool logInFromFile_Faculty(string course_input, string name_input)
    {
        ifstream fin("Faculty.txt");

        string fcourse, ffname, fdeg, fnum, femail, fdesk;

        while(fin >> fcourse >> ffname >> fdeg >> fnum >> femail >> fdesk)
        {
            if(fcourse == course_input && ffname == name_input)
            {
                course = fcourse;
                faculty_name = ffname;
                designation = fdeg;
                phone_num = fnum;
                E_Mail = femail;
                Desk = fdesk;

                fin.close();
                return true;   // ONLY when matched
            }
        }

        fin.close();
        return false;  // nothing matched
    }




    void Set_Password()
    {
        string pass,course;
        cout<<"Enter your Course : ";
        cin>>course;

        cout<<"Set your password to give marks of the student : ";

        cout<<"Suggested Password : ";
        cout<<course<<"1234"<<endl;

        char c;
        int i = 0;
        while(i<10)
        {
            c = getch();

            if(c == 13)
            {
                break;
            }

            pass += c;

            cout<<"*";
            i++;
        }
        cout<<endl;
        cout<<"You have 5 times to confirm your password"<<endl;
        for(int j=0; j<5; j++)
        {
            cout<<"Confirm your password : ";
            string pass1;
            char c1;
            int i1 = 0;
            while(i1<10)
            {
                c1 = getch();

                if(c1 == 13)
                {
                    break;
                }

                pass1 += c1;

                cout<<"*";
                i1++;
            }
            if(pass == pass1)
            {
                ofstream fout("Password.txt",ios::app);

                fout<<course<<" "<<pass<<endl;

                fout.close();
                break;

            }
            else
            {
                cout<<"Invalid password!"<<endl;

            }
            cout<<endl;

        }




    }
    // FIX: previously this opened the SAME file for reading (roster) and
    // appending (marks) at once. Combined with Copy_Student_details()
    // re-copying the roster on every call, repeated use corrupted the file
    // (mark values started getting misread as student IDs). This version
    // loads the whole roster + any existing marks into memory, only asks
    // for marks that are still missing, then rewrites the file cleanly.
    // It's safe to call multiple times / across multiple sessions.
    void Enter_Marks()
    {
        string course;
        cout<<"Enter your course : ";
        cin>>course;

        // ---------- Read password ----------
        ifstream pfin("Password.txt");
        string fc, fp;
        string password = "";

        while (pfin>>fc >>fp)
        {
            if (fc == course)
            {
                password = fp;
                break;
            }
        }

        pfin.close();

        if (password == "")
        {
            cout << "Course not found! Set a password for it first." << endl;
            return;
        }

        cout << "To enter marks give your password" << endl;
        cout << "You have 5 tries only" << endl;

        bool authorized = false;
        for (int i = 0; i < 5 && !authorized; i++)
        {
            string pass = "";
            char c;

            cout<<"Enter Password : ";

            while (true)
            {
                c = getch();
                if (c == 13)
                {
                    break;
                }

                pass += c;
                cout << "*";
            }

            cout << endl;

            if (pass == password)
            {
                authorized = true;
            }
            else
            {
                cout << "Invalid Password!" << endl;
            }
        }

        if (!authorized)
        {
            cout << "Access denied!" << endl;
            return;
        }

        // ---------- Load roster + any marks already entered ----------
        string filename = course + ".txt";
        ifstream fin(filename);
        if (!fin)
        {
            cout << "Course file not found! Ask admin to initialize it first." << endl;
            return;
        }

        struct Rec
        {
            string id, name;
            bool hasMark = false;
            int mark = 0;
        };

        vector<Rec> records;
        string line;
        while (getline(fin, line))
        {
            if (line.empty()) continue;
            istringstream iss(line);
            Rec r;
            iss >> r.id >> r.name;
            if (iss >> r.mark) r.hasMark = true;
            records.push_back(r);
        }
        fin.close();

        // ---------- Ask only for missing marks ----------
        bool anyMissing = false;
        for (auto &r : records)
        {
            if (r.hasMark) continue;
            anyMissing = true;
        }

        if (!anyMissing)
        {
            cout << "All students in " << course << " already have marks!" << endl;
            return;
        }

        cout << "Give marks below. Students who already have a mark are skipped." << endl;
        for (auto &r : records)
        {
            if (r.hasMark) continue;
            int mark;
            cout << r.id << " " << r.name << " : ";
            cin >> mark;
            r.mark = mark;
            r.hasMark = true;
        }

        // ---------- Rewrite the file cleanly (no append, no duplicates) ----------
        ofstream fout(filename);
        for (auto &r : records)
        {
            fout << r.id << " " << r.name;
            if (r.hasMark) fout << " " << r.mark;
            fout << endl;
        }
        fout.close();

        cout << "Marks saved successfully!" << endl;
    }


    void Result()
    {
        string subjects[] =
        {
            "CSE-111.txt",
            "CSE-112.txt",
            "CSE-103.txt",
            "EEE-101.txt",
            "EEE-102.txt",
            "MAT-111.txt"
        };

        map<string, int>total;
        map<string, string>name;

        for(int i=0; i<6; i++)
        {
            string fnm,fid;
            int mark;
            ifstream fin(subjects[i]);
            while(fin>>fid>>fnm>>mark)
            {
                total[fid] += mark;
                name[fid] = fnm;
            }
            fin.close();
        }

        ofstream fout("Results.txt");


        for(auto it: total)
        {
            fout<<it.first<<" "<<name[it.first]<<" "<<it.second<<endl;
        }
        fout.close();
    }

};


// ================= LOGIN FUNCTIONS =================


bool AdminLogin()
{
    string u,p;
    cout<<"Username: ";
    cin>>u;
    cout<<"Password: ";
    cin>>p;

    return (u=="admin" && p=="1234");
}

bool StudentLogin(student &s)
{
    // FIX: LoginfromFile_Student() takes no arguments — it hardcodes
    // "Student.txt" internally and prompts for the ID itself. Passing a
    // filename here didn't match any overload and wouldn't compile.
    return s.LoginfromFile_Student();
}

bool FacultyLogin(Faculty &f)
{
    string c,n;
    cout<<"Course: ";
    cin>>c;
    cout<<"Name: ";
    cin>>n;

    return f.logInFromFile_Faculty(c,n);
}



// ================= HELPER FUNCTIONS =================



void copy_File(string file1, string file2)
{
    ifstream fin(file1);
    ofstream fout(file2);

    if (!fin)
    {
        cout << "Source file not found: " << file1 << endl;
        return;
    }

    string line;
    while (getline(fin, line))  // read full line
    {
        fout << line << endl;    // write the line exactly as it is
    }

    fin.close();
    fout.close();

    cout << "File copied successfully from " << file1 << " to " << file2 << "!\n";
}


void FixStudentNames(string filename)
{
    ifstream fin(filename);
    ofstream fout("temp.txt");

    if (!fin)
    {
        cout << "File not found: " << filename << endl;
        return;
    }

    string id, name;

    while (fin >> id)
    {
        getline(fin, name); // read full name with spaces

        // remove leading space
        if (!name.empty() && name[0] == ' ')
            name.erase(0, 1);

        // skip first character if it is underscore
        size_t start = 0;
        if (!name.empty() && name[0] == '_')
            start = 1;

        // replace spaces with underscores, except the first char if it was '_'
        for (size_t i = start; i < name.size(); i++)
        {
            if (name[i] == ' ')
                name[i] = '_';
        }

        fout << id << " " << name << endl;
    }

    fin.close();
    fout.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    cout << "Names fixed successfully in " << filename << "!\n";
}

// Check if Results.txt has been generated.
// FIX: this used to read 4 fields (id, name, mark, total), but Result()
// only ever writes 3 (id, name, total) — so the read always failed and
// this returned false forever, permanently blocking "Calculate CGPA" in
// the admin menu even after results existed.
bool isResultGiven(const string &filename)
{
    ifstream fin(filename);
    if(!fin) return false;

    string id, name;
    int total;

    if(fin >> id >> name >> total)
    {
        fin.close();
        return true;
    }

    fin.close();
    return false;
}
bool isMarksGiven(const string &filename)
{
    ifstream fin(filename);
    if(!fin) return false; // file doesn't exist → marks not entered

    string id, name;
    int mark;

    // Read each line as: ID Name Mark
    while(fin >> id >> name >> mark)
    {
        // if we can read ID, Name, and Mark → marks exist
        fin.close();
        return true;
    }

    fin.close();
    return false; // no marks found
}

bool allMarksGiven()
{
    string subjects[] = {"CSE-111.txt", "CSE-112.txt", "CSE-103.txt",
                         "EEE-101.txt", "EEE-102.txt", "MAT-111.txt"
                        };

    for(string s : subjects)
    {
        if(!isMarksGiven(s))
        {
            cout << "Marks not yet entered for " << s << endl;
            return false;
        }
    }

    cout << "Marks have been entered for all subjects!\n";
    return true;
}


// ================= MENUS =================



void StudentMenu(student &s)
{
    int ch;
    while(true)
    {
        cout << "\n----- STUDENT MENU -----\n";
        cout << "1. See Student details "<<endl;
        cout << "2. Edit Student Info\n";
        cout << "3. View Routine\n";
        cout << "4. View Result"<<endl;
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> ch;
        cin.ignore();

        if(ch == 1)
        {
            // FIX: was calling s.LoginfromFile_Student("Students.txt") — that
            // overload doesn't take a filename argument, so this wouldn't
            // even compile. It was also redundant: the student already
            // logged in before reaching this menu, so we just show the
            // details already loaded into `s`.
            s.show_Student_details();
        }

        else if(ch == 2)
        {
            s.Edit_Info();

        }
        else if(ch == 3)
        {
            s.Routine();
        }

        else if(ch == 4)
        {
            s.ShowCGPAResults();
        }
        else if(ch == 0)
        {
            return;
        }
        else
        {
            cout << "Invalid option!\n";
        }

    }
}

// ===== FACULTY MENU =====
void FacultyMenu(Faculty &f, student &s)
{
    int ch;
    while(true)
    {
        cout << "\n----- FACULTY MENU -----\n";
        cout << "1. Set Password\n";
        cout << "2. Enter Marks\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> ch;

        if(ch == 1)
        {
            f.Set_Password();
        }
        else if(ch == 2)
        {
            string course;
            cout<<"Enter your course : ";
            cin>>course;
            s.Copy_Student_details(course);
            f.Enter_Marks();
        }

        else if(ch == 0)
        {
            return;
        }
        else
        {
            cout <<"Invalid option!\n";
        }
    }
}

// ===== ADMIN MENU =====
void AdminMenu(Faculty &f, student &s)
{
    int ch;
    while(true)
    {
        cout << "\n====== ADMIN MENU ======\n";
        cout << "1. Add Faculty Info"<<endl;
        cout << "2. Add Student Info"<<endl;
        cout << "3. Calculate total marks"<<endl;
        cout << "4. Calculate CGPA"<<endl;
        cout << "5. Fix Student Names"<<endl;
        cout << "6. Copy Any File"<<endl;
        cout << "7. Student Panel\n";
        cout << "8. Faculty Panel\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> ch;
        cin.ignore();

        if(ch == 1)
        {
            f.set_Faculty_Info();
            ofstream fout("Faculty.txt", ios::app);
            fout << f.get_course() << " "
                 << f.get_faculty_name() << " "
                 << f.get_designation() << " "
                 << f.get_phoneNumber() << " "
                 << f.get_email() << " "
                 << f.get_Desk() << endl;
            fout.close();
            cout << "Faculty Added Successfully!\n";
        }
        else if(ch == 2)
        {
            s.Save_StudentDetailsTo_file();
            cout<<"Saved successfully!"<<endl;

        }
        else if(ch == 3)
        {
            if(allMarksGiven())
            {
                f.Result();
                cout<<"Total mark calculated!"<<endl;
            }
        }
        else if(ch == 4)
        {
            if(isResultGiven("Results.txt"))
            {
                s.CalculateCGPA();
            }
        }
        else if(ch == 5)
        {
            string file;
            cout << "Enter filename: ";
            cin >> file;
            FixStudentNames(file);
        }
        else if(ch == 6)
        {
            string f1, f2;
            cout << "Source file: ";
            cin >> f1;
            cout << "Destination file: ";
            cin >> f2;
            copy_File(f1, f2);
        }
        else if(ch == 7)
        {
            StudentMenu(s);
        }
        else if(ch == 8)
        {
            FacultyMenu(f,s);
        }
        else if(ch == 0)
        {
            return;
        }
        else
        {
            cout << "Invalid Option!\n";
        }
    }
}

// ===== LOGIN MENU =====
void LoginMenu(Faculty &f, student &s)
{
    int ch;
    while(true)
    {
        cout << "\n===== LOGIN MENU =====\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "3. Faculty Login\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        if(ch == 1)
        {
            if(AdminLogin())
            {
                AdminMenu(f, s);

            }
        }
        else if(ch == 2)
        {
            if(StudentLogin(s))
            {
                StudentMenu(s);
            }
        }
        else if(ch == 3)
        {
            if(FacultyLogin(f))
            {
                FacultyMenu(f,s);
            }
        }
        else if(ch == 0)
        {
            return;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }
}


// ================= MAIN =================



int main()
{
    Faculty f;
    student s;

    LoginMenu(f,s);

    return 0;
}
