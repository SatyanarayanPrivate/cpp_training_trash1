#include <iostream>
#include <string>
using namespace std;

/*
- facade design
- reference variable
    - never return reference of local object.
- const pointer and pointer to const
- copy ctor
    - copy ctor should have always reference parameter, else stack overflow occure bcz if you as value copy ctor gets called recursively
- order of initialization should be matched with order declairation.
- new and delete
- containment
*/


namespace basic_facade {
class MessageTunnel
{
    string msg;
public:
    MessageTunnel (string msg): msg(msg)
    {
        cout << "MessageTunnel Ctor" << endl;
    }
    MessageTunnel & LogMessage () {
        cout << "Message logged (\" " << msg << "\")"<< endl;
        return *this;
    }
    MessageTunnel & StreamMessage () {
        cout << "Message Streamed (\" " << msg << "\")"<< endl;
        return *this;
    }
    MessageTunnel & EncodeMessage () {
        cout << "Message Encoded (\" " << msg << "\")"<< endl;
        return *this;
    }
    MessageTunnel & EncryptorMessage () {
        cout << "Message Encrypted (\" " << msg << "\")"<< endl;
        return *this;
    }
    MessageTunnel & SendMessage () {
        cout << "Message Sent (\" " << msg << "\")"<< endl;
        cout << "-----------------------------------------------"<<endl;
        return *this;
    }
};

enum class MessageOperations
{
    LogSend,
    EcrSend,
    EndEcrSend,
};

class MessageFacade {
    MessageTunnel msgtnl;
public:
    MessageFacade (string msg): msgtnl(msg){
        cout << "MessageFacade Ctor" << endl;
    }

    MessageTunnel EcrEdrSend() {
        // fluent api:: whoes operations may extend
        msgtnl.EncryptorMessage().EncodeMessage().SendMessage();
        return msgtnl;
    }

    MessageTunnel Operation(MessageOperations ch)
    {
        switch (ch) {
            case MessageOperations::LogSend: return msgtnl.LogMessage().SendMessage();
            case MessageOperations::EcrSend: return msgtnl.EncryptorMessage().SendMessage();
            case MessageOperations::EndEcrSend: return msgtnl.EncodeMessage().EncryptorMessage().SendMessage();
            default: return msgtnl;
        }
    }
};


int main () {

    MessageFacade mf("India is great");
    //mf.EcrEdrSend().LogMessage();

    mf.Operation(MessageOperations::LogSend);
    mf.Operation(MessageOperations::EcrSend);
    mf.Operation(MessageOperations::EndEcrSend).LogMessage();

    return 0;
}
}

namespace basic_copy_ctor {
class CA
{
public:
    int x;
    CA ()
    {
        cout << "CA Default Ctor" << endl;
    }
    CA (const CA &objref)
    {
        cout << "CA Copy Ctor" << endl;
    }
    ~CA ()
    {
        cout << "CA Dtor" << endl;
    }
};

CA fun ()
{
    CA obj;
    obj.x = 10;
    return obj;
}

int main1 () {
    //CA obj1;
    //obj1 = fun ();

    CA obj2 = fun();

    cout << "Apple" << endl;
    return 0;
}

void fun2 (CA obj) { }

void fun3 (CA & obj) { }

int main2 ()
{
    CA obj;
    //fun2(obj); // passby value:: uses copy ctor

    fun3(obj); // passby reference:: dont use copy ctor

    cout << "apple "<< endl;
    return 0;
}

class Employee
{
    int x;
    int y;
    int z;
public:
    Employee(int x, int y, int z): x(x), y(x), z(z)
    {
        cout << "Employee Default Ctor this = "<< this<< endl;
    }
    Employee(const Employee &objRef): x(objRef.x), y(objRef.x), z(objRef.z)
    {
        cout << "Employee Copy Ctor this = "<< this<< endl;
    }
    void Display () {
        cout << "this = " << this << endl;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
        cout << "---------------------------------" << endl;
    }
    ~Employee() { cout << "Employee Dtor this = "<< this << endl; }
};

int main ()
{
    Employee obj (11,12,13);
    Employee obj1 (obj);
    Employee obj2 = obj1;
    obj.Display();
    obj1.Display();
    obj2.Display();

    cout << "Apple" << endl;

    return 0;
}
}

namespace basic_facade01 {
#if 0
enum class AccountType {
    Saving,
    Current,
    DMat
};

enum class BuisenessOperations
{
    Credit,
    Debit,
    CheckBalance
};


class RBI
{
    string pan;
    double ammount;
    AccountType accType;
public:

    RBI (string pan, double ammount, AccountType accType): pan(pan), ammount(ammount), accType(accType)
    {
    }

    RBI & LogInfo ()
    {
        cout << "RBI logged for = " << pan << " value = "<< ammount << endl;
        return *this;
    }
};

class IT
{
    string pan;
    double ammount;
    AccountType accType;
public:

    IT (string pan, double ammount, AccountType accType): pan(pan), ammount(ammount), accType(accType)
    {
    }

    IT & Calculate ()
    {
        cout << "IT Calculating for = " << pan << " value = "<< ammount << endl;
        return *this;
    }
};

class Bank
{
    string pan;
    double ammount;
    AccountType accType;
public:

    Bank (string pan, double ammount, AccountType accType): pan(pan), ammount(ammount), accType(accType)
    {
    }

    Bank & Transaction ()
    {
        cout << "Bank Transaction for = " << pan << " value = "<< ammount << endl;
        return *this;
    }
};

class BuisenessBank
{
    RBI rbi;
    IT it;
    Bank bank;
public:
    BuisenessBank (string pan, double ammount, AccountType accType): rbi(pan, ammount, accType), it(pan, ammount, accType), bank(pan, ammount, accType)
    {
    }

    void Operation(BuisenessOperations ch, double amnt = 0.0)
    {
        switch (ch) {
            case BuisenessOperations:: Credit:
            {
                rbi.LogInfo();
                it.Calculate();
                bank.Transaction();
                cout << "-------------------------------------" << endl;
            }
            return;
            case BuisenessOperations:: Debit:
            {
                rbi.LogInfo();
                it.Calculate();
                bank.Transaction();
                cout << "-------------------------------------" << endl;
            }
            return;
            case BuisenessOperations:: CheckBalance:
            {

            }
            return ;
            default:
                cout << "invalid operation" << endl;
                return ;
        }
    }
};


int main ()
{
    BuisenessBank obj ("12345", 1000.00, AccountType::Current);

    obj.Operation(BuisenessOperations::CheckBalance);
    obj.Operation(BuisenessOperations::Credit, 1000.00);
    obj.Operation(BuisenessOperations::CheckBalance);
    obj.Operation(BuisenessOperations::Debit, 100.00);
    obj.Operation(BuisenessOperations::CheckBalance);
    return 0;
}
#endif // 0


enum class AccountType {
    Saving,
    Current,
    DMat
};

enum class BuisenessOperations
{
    Credit,
    Debit,
    CheckBalance
};

class IT;
class Bank;

class RBI
{
    string pan;
    double ammount;
    AccountType accType;
    IT *it;
public:

    RBI (string pan, double ammount, AccountType accType);

    IT & LogInfo ()
    {
        cout << "RBI logged for = " << pan << " value = "<< ammount << endl;
        return *it;
    }
    ~RBI () {
        delete it;
    }
};

class IT
{
    string pan;
    double ammount;
    AccountType accType;
    Bank *bank;
public:

    IT (string pan, double ammount, AccountType accType);

    Bank & Calculate ()
    {
        cout << "IT Calculating for = " << pan << " value = "<< ammount << endl;
        return *bank;
    }

    ~IT ()
    {
        delete bank;
    }
};

class Bank
{
    string pan;
    double ammount;
    AccountType accType;
public:

    Bank (string pan, double ammount, AccountType accType): pan(pan), ammount(ammount), accType(accType)
    {
    }

    Bank & Transaction ()
    {
        cout << "Bank Transaction for = " << pan << " value = "<< ammount << endl;
        return *this;
    }
};

RBI::RBI (string pan, double ammount, AccountType accType): pan(pan), ammount(ammount), accType(accType), it (new IT(pan, ammount, accType))   {}
IT::IT (string pan, double ammount, AccountType accType): pan(pan), ammount(ammount), accType(accType), bank(new Bank(pan, ammount, accType)) {}


class BuisenessBank
{
    RBI rbi;
public:
    BuisenessBank (string pan, double ammount, AccountType accType): rbi(pan, ammount, accType)
    {
    }

    void Operation(BuisenessOperations ch, double amnt = 0.0)
    {
        switch (ch) {
            case BuisenessOperations:: Credit:
            {
                rbi.LogInfo().Calculate().Transaction();
                cout << "-------------------------------------" << endl;
            }
            return;
            case BuisenessOperations:: Debit:
            {
                rbi.LogInfo().Calculate().Transaction();
                cout << "-------------------------------------" << endl;
            }
            return;
            case BuisenessOperations:: CheckBalance:
            {

            }
            return ;
            default:
                cout << "invalid operation" << endl;
                return ;
        }
    }
};


int main ()
{
    BuisenessBank obj ("12345", 1000.00, AccountType::Current);

    obj.Operation(BuisenessOperations::CheckBalance);
    obj.Operation(BuisenessOperations::Credit, 1000.00);
    obj.Operation(BuisenessOperations::CheckBalance);
    obj.Operation(BuisenessOperations::Debit, 100.00);
    obj.Operation(BuisenessOperations::CheckBalance);
    return 0;
}
}

namespace basics_containment {
class CA
{
    int x;
    int y;
    int z;
public:
    CA (int x, int y, int z): x(x), y(y), z(100)
    {
        cout << "CA Ctor" << endl;
    }
    CA (const CA &objRef): x(objRef.x), y(objRef.y), z(objRef.z)
    {
        cout << "CA Copy Ctor" << endl;
    }
    void Display() {
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
        cout << "------------------------------------" << endl;
    }
    ~CA () {
        cout << "CA Dtor" << endl;
    }
};

int main1 ()
{
    CA *ptr = new CA(1,23,4);
    CA *ptr1 = new CA(*ptr);


    delete ptr;
    delete ptr1;
    return 0;
}

class Wrapper
{
    CA *ptr;
public:
    Wrapper (): ptr(new CA(11,22,33))
    {
    }
    Wrapper (const Wrapper &ObjRef): ptr (new CA(*ObjRef.ptr))
    {
    }
    void Display()
    {
        ptr->Display();
    }
    ~Wrapper () {
        delete ptr;
    }
};

int main () {
    Wrapper obj;
    Wrapper obj1 (obj);
    Wrapper obj2 = obj;


    obj.Display();
    obj1.Display();
    obj2.Display();

    cout << "Appple" << endl;
    return 0;
}
}
// problem demnomination
class Currency
{
    int amnt;
public:
    Currency()
    {
    }
    void SetAmount (int amt)
    {
        amnt = amt;
    }
    Currency & GetCount (int para_currency)
    {
        int count_currency = 0x00;
        switch (para_currency)
        {
            //case 1000:
            case 2000:
            case 500:
            case 100:
            case 50:
            case 20:
            case 10:
            case 5:
            case 2:
            case 1:
                count_currency = amnt / para_currency;
                break;
            default:
                count_currency = 0x00;
                cout << para_currency << "\tX\t-" << "\t= \t" << "Invlalid currency"<< endl;
                return *this;
        }
        amnt = amnt % para_currency;
        cout << para_currency << "\tX\t" << count_currency << "\t= \t" << para_currency * count_currency << endl;
        return *this;
    }
};

class Denomination
{
    Currency crn;
public:
    Denomination()
    {
    }
    void GetCurrency(int amnt)
    {
        crn.SetAmount(amnt);
        crn.GetCount(2000).GetCount(1000).GetCount(500).GetCount(100).GetCount(50).GetCount(20).GetCount(10).GetCount(5).GetCount(2).GetCount(1);
    }
};


int main ()
{
    Denomination obj;
    obj.GetCurrency(2888);
    return 0;
}

