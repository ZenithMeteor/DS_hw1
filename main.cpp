#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<string.h>
using namespace std;

char * memblock;
int picture[65536], int_DPCM[65536];
char *_input = new char[50];
char *_t_output = new char[50];
char *_dpcm_input = new char[50];
char *_toDPCM_output = new char[100];
fstream ofile;

void _DPCM(int);
void _sys_call(int, int, char *sys_input);

int main()
{
    string input, t_input, output, t_output;
    char _output[100], _tt[100];
    for(int i=0; i<100; i++)
    {
        _output[i]='\0';
        _tt[i]='\0';
        _toDPCM_output[i]='\0';
    }

    int c_mode=0, o_mode=0, d_mode=0;

    cout<<"Name: GUAN-XIN ZENG\nStudent ID:106522011\n***************\n";
    cout<<"*Input filename:\n";
    cin>>_input;
    //_DPCM(1);
    cout<<"*Output filename:\n";
    cin>>_t_output;
    ///
    cout<<"*Choose one compression method:\n";
    cout<<"1)Huffman coding\n2)Adaptive Huffman coding\n3)Arithmetic coding\n4)LZSS\n5)LZW\n";
    cin>>c_mode;
    cout<<c_mode;
    if(c_mode<1 || c_mode>5)
        exit(0);
    ///
    cout<<"*Coding operation:\n";
    cout<<"1) Encoding\n2) Decoding\n";
    cout<<"Your choice: (1 or 2, other to exit):\n";
    cin>>o_mode;
    if(o_mode<1 || o_mode>2)
        exit(0);
    ///
    cout<<"Data:\n";
    cout<<"1) Original data\n2) DPCM\n";
    cout<<"Your choice: (1 or 2, other to exit):\n";
    cin>>d_mode;
    if(d_mode<1 || d_mode>2)
        exit(0);
    ///
    cout<<"... Program is running and generating useful information\n";

    if(d_mode == 2)///DPCM
    {
        if(o_mode == 1)///DPCM encoder
        {
            _DPCM(o_mode);
            strcat(_tt," temp_DPCM.raw ");
            strcat(_tt,_t_output);
            switch (c_mode)
            {
            case 1:
                strcat(_output,".\\exe\\Huffman-c");
                strcat(_output,_tt);
                system(_output);
                break;
            case 2:
                strcat(_output,".\\exe\\ahuff-c");
                strcat(_output,_tt);
                system(_output);
                break;
            case 3:
                strcat(_output,".\\exe\\Arith-c");
                strcat(_output,_tt);
                system(_output);
                break;
            case 4:
                strcat(_output,".\\exe\\LZSS-c");
                strcat(_output,_tt);
                system(_output);
                break;
            case 5:
                strcat(_output,".\\exe\\LZW-c");
                strcat(_output,_tt);
                system(_output);
                break;
            }
        }
        else///DPCM decode
        {
            strcat(_toDPCM_output, "DPCM_");
            strcat(_toDPCM_output, _t_output);
            ///
            strcat(_tt," ");
            strcat(_tt,_input);
            strcat(_tt," ");
            strcat(_tt,_toDPCM_output);
            switch (c_mode)
            {
            case 1:
                strcat(_output,".\\exe\\Huffman-e");
                strcat(_output,_tt);
                system(_output);
                break;
            case 2:
                strcat(_output,".\\exe\\ahuff-e");
                strcat(_output,_tt);
                system(_output);
                break;
            case 3:
                strcat(_output,".\\exe\\Arith-e");
                strcat(_output,_tt);
                system(_output);
                break;
            case 4:
                strcat(_output,".\\exe\\LZSS-e");
                strcat(_output,_tt);
                system(_output);
                break;
            case 5:
                strcat(_output,".\\exe\\LZW-e");
                strcat(_output,_tt);
                system(_output);
                break;
            }
            _DPCM(o_mode);
        }
    }
    else
    {
        strcat(_tt," ");
        strcat(_tt,_input);
        strcat(_tt," ");
        strcat(_tt,_t_output);
        if(o_mode == 1)
        {
            switch (c_mode)
            {
            case 1:
                strcat(_output,".\\exe\\Huffman-c");
                strcat(_output,_tt);
                system(_output);
                break;
            case 2:
                strcat(_output,".\\exe\\ahuff-c");
                strcat(_output,_tt);
                system(_output);
                break;
            case 3:
                strcat(_output,".\\exe\\Arith-c");
                strcat(_output,_tt);
                system(_output);
                break;
            case 4:
                strcat(_output,".\\exe\\LZSS-c");
                strcat(_output,_tt);
                system(_output);
                break;
            case 5:
                strcat(_output,".\\exe\\LZW-c");
                strcat(_output,_tt);
                system(_output);
                break;
            }
        }
        else
        {
            switch (c_mode)
            {
            case 1:
                strcat(_output,".\\exe\\Huffman-e");
                strcat(_output,_tt);
                system(_output);
                break;
            case 2:
                strcat(_output,".\\exe\\ahuff-e");
                strcat(_output,_tt);
                system(_output);
                break;
            case 3:
                strcat(_output,".\\exe\\Arith-e");
                strcat(_output,_tt);
                system(_output);
                break;
            case 4:
                strcat(_output,".\\exe\\LZSS-e");
                strcat(_output,_tt);
                system(_output);
                break;
            case 5:
                strcat(_output,".\\exe\\LZW-e");
                strcat(_output,_tt);
                system(_output);
                break;
            }
        }
    }
    cout<<"... Writing file...\n";
    cout<<"... Done.";
    system("PAUSE");
    return 0;
}
void _DPCM(int isencoder)
{
    ifstream file;
    fstream ofs;
    if(isencoder == 1)
    {
//        char *dp = new char[10];
//        dp = "DPCM_";
//        strcat(dp, _input);
        file.open(_input, ios::in|ios::binary|ios::ate);
        ofs.open("temp_DPCM.raw", std::fstream::out | fstream::binary);
    }
    else
    {
        file.open(_toDPCM_output, ios::in|ios::binary|ios::ate);
        ofs.open(_t_output, std::fstream::out | fstream::binary);
    }
    ///
    streampos size;
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();
    }
    ///get bits of input c
    int *i_input = new int [size * 8];
    for (int i = 0; i < size * 8; i++)
    {
        unsigned char c = memblock[i / 8];
        int bitPos = i % 8;
        *(i_input + i) = (int)((c >> (7 - bitPos)) & 1);
        //cout << *(i_input + i);
    }
    ///change to int
    for (int i = 0; i < size * 8; i=i+8)
    {
        int temp;
        temp = (*(i_input+i))*128 + (*(i_input+i+1))*64 + (*(i_input+i+2))*32 + (*(i_input+i+3))*16 + (*(i_input+i+4))*8 + (*(i_input+i+5))*4 + (*(i_input+i+6))*2 + *(i_input+i+7);
        picture[i/8] = temp;
//        cout<<picture[i/8];
    }
    if(isencoder == 1)///encode
    {
        int_DPCM[0] = picture[0];
        for(int i = 1; i<256*256; i++)//0不變所以從1開始
        {
            if(i%256 == 0)
            {
                int_DPCM[i] = picture[i] - picture[i-256];
            }
            else
            {
                int_DPCM[i] = picture[i] - picture[i-1];
            }
        }
    }
    else///decode
    {
        int_DPCM[0] = picture[0];
        for(int i = 1; i<256*256; i++)//0不變所以從1開始
        {
            if(i%256 == 0)
            {
                int_DPCM[i] = int_DPCM[i-256] + picture[i];
            }
            else
            {
                int_DPCM[i] = int_DPCM[i-1] + picture[i];
            }
            //cout<<int_DPCM[i];
        }
    }
    for(int i = 0 ; i < 256*256 ; i++)
    {
        int8_t int8_DPCM_output = int_DPCM[i];
        ofs << int8_DPCM_output;
    }
    ofs.close();
}

