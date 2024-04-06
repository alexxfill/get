#include <iostream>
#include <string>

#define protected_get_hours \
try \
    { hours = get_value(); \
    } \
    catch (const WrongTypeException& exc) \
    { cout << exc.value << " is not a natural number!\n"; continue;}

using namespace std;


bool isNumeric(string str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

struct WrongTypeException
{
    string value;
    WrongTypeException(string value)
    {
        this -> value = value;
    }
};

int get_value()
{
    string value;
    cin >> value;
    if (!isNumeric(value))
    {
        throw WrongTypeException(value);
    }
    return stoi(value);
}

class Student
{
private:
    const string fname, lname;
    string group;
    int XP, money;
    int time = 0 , student_time;
public:

    Student(const string FirstName, const string LastName, string group)
    :fname(FirstName), lname(LastName)
    {
         this -> group = group;
         this -> XP = 100;  //default value
    }

    void Study(int hours, int XP)
    {
       this -> student_time += hours;
       this -> time += hours;
       if ( student_time >= 24)
       {
            this -> XP -= 3*XP;
       }
       else
       {
            this -> XP -= XP;
       }
    }

    void Eat(int XP, int money, int hours = 0)
    {

       if ( money <= 0)
       {
           cout << "You have not enough money!" << endl;
       }
       else
       {
            this -> XP += XP;
            this -> money += money;
            this -> student_time += hours;
            this -> time += hours;
       }
    }

    void Sleep(int hours, int XP)
    {
        this -> XP += XP;
        if (hours >= 6)
        {
             this -> student_time = 0;
        }
        this -> time += hours;
    }

      void Relax(int hours, int money, int XP)
    {
       if ( money <= 0)
       {
           cout << "You have not enough money!" << endl;
       }
       else
       {
           if ( student_time >= 24)
           {
                this -> XP += XP / 3;
           }
           else
           {
                this -> XP += XP;
           }
            this -> money -= money;
            this -> student_time += hours;
            this -> time += hours;
       }
    }

      void Work (int hours, int money, int XP)
    {
       this -> student_time += hours;
       this -> time += hours;
       this -> money += money;
       if ( student_time >= 24)
       {
            this -> XP -= 3*XP;
       }
       else
       {
            this -> XP -= XP;
       }
    }

    void XP_Info()
    {
        cout << "\nXP: " <<  XP << endl;
    }

    void Money_Info()
    {
        cout << "\nMoney: " <<  money << endl;
    }

    void Time_Remaining()
    {
        cout << "\nRemaining time of the day: " << 24 -  money << endl;
    }

    void Full_Info()
    {
        cout << "\n------Full Information------\nName: " << this -> fname << endl;
        cout << "Surname: " << this -> lname <<"\nGroup: " << this -> group << "\nXP:" << this -> XP << endl;
        cout << "Money: " << this -> money << "\nRemaining time of the day: " << 24 - this -> student_time << "\nFull time: " << this -> time << endl;
        cout << "----------------------------" << endl;
    }

    bool Check()
    {
        if (this -> XP <= 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

int main()
{
    string name, s_name, group;

    cout << "Welcome to Student Simulator v.23w35a!\n" << endl;
    cout << "Enter the data:\n";

    cout << "Name: ";
    cin >> name;

    cout << "Surname: ";
    cin >> s_name;

    cout << "Group: ";
    cin >> group;


    Student Student1(name, s_name, group);

    while(true)
    {
        int v;
        int hours, money, XP;
        cout << "\nChoose action: ";
        cout << "\n1) Sleep\n" << "2) Study\n" << "3) Work\n" << "4) Eat\n";
        cout << "5) Relax " << "\n6) XP info" << "\n7) Money info";
        cout << "\n8) Remaining time of the day: " << "\n9) Full info";
        cout << "\nYour choice: ";

        try
        {
            v = get_value();
        }
        catch (const WrongTypeException& exc)
        {
            cout << exc.value << " is not a natural number!\n";
        }

        switch (v)
        {
            case 1:  // Sleep
            {
                cout << "Hours: ";
                protected_get_hours;

                cout << "XP per hour: +5\n";
                XP = 5;

                Student1.Sleep(hours, XP);
                break;

            }

            case 2:  // Study
                {
                cout << "Hours: ";
                protected_get_hours;

                cout << "XP per hour: -3\n";
                XP = -3;

                Student1.Study(hours, XP * hours);
                break;

                }

            case 3:  // Work
                {
                    cout << "Hours: ";
                    protected_get_hours;

                    cout << "Money per hour: +25\n";
                    money = 25;

                    cout << "XP per hour: -4\n";
                    XP = -4;

                    Student1.Work(hours, money * hours, XP * hours);
                    break;
                }


            case 4:  // Eat
                {
                    cout << "Hours: ";
                    protected_get_hours;

                    cout << "XP: +10\n";
                    XP = 10;

                    cout << "Money: -15\n";
                    money = -15;

                    Student1.Eat(XP, money, hours);
                    break;

                }

            case 5:  // Relax
                {
                    cout << "Hours: ";
                    protected_get_hours;

                    cout << "Money per hour: -5\n";
                    money = -5;

                    cout << "XP per hour: +5\n";
                    XP = 5;

                    Student1.Relax(hours, money * hours, XP * hours);
                    break;
                }

            case 6:
                {
                    Student1.XP_Info();
                    break;
                }

            case 7:
                {
                    Student1.Money_Info();
                    break;
                }

            case 8:
                {
                    Student1.Time_Remaining();
                    break;
                }

            case 9:
                {
                    Student1.Full_Info();
                    break;
                }

            default:
                {
                    cout << "\nChoose action from the list!\n";
                    break;
                }
        }
        if (Student1.Check() == false)
        {
            cout << "Went to the academ...";
            break;
        }
    }
}
