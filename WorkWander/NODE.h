
class NODE
{
    NODE *next;
    NODE *appl;

public:
    NODE();
    virtual ~NODE();
    void insertNext(NODE *&);
    void insertAppl(NODE *&);
    NODE *move_next();
    NODE *move_appl();
    void setAppl(NODE *);
    //---------------------
    virtual void display() = 0;
    virtual void show() = 0;
    virtual void setNum(int) = 0;
    virtual string getID() = 0;
    virtual int getSalary() = 0;
    virtual int getOrder() = 0;
    virtual void statusUpdate() = 0;
    virtual int getStatus() = 0;
    virtual int getNum() = 0;
    virtual string getCompany() = 0;
};

NODE::NODE()
{
    next = NULL;
    appl = NULL;
    // cout << "adding " << x << endl;
}

NODE::~NODE()
{
    // cout << "Node " << data << " is being deleted" << endl;
}

NODE *NODE::move_next()
{
    return next;
}

NODE *NODE::move_appl()
{
    return appl;
}

void NODE::insertNext(NODE *&x)
{
    x->next = this;
}

void NODE::insertAppl(NODE *&x)
{
    this->appl = x;
}
void NODE::setAppl(NODE *A)
{
    appl = A;
}
