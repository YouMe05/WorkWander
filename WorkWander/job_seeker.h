
class JobSeeker : public User
{
private:
    string About;
    string Skill;
    string Email;
    string Phone;
    string Resume;

public:
    JobSeeker(string);
    ~JobSeeker() {};

    // Page -------------------
    int Menu();
    void Profile();

    // function ---------------
    void displayProfile();
    void editProfile();
    void post(){};
};

JobSeeker::JobSeeker(string username)
{
    fstream file;
    file.open("jobSeeker/" + username + ".txt", ios::in);
    getline(file, Username);
    getline(file, Password);
    file.close();
    file.open("jobSeeker/" + Username + "_profile.txt", ios::in);
    getline(file, Name);
    getline(file, About);
    getline(file, Skill);
    getline(file, Email);
    getline(file, Phone);
    getline(file, Resume);
    file.close();
}

int JobSeeker::Menu()
{
    displayUser();
    cout << "  1. Profile\n  2. Seek Job\n  3. Applied Job\n  0. Log out" << endl;
    return getInput(0, 3);
}

void JobSeeker::Profile()
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
            edit_password("jobSeeker/");
        else
            break;
    }
}

void JobSeeker::displayProfile()
{
    system("CLS");
    cout << "\n\tProfile" << endl;
    cout << "\t@" << Username << endl;
    cout << "-------------------------------------" << endl;
    cout << "  Name    : " << Name << endl;
    cout << "  About me: " << About << endl;
    cout << "  Skill   : " << Skill << endl;
    cout << "  Email   : " << Email << endl;
    cout << "  Phone   : " << Phone << endl;
    cout << "  Resume  : " << Resume << endl;
    cout << "-------------------------------------" << endl;
}

void JobSeeker::editProfile()
{
    int choice;
    bool editMore = true;

    while (editMore)
    {
        system("CLS");
        cout << "\n\tEdit Profile" << endl;
        cout << "-------------------------------------" << endl;
        cout << "What information do you want to edit?" << endl;
        cout << "  1. Name    : " << Name << endl;
        cout << "  2. About me: " << About << endl;
        cout << "  3. Skill   : " << Skill << endl;
        cout << "  4. Email   : " << Email << endl;
        cout << "  5. Phone   : " << Phone << endl;
        cout << "  6. Resume  : " << Resume << endl;
        cout << "  0. Back to Profile" << endl;
        choice = getInput(0, 6);

        switch (choice)
        {
        case 1:
            cout << "Name  : ";
            getline(cin >> ws, Name);
            break;

        case 2:
            cout << "About : ";
            getline(cin >> ws, About);
            break;

        case 3:
            cout << "Skill : ";
            getline(cin>> ws, Skill);
            break;

        case 4:
            cout << "Email : ";
            getline(cin>> ws, Email);
            break;

        case 5:
            cout << "Phone : ";
            getline(cin>> ws, Phone);
            break;
        case 6:
            cout << "Resume(Link): ";
            getline(cin>> ws, Resume);
            break;
        case 0:
            editMore = false;
            break;
        }
        fstream file;
        file.open("jobSeeker/" + Username + "_profile.txt", ios::out);
        file << Name << "\n"
             << About << "\n"
             << Skill << "\n"
             << Email << "\n"
             << Phone << "\n"
             << Resume;
        file.close();
    }
}


