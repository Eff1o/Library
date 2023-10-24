
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <ctime>


using namespace std;

struct Lbook {
    int id;
    
    string author;

    string title;

    int user_id_borrow = 0;
};


struct Ldataq {
    int rok = 0;
    int miesiac = 0;
    int dzien = 0;
};


struct Lborrowed_book {
    int id=0;
    Ldataq borrow_data;
};

struct Luser {
    int id;

    string name_lastname;   

    Lborrowed_book borrowed_book[5];

    bool block = false;
};


fstream fbooks;
fstream fusers;

Ldataq todays_data;


string data;
string key;

Lbook book;

Luser user;

Lbook books[25];

Luser users[25];

int last_user_id =1 , number_of_users =0;
int last_book_id = 1, number_of_books= 0;

// biblioteczka \\


// wywalilo program przy ustawianiu normalnej daty repro-rate 1/10
int main()
{
    cout << "|Witaj uzytkowniku najlepszej biblioteki w Polsce. Prosze o wprowadzenie dzisiejszej daty|:" << endl;;
    // przy podaniu litery program wywala repro-rate 5/5
    cout << "|Prosze podac Rok|: ";
    cin >> data;
    todays_data.rok = stoi(data);
    cout << "|Prosze podac Miesiac|: ";
    cin >> data;
    todays_data.miesiac = stoi(data);
    cout << "|Prosze podac Dzien|: ";
    cin >> data;
    cout << "|Przetwarzam podane dane - prosze czekac|";
    todays_data.dzien = stoi(data);

    fbooks.open("books.txt", ios::in);
    if (!fbooks.good())

    {
        cout << "\nNIE MA PLIKU -_-\n";
        return 0;
    }

    string temp;
    getline(fbooks, temp, ';');

    getline(fbooks, temp);
    last_book_id = stoi(temp);

    number_of_books = stoi(temp);


    // wariant test 

    for (int i = 0; i < number_of_books; i++) {

        getline(fbooks, temp, ';');
        books[i].id = stoi(temp);
        getline(fbooks, books[i].author, ';');
        getline(fbooks, books[i].title, ';');


        getline(fbooks, temp);
    // do uzytkownikow
        books[i].user_id_borrow = stoi(temp);        
    }

    fbooks.close();


    fbooks.open("users.txt", ios::in);
    if (!fusers.good())
    {
        cout << "\nNIE MA PLIKU -_-\n";
        return 0;
    }

    
    getline(fusers, temp, ';');

    getline(fusers, temp);

    for (int i = 0; i < number_of_users; i++) {

        getline(fusers, users[i].name_lastname, ';');             



        for (int j = 0; j < 5; j++) {
            getline(fusers, temp, ';');
            users[i].borrowed_book[j].id = stoi(temp);               
            getline(fusers, temp, ';');
            users[i].borrowed_book[j].borrow_data.rok = stoi(temp);
            getline(fusers, temp, ';');
            users[i].borrowed_book[j].borrow_data.miesiac = stoi(temp);
            getline(fusers, temp, ';');
            users[i].borrowed_book[j].borrow_data.dzien = stoi(temp);              
        }        

       getline(fusers, temp);
        if (stoi(temp)) users[i].block = true;
        cout << endl;
    }

    fusers.close();


    system("cls");

    cout << "|====================[NAJLEPSZE KSIAZKI NASZYCH CZASOW]====================|" << endl;
    cout << "|[DZISIEJSZA DATA]|: " << todays_data.rok << "." << todays_data.miesiac << "." << todays_data.dzien << endl;

    cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|"<<endl;

    while (1) {    
        cout << endl;
        cout << "========[Panel Uzytkownika]==========:" << endl;

        cout << "|Wybierz [1] aby dodac nowego uzytkownika do biblioteki|" << endl;

        cout << "|Wybierz [2] aby wypozyczyc nowa ksiazke|" << endl;

        cout << "|Wybierz [3] aby dodac nowa ksiazke|" << endl;

        cout << "|Wybierz [4] aby usunac ksiazke|" << endl;

        cout << "|[OPCJA ADMINISTRATORA] Wybierz [5] aby dokonac edycji danych|" << endl;

        cout << "|Wybierz [6] aby wyswietlic wszystkich uzytkownikow|" << endl;

        cout << "|[OPCJA ADMINISTRATORA] Wybierz [7] aby dokonac edycji uzytkownika biblioteki|" << endl;

        cout << "|[OPCJA ADMINISTRATORA] Wybierz [8] aby dokonac trwalego usuniecia uzytkownika biblioteki|" << endl;

        cout << "|Wybierz [9] aby wyswietlic wszystkie ksiazki|" << endl;

        cout << "|[PANEL KSIAZEK] Wybierz [10] aby zwrocic wybrana ksiazke|" << endl;

        cout << "|[WYBRANA LICZBA DO WYKONANIA AKCJI]:" << endl;

        cin >> key;



        if (key == "6") {

            system("cls");

            cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;

            cout << "|AKTYWNI UZYTKOWNICY|:" << endl;

            cout << "|[========]. \t [ID KSIAZKI]]. \t [IMIE I NAZWISKO] \t [WYPOZYCZONE KSIAZKI]| \t" << endl;

            for (int i = 0; i < number_of_users; i++) {

                cout << i << "\t " << users[i].id << "\t" << users[i].name_lastname << "\t" << "\t" << "\t";


                int number_of_borrowed_books = 0;


                for (int j = 0; j < 5; j++) {
                    if (users[i].borrowed_book[j].id != 0)
                        number_of_borrowed_books++;
                }

                cout << number_of_borrowed_books << "\t";

                if (users[i].block) cout << "X";
                cout << endl;
            }

        }
            // program normalnie wyswietla 5 ksiazek, ale przy wypozyczaniu sa 2 albo 3 - potrzebny fix
            if (key == "9") {

                system("cls");

                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;

                cout << "Ksiazki:" << endl;

                cout << "|[========]. \t [NUMER]. \t [AUTOR]  \t \t \t [TYTUL] \t \t \t [ZAJETA PRZEZ]|" << endl;


                for (int i = 0; i < number_of_books; i++) {

                    cout << i << "\t " << books[i].id << "\t \t" << books[i].author << "\t \t" << books[i].title << "\t \t";

                    for (int j = 0; j < number_of_users; j++) {

                        if (users[j].id == books[i].user_id_borrow) cout << users[j].name_lastname;
                    }
                    cout << endl;
                }

            }

            if (key == "3") {

                last_book_id ++;

                books[number_of_books].id = last_book_id;

                // podanie tylko imienia wywala program? repro 1/10 sprawdzic 

                cout << "|==========[PANEL DODANIA KSIAZKI - PROSZE PODAC IMIE I NAZWISKO AUTORA]==========|" << endl
                ;
                cin.ignore();

                getline(cin, data);

                books[number_of_books].author = data;
                
                cout << "|[PROSZE PODAC TYTUL]|" << endl;

                cin.ignore();
                getline(cin, data);        

                books[number_of_books].title = data;

                number_of_books++;

                system("cls");

                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;



                cout << "[KSIAZKI]:" << endl;

                cout << "|[========]. \t [NUMER]. \t [AUTOR]  \t \t \t [TYTUL] \t \t \t [ZAJETA PRZEZ]|" << endl;

                for (int i = 0; i < number_of_books; i++) {

                    cout << i << "\t " << books[i].id << "\t \t" << books[i].author << "\t \t" << books[i].title;

                    if (books[i].user_id_borrow != 0) {

                        for (int j = 0; j < number_of_users; j++) {

                            if (users[j].id == books[j].user_id_borrow) cout << users[j].name_lastname;
                        }
                    }
                    cout << endl;
                }

                fbooks.open("books.txt", ios::out);
                
                if (!fbooks.good())
                {
                    cout << "\nNIE MA PLIKU -_-\n";
                    return 0;
                }

                fbooks << number_of_books << ";" << last_book_id << "\n";
                for (int i = 0; i < number_of_books; i++)

                {
                    fbooks << books[i].id << ";" << books[i].author << ";" << books[i].title << ";" << books[i].user_id_borrow << "\n";
                }

                fbooks.close(); 

                cout << "|[KSIAZKA ZOSTALA DODANA POMYSLNIE]|";

                cout << endl;
            }


            if (key == "1") {

                last_user_id++;

                users[number_of_users].id = last_user_id;

                cout << "|[WPISZ IMIE I NAZWISKO UZYTKOWNIKA]|" << endl;


                cin.ignore();
                getline(cin, data);

                users[number_of_users].name_lastname = data;

                number_of_users++;



                system("cls");


                
                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;

                cout << "|[WYBRANI UZYTKOWNICY]|:" << endl;

                cout << "[ID] \t [IMIE I NAZWISKO]] \t [=======]" << endl;

                for (int i = 0; i < number_of_users; i++) {

                    cout << users[i].id << "\t" << users[i].name_lastname << "\t";

                    if (users[i].block) cout << "X";

                    cout << endl;
                }

                fusers.open("users.txt", ios::out);

                // gdzies tu jest problem - uzytkownik resetuje sie przy ponowym uruchomieniu programu - repro-rate 5/5 (data?)

                if (!fusers.good())
                {
                    cout << "\nNIE MA PLIKU -_-\n";
                    return 0;
                }
                fusers << number_of_users << ";" << last_user_id << "\n";

                for (int i = 0; i < number_of_users; i++)
                {
                    fusers << users[i].id << ";" << users[i].name_lastname << ";";

                    for (int j = 0; j < 5; j++)
                    {
                        fusers << users[i].borrowed_book[j].id << ";"
                            << users[i].borrowed_book[j].borrow_data.rok << ";"
                            << users[i].borrowed_book[j].borrow_data.miesiac << ";"
                          << users[i].borrowed_book[j].borrow_data.dzien << ";";
                    }

                    fusers << users[i].block << "\n";
                }
                fusers.close();

                cout << endl;

                cout << "|[UZYTKOWNIK ZOSTAL DODANY POMYSLNIE]|";
            }

            if (key == "7") {



                system("cls");



                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;

                cout << "|[AKTYWNI UZYTKOWNICY]|:" << endl;

                cout << "|[=====] \t [ID] \t [IMIE I NAZWISKO] \t [====]|" << endl;

                for (int i = 0; i < number_of_users; i++) {

                    cout << i << "\t " << users[i].id << "\t" << users[i].name_lastname << "\t";
                    if (users[i].block) cout << "X";
                    cout << endl;
                }
                cout << endl;

                cout << "[PROSZE PODAC ID UZYTKOWNIKA]:";

                cin >> data;
                int edit_id = stoi(data); 

                int edit_user=0;
                
                for (int i = 0; i < number_of_users; i++) {
                    if (users[i].id == edit_id)edit_user = i;
                }

                cout << "[PROSZE PODAC IMIE I NAZWISKO UZYTKOWNIKA]:" << endl;

                cin.ignore();
                getline(cin, data);

                users[edit_user].name_lastname = data;
                
                system("cls");

                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;

                cout << "|[AKTYWNI UZYTKOWNICY]|:" << endl;

                cout << "|[=====] \t [ID] \t [IMIE I NAZWISKO] \t [====]|" << endl;

                for (int i = 0; i < number_of_users; i++) {

                    cout << users[i].id << "\t" << users[i].name_lastname << "\t";
                    if (users[i].block) cout << "X";
                    cout << endl;
                }

                fusers.open("users.txt", ios::out);
                if (!fusers.good())
                {
                    cout << "\nNIE MA PLIKU -_-\n";
                    return 0;
                }
                fusers << number_of_users << ";" << last_user_id << "\n";
                for (int i = 0; i < number_of_users; i++)
                {
                    fusers << users[i].id << ";" << users[i].name_lastname << ";";

                    for (int j = 0; j < 5; j++)
                    {
                        fusers << users[i].borrowed_book[j].id << ";"
                            << users[i].borrowed_book[j].borrow_data.rok << ";"
                            << users[i].borrowed_book[j].borrow_data.miesiac << ";"
                           << users[i].borrowed_book[j].borrow_data.dzien << ";";
                    }

                    fusers << users[i].block << "\n";
                }
                fusers.close();

                cout << endl;
                cout << "|[UZYTKOWNIK ZOSTAL DODANY POMYSLNIE]|";
            }
        
            if (key == "8") {

                system("cls");

                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;

                cout << "|[AKTYWNI UZYTKOWNICY]|:" << endl;

                cout << "|[=====] \t [ID] \t [IMIE I NAZWISKO] \t [====]|" << endl;

                for (int i = 0; i < number_of_users; i++) {

                    cout << i << "\t " << users[i].id << "\t" << users[i].name_lastname << "\t";
                    if (users[i].block) cout << "X";
                    cout << endl;
                }
                cout << endl;

                cout << "[PROSZE PODAC IMIE I NAZWISKO UZYTKOWNIKA]:";

                cin >> data;

                int edit_id = stoi(data);

                int edit_user = 0;

                for (int i = 0; i < number_of_users; i++) {
                    if (users[i].id == edit_id)edit_user = i;

                    
                }

                bool if_blocked = false;     
                

                if (users[edit_user].block) if_blocked = true;

                else  
                {
                    for (int j = 0; j < 5; j++) {
                        if (users[edit_user].borrowed_book[j].id != 0)
                            if_blocked = true;
                    }
                }


                
                fusers.open("users.txt", ios::out);
                if (!fusers.good())
                {
                    cout << "\nNIE MA PLIKU -_-\n";
                    return 0;
                }
                fusers << number_of_users << ";" << last_user_id << "\n";
                for (int i = 0; i < number_of_users; i++)
                {
                    fusers << users[i].id << ";" << users[i].name_lastname << ";";

                    for (int j = 0; j < 5; j++)
                    {
                        fusers << users[i].borrowed_book[j].id << ";"
                            << users[i].borrowed_book[j].borrow_data.rok << ";"
                            << users[i].borrowed_book[j].borrow_data.miesiac << ";"
                            << users[i].borrowed_book[j].borrow_data.dzien << ";";
                    }

                    fusers << users[i].block << "\n";
                }
                fusers.close();
                

                system("cls");

                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;

                cout << "|[AKTYWNI UZYTKOWNICY]|:" << endl;


                cout << "|[=====] \t [ID] \t [IMIE I NAZWISKO] \t [====]|" << endl;



                for (int i = 0; i < number_of_users; i++) {

                    cout << users[i].id << "\t" << users[i].name_lastname << "\t";

                    if (users[i].block) cout << "X";
                    cout << endl;
                }



                cout << endl;
                if (if_blocked == true) cout << "[blad]|NIE MOZNA USUNAC UZYTKOWNIKA Z WYPOZYCZONYMI KSIAZKAMI, PROSZE SPROBOWAC PONOWNIE POZNIEJ|";


                if (if_blocked == false) cout << "[System Biblioteki wykonal zadanie]";

                cout << endl;

            }

            // program moze wywalac i wyswietla tylko 2 ksiazki - wypozyczanie

            if (key == "2") {

                system("cls");

                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;


                cout << "|[AKTYWNI UZYTKOWNICY]|:" << endl;


                cout << "|[=====] \t [ID] \t [IMIE I NAZWISKO] \t [====]|" << endl;

                for (int i = 0; i < number_of_users; i++) {

                    int number_of_borrowed_books = 0;

                    for (int j = 0; j < 5; j++) {
                        if (users[i].borrowed_book[j].id != 0)
                            number_of_borrowed_books ++;
                    }

                    if (number_of_borrowed_books < 5 && users[i].block == false) {

                        cout << i << "\t " << users[i].id << "\t" << users[i].name_lastname << "\t";
                        
                        cout << endl;
                    }
                }
                cout << endl;

                bool true_id=true;

                int edit_user_id;

                int user_borrow = 0;

                
                while (true_id) {
                    cout << "[PROSZE PODAC ID UZYTKOWNIKA]:";
                    cin     >> data;
                    edit_user_id = stoi(data);
                    int number_of_borrowed_books = 0;
                    for (int i = 0; i < number_of_users; i++) {
                        if (users[i].id == edit_user_id)user_borrow = i;
                    }
                    for (int j = 0; j < 5; j++) {
                        if (users[user_borrow].borrowed_book[j].id != 0)
                            number_of_borrowed_books++;
                    }
                    if ( number_of_borrowed_books < 5 && users[user_borrow].block == false && user_borrow < number_of_users) 
                        true_id = false;

                }             

                cout << "[UZYTKOWNIK WYBRANY]:" << users[user_borrow].name_lastname ;

                cout << endl;

                cout << "[KSIAZKI]:" << endl;

                cout << "|[========]. \t [NUMER]. \t [AUTOR]  \t \t \t [TYTUL] \t \t \t [ZAJETA PRZEZ]|" << endl;

                for (int i = 0; i < number_of_books; i++) {

                    if (books[i].user_id_borrow == 0)
                    {
                        cout << i << "\t " << books[i].id << "\t \t" << books[i].author << "\t \t" << books[i].title;
                        cout << endl;
                    }
                }

                true_id = true;

                int edit_book_id = 0;

                int borrowed_book = 0;
                

                // raczej problem z id ksiazki repro-rate 5/5

                while (true_id) {
                    cout << "[PROSZE PODAC ID KSIAZKI]";
                    cin >> data;
                    edit_book_id = stoi(data);

                    for (int i = 0; i < number_of_books; i++) {
                        if (books[i].id == edit_book_id)borrowed_book = i;
                    }

                    if (books[borrowed_book].user_id_borrow == 0 && borrowed_book < number_of_books) true_id = false;
                }
               
                books[borrowed_book].user_id_borrow = edit_user_id;

                for (int j = 0; j < 5; j++) {
                    if (users[user_borrow].borrowed_book[j].id == 0)
                    {
                        users[user_borrow].borrowed_book[j].id = edit_book_id;
                        break;
                    }
                }

                fusers.open("users.txt", ios::out);
                if (!fusers.good())
                {
                    cout << "\nNIE MA PLIKU -_-\n";
                    return 0;
                }
                fusers << number_of_users << ";" << last_user_id << "\n";
                for (int i = 0; i < number_of_users; i++)
                {
                    fusers << users[i].id << ";" << users[i].name_lastname << ";";

                    for (int j = 0; j < 5; j++)
                    {
                        fusers << users[i].borrowed_book[j].id << ";"
                            << users[i].borrowed_book[j].borrow_data.rok << ";"
                           << users[i].borrowed_book[j].borrow_data.miesiac << ";"
                            << users[i].borrowed_book[j].borrow_data.dzien << ";";
                    }

                    fusers << users[i].block << "\n";
                }
                fusers.close();

                fbooks.open("books.txt", ios::out);
                if (!fbooks.good())
                {
                    cout << "\nNIE MA PLIKU -_-\n";
                    return 0;
                }
                fbooks << number_of_books << ";" << last_book_id << "\n";
                for (int i = 0; i < number_of_books; i++) 
                {
                    fbooks << books[i].id << ";" << books[i].author << ";" << books[i].title << ";" << books[i].user_id_borrow << "\n";
                }
                fbooks.close();

                system("cls");

                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;

                cout << "[KSIAZKI]:" << endl;


                cout << "|[========]. \t [NUMER]. \t [AUTOR]  \t \t \t [TYTUL] \t \t \t [ZAJETA PRZEZ]|" << endl;

                for (int i = 0; i < number_of_books; i++) {



                    cout << i << "\t " << books[i].id << "\t \t" << books[i].author << "\t \t" << books[i].title << "\t \t" ;
                    if (books[i].user_id_borrow != 0) {

                        for (int j = 0; j < number_of_users; j++) {
                            if (users[j].id == books[i].user_id_borrow) cout << users[j].name_lastname;
                        }
                    }
                    cout << endl;
                }

                cout << "[KSIAZKA]" << books[borrowed_book].title  << "|WYPOZYCZONA DLA UZYTKOWNIKA|:" << users[user_borrow].name_lastname ;
                cout << endl;
                cout << endl;

            }


            if (key == "10") {

                system("cls");

                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;

                cout << "[WYPOZYCZONE KSIAZKI]:" << endl;

                cout << "|[========]. \t [NUMER]. \t [AUTOR]  \t \t \t [TYTUL] \t \t \t [ZAJETA PRZEZ]|" << endl;
                
                // program wyswietla uzytkownikowi wypozyczone wszystkie ksiazki - repro 5/5 

                for (int i = 0; i < number_of_books; i++) {
                    if (books[i].user_id_borrow != 0) {
                        cout << i << "\t " << books[i].id << "\t \t" << books[i].author << "\t \t" << books[i].title << "\t \t";
                        for (int j = 0; j < number_of_users; j++) {
                            if (users[j].id == books[i].user_id_borrow) cout << users[j].name_lastname;
                        }
                        cout << endl;
                    }
                    
                }

                bool true_id = true;
                int edit_book_id = 0;
                int borrowed_book = 0;


                while (true_id) {
                    cout << "[PODAJ ID KSIAZKI]:";
                    cin >> data;
                    edit_book_id = stoi(data);

                    for (int i = 0; i < number_of_books; i++) {
                        if (books[i].id == edit_book_id)borrowed_book = i;
                    }

                    if (books[borrowed_book].user_id_borrow != 0 && borrowed_book< number_of_books) true_id = false;
                }

                int edit_user = 0;

                for (int i = 0; i < number_of_books; i++) {
                    if (users[i].id == books[borrowed_book].user_id_borrow)edit_user = i;


                }

                for (int j = 0; j < 5; j++) {
                    if (users[edit_user].borrowed_book[j].id == edit_book_id)
                    {
                        users[edit_user].borrowed_book[j].id = 0;
                       users[edit_user].borrowed_book[j].borrow_data.rok = 0;
                       users[edit_user].borrowed_book[j].borrow_data.miesiac = 0;
                     users[edit_user].borrowed_book[j].borrow_data.dzien = 0;
                       break;
                    }
                }




                for (int i = 0; i < number_of_users; i++) {

                    users[i].block = false;
                    for (int j = 0; j < 5; j++) {

                        if (users[i].borrowed_book[j].id != 0) {
                           Ldataq back_data = {
                           users[i].borrowed_book[j].borrow_data.rok,
                           users[i].borrowed_book[j].borrow_data.miesiac + 3,
                            users[i].borrowed_book[j].borrow_data.dzien
                            };

                           bool terminated  = false; //przeterminowa

                           if ((todays_data.rok - back_data.rok) > 1) terminated = true;
                            if ((todays_data.rok - back_data.rok) == 1 && ((back_data.miesiac - 12 < todays_data.miesiac)))
                                terminated = true;
                           if ((todays_data.rok - back_data.rok) == 1 && ((back_data.miesiac - 12 == todays_data.miesiac)))
                                if (todays_data.dzien > back_data.dzien) terminated = true;
                           if ((todays_data.rok == back_data.rok) && ((todays_data.miesiac > back_data.miesiac)))
                                terminated = true;
                            if ((todays_data.rok == back_data.rok) && ((todays_data.miesiac = back_data.miesiac)))
                                if (todays_data.dzien > back_data.dzien) terminated = true;

                            if (terminated) users[i].block = true;
                        }

                    }
                }

                // to chyba nie dziala?

                fusers.open("users.txt", ios::out);
                if (!fusers.good())
                {
                    cout << "\nNIE MA PLIKU -_-\n";
                    return 0;
                }
                fusers << number_of_users << ";" << last_user_id << "\n";
                for (int i = 0; i < number_of_users; i++)
                {
                    fusers << users[i].id << ";" << users[i].name_lastname << ";";

                    for (int j = 0; j < 5; j++)
                    {
                        fusers << users[i].borrowed_book[j].id << ";"

                            << users[i].borrowed_book[j].borrow_data.rok << ";"
                           << users[i].borrowed_book[j].borrow_data.miesiac << ";"
                            << users[i].borrowed_book[j].borrow_data.dzien << ";";
                    }

                    fusers << users[i].block << "\n";
                }
                fusers.close();

                system("cls");

                books[borrowed_book].user_id_borrow = 0;

                fbooks.open("books.txt", ios::out);
                if (!fbooks.good())
                {
                    cout << "\nNIE MA PLIKU -_-\n";
                    return 0;
                }
                fbooks << number_of_books << ";" << last_book_id << "\n";
                for (int i = 0; i < number_of_books; i++)
                {
                    fbooks << books[i].id << ";" << books[i].author << ";" << books[i].title << ";" << books[i].user_id_borrow << "\n";
                }
                fbooks.close();



                            
                system("cls");




                cout << "|====================[BIBLIOTEKA NAJLEPSZYCH KSIAZEK]====================|" << endl << endl;

                cout << "[WYPOZYCZONE KSIAZKI]" << endl;

                cout << "|[========]. \t [NUMER]. \t [AUTOR]  \t \t \t [TYTUL] \t \t \t [ZAJETA PRZEZ]|" << endl;

                for (int i = 0; i < number_of_books; i++) {
                    if (books[i].user_id_borrow != 0) {
                        cout << i << "\t " << books[i].id << "\t \t" << books[i].author << "\t \t" << books[i].title << "\t \t";
                        for (int j = 0; j < number_of_users; j++) {
                            if (users[j].id == books[i].user_id_borrow) cout << users[j].name_lastname;
                        }
                        cout << endl;
                    }

                }
                cout << endl;
                cout << endl;

            }
    }
    // 
}


