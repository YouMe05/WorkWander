
class LL
{
    NODE *hol;
    NODE *tail;
    int size;
    int not_show;

public:
    LL();
    ~LL();
    void newPost(NODE *&);
    void newAppl(NODE *&);
    int getSize() { return size; };
    int getNotShow() { return not_show; };

    void displayAllPost();
    void displayAllAppl();
    int inputPostNumber();
    string getPost();
    void displayApplied();
    void salaryFilter();
    void orderFilter();
    void displaybyFilter(int);
    void apply(User *user);
    void setStatus(string);
    void applied(string);
    void displayMyPost(User *user);
};

LL::LL()
{
    hol = NULL;
    tail = NULL;
    size = 0;
    not_show = 0;
}

LL::~LL()
{
    int i;
    for (i = 0; i < size; i++)
    {
        NODE *h = hol;
        tail = hol;
        if(tail->move_appl() != NULL){
            do {
                tail = tail->move_appl();
                NODE *t = tail;
                delete t;
            } while (tail->move_appl());
        }
        hol = hol->move_next();
        delete h;
    }
    size = 0;
}

void LL::newPost(NODE *&A)
{
    hol->insertNext(A);
    hol = A;
    tail = A;
    size++;
}

void LL::newAppl(NODE *&A)
{
    tail->insertAppl(A);
    tail = A;
}

int LL::inputPostNumber()
{
    string input;
    bool invalid;
    do
    {
        cout << "  Post number: ";
        invalid = false;
        getline(cin >> ws, input);
        for (char c : input)
        {
            if (!isdigit(c))
            {
                invalid = true;
                cout << "Invalid Input :(" << endl;
                break;
            }
        }
        if (invalid == false && stoi(input) == 0) {
            invalid = true;
            cout << "Invalid Input :(" << endl;
        }
    } while (invalid);

    return stoi(input);
}

void LL::displayAllPost()
{
    NODE *t = hol;
    int i;
    int count = 1;
    
    for (i = 0; i < size; i++)
    {
        if (t->getStatus() != 1)
        {
            cout << " " << setw(4) << count << ".";
            t->setNum(count);
            t->display();
            count++;
        }
        else {
            t->setNum(-1);
        }
        t = t->move_next();
    }
}

void LL::displayAllAppl()
{
    int postNum;
    string id;
    
    postNum = inputPostNumber();
   
    NODE *t = hol;
    NODE *a;
    int i = 1;
    bool not_found = true;
    system("CLS");
    cout << "\n\tAll Applicants" << endl;
    cout << "----------------------------------------" << endl;
    while (t != NULL)
    {
        a = t;
        if (t->getNum() == postNum)
        {
            not_found = false;
            a = a->move_appl();
            if (a == NULL){
                cout << "\n             No applicants\n" << endl;
                cout << "----------------------------------------" << endl;
                break;
            }
            while (a != NULL)
            {
                cout << " " << setw(4) << i << ".";
                a->display();
                a = a->move_appl();
                i++;
            }
            break;
        }
        t = t->move_next();
    }
    if(not_found) {
        cout << "\n            Post not found\n" << endl;
        cout << "----------------------------------------" << endl;
    }
}

string LL::getPost()
{
    int postNum;

    postNum = inputPostNumber();

    NODE *current = hol;

    while (current != NULL)
    {
        if (current->getNum() == postNum)
        {
            current->show();

            return current->getID();
        }

        current = current->move_next();
    }
    return "not found";
}

void LL::displayApplied() {
    NODE *t = hol;
    int i;
    bool no_applied = true;
    cout << "\n\tApplied Job" << endl;
    cout << "----------------------------------------" << endl;
    for (i = 0; i < size; i++)
    {
        if (t->getStatus() == 1)
        {
            t->show();
            no_applied = false;
        }
        t = t->move_next();
    }
    if (no_applied)
    {
        cout << " \n   You Haven't Applied to Any Jobs.\n" << endl;
    }
    cout << "\nPress Enter to Back to menu..." << endl;
    cin.get();
    cin.clear();
    cin.ignore(10000, '\n');
}

void LL::salaryFilter()
{
    NODE *before_key = hol;
    NODE *key;
    NODE *temp;
    NODE *before_t;

    do
    {
        key = before_key->move_next();
        NODE *t = hol;
        before_t = t;
        while (t != key)
        {
            if (key->getSalary() > t->getSalary())
            {
                temp = key->move_next();
                temp->insertNext(before_key);
                if (t != hol)
                {
                    key->insertNext(before_t);
                }
                t->insertNext(key);
                if (key->move_next() == hol)
                {
                    hol = key;
                }

                break;
            }
            before_t = t;
            t = t->move_next();
            if (t == key)
            {
                before_key = key;
            }
        }

    } while (before_key->move_next() != NULL);

    displayAllPost();
}

void LL::orderFilter()
{
    NODE *before_key = hol;
    NODE *key;
    NODE *temp;
    NODE *before_t;

    do
    {
        key = before_key->move_next();
        NODE *t = hol;
        before_t = t;
        while (t != key)
        {
            if (key->getOrder() > t->getOrder())
            {
                temp = key->move_next();
                temp->insertNext(before_key);
                if (t != hol)
                {
                    key->insertNext(before_t);
                }
                t->insertNext(key);
                if (key->move_next() == hol)
                {
                    hol = key;
                }

                break;
            }
            before_t = t;
            t = t->move_next();
            if (t == key)
            {
                before_key = key;
            }
        }

    } while (before_key->move_next() != NULL);

    displayAllPost();
}

void LL::displaybyFilter(int filter)
{
    cout << "  No. | Post" << endl;
    cout << "+-----+--------------------------------+" << endl;
    switch (filter)
    {
    case 1:
        orderFilter();
        break;
    case 2:
        salaryFilter();
        break;
    }
}

void LL::setStatus(string id)
{
    NODE *current = hol;

    while (current != NULL)
    {
        if (current->getID() == id)
        {
            current->statusUpdate();
            not_show++;
            break;
        }
        current = current->move_next();
    }
}

void LL::applied(string username) {
    string id;
    fstream file;
    file.open("jobSeeker/" + username + "_applied.txt", ios::in);
    if (!file) return;

    while (!file.eof())
    {
        NODE *current = hol;
        getline(file, id);
        if (id == "")
            break;

        setStatus(id);
    }
}

void LL::apply(User*user)
{
    int choice;
    fstream file;
    string id;
    while (true)
    {
        system("CLS");
        cout << "\n\tApply Job" << endl;
        cout << "-------------------------------------" << endl;
        id = getPost();
        if (id == "not found")
        {
            cout << "          Post Not Found:(\n"
                 << endl;
            cout << "Menu 1. Change post number\n     0. Back to view post" << endl;
            choice = user->getInput(0, 1);
            if (choice == 0)
                break;
        }
        else
        {
            cout << "Menu 1. Change post number\n     2. Apply Job\n     0. Back" << endl;
            choice = user->getInput(0, 2);
            if (choice == 2)
            {
                setStatus(id);
                file.open("jobSeeker/" + user->getUsername() + "_applied.txt", ios::app);
                file << id << endl;
                file.close();
                file.open("applicant/" + id + ".txt", ios::app);
                file << user->getUsername() << endl;
                file.close();
                system("CLS");
                cout << "\n\tApply Job" << endl;
                cout << "-------------------------------------\n" << endl;
                cout << "        Apply successfull:)\n\nPress Enter to Back to menu..." << endl;
                cin.get();
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            else if (choice == 0)
                break;
        }
    }
}

void LL::displayMyPost(User *user) {
    string id;
    int count, choice;
    bool no_post = true;

    while(true) {
        count = 1;
        system("CLS");
        cout << "\n\tMy Post" << endl;
        cout << "----------------------------------------" << endl;
        NODE *current = hol;
        while (current != NULL)
        {
            if (current->getCompany() == user->getName())
            {
                no_post = false;
                cout << " " << setw(4) << count << ".";
                current->setNum(count);
                current->display();
                count++;
            }
            current = current->move_next();
        }

        if(no_post) {
            cin.ignore();
            cout << "\n           No posts yet.\n" << endl;
            cout << "Press Enter to Back to menu..." << endl;
            cin.get();
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
        else {
            cout << "Menu 1. View applicant with post number\n     0. Back to menu" << endl;
            choice = user->getInput(0,1);
            if(choice == 1){
                system("CLS");
                cout << "\n\tView Applicants" << endl;
                cout << "-------------------------------------" << endl;
                displayAllAppl();
                cout << "Menu 1. Back to my post\n     2. Back to menu" << endl;
                choice = user->getInput(1, 2);
                if(choice == 2) return;
            }
            else return;
        }
    }
}
