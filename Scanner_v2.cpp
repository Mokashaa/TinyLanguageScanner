#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include<algorithm>
using namespace std;

bool is_char(const char& c);
bool is_digit(const char& c);
bool is_charOrDigit(const char& c);


vector<string> reserved= {"if","then","else","end","repeat","until","read","write"};

int main (void)
{
char infinite = 'Y';
string file_path;
string full_text;
string line;
vector <string> Tokens;
vector<string>::iterator it;
bool error_flag = 0 ;
while (infinite =='Y')
{   error_flag =0;
    Tokens.clear();
    full_text="";
    infinite = 'n';
    cout <<"Please enter the file full path Ex:  D:\\Folder\\File.txt "<<endl;
    cin >>file_path;
    ifstream input_file (file_path);

    while (getline(input_file,line))
    {
        full_text+=line;
        full_text+=" ";
    }
    int  i =0;
    char space = ' ';
    char tab ='\t';
    string tabb ="" + tab;
    
    full_text.erase(std::remove(full_text.begin(), full_text.end(), '\t'), full_text.end());
   /* int pos = full_text.find('\t');
    while (pos!=std::string::npos)
    {
        full_text.erase(pos);
        pos= full_text.find('\t');
    }*/

    while (full_text[i]!= '\0')
    {
        if (full_text[i] == '}')
        {
            error_flag =1;
            cout<< "ERROR! undefined curl bracket"<<endl;
            break;
        }
        if (full_text[i]=='{')
        {   int temp = i;
            for(;i<full_text.size();i++)
            {
               if(full_text[i]=='}')
               {
                   break;
               }
            }
            if(i==full_text.size())
            {
                error_flag=1;
                cout<< "ERROR! undefined curl bracket"<<endl;
                break;
            }
            full_text.erase(full_text.begin()+temp,full_text.begin()+i+1);
            i=temp;
        }
        else if(full_text[i]=='+'||full_text[i]=='-'||full_text[i]=='*'||full_text[i]=='/'||full_text[i]=='('||full_text[i]==';'||full_text[i]=='='||full_text[i]=='>'||full_text[i]=='<'||full_text[i]==')')
        {   
           
                full_text.insert( full_text.begin()+i,space);
                full_text.insert( full_text.begin()+i+2,space);
                i+=2;  
        }
        /*else if(full_text[i]==')')
        {  
            if (is_charOrDigit(full_text[i+1])||full_text[i+1]==' '|| full_text[i+1]=='('||full_text[i+1]=='{'||full_text[i+1]==';')
            {
                full_text.insert( full_text.begin()+i,space);
                full_text.insert( full_text.begin()+i+2,space);
                i+=2;  
            }
            else 
            {   
                cout<<"ERROR wrong operator!"<<endl;
                error_flag=1;
                break;
            }
        }*/
        else if(full_text[i]==':')
        {
            if ((full_text[i+1]=='='))
            {
                full_text.insert( full_text.begin()+i,space);
                full_text.insert( full_text.begin()+i+3,space);
                i+=3;  
            }
            else
            {
                cout<<"ERROR wrong assign operator!"<<endl;
                error_flag=1;
                break;
            } 
        }
        /*else if(full_text[i]=='=')
        {
            if ((is_charOrDigit(full_text[i+1])||full_text[i+1]==' '|| full_text[i+1]=='('||full_text[i+1]=='{'))
            {
                full_text.insert( full_text.begin()+i,space);
                full_text.insert( full_text.begin()+i+2,space);
                i+=2;  
            }
            else
            {
                cout<<"ERROR wrong comparison operator!"<<endl;
                error_flag=1;
                break;
            } 
        }*/
        /*else if(full_text[i]=='<')
        {
            if (full_text[i+1]=='='&&(is_charOrDigit(full_text[i+2])||full_text[i+2]==' '|| full_text[i+2]=='('||full_text[i+2]=='{'))
            {
                full_text.insert( full_text.begin()+i,space);
                full_text.insert( full_text.begin()+i+3,space);
                i+=3;  
            }
            else if ((is_charOrDigit(full_text[i+2])||full_text[i+2]==' '|| full_text[i+2]=='('||full_text[i+2]=='{'))
            {
                full_text.insert( full_text.begin()+i,space);
                full_text.insert( full_text.begin()+i+2,space);
                i+=2;
            }
            else
            {
                cout<<"ERROR wrong comparison operator!"<<endl;
                error_flag=1;
                break;
            } 
        }*/
        
        
        /*else if(full_text[i]=='>')
        {
            if (full_text[i+1]=='='&&(is_charOrDigit(full_text[i+2])||full_text[i+2]==' '|| full_text[i+2]=='('||full_text[i+2]=='{'))
            {
                full_text.insert( full_text.begin()+i,space);
                full_text.insert( full_text.begin()+i+3,space);
                i+=3;  
            }
            else if ((is_charOrDigit(full_text[i+2])||full_text[i+2]==' '|| full_text[i+2]=='('||full_text[i+2]=='{'))
            {
                full_text.insert( full_text.begin()+i,space);
                full_text.insert( full_text.begin()+i+2,space);
                i+=2;
            }
            else
            {
                cout<<"ERROR wrong comparison operator!"<<endl;
                error_flag=1;
                break;
            } 
        }*/
        i++;
    }
    if (!error_flag)
    {

    boost::split(Tokens,full_text,boost::is_any_of(" "));

    
    it= find(Tokens.begin(),Tokens.end(),"");
    while (it != Tokens.end())
    {
        Tokens.erase(it);
        it=find(Tokens.begin(),Tokens.end(),"");

    }
    
    vector<string> results;
    for (int i=0 ; i< Tokens.size(); i++)
    {   
        it = find(reserved.begin(),reserved.end(),Tokens[i]);
        if (it != reserved.end())
        {
            results.push_back(Tokens[i]+"_Token");
        }
        else if (is_digit(Tokens[i][0]))
        {   
            int k;
            for (k =1 ;k < Tokens[i].size();k++)
            {   
                if (!is_digit(Tokens[i][k]))
                {   
                    break;}
            }
            if(k!= Tokens[i].size())
            {  
                error_flag=1;
                cout<<"Wrong Identifier Or Number"<<endl;
                break;
            }
           else
           {    
                results.push_back("Number");
            }
                
        }
        else if (is_char(Tokens[i][0]))
        {
            int k;
            for (k =1 ;k < Tokens[i].size();k++)
            {
                if (!is_char(Tokens[i][k]))
                    break;
            }
            if(k!= Tokens[i].size())
            {
                error_flag=1;
                cout<<"Wrong Identifier"<<endl;
                break;
            }
            else
            {
                results.push_back("Identefier");
            }    
                //error unavailable token
        }
        else if(Tokens[i]=="+")
        {
            results.push_back("PLUS Token");
        }
        else if(Tokens[i]=="-")
        {
            results.push_back("MINUS Token");
        }
        else if(Tokens[i]=="*")
        {
            results.push_back("MULTIPLY Token");
        }
        else if(Tokens[i]==":=")
        {
            results.push_back("ASSIGN Token");
        }
        else if(Tokens[i]=="=")
        {
            results.push_back("Equal Token");
        }
        else if(Tokens[i]==">")
        {
            results.push_back("Greater Than Token");
        }
        else if(Tokens[i]=="<")
        {
            results.push_back("Less Than Token");
        }   
        else if(Tokens[i]=="/")
        {
            results.push_back("DIVIDE Token");
        }
        else if(Tokens[i]=="(")
        {
            results.push_back("Left Bracket Token");
        }
        else if(Tokens[i]==")")
        {
            results.push_back("Right Bracket Token");
        }
        else if(Tokens[i]==";")
        {
            results.push_back("Semicolon Token");
        }
        else
        {  
            error_flag=1;
            cout<<"Wrong Identifier"<<endl;
            break;
        }
             
    }
    if(!error_flag)
    {   for (int i =0; i<Tokens.size();i++)
        {
        cout<<Tokens[i]<<" , "<<results[i]<<endl;
        }
    }    
}

    cout <<"If you want to continue input Y and to exit input any char"<<endl;
    cin >>infinite;


}

 return 0;   
}



bool is_char(const char &c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
    return false;
}

bool is_digit(const char& c)
{
	if ((c >= '0' && c <= '9'))
		return true;
    return false;
}

bool is_charOrDigit(const char& c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')|| (c >= '0' && c <= '9'))
		return true;

    return false;
}


