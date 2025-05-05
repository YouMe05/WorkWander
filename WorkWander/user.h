
using namespace std;

class User
{
protected:
    string Username;
    string Password;
    string Name;

public:
    User(string = "unknown", string = "unknown", string = "unknown");
    virtual ~User(){};
    int getInput(int, int);
    string getUsername() { return Username; };
    string getPwd() { return Password; };
    string getName() { return Name; };

    // Page -------------------
    void RegisPage();

    //main function -----------
    bool specialChar(const string &);
    void regis(string);
    string login(string);
    void displayUser();
    void edit_password(string folder);

    virtual int Menu() = 0;
    virtual void Profile() = 0;
    virtual void displayProfile() = 0;
    virtual void editProfile() = 0;
    virtual void post() = 0;
};

User::User(string user, string pwd, string name)
{
    Username = user;
    Password = pwd;
    Name = name;
}

bool User::specialChar(const string &str)
{
    string specialChars = "<>:/\\|?*\" ";
    return any_of(str.begin(), str.end(), [&](char c) { return specialChars.find(c) != string::npos; });
}

void User::regis(string user_type)
{
    string username, pwd, name, email, phone, about, skill, location, resume;
    bool usernameTaken;
    string uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    fstream file;
    do
    {
        system("CLS");
        cout << "\n\tRegister" << endl;
        cout << "----------------------------------------" << endl;
        usernameTaken = false;
        while(true) {
            cout << "  Username: ";
            getline(cin >> ws, username);
            if (specialChar(username))
                cout << "Invalid username!\n [!] contain <, >, :, /, \\, |, ?, *, \" or white space)" << endl;
            else if (username.find_first_of(uppercaseLetters) != string::npos)
                cout << "Invalid username!\n [!] contain uppercase letter" << endl;
            else break;
        }

        file.open(user_type + username + ".txt", ios::in);
        if (file)
        {
            cout << "Oops! This Username is already taken." << endl;
            cout << "  1.Try another one\n  2.Cancel Registration" << endl;
            if(getInput(1, 2) == 1) usernameTaken = true;
            else return;
        }
        file.close();
    } while (usernameTaken);

    while(true) {
            cout << "  Password: ";
            getline(cin >> ws, pwd);
            bool hasSpace = false;
            for (char c : pwd) {
                if (c == ' ') {
                    hasSpace = true;
                    break;
                }
            }

            if (hasSpace) {
                cout << "Invalid password!\n [!] contain white space" << std::endl;
            }
            else break;
    }

    file.open(user_type + username + ".txt", ios::out);
    file << username << "\n"<< pwd;
    file.close();

    file.open(user_type + username + "_profile.txt", ios::out);
    system("CLS");
    cout << "\n\tSet up your Profile" << endl;
    cout << "----------------------------------------" << endl;

    if (user_type == "jobSeeker/")
    {
        cout << "  Display Name:  ";
        getline(cin >> ws, name);
        file << name << "\n";
        cout << "  About you: ";
        getline(cin >> ws, about);
        cout << "  Skill: ";
        getline(cin >> ws, skill);
        file << about << "\n"
             << skill << "\n";
    }
    else
    {
        cout << "  Company Name(Can't edit later):\n  ";
        getline(cin >> ws, name);
        file << name << "\n";
        cout << "  Location: ";
        getline(cin >> ws, location);
        file << location << "\n";
    }
    cout << "  Email: ";
    getline(cin >> ws, email);
    cout << "  Phone: ";
    getline(cin >> ws, phone);
    file << email << "\n"
         << phone;
    if (user_type == "jobSeeker/") {
        cout << "  Resume(Link): ";
        getline(cin >> ws, resume);
        file << "\n" << resume;
    }
    file.close();

    if (user_type == "jobSeeker/")
        cout << "\nJob Seeker Registration successfull:)" << endl;
    else
        cout << "\nCompany Registration successfull:)" << endl;
    cout << "Press Enter to Back to menu..." << endl;
    cin.get();
    cin.clear();
    cin.ignore(10000, '\n');
}

string User::login(string user_type)
{
    string userInput, pwdInput, username, password;
    int attempts = 0;
    const int maxAttempts = 3;
    int choice;
    fstream file;

    while (attempts <= maxAttempts)
    {
        system("CLS");
        cout << "\n\tLogin" << endl;
        cout << "----------------------------------------" << endl;
        cout << "  Username: ";
        getline(cin >> ws, userInput);
        cout << "  Password: ";
        getline(cin >> ws, pwdInput);

        file.open(user_type + userInput + ".txt", ios::in);
        getline(file, username);
        getline(file, password);
        file.close();

        if (password == pwdInput)
        {
            return username;
        }
        else if (attempts != 3)
        {
            cout << "\nLogin Faild:( Incorrect username or password" << endl;
            cout << "  1. Try again (" << maxAttempts - attempts << " attempts left)\n  0. Back to menu" << endl;
            choice = getInput(0, 1);
            if (choice == 1)
                attempts++;
            else
                break;
        }
        else
        {
            cout << "\nLogin Faild:(" << endl;
            cout << "Max login attempts reached. Please try again later." << endl;
            cout << "Press Enter to Back to menu..." << endl;
            cin.get();
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
    }
    return "<failed>";
}

void User::displayUser()
{
    system("CLS");
    cout << "\n\t" << Name;
    cout << "\n\t@" << Username << endl;
    cout << "----------------------------------------" << endl;
}

void User::edit_password(string folder)
{
    string checkpass, pwd;
    int choice;
    bool hasSpace;

    system("CLS");
    cout << "\n\tChange Password" << endl;
    cout << "-------------------------------------" << endl;
    while (true)
    {
        cout << "  Current Password : ";
        getline(cin >> ws, checkpass);
        if (checkpass == Password)
        {
            while (true)
            {
                cout << "  New Password : ";
                getline(cin >> ws, pwd);
                bool hasSpace = false;
                for (char c : pwd)
                {
                    if (c == ' ')
                    {
                        hasSpace = true;
                        break;
                    }
                }

                if (hasSpace)
                {
                    cout << "Invalid password!\n [!] contain white space" << std::endl;
                }
                else
                    break;
            }
            Password = pwd;
            fstream file;
            file.open(folder + Username + ".txt", ios::out);
            file << Username << "\n"
                 << Password;
            file.close();
            break;
        }
        else
        {
            cout << "\nIncorrect Password!" << endl;
            cout << "  1. Try again\n  0. Cancle" << endl;
            choice = getInput(0, 1);
            if (choice == 1)
                continue;
            else
                break;
        }
    }
}

int User::getInput(int min, int max)
{
    string input;
    int choice;
    bool notNum = false;

    while (1)
    {
        do
        {
            notNum = false;
            cout << ">> ";
            getline(cin >> ws, input);
            for (char c : input)
            {
                if (!isdigit(c) || specialChar(input))
                {
                    notNum = true;
                    cout << "Invalid Input :(" << endl;
                    break;
                }
            }
        } while (notNum);

        choice = stoi(input);
        if (choice < min || choice > max)
            cout << "Invalid Input :(" << endl;
        else
            break;
    }

    return choice;
}

void User::RegisPage() {
    int choice;
    system("CLS");
    cout << "\n\tRegister" << endl;
    cout << "-------------------------------------" << endl;
    cout << "  1. Register as Job Seeker\n  2. Register as Company\n  3. Back" << endl;
    choice = getInput(1, 3);
    switch(choice)
    {
    case 1:
        regis("jobSeeker/");
        break;

    case 2:
        regis("company/");
        break;
    }
}
