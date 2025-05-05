
class Post : public NODE
{
private:
    int number;
    int order;
    int status;
    string id;
    string company;
    string location;
    string title;
    string workType;
    int salary;
    string description;
    string requirement;
    string time;

public:
    Post(int, string, string, string, string, string, int, string, string, string);
    ~Post() {};
    void display();
    void show();
    
    void setNum(int n) { number = n; };
    void statusUpdate() { status = 1; };
    string getID() { return id; };
    int getSalary() { return salary; };
    int getOrder() { return order; };
    int getStatus() { return status; };
    int getNum() { return number; };
    string getCompany() { return company; };
};

Post::Post(int Order, string ID, string Company, string Location, string Title, string Type, int Salary, string Des, string Req, string Time)
{
    order = Order;
    id = ID;
    company = Company;
    location = Location;
    title = Title;
    workType = Type;
    salary = Salary;
    description = Des;
    requirement = Req;
    time = Time;
    status = 0;
}

void Post::display()
{
    cout << "| Company: " << company << " (" << location << ")" << endl;
    cout << "      |   Job: " << title << endl;
    cout << "      |   Work type: " << workType << endl;
    cout << "      |   Salary: " << salary << endl;
    cout << "      |   Description: " << description << endl;
    cout << "      |   Requirement: " << requirement << endl;
    cout << "      |   Posted on " << time << endl;
    cout << " -----+------------------------------" << endl;
}

void Post::show()
{
    cout << "    Company: " << company << " (" << location << ")" << endl;
    cout << "    Job: " << title << endl;
    cout << "    Work type: " << workType << endl;
    cout << "    Salary: " << salary << endl;
    cout << "    Description: " << description << endl;
    cout << "    Requirement: " << requirement << endl;
    cout << "    Posted on " << time << endl;
    cout << " --------------------------------------" << endl;
}
