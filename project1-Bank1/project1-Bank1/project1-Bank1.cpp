#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowMainMenue();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

vector<string>SpiltString(string S1, string Delim)
{
    vector<string>vString;
    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }


    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

sClient ConverLineToRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string>vClientData;
    vClientData = SpiltString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

string ConverRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

bool ClientExistByAccoutNumber(string AccountNumber, string FileName)
{
    vector<sClient>vClient;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConverLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClient.push_back(Client);
        }

        MyFile.close();
    }

    return false;
}

sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistByAccoutNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Accout Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccoutBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

vector<sClient>LoadClientsDataFromFile(string FileName)
{
    vector<sClient>vClient;
    fstream Myfile;
    Myfile.open(FileName, ios::in);

    if (Myfile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(Myfile, Line))
        {
            Client = ConverLineToRecord(Line);
            vClient.push_back(Client);
        }
        Myfile.close();
    }
    return vClient;
}

void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
    vector<sClient>vClient = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClient.size() << ") Client(s).";
    cout << "\n\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClient.size() == 0)
        cout << "\t\t\tNo Clients Available In the system!";
    else
    {
        for (sClient Client : vClient)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }
    }
    cout << "\n\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;


}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccount Number: " << Client.AccountNumber;
    cout << "\nPin Code      : " << Client.PinCode;
    cout << "\nName          : " << Client.Name;
    cout << "\nPhone         : " << Client.Phone;
    cout << "\nAccout Balance: " << Client.AccountBalance;
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient>vClient, sClient& Client)
{
    for (sClient C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

sClient ChangeClientRecord(string AccoutNumber)
{
    sClient Client;

    Client.AccountNumber = AccoutNumber;

    cout << "\n\nEnter Pin Code? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool MarkClientForDelteByAccoutNumber(string AccoutNumber, vector<sClient>& vClient)
{
    for (sClient& C : vClient)
    {
        if (C.AccountNumber == AccoutNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

vector<sClient>SaveClientsDataToFile(string FileName, vector<sClient>vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConverRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }

    return vClients;
}

void AddDataLineToFile(string FileName, string stdataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stdataLine << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConverRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';

    do
    {
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccoutNumber(string AccountNumber, vector<sClient>& vClient)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'y')
        {
            MarkClientForDelteByAccoutNumber(AccountNumber, vClient);
            SaveClientsDataToFile(ClientsFileName, vClient);

            vClient = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClinet Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Accout Number (" << AccountNumber << ") is Not Found! ";
        return false;
    }
}

bool UpdateClientByAccoutNumber(string AccountNumber, vector<sClient>& vClient)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClient)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientsDataToFile(ClientsFileName, vClient);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

string ReadClientAccoutNumber()
{
    string AccoutNumber = "";

    cout << "\nplease enter AccoutNumber? ";
    cin >> AccoutNumber;
    return AccoutNumber;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Clinet Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient>vClient = LoadClientsDataFromFile(ClientsFileName);

    string AccoutNumber = ReadClientAccoutNumber();
    DeleteClientByAccoutNumber(AccoutNumber, vClient);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccoutNumber();
    UpdateClientByAccoutNumber(AccountNumber, vClients);

}

void ShowAddNewClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddNewClients();

}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccoutNumber();

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eExit = 6
};

void GoBackToMainMenue()
{
    cout << "\n\nPredd any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}

short ReadMinMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void PerFromMainmenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
        break;
    }
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "===========================================\n";
    PerFromMainmenueOption((enMainMenueOptions)ReadMinMenueOption());

}

int main()
{
    ShowMainMenue();

    system("pause>0");
    return 0;
}

