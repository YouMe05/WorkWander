
class Company : public User
{
private:
    string Email;
    string Phone;
    string Location;

public:
    Company(string);
    ~Company(){};

    // Page ---------------------
    int Menu();
    void Profile();

    // function -----------------
    void displayProfile();
    void editProfile();
    void post();
};

Company::Company(string username)
{
    fstream file;
    file.open("company/" + username + ".txt", ios::in);
    getline(file, Username);
    getline(file, Password);
    file.close();
    file.open("company/" + Username + "_profile.txt", ios::in);
    getline(file, Name);
    getline(file, Location);
    getline(file, Email);
    getline(file, Phone);
    file.close();
}

int Company::Menu()
{
    displayUser();
    cout << "  1. Profile\n  2. Post Job Ad\n  3. My Post\n  0. Log out" << endl;
    return getInput(0, 3);
}

void Company::Profile()
{
    int choice;
    while (true)
    {
        displayProfile();
        cout << "Menu  1. Edit Profile\n      2. Change Password\n      0. Back" << endl;
        choice = getInput(0, 2);
        if (choice == 1)
            editProfile();
        else if (choice == 2)
            edit_password("company/");
        else
            break;
    }
}

void Company::displayProfile()
{
    system("CLS");
    cout << "\n\tProfile" << endl;
    cout << "\t@" << Username << endl;
    cout << "----------------------------------------" << endl;
    cout << "  Company  : " << Name << endl;
    cout << "  Location : " << Location << endl;
    cout << "  Email    : " << Email << endl;
    cout << "  Phone    : " << Phone << endl;
    cout << "-------------------------------------" << endl;
}

void Company::editProfile()
{
    int choice;
    bool editMore = true;

    while (editMore)
    {
        system("CLS");
        cout << "\n\tEdit Profile" << endl;
        cout << "-------------------------------------" << endl;
        cout << "What information do you want to edit?" << endl;
        cout << "  1. Location: " << Location << endl;
        cout << "  2. Email   : " << Email << endl;
        cout << "  3. Phone   : " << Phone << endl;
        cout << "  0. Back to Profile" << endl;
        choice = getInput(0, 3);

        switch (choice)
        {
        case 1:
            cout << "Location : ";
            getline(cin >> ws, Location);
            break;
        case 2:
            cout << "Email    : ";
            getline(cin >> ws, Email);
            break;
        case 3:
            cout << "Phone    : ";
            getline(cin >> ws, Phone);
            break;
        case 0:
            editMore = false;
            break;
        }
        fstream file;
        file.open("company/" + Username + "_profile.txt", ios::out);
        file << Name << "\n"
             << Location << "\n"
             << Email << "\n"
             << Phone;
        file.close();
    }
}

void Company::post()
{
    string title, desc, req, type;
    system("CLS");
    cout << "\n\tPost Job Ad" << endl;
    cout << "----------------------------------------" << endl;

    cout << "  Job title: ";
    getline(cin >> ws, title);

    int choice;
    cout << "  Type: 1.Full-time  2.Part-time  3.Contract" << endl;
    choice = getInput(1, 3);
    if (choice == 1)
        type = "Full-time";
    else if (choice == 2)
        type = "Part-time";
    else
        type = "Contract";
    //cin.ignore();

    string input;
    int salary;
    bool notNum = false;

    do
    {
        cout << "  Salary: ";
        notNum = false;
        getline(cin >> ws, input);
        for (char c : input)
        {
            if (!isdigit(c))
            {
                notNum = true;
                cout << "Invalid Input :( Not Number!" << endl;
                break;
            }
        }
    } while (notNum);

    salary = stoi(input);

    cout << "  Description: ";
    getline(cin >> ws, desc);

    cout << "  Requirement: ";
    getline(cin >> ws, req);

    time_t now = time(0);
    tm *timeInfo = std::localtime(&now);

    fstream file, post;
    file.open("company/" + Username + "_post.txt", ios::app);
    file << Username << put_time(timeInfo, "%b%d%Y%H%M%S") << "\n"
         << title << "\n"
         << type << "\n"
         << salary << "\n"
         << desc << "\n"
         << req << "\n"
         << put_time(timeInfo, "%b %d, %Y") << endl;
    file.close();
    post.open("post/post.txt", ios::app);
    post << Username << put_time(timeInfo, "%b%d%Y%H%M%S") << "\n"
         << Name << "\n"
         << Location << "\n"
         << title << "\n"
         << type << "\n"
         << salary << "\n"
         << desc << "\n"
         << req << "\n"
         << put_time(timeInfo, "%b %d, %Y") << endl;
    post.close();

    system("CLS");
    cout << "\n\tPost Job Ad" << endl;
    cout << "----------------------------------------" << endl;
    cout << "\n        Posting Successfull\n"
         << endl;
    cout << "-------------------------------------" << endl;
    cout << "Press Enter to Back to menu..." << endl;
    cin.get();
    cin.clear();
    cin.ignore(10000, '\n');
}
