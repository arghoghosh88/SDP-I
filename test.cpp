#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
void Login()
    {
        string username, password;
        string storedUsername, storedPassword;

        ifstream file("Admin.txt");

        // File empty হলে Admin info set করবে
        if(!(file >> storedUsername >> storedPassword))
        {
            file.close();

            cout<<"Enter Admin Username: ";
            cin>>username;

            cout<<"Enter Admin Password: ";
            cin>>password;

            password = hashPassword(password);

            ofstream out("Admin.txt");

            out<<username<<" "<<password;

            out.close();

            cout<<"Admin Information Saved!"<<endl;
        }

        // File এ info থাকলে login
        else
        {
            file.close();

            cout<<"Enter Username: ";
            cin>>username;

            cout<<"Enter Password: ";
            cin>>password;

            password = hashPassword(password);

            if(username == storedUsername &&
               password == storedPassword)
            {
                cout<<"Login Successful!"<<endl;
                cout<<"Welcome to Admin Panel"<<endl;
            }
            else
            {
                cout<<"Wrong Username or Password!"<<endl;
            }
        }
    }
string hashPassword(string password)
{
    hash<string> h;
    return to_string(h(password));
}

int main()
{
    string username;
    string password;

    cout<<"Enter Username: ";
    cin>>username;

    cout<<"Enter Password: ";

    char ch;

    while((ch = _getch()) != '\r')
    {
        password += ch;
        cout<<"*";
    }

    password = hashPassword(password);

    cout<<endl;

    cout<<"Username: "<<username<<endl;
    cout<<"Hashed Password: "<<password<<endl;

    return 0;
}
//class Admin
//{
//public:
//
//    void AdminLogin()
//    {
//        ifstream file("Admin.txt");
//
//        string username, password;
//
//        // File empty কিনা check
//        if(!file || file.peek() == EOF)
//        {
//            file.close();
//
//            cout<<"No Admin Information Found!"<<endl;
//            cout<<"Set Admin Information"<<endl;
//
//            cout<<"Enter Username: ";
//            cin>>username;
//
//            cout<<"Enter Password: ";
//            cin>>password;
//
//            password = hashPassword(password);
//
//            ofstream out("Admin.txt");
//
//            out<<username<<endl;
//            out<<password<<endl;
//
//            out.close();
//
//            cout<<"Admin Information Saved Successfully!"<<endl;
//        }
//
//        else
//        {
//            string storedUsername, storedPassword;
//
//            file>>storedUsername;
//            file>>storedPassword;
//
//            file.close();
//
//            int chance = 3;
//
//            while(chance > 0)
//            {
//                cout<<"Enter Username: ";
//                cin>>username;
//
//                cout<<"Enter Password: ";
//                cin>>password;
//
//                password = hashPassword(password);
//
//                if(username == storedUsername &&
//                   password == storedPassword)
//                {
//                    cout<<"Login Successful!"<<endl;
//                    return;
//                }
//
//                chance--;
//
//                cout<<"Wrong Username or Password!"<<endl;
//                cout<<"Remaining Chance: "<<chance<<endl;
//            }
//
//            cout<<"Login Failed!"<<endl;
//        }
//    }
//};
