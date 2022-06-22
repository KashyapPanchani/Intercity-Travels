#include <bits/stdc++.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>

using namespace std;

int count_days(string s_month, int year); 

int flag1 = 0;

//To change the color of the font in terminal
void changeColor(int desiredColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

//Each node represents a route
struct node
{ 
    int registration_no;
    string source;
    string destination;
    string bus_number; 
    string time;
    string duration;
    vector<string> via;
    int cnt_via = 0;
    vector<string> seat;
    vector<string> time_arrive;
};

//This class includes all the critical funtions e.g.booking, display etc.....
class path
{
    node *n;
    string s1, s2, s3, s4, s5, str, s,t;
    int registration_id, id, seat;
    string time1, time2, time3, time4, time5, User_source, User_destination, User_name;
    string pdf_name;
    ifstream one;
    ifstream two;
    ifstream for_cnt;
    ifstream for_cnt_his;
    ifstream for_time;
    int cnt = 0;
    int cnt_his = 0;
    int cnt_bus = 0;
    int count = 0;

public:


    void clearing_past_data();
    bool deleting_line(int ticket_id);
    bool file_opening(string gmail, string password);
    bool checking(string gmail, string password);
    bool ticket_id_valid(int id);
    void printing_History();
    int input();
    void search(string source_temp, string destination_temp, int day);
    bool switching(int choice);
    void booking(int id, int day);
    void confirm(int id, string name, int age, int seat_no, int i);
    void display_allseat(int bus_id, int day);
    bool checking_source_destination(string user_source, string user_destination, int bus_id, int seat_no, int day);
    path();
    void display();
    
};

//Reads and saves info from the file which includes source,destination,bus registration no.....
path::path()
    {
        int flag = 1;
        for_cnt.open("source_and_destination.txt");
        one.open("source_and_destination.txt");
        two.open("source_via_destination.txt");
        for_time.open("time.txt");
        string temp;
        two >> temp;
        while (for_cnt >> s1 >> s2 >> s3 >> s4 >> s5)
        {
            cnt_bus++;
            //Counting no. of buses from the available data
        }
        for_cnt.close();
        n = new node[cnt_bus]; //Assigning one node to each of the routes
        while (one >> s1 >> s2 >> s3 >> s4 >> s5)
        {
            n[cnt].source = s1;
            n[cnt].destination = s2;
            n[cnt].bus_number = s3;
            n[cnt].time = s4;
            n[cnt].duration = s5;
            n[cnt].registration_no = cnt + 1;
            while (1 && two)
            {
                two >> str;
                if (str[2] == '-')
                    break;
                else
                {
                    for_time >> s;
                    n[cnt].time_arrive.push_back(s);
                    n[cnt].via.push_back(str);
                    n[cnt].cnt_via++;
                }
            }
            cnt++;
        }
        n[cnt_bus - 1].via.erase(n[cnt_bus - 1].via.begin() + n[cnt_bus - 1].cnt_via - 2);
        n[cnt_bus - 1].time_arrive.erase(n[cnt_bus - 1].time_arrive.begin() + n[cnt_bus - 1].cnt_via - 2);
        n[cnt_bus - 1].cnt_via--;
        // for(int i=0;i<cnt;i++)
        // {
        //     for(int j=0;j<n[i].time_arrive.size();j++)
        //     {
        //         cout<<n[i].time_arrive[j]<<" ";
        //     }
        //     cout<<endl;
        // }
        one.close();
        for_time.close();
        two.close();
    }




//Displaying all the routes available with necessary details
void path::display()
    {
        system("cls");
        cout << "\tDisplaying all Routes.";
        sleep(1);
        system("cls");
        cout << "\tDisplaying all Routes..";
        sleep(1);
        system("cls");
        cout << "\tDisplaying all Routes...";
        sleep(1);
        system("cls");
        cout << endl
             << "Available Buses : " << endl
             << endl;
        changeColor(2);
        for (int i = 0; i < cnt_bus; i++)
        {
            cout << "(" << i + 1 << ")\t";
            cout << "Bus registration No " << setfill(' ') << setw(1) << ":  " << n[i].registration_no
                 << "\n\t"
                 << "source " << setfill(' ') << setw(16) << ":  " << n[i].source
                 << "\n\t"
                 << "destination " << setfill(' ') << setw(11) << ":  " << n[i].destination
                 << "\n\t"
                 << "departure time " << setfill(' ') << setw(8) << ":  " << n[i].time
                 << "\n\t"
                 << "Bus number " << setfill(' ') << setw(12) << ":  " << n[i].bus_number
                 << "\n\t"
                 << "Duration of jounrey :  " << n[i].duration << endl
                 << "\tVia" << setfill(' ') << setw(20) << ":  ";
            for (int j = 0; j < n[i].cnt_via; j++)
            {
                cout << n[i].via[j];
                if (j != n[i].cnt_via - 1)
                {
                    cout << "->";
                }
            }
            cout << endl
                 << endl;
        }
        changeColor(7);
    }

//verifying login details
bool path::checking(string gmail, string password)
{
    int flag = 0;
    int s = gmail.find(".");
    if (s == -1)
        return 0;
    s = gmail.find("@");
    if (s == -1)
        return 0;
    if (password.length() < 8)
        return 0;
    for (int i = 0; i < password.length(); i++)
    {
        if (password[i] >= '0' && password[i] <= '9')
            flag = 1;
    }
    if (flag == 0)
        return 0;
    return 1;
}

//Creating file which contains id and password
bool path::file_opening(string gmail, string password)
{
    ofstream os;
    os.open("id_and_password.txt", ios::app);
    os << gmail << " " << password << endl;
    os.close();
    int s = gmail.find("@");
    string str(gmail, 0, s);
    str += "_activity_history.txt";
    os.open(str, ios::app);
    os.close();
    return 1;
}

//verifies id and password when user logins
bool finding(string gmail, string password)
{
    ifstream ifs;
    string s1, s2;
    ifs.open("id_and_password.txt");
    while (ifs >> s1 >> s2)
    {
        if (s1 == gmail && s2 == password)
        {
            return 1;
        }
    }
    return 0;
}

//getting input from the user
int path::input()
{
    int i;
    string gmail, password;
    int flag = 0;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    ifstream ifs;
    string s1, s2;
    if (flag1 == 0)
    {
        while (flag == 0)
        {
            cout << "Enter 1 for Sign up.."
                 << "\n"
                 << "Enter 2 for Log in.."
                 << "\n"
                 << "Enter 3 for Exit.."
                 << "\n\n"
                 << "Enter Your Choice : ";
            cin >> i;
            switch (i)
            {
            case 1:
                cout << "Enter Gmail ID : ";
                cin >> gmail;
                ifs.open("id_and_password.txt");
                while (ifs >> s1 >> s2)
                {
                    if (s1 == gmail)
                    {
                        changeColor(12);
                        cout << endl
                             << "This ID is already registrated..." << endl
                             << endl;
                        changeColor(7);
                        ifs.close();
                        goto end;
                    }
                }
                cout << "Enter PassWord  (Password which you will enter can't display on the screen for User safety!) : ";
                GetConsoleMode(hStdin, &mode);
                SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
                //Hiding what user enters
                cin >> password;
                SetConsoleMode(hStdin, mode);
                if (checking(gmail, password))
                {
                    if (file_opening(gmail, password))
                    {
                        int s = gmail.find("@");
                        flag1 = 1;
                        flag = 1;
                        pdf_name = gmail.substr(0, s);
                        pdf_name += "_activity_history.txt";
                    }
                }
                else
                {
                    changeColor(12);
                    cout << endl
                         << "Enter valid Gmail ID/Password(Password Must contain 8 characters length & atleast 1 digit).." << endl
                         << endl;
                    changeColor(7);
                }
                break;
            case 2:
                cout << "Enter Gmail ID : ";
                cin >> gmail;
                cout << "Enter PassWord(Password which you will enter can't display on the screen for User safety!) : ";
                GetConsoleMode(hStdin, &mode);
                SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
                cin >> password;
                SetConsoleMode(hStdin, mode);
                if (finding(gmail, password))
                {
                    int s = gmail.find("@");
                    pdf_name = gmail.substr(0, s);
                    pdf_name += "_activity_history.txt";
                    flag1 = 1;
                    flag = 1;
                }
                else
                {
                    changeColor(12);
                    cout << endl
                         << "No Such ID/Password found!!please sign up or Enter correct password!!" << endl
                         << endl;
                    changeColor(7);
                }
                break;

            case 3:

                return 8;

            default:

                changeColor(12);
                cout << endl
                     << "Please Enter Value in between 1 & 3 !!" << endl
                     << endl;
                changeColor(7);
                break;
            }
        end:
        {
        }
        }
    }

    int choice;
    //Giving choice to user
    cout << "\n\nEnter 1 for Search Bus"
         << "\n"
         << "Enter 2 for View whole Schedule"
         << "\n"
         << "Enter 3 for Clear screen"
         << "\n"
         << "Enter 4 for Booking."
         << "\n"
         << "Enter 5 for Cancel your ticket. "
         << "\n"
         << "Enter 6 for Viewing your History..."
         << "\n"
         << "Enter 7 for Logged out..."
         << "\n"
         << "Enter 8 for Exit..."
         << "\n\n"
         << "Enter Your Choice : ";
    cin >> choice;
    cout << "\n\n";
    return choice;
}

//Finding all the appropriate routes
void path::search(string source_temp, string destination_temp, int day)
{
    int bus_no = 1, flag = 0;
    for (int i = 0; i < cnt; i++)
    {
        vector<string>::iterator it;
        it = find(n[i].via.begin(), n[i].via.end(), source_temp); //finding the source which user entered from our data
        if (it != n[i].via.end())
        {
            int store = distance(n[i].via.begin(), it);
            if (i == n[i].cnt_via)
                break;
            it = find(n[i].via.begin() + store, n[i].via.end(), destination_temp); //finding the destination which user entered from our data
            if (it != n[i].via.end())
            {
                if (flag == 0)
                {
                    cout << "Here are some available buses : " << endl
                         << endl;
                }
                flag = 1;
                changeColor(2);
                cout << "(" << bus_no << ")\t";
                cout << "Bus registration No " << setfill(' ') << setw(1) << ":  " << n[i].registration_no
                     << "\n\t"
                     << "source " << setfill(' ') << setw(16) << ":  " << n[i].source
                     << "\n\t"
                     << "destination " << setfill(' ') << setw(11) << ":  " << n[i].destination
                     << "\n\t"
                     << "departure time " << setfill(' ') << setw(8) << ":  " << n[i].time
                     << "\n\t"
                     << "Bus number " << setfill(' ') << setw(12) << ":  " << n[i].bus_number
                     << "\n\t"
                     << "Duration of jounrey :  " << n[i].duration << endl
                     << "\tVia" << setfill(' ') << setw(20) << " :  ";
                for (int j = 0; j < n[i].cnt_via; j++)
                {
                    cout << n[i].via[j];
                    if (j != n[i].cnt_via - 1)
                    {
                        cout << "->";
                    }
                }
                changeColor(7);
                bus_no++;
                cout << endl
                     << endl;
            }
        }
    }
    if (flag == 0)
    {
        changeColor(12);
        cout << "Sorry...There is no bus available of this route.." << endl
             << endl;
        changeColor(7);
    }
}

//Cancels the booking
bool path::deleting_line(int ticket_id)
{
    string line, deleteline;
    ofstream temp;
    temp.open("temp.txt");
    ifstream ifs("booking_history.txt");
    while (getline(ifs, line))
    {
        temp << line << endl;
    }
    temp.close();
    ifs.close();
    temp.open("booking_history.txt");
    ifs.open("temp.txt");
    int i, id, seat, flag = 0, d;
    string time1, time2, time3, time4, time5;
    string s1, s2, s3;
    while (ifs >> d >> i >> id >> seat >> s1 >> s2 >> s3 >> time1 >> time2 >> time3 >> time4 >> time5)
    {
        if (id == ticket_id)
        {
            ofstream os;
            os.open(pdf_name, ios::app);
            time_t rawtime;
            struct tm *timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            string time = asctime(timeinfo);
            //Storing the booking cancellation info from your account
            os << 0 << " " << d << " " << i << " " << id << " " << seat << " " << s1 << " " << s2 << " " << s3 << " " << time;
            os.close();
            flag = 1;
            continue; //Not saving the ticket details which has been cancelled
        }
        temp << d << " " << i << " " << id << " " << seat << " "
             << s1 << " " << s2 << " " << s3 << " " << time1 << " " << time2
             << " " << time3 << " " << time4 << " " << time5 << endl;
    }
    if (flag == 0)
        return 0;
    else
        return 1;
}

//Displays the booking history to the user
void path::printing_History()
{
    ifstream ifs;
    ifs.open(pdf_name);
    int id, seat, num, d;
    string time1, time2, time3, time4, time5;
    string s1, s2, s3;
    int ii = 1,i;
    while (ifs >> num >> d >> i >> id >> seat >> s1 >> s2 >> s3 >> time1 >> time2 >> time3 >> time4 >> time5)
    {
        string time = time1 + " " + time2 + " " + time3 + " " + time4 + " " + time5;
        cout << "(" << ii << ")";
        if (num == 1)
        {
            vector<string>::iterator it;
            it = find(n[i-1].via.begin(), n[i-1].via.end(), s1);
            int index = distance(n[i-1].via.begin(),it);
            changeColor(2);
            cout << "\n   =>\t"
                 << "You booked below ticket on time : " << time << endl;
            cout << "\n\t"
                 << "Ticket details : \n";
            cout << "\n\tTikcet Booked in " << d << " days in advance " << endl;
            cout << "\n\t"
                 << "Ticket registration No " << setfill(' ') << setw(12) << ":  " << id
                 << "\n\t"
                 << "Source " << setfill(' ') << setw(28) << ":  " << s1
                 << "\n\t"
                 << "Destination " << setfill(' ') << setw(23) << ":  " << s2
                 << "\n\t"
                 << "Bus Departure time " << setfill(' ') << setw(16) << ":  " << n[i - 1].time
                 << "\n\t"
                 << "Your Departure time " << setfill(' ') << setw(15) << ":  " << n[i - 1].time_arrive[index]
                 << "\n\t"
                 << "Bus number " << setfill(' ') << setw(24) << ":  " << i
                 << "\n\t"
                 << "Seat Number " << setfill(' ') << setw(23) << ":  " << seat
                 << "\n\t"
                 << "Name of passenger " << setfill(' ') << setw(17) << ":  " << s3 << endl
                 << endl;
            changeColor(7);
        }
        else
        {
            changeColor(12);
            cout << "\n   =>\t"
                 << "You cancelled below ticket on time : " << time << endl;
            cout << "\n\t"
                 << "Tikcet details : \n";
            cout << "\n\t"
                 << "Ticket registration No " << setfill(' ') << setw(12) << ":  " << id
                 << "\n\t"
                 << "source " << setfill(' ') << setw(28) << ":  " << s1
                 << "\n\t"
                 << "destination " << setfill(' ') << setw(23) << ":  " << s2
                 << "\n\t"
                 << "departure time " << setfill(' ') << setw(20) << ":  " << n[i - 1].time
                 << "\n\t"
                 << "Bus number " << setfill(' ') << setw(24) << ":  " << i
                 << "\n\t"
                 << "Seat Number " << setfill(' ') << setw(23) << ":  " << seat
                 << "\n\t"
                 << "Name of passenger " << setfill(' ') << setw(17) << ":  " << s3 << endl
                 << endl;
            changeColor(7);
        }
        ii++;
    }
}

//counting days in given month
int count_days(string s_month, int year)
{
    //leap year condition, if month is 2
    if (s_month == "Jan")
        s_month = "1";
    if (s_month == "Feb")
        s_month = "2";
    if (s_month == "Mar")
        s_month = "3";
    if (s_month == "Apr")
        s_month = "4";
    if (s_month == "May")
        s_month = "5";
    if (s_month == "Jun")
        s_month = "6";
    if (s_month == "Jul")
        s_month = "7";
    if (s_month == "Aug")
        s_month = "8";
    if (s_month == "Sep")
        s_month = "9";
    if (s_month == "Oct")
        s_month = "10";
    if (s_month == "Nov")
        s_month = "11";
    if (s_month == "Dec")
        s_month = "12";
    stringstream s(s_month);
    int month;
    s >> month;
    if (month == 2)
    {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
            return 29;
        else
            return 28;
    }
    //months which has 31 days
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    else
        return 30;
}




//Displays booked as well as available seats
void path::display_allseat(int bus_id, int day) 
{
    int temp = 1;
    int d;
    vector<string> v(41, "Empty "); //Making a vector for the bus and intializing bus seats to empty
    cout << "Seats of bus id of " << bus_id << " are given below : " << endl
         << endl;
    ifstream ifs;
    ifs.open("booking_history.txt");
    int i, id, seat, x;
    string time1, time2, time3, time4, time5;
    string s1, s2, s3;
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    int curr_day = aTime->tm_mday; 
    while (ifs >> d >> i >> id >> seat >> s1 >> s2 >> s3 >> time1 >> time2 >> time3 >> time4 >> time5)
    {
        int days = aTime->tm_mday;
        stringstream past(time3);
        past >> x;
        int d1 = (d + x) % count_days(time2, 2021);
        if (i == bus_id && (d1) == (curr_day + day))
        {
            if (s1 != n[bus_id - 1].source || s2 != n[bus_id - 1].destination)
            {
                v[seat] = "Filled1";
            }
            else
                v[seat] = "Filled";
        }
    }
    ifs.close();
    changeColor(2);
    for (int i = 0; i < 10; i++)
    {
        changeColor(7);
        cout << "(" << setw(2) << setfill('0') << temp++ << ") ";
        changeColor(2);
        if (v[temp - 1] != "Empty ")
        {
            if (v[temp - 1] == "Filled1")
            {
                changeColor(1);
                v[temp - 1].erase(v[temp - 1].length() - 1);
            }
            else
                changeColor(12);
            cout << v[temp - 1] << " ";
            changeColor(2);
        }
        else
            cout << v[temp - 1] << " ";
        changeColor(7);
        cout << "(" << setw(2) << setfill('0') << temp++ << ") ";
        changeColor(2);
        if (v[temp - 1] != "Empty ")
        {
            if (v[temp - 1] == "Filled1")
            {
                changeColor(1);
                v[temp - 1].erase(v[temp - 1].length() - 1);
            }
            else
                changeColor(12);
            cout << v[temp - 1] << "\t\t";
            changeColor(2);
        }
        else
            cout << v[temp - 1] << "\t\t";
        changeColor(7);
        cout << "(" << setw(2) << setfill('0') << temp++ << ") ";
        changeColor(2);
        if (v[temp - 1] != "Empty ")
        {
            if (v[temp - 1] == "Filled1")
            {
                changeColor(1);
                v[temp - 1].erase(v[temp - 1].length() - 1);
            }
            else
                changeColor(12);
            cout << v[temp - 1] << " ";
            changeColor(2);
        }
        else
            cout << v[temp - 1] << " ";
        changeColor(7);
        cout << "(" << setw(2) << setfill('0') << temp++ << ") ";
        changeColor(2);
        if (v[temp - 1] != "Empty ")
        {
            if (v[temp - 1] == "Filled1")
            {
                changeColor(1);
                v[temp - 1].erase(v[temp - 1].length() - 1);
            }
            else
                changeColor(12);
            cout << v[temp - 1] << " ";
            changeColor(2);
        }
        else
            cout << v[temp - 1] << " ";
        cout << endl;
    }
    changeColor(1);
    cout << endl
         << "This Color represent that this seat is filled but not for whole journy..." << endl;
    changeColor(12);
    cout << endl
         << "This Color represent that this seat is filled for whole journy..." << endl;
    changeColor(2);
    cout << endl
         << "This Color represent that this seat is Empty for whole journy." << endl;
    changeColor(7);
    cout << endl;
}

//Checks if the entered source and destinations are valid or not
bool path::checking_source_destination(string user_source, string user_destination, int bus_id, int seat_no, int day)
{
    for_cnt_his.open("booking_history.txt");
    int i = 0, d;
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    while (for_cnt_his >> d >> i >> id >> seat >> User_source >> User_destination >> User_name >> time1 >> time2 >> time3 >> time4 >> time5)
    {
        int curr_day = aTime->tm_mday, x;
        int days = aTime->tm_mday;
        stringstream past(time3);
        past >> x;
        int d1 = (d + x) % count_days(time2, 2021);
        if ((i == bus_id) && (seat == seat_no) && (d1) == (curr_day + day))
        {
            if(User_destination == user_destination && User_source==user_source)
            {
                return 0;
            }
            vector<string>::iterator it;
            it = find(n[bus_id - 1].via.begin(), n[bus_id - 1].via.end(), User_source);
            int index = distance(n[bus_id - 1].via.begin(), it) + 1;
            while (1)
            {
                if (n[bus_id - 1].via[index] == User_destination)
                {
                    break;
                }
                if (n[bus_id - 1].via[index] == user_source)
                {
                    for_cnt_his.close();
                    return 0;
                }
                if (n[bus_id - 1].via[index] == user_destination)
                {
                    for_cnt_his.close();
                    return 0;
                }
                index++;
            }
        }
        i++;
    }
    for_cnt_his.close();
    return 1;
}

//Books ticket
void path::booking(int bus_id, int day)
{
    for (int i = 0; i < cnt; i++)
    {
        if (n[i].registration_no == bus_id)
        {
            display_allseat(bus_id, day);
            int seat_no;
            cout << "Enter seat no (In between 1 and 40)/(-1 for main-menu): ";
            cin >> seat_no;
            if (seat_no == -1)
                return;
            if (seat_no <= 40)
            {
                string user_source, user_destination;
                cout << "Enter Your Source : ";
                cin >> user_source;
                transform(user_source.begin(), user_source.end(), user_source.begin(), ::tolower);
                //Converting the entered source to lower case
                cout << "Enter Your Destionation : ";
                cin >> user_destination;
                transform(user_destination.begin(), user_destination.end(), user_destination.begin(), ::tolower);
                //Converting the entered destination to lower case
                vector<string>::iterator it1;
                vector<string>::iterator it2;
                it1 = find(n[bus_id - 1].via.begin(), n[bus_id - 1].via.end(), user_source);
                it2 = find(n[bus_id - 1].via.begin(), n[bus_id - 1].via.end(), user_destination);
                if (it1 == n[bus_id - 1].via.end() || it2 == n[bus_id - 1].via.end() || it1 >= it2)
                {
                    changeColor(12);
                    cout << "\nNot Found!!" << endl;
                    changeColor(7);
                }
                else if (checking_source_destination(user_source, user_destination, bus_id, seat_no, day))
                {
                    cout << "Enter your name : ";
                    string Name;
                    cin >> Name;
                    cout << "Enter Your Age : ";
                    int age;
                    cin >> age;
                    system("cls");
                    cout << "\tConfirming Your Booking.";
                    sleep(1);
                    system("cls");
                    cout << "\tConfirming Your Booking..";
                    sleep(1);
                    system("cls");
                    cout << "\tConfirming Your Booking...";
                    sleep(1);
                    system("cls");
                    ofstream ofs;
                    ofs.open("booking_history.txt", ios::app);
                    time_t rawtime;
                    struct tm *timeinfo;
                    time(&rawtime);
                    timeinfo = localtime(&rawtime);
                    string time = asctime(timeinfo);
                    long int store = 22320444 + (rand() % 23133424); //generating registration id
                    ofs << day << " " << bus_id << " " << store << " "
                        << seat_no << " " << user_source << " " << user_destination << " " << Name << " " << time;
                    ofs.close();
                    ofstream os;
                    os.open(pdf_name, ios::app); //Saving the details in user's account
                    os << 1 << " " << day << " " << bus_id << " " << store
                       << " " << seat_no << " " << user_source << " " << user_destination << " " << Name << " " << time << endl;
                    os.close();
                    changeColor(2);
                    vector<string>::iterator it;
                    it = find(n[i].via.begin(), n[i].via.end(), user_source);
                    int index = distance(n[i].via.begin(),it);
                    ofstream ofs1;
                    //opening html file
                    ofs1.open("booking.html");
                    //printing in html file 
                    ofs1 << "<!DOCTYPE html>" << endl
                        << "<html lang=\"en\">" << endl  
                        << "<head>" << endl
                        << "<meta charset = \"UTF-8\">" << endl
                        << "<meta http - equiv = \"X-UA-Compatible\" content = \"IE=edge\">" << endl
                        << "<meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\">" << endl
                        << "<title>RESULT!</title>" << endl
                        << "</head>" << endl
                        << "<body style=\"background: url('img1.jpg'); background-repeat: no-repeat;background-size: 1600px 800px;\">" << endl;
                        ofs1<< "<h2 style=\" color: rgb(0, 0, 0); text-align: center; font-weight: bolder; margin: 0; font-size: 48px; font-weight: 700; line-height: 56px; text-transform: uppercase; color: #273847;\">"<<endl
                        <<"Thank You For Booking!"<<endl
                        <<"</h2>"<<endl
                        <<"<br>"<<endl
                        <<"<h5 style=\"color: rgb(0, 0, 0);"
                        <<"text-align: center;"
                        <<"margin: 0;"
                        <<"font-size: 25px;"
                        <<"font-weight: 600;"
                        <<"line-height: 56px;"
                        <<"text-transform: uppercase;"
                        <<"color: #273847;\">"
                        <<"!! Booking confirmed !!"<<endl
                        <<"</h5><br>"<<endl
                        <<"<div style=\"color: #fffddc; text-align: center; background: rgb(0, 0, 0);background: rgba(0, 0, 0, 0.2);color: rgb(0, 0, 0);text-align: center;color: #fffddc;margin: 10px 0 0 0;font-size: 24px; \">"<<endl
                        <<"<br>"<<endl
                        <<"You Booked your Ticket in " << day;
                        if(day<2)   ofs1<<" day";
                        else    ofs1<<" days";
                        ofs1<<" Advance!"<<endl
                        <<"<br><br>"<<endl
                        <<"</div>"<<endl
                        <<"<div style = \"background: rgb(0, 0, 0);background: rgba(0, 0, 0, 0.2);color: rgb(0, 0, 0);padding-left: 550px;color: #fffddc;margin: 10px 0 0 0;font-size: 24px;\">"<<endl
                        
                        <<"<b>Here is your Detail's of Booking : </b>"<<endl
                        <<"<br><br>"<<endl
                        <<"Name <span style=\"padding-left: 216px;\">: </span> <b> " << Name <<"</b>"<<endl
                        <<"<br>"<<endl
                        <<"Bus registration No <span style=\"padding-left: 85px;\">: </span> <b> " <<bus_id <<"</b>"<<endl
                        <<"<br>"<<endl 
                        <<"Seat No <span style=\"padding-left: 198px;\">: </span> <b> " <<seat_no <<"</b>"<<endl
                        <<"<br>"<<endl
                        <<"Ticket ID <span style=\"padding-left: 180px;\">: </span> <b> " <<store <<"</b>"<<endl
                        <<"<br>"<<endl
                        <<"Bus Departure Platform   <span style=\"padding-left: 40px;\">: </span> <b> " <<n[bus_id - 1].source <<"</b>"<<endl
                        <<"<br>"<<endl
                        <<"Bus Destination Point    <span style=\"padding-left: 58px;\">: </span> <b> " <<n[bus_id - 1].destination<<"</b>"<<endl
                        <<"<br>"<<endl
                        <<"Bus Departure Time       <span style=\"padding-left: 75px;\">: </span> <b> " <<n[bus_id - 1].time<<"</b>"<<endl
                        <<"<br>"<<endl
                        <<"Your Departure Time       <span style=\"padding-left: 67px;\">: </span> <b> " <<n[bus_id - 1].time_arrive[index]<<"</b>"<<endl
                        <<"<br>"<<endl
                        <<"Time Duretion For journy <span style=\"padding-left: 20px;\">: </span> <b> " <<n[bus_id-1].duration<<"</b>"<<endl
                        <<"<br>"<<endl
                        <<"Your Departure Platform <span style=\"padding-left: 30px;\">: </span> <b> " <<user_source<<"</b>"<<endl
                        <<"<br>"<<endl
                        <<"Your Destination Point <span style=\"padding-left: 48px;\">: </span> <b> " <<user_destination<<"</b>"<<endl
                        <<"<br>"<<endl
                        <<"</div>"<<endl
                        <<"</body>"<<endl
                        <<"</html>"<<endl;
                        //opening html output in web
                    ShellExecute(NULL, "open", "booking.html", NULL, NULL, SW_SHOWNORMAL);
                    ofs1.close();
                    cout<<endl;
                    changeColor(7);
                }
                else
                {
                    changeColor(12);
                    cout << endl
                         << "Sorry...this seat is not available!!" << endl;
                    changeColor(7);
                }
            }
            else
            {
                changeColor(12);
                cout << "Please Enter valid Seat No !!" << endl;
                changeColor(7);
                return;
            }
        }
    }
}

//Basic switch case structure for choosing from available options
bool path::switching(int choice)
{
    string source_temp, destination_temp;
    int id;
    int day = -1;
    switch (choice)
    {
    case 1:

        cout << "Enter Source : ";
        cin >> source_temp;
        transform(source_temp.begin(), source_temp.end(), source_temp.begin(), ::tolower);
        cout << "Enter Destination : ";
        cin >> destination_temp;
        transform(destination_temp.begin(), destination_temp.end(), destination_temp.begin(), ::tolower);
        while (day > 20 || day < 0)
        {
            cout << endl
                 << "Enter Day in which you want to search this route in advance(consider 0 as Today, you can search bus in max 20 days in advance) : ";
            cin >> day;
        }
        cout << endl
             << endl;
        system("cls");
        cout << "Searching Bus.";
        sleep(1);
        system("cls");
        cout << "Searching Bus..";
        sleep(1);
        system("cls");
        cout << "Searching Bus...";
        sleep(1);
        system("cls");
        search(source_temp, destination_temp, day);
        return 1;

    case 2:

        display();
        return 1;

    case 3:

        system("CLS");
        return 1;

    case 4:

        cout << "Enter Registration ID of Bus : ";
        cin >> id;
        if (id > cnt)
        {
            changeColor(12);
            cout << "Please Enter available value!!" << endl;
            changeColor(7);
        }
        while (day > 10 || day < 0)
        {
            cout << "Enter Day in which you want to search this route in advance(consider 0 as Today, you can search bus in max 10 days in advance) : ";
            cin >> day;
        }
        booking(id, day);
        return 1;

    case 5:

        cout << "Enter Your Ticket ID : ";
        cin >> id;
        if (deleting_line(id))
        {
            system("cls");
            cout << "\tDeleting Your Ticket.";
            sleep(1);
            system("cls");
            cout << "\tDeleting Your Ticket..";
            sleep(1);
            system("cls");
            cout << "\tDeleting Your Ticket...";
            sleep(1);
            system("cls");
            changeColor(2);
            cout << endl
                 << "Your Ticket has been cancelled.." << endl
                 << endl;
            changeColor(7);
        }
        else
        {
            changeColor(12);
            cout << "No such ID found!!" << endl;
            changeColor(7);
        }
        return 1;

    case 6:

        system("cls");
        cout << "Printing Your History.";
        sleep(1);
        system("cls");
        cout << "Printing Your History..";
        sleep(1);
        system("cls");
        cout << "Printing Your History...";
        sleep(1);
        system("cls");
        printing_History();
        return 1;

    case 7:

        flag1 = 0;
        return 1;

    case 8:
        system("cls");
        cout << "\tThank You for visiting..." << endl
             << endl
             << "\tExiting Program.";
        sleep(1);
        system("cls");
        cout << "\tThank You for visiting..." << endl
             << endl
             << "\tExiting Program..";
        sleep(1);
        system("cls");
        cout << "\tThank You for visiting..." << endl
             << endl
             << "\tExiting Program...";
        sleep(1);
        system("cls");
        return 0;

    default:

        changeColor(12);
        cout << "Enter value in between 1-6 !!" << endl;
        changeColor(7);
        return 1;
    }
    return 0;
}



int main()
{
    srand(time(NULL));
    system("cls");
    path p; //Calling constuctor
    int choice;
    while (1)
    {
        choice = p.input(); //Taking input i.e. choice
        if (!p.switching(choice))
            return 0;
    }

    return 0;
}