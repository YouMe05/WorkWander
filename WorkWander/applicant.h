
class Applicant : public NODE
{
private:
    string Name;
    string About;
    string Skill;
    string Email;
    string Phone;
    string Resume;

public:
    Applicant(string, string, string, string, string, string);
    ~Applicant() {};
    void display();
    
    void show(){};
    void setNum(int){};
    string getID() { return Name; };
    int getSalary() { return 0; };
    int getOrder() { return 0; };
    void statusUpdate(){};
    int getStatus() { return 0; };
    int getNum() { return 0; };
    string getCompany() { return "N/A"; };
};

Applicant::Applicant(string name, string about, string skill, string email, string phone, string resume)
{
    Name = name;
    About = about;
    Skill = skill;
    Email = email;
    Phone = phone;
    Resume = resume;
}

void Applicant::display()
{
    cout << "|   Name    : " << Name << endl;
    cout << "      |   About me: " << About << endl;
    cout << "      |   Skill   : " << Skill << endl;
    cout << "      |   Email   : " << Email << endl;
    cout << "      |   Phone   : " << Phone << endl;
    cout << "      |   Resume  : " << Resume << endl;
    cout << " -----+------------------------------" << endl;
}
