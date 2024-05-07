#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
using namespace std;
void instruction ();
int random_number (int);
void clear_screen ();
void result (bool);
void setting ();
void adjust ();
void exit ();
void name ();
int main(){

int i, size, temp, count=0, random, rows, columns, rocks, coins, x, life, bombs, elixir, score, first_action, count_coins, arr_score[100];
bool lost, settings=false, close_console=true;
string your_name, arr_name[1000];
char close;

while (close_console) {

instruction(); cin>>first_action; clear_screen ();

switch (first_action)
{
case 1:
{
  if (!settings) { adjust (); cin>>close; clear_screen ();  break; }
  else
  {
    name (); cin>>your_name; clear_screen ();

    size=rows*columns, random=random_number (columns);

    char* shape;
    shape=new char[size];

    char action;     score=0;     x=0; lost=true;     life=temp;
    for (i=1;i<size;i++)
    shape[i]='#';
    int count_rocks=0;
    for (i=random;;i+=columns+2)
    { shape[i]='@'; count_rocks++; if (count_rocks==rocks) break; }
    count_coins=0;
    for (i=random+2;;i+=columns+3)
    { shape[i]='$'; count_coins++; if (count_coins==coins) break; }
    int count_bombs=0;
    for (i=random+4;;i+=columns+7)
    { shape[i]='B'; count_bombs++; if (count_bombs==bombs) break; }
    int count_elixir=0;
    for (i=random+6;;i+=columns+7)
    { shape[i]='P'; count_elixir++; if (count_elixir==elixir) break; }
    shape[0]='i';

    for (i=0;i<size;i++)
    {
        cout<<shape[i]<<" "; 
        if ((i+1)%columns==0) cout<<"\n";
        if (i==size-1) cout<<"score: "<<score<<"\n"<<"life: "<<life<<"\n"<<"Input: ";
    }

    count_coins=0;

    while (true)
    {
        cin>>action; clear_screen ();
        switch (action)
    {
        case 'w': 
        {
            if ((shape[x-columns]=='@') || (shape[x-columns]=='#') || (x<columns)) break;
            else if (shape[x-columns]=='P') { life++; shape[x-columns]=' '; }
                 else if (shape[x-columns]=='B') { life--; shape[x-columns]=' '; if (life==0) { lost=false; result (false); } }
                      else if (shape[x-columns]=='$') { score++; shape[x-columns]=' '; count_coins++; if (count_coins==coins) result (true); }
                           else { shape[x-columns]=shape[x]; shape[x]=' '; x-=columns; }
        }
        break;
        case 's': 
        {
            if ((shape[x+columns]=='@') || (shape[x+columns]=='#') || (x>(((rows-1)*columns)-1))) break;
            else if (shape[x+columns]=='P') { life++; shape[x+columns]=' '; }
                 else if (shape[x+columns]=='B') { life--; shape[x+columns]=' '; if (life==0) { lost=false; result (false); } }
                      else if (shape[x+columns]=='$') { score++; shape[x+columns]=' '; count_coins++; if (count_coins==coins) result (true); }
                           else { shape[x+columns]=shape[x]; shape[x]=' '; x+=columns; }
        }
        break;
        case 'a':
        {
            if ((shape[x-1]=='@') || (shape[x-1]=='#') || (x%columns==0)) break;
            else if (shape[x-1]=='P') { life++; shape[x-1]=' '; }
                 else if (shape[x-1]=='$') { score++; shape[x-1]=' '; count_coins++; if (count_coins==coins) result (true); }
                      else if (shape[x-1]=='B') { shape[x-1]=' '; life--; if (life==0) { lost=false; result (false); } }
                           else { shape[x-1]=shape[x]; shape[x]=' '; x-=1; }
        }
        break;
        case 'd':
        {
            if ((shape[x+1]=='@') || (shape[x+1]=='#') || ((x+1)%columns==0)) break;
            else if (shape[x+1]=='P') { life++; shape[x+1]=' '; }
                 else if (shape[x+1]=='$') {  score++; shape[x+1]=' '; count_coins++; if (count_coins==coins) result (true); }
                      else if (shape[x+1]=='B') { shape[x+1]=' '; life--; if (life==0) { lost=false; result (false); } }
                           else { shape[x+1]=shape[x]; shape[x]=' '; x+=1; }
        }
        break;
        case 'i':
        {
            if ((shape[x-columns]=='@') || (shape[x-columns]=='B') || (shape[x-columns]=='P')) break;
            else { shape[x-columns]=' '; }
                 if (shape[x-2*columns]=='$') { score++; shape[x-2*columns]=' '; count_coins++; if (count_coins==coins) result (true); }
                 if (shape[x-2*columns]=='@') { result (false); lost=false; }
                 if (shape[x-2*columns]=='P') { life++; shape[x-2*columns]=' '; }
                 if (shape[x-2*columns]=='B') { life--; shape[x-2*columns]=' '; if (life==0) { lost=false; result (false); } }

        }
        break;
        case 'k': 
        {
            if ((shape[x+columns]=='@') || (shape[x+columns]=='$') || (shape[x+columns]=='B') || (shape[x+columns]=='P')) break;
            else { shape[x+columns]=' '; }
        }
        break;
        case 'j':
        {
            if ((shape[x-1]=='$') || (shape[x-1]=='B') || (shape[x-1]=='@') || (shape[x-1]=='P')) break;
            else { shape[x-1]=' '; }
        }
        break;
        case 'l':
        {
            if ((shape[x+1]=='$') || (shape[x+1]=='B') || (shape[x+1]=='P') || (shape[x+1]=='@')) break;           
            else { shape[x+1]=' '; }        
        }        
        break;    
    }
  
    for (i=0;i<size;i++)
    {
        if (((shape[i]=='@') || (shape[i]=='$') || (shape[i]=='B') || (shape[i]=='P')) && (shape[i+columns]==' '))
        { shape[i+columns]=shape[i]; shape[i]=' '; }
    }

    for (i=0;i<size;i++)
    {
        if (((shape[i]=='@') || (shape[i]=='$') || (shape[i]=='B') || (shape[i]=='P')) && (shape[i+columns]==' '))
        { shape[i+columns]=shape[i]; shape[i]=' '; }
    }

    if ((count_coins==coins) || (lost==false)) { exit (); char close; cin>>close; clear_screen (); break;}

    for (i=0;i<size;i++)
    {
        cout<<shape[i]<<" "; 
        if ((i+1)%columns==0) cout<<"\n";
        if (i==size-1) cout<<"score: "<<score<<"\n"<<"life: "<<life<<"\n"<<"Input: ";
    } 

    }

    if (coins==count_coins) 
    {
        arr_name[count]=your_name;
        arr_score[count]=score; 
        count++;
        ofstream MyFile("filename.txt");
        MyFile <<"Name"<<"\t"<<"|"<<"    Score"<<"\n";
        for (i=0;i<count;i++)
        MyFile <<arr_name[i]<<"\t"<<"|    "<<arr_score[i]<<"\n";
        MyFile.close();
    } } }
break;    
case 2: { setting (); cin>>rows>>columns>>rocks>>coins>>bombs>>elixir>>life; temp=life; clear_screen (); settings=true; }
break;
case 3:
{
    clear_screen ();
    string myText;
    ifstream MyReadFile("filename.txt");
    while (getline (MyReadFile, myText)) {
    cout << myText<<"\n";   }
    MyReadFile.close();
    exit ();
    cin>>close;
    clear_screen ();
}
break;
case 4: close_console=false;
break; } 

} 

return 0;
}

void instruction()
{
    cout<<"1. Start Game"<<"\n"<<"2. Settings"<<"\n"<<"3. Records"<<"\n"<<"4. Exit"<<"\n"<<"Input: ";

}

int random_number (int columns)
{
    srand ( time(NULL) );
    int random=(rand()%columns);
    return random;
}

void clear_screen ()
{
    cout<<"\033[2J\033[1;1H";
}

void result (bool won_or_lost)
{
    if (won_or_lost==true) {
     cout<<endl<<endl;
        cout<<"    |#|      |#|                                     |#|     |#|     |#|\n";
        cout<<"    |#|`     |#|                                     |#|     |#|     |#|    _________    |#|#|           |#|\n";
        cout<<"    |#|      |#|    _________                        |#|    `|#|     |#|   |#########|   |#|  |#|        |#|\n";
        cout<<"    |#|      |#|   |#########|  |#|      |#|         |#|     |#|     |#|   |#|     |#|   |#|   |#|       |#|\n";
        cout<<"     \\#\\    /#/    |#|     |#|  |#|      |#|         |#|     |#|     |#|   |#|     |#|   |#|     |#|     |#|\n";
        cout<<"      \\#\\__/#/     |#|     |#|  |#|      |#|         |#|     |#|     |#|   |#|     |#|   |#|       |#|   |#|\n";
        cout<<"         |#|       |#|     |#|  |#|      |#|         |#|     |#|     |#|   |#|     |#|   |#|         |#| |#|\n";
        cout<<"         |#|       |#|     |#|  |#|      |#|         |#|     |#|     |#|   |#|     |#|   |#|          |#||#|\n";
        cout<<"         |#|       |#|_____|#|  |#|      |#|            |#|  |#|  |#|      |#|_____|#|   \n";
        cout<<"         |#|       |#########|  |#|      |#|              |#|   |#|        |#########|   \n";
        cout<<"         |#|                    |#|______|#|                 |#|                         \n";
        cout<<"         |#|                    |##########|                 |#|                          \n"; }
    else {
    cout<<endl<<endl<<endl;
    cout<<"   |#|#|#|#|#|#|#|##|   |#|#|#|    |#|          |#|  |#|#|#|#|     |#||#||#||#|  |#|    |#|  |#||#|#|#|    |#|#|#|#|#|\n";
    cout<<"   |#|#|#|#|#|#|#|##||#|       |#| |#|#|      |#|#|  |#|           |#||#||#||#|  |#|    |#|  |#|           |#|     |#|\n";
    cout<<"   |#|           |##||#|       |#| |#|  |#| |#| |#|  |#|           |#|      |#|  |#|    |#|  |#|           |#|     |#|\n";
    cout<<"   |#|               |#|       |#| |#|    |#|   |#|  |#|           |#|      |#|  |#|    |#|  |#|           |#|     |#|\n";
    cout<<"   |#|               |#|       |#| |#|    |#|   |#|  |#|           |#|      |#|  |#|    |#|  |#|           |#|#|#|#|#|\n";
    cout<<"   |#|               |#|#|#|#|#|#| |#|          |#|  |#|#|#|#|     |#|      |#|  |#|    |#|  |#|#|#||#|    |#|#|\n";
    cout<<"   |#| |#|#|#|#|#|#| |#|       |#| |#|          |#|  |#|           |#|      |#|  |#|    |#|  |#|           |#| |#|\n";
    cout<<"   |#| |#|#|#|#|#|#| |#|       |#| |#|          |#|  |#|           |#|      |#|  |#|    |#|  |#|           |#|  |#|\n";
    cout<<"   |#|           |#| |#|       |#| |#|          |#|  |#|           |#|      |#|  |#|    |#|  |#|           |#|   |#|\n";
    cout<<"   |#|           |#| |#|       |#| |#|          |#|  |#|           |#|      |#|  |#|    |#|  |#|           |#|    |#|\n";
    cout<<"   |#|           |#| |#|       |#| |#|          |#|  |#|           |#||#||#||#|   |#|  |#|   |#|           |#|     |#|\n";
    cout<<"   |#|#|#|#|#|#|#|#| |#|       |#| |#|          |#|  |#|#|#|#|     |#||#||#||#|      |#|     |#|#|#|#|     |#|      |#|\n";}
}

void setting ()
{
    cout<<"Please enter the number of rows, columns, rocks, coins, bombs, elixirs and lifes:"<<"\n";
}

void adjust ()
{
    cout<<"Please adjust the settings first"<<"\n"<<"\n"<<"Press any key to exit... ";
}

void exit ()
{
    cout<<"\n"<<"Press any key to exit... ";
}

void name ()
{
    cout<<"Enter your name please: ";
}