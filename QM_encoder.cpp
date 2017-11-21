#include<iostream>
#include<fstream>
#include <cstdlib>
#include<cstdio>
#include<string.h>
using namespace std;

char *c_qmtable;
int num_output = 0;
char index[46][5] = {'\0'};
fstream ofile;
char *_input = new char[50];
char *_output = new char[100];
int *output = new int[256*256*8];

void change_value(int &A, int &B)
{
    int t = A;
    A = B;
    B = t;
}

void Qc_change_state(int &state, int mode, char *q, int &LPS, int &MPS, int &Qc)
{
    //cout<<" state:"<<state;
    if(mode == 1)//increase
    {
        state += (*(c_qmtable + state*2)-'0');

    }
    else//decrease
    {
        if(*(c_qmtable + state*2 + 1) == 's')
        {
            change_value(LPS, MPS);
            //cout<<" s ";
        }
        else
        {
            state -= (*(c_qmtable + state*2 + 1)-'0');
            //cout<<*(c_qmtable+ 1);
        }
    }
    Qc= strtol(index[state],NULL,16);//string to hex
    //cout<<" change state:"<<state<<" Qc:"<<Qc;
}
void renormalize(int &A, int &C)
{
    int8_t one=1, zero=0;
    if(C >= 0x10000)
    {
        output[num_output] = 1;
        //cout<<*(output + num_output);
        //ofile<<one;
        num_output += 1;
    }
    while(A < 0x8000)
    {
        A <<= 1;
        C <<= 1;
        if(C >= 0x10000)
        {
            output[num_output] = 1;
            num_output += 1;;
            //ofile<<one;
            C = C - 0x10000;
        }
        else
        {
            output[num_output] = 0;
            //ofile<<zero;
            num_output += 1;
        }
    }
}
int main()
{
    for(int i=0; i<100; i++)
    {
        _output[i]='\0';
    }
    cout<<"*Input filename:\n";
    cin>>_input;

    strcat(_output,_input);
    strcat(_output,".qm");

    ofile.open(_output, fstream::out | fstream::binary);
    ///input picture
    streampos size;
    char * memblock, *c_input;
    int *i_input;

    ifstream file (_input, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();
    }
    ///get bits of input c
    i_input = new int [size * 8];
    for (int i = 0; i < size * 8; i++)
    {
        unsigned char c = memblock[i / 8];
        int bitPos = i % 8;
        *(i_input + i) = (int)((c >> (7 - bitPos)) & 1);
        //cout << *(i_input + i);
    }
    ///read table
    c_qmtable = new char [46*3];
    fstream qm_table;
    qm_table.open("QM_table.txt", fstream::in | fstream::binary);
    if( !qm_table.good())
        cout << "fileÅªÀÉ¥¢±Ñ" << endl;
    for(int i = 0 ; i < 46 ; i++)
    {
        for(int j = 0 ; j < 6; j++)
        {
            if(j<4)
            {
                qm_table >> index[i][j];
            }
            else
            {
                qm_table >> *(c_qmtable + (i*2 + (j-4)));
                //cout << *(c_qmtable + (i*2 + (j-4)));
            }
        }
        //cout<<"a"<<index[i]<<endl;
    }
    ///QM encoding
    int MPS = 0, LPS = 1, state = 0;
    int A = 0xFFFF, C = 0x0000, Qc = 0x59EB;

    for(int i = 0; i < size * 8; i++)
    {
        //cout<<endl<<*(i_input + i)<<" ";
        if(*(i_input + i) == MPS)
        {
            //cout<<"MPS";
            A = A - Qc;
            //cout<<" A:"<<A;
            if(A < 0X8000)
            {
                if(A < Qc)
                {
                    C = C + A;
                    A = Qc;
                }
                Qc_change_state(state, 1, c_qmtable, LPS, MPS, Qc);
                renormalize(A, C);
            }
        }
        else//LPS
        {
            //cout<<"LPS";
            A = A - Qc;
            //cout<<" A:"<<A;
            if(A >= Qc)
            {
                C = C + A;
                A = Qc;
            }
            Qc_change_state(state, -1, c_qmtable, LPS, MPS, Qc);
            renormalize(A, C);
        }
    }
    ///expand
    while(num_output%8 !=0)
    {
        output[num_output] = 0;
        num_output++;
    }
    cout<<"\nQM:"<<num_output/8<<"bytes";
    ///Output
    int int_hex[256*256];
    for (int i = 0; i < num_output; i=i+8)
    {
        int temp;
        temp = output[i]*128 + output[i+1]*64 + output[i+2]*32 + output[i+3]*16 + output[i+4]*8 + output[i+5]*4 + output[i+6]*2 + output[i+7]*1;
        int_hex[i/8] = temp;
    }
    for(int i = 0 ; i < num_output/8 ; i++)
    {
        int8_t int8_output = int_hex[i];
        ofile << int8_output;
    }
    ofile.close();

    system("PAUSE");
    return 0;
}
