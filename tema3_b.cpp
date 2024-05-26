#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<stack>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");/// lambda tranziþiile se vor nota cu "-"
const int NMAX=10007;
struct tran
{
    string next_state;
    string stack_sym;
};
tran auxtran;
int nr_states,nr_trans,q;
int it,y;
string current_state;
char input_letter;
char input_stack_top;
string next_stat;
string output_stack_top;
string S;  ///starea de start
char Z='Z'; ///caracterul iniþial din stivã
int nr_final_states;
unordered_set<string> finals;
string aux;
string word;   ///trans[state][letter][stacktop]
unordered_map<string,unordered_map<char,unordered_map<char,tran>>> trans;

string convert(string stat,int pos, stack<char> stac)
{
    stat.push_back('@');
    stat.append(to_string(pos));
    while(!stac.empty())
    {
        stat.push_back('@');
        stat.append(to_string(stac.top()));
        stac.pop();
    }
    return stat;
}

int poz;
int main()
{
    in>>nr_states>>nr_trans;
    for(it=1;it<=nr_trans;it++)
    {
        in>>current_state>>input_letter>>input_stack_top>>next_stat>>output_stack_top;
        auxtran.next_state=next_stat;
        auxtran.stack_sym=output_stack_top;
        trans[current_state][input_letter][input_stack_top]=auxtran;
    }
    in>>S;
    in>>nr_final_states;
    for(it=1;it<=nr_final_states;it++)
    {
        in>>aux;
        finals.insert(aux);
    }
    in>>q;
    for(it=1;it<=q;it++)
    {
        unordered_set<string> bo;
        bool accept=0;
        in>>word;
        stack<char> st;
        st.push(Z);

        current_state=S;
        int poz=0;
        while(poz<=word.size())
        {
            string cool=convert(current_state,poz,st);
            if(bo.find(cool)!=bo.end())
            {
                break;
            }
            bo.insert(cool);
            //out<<current_state<<" "<<st.top()<<" "<<word<<"\n";
            char stack_symbol=st.top();
            st.pop();
            char letter='-';
            if(poz<word.size())
            {
                letter=word[poz];
            }
            char lambda='-';
            if(poz<word.size()&&trans[current_state].find(letter)!=trans[current_state].end()&&
               trans[current_state][letter].find(stack_symbol)!=trans[current_state][letter].end())
            {
                auxtran=trans[current_state][letter][stack_symbol];
                current_state=auxtran.next_state;
                if (auxtran.stack_sym!="-")
                {
                    for (y=auxtran.stack_sym.size()-1;y>=0;--y)
                    {
                        st.push(auxtran.stack_sym[y]);
                    }
                }
                poz++;
                if(st.empty())
                {
                    ///Dacã vrem sã acceptãm atunci când stiva e goalã ar trebui sã lucrãm aici;
                    break;
                }
            }
            else if(trans[current_state].find(lambda)!=trans[current_state].end()&&
               trans[current_state][lambda].find(stack_symbol)!=trans[current_state][lambda].end())
            {
                auxtran=trans[current_state][lambda][stack_symbol];
                current_state=auxtran.next_state;
                if (auxtran.stack_sym!="-")
                {
                    for (y=auxtran.stack_sym.size()-1;y>=0;--y)
                    {
                        st.push(auxtran.stack_sym[y]);
                    }
                }
                if(st.empty())
                {
                    ///Dacã vrem sã acceptãm atunci când stiva e goalã ar trebui sã lucrãm aici;
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if(finals.find(current_state)!=finals.end()&&st.empty()&&poz==word.size())
        {
            accept=1;
        }
        if(accept==1)
        {
            out<<"The word was accepted\n";
        }
        else
        {
            out<<"The word was rejected\n";
        }
    }
}
