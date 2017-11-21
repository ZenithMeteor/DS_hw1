#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    int w=0;
    while(w==0)
    {
        char * memblock;
        char *_input = new char[50];
        cout<<"*Input filename:\n";
        cin>>_input;
        streampos size;

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
        int *i_input = new int [size * 8];
        for (int i = 0; i < size * 8; i++)
        {
            unsigned char c = memblock[i / 8];
            int bitPos = i % 8;
            *(i_input + i) = (int)((c >> (7 - bitPos)) & 1);
            //cout << *(i_input + i);
        }
        ///set table
        float table[256];
        for(int i=0; i<256; i++)
        {
            table[i] = 0;
        }
        ///change to int
        for (int i = 0; i < size * 8; i=i+8)
        {
            int temp;
            temp = (*(i_input+i))*128 + (*(i_input+i+1))*64 + (*(i_input+i+2))*32 + (*(i_input+i+3))*16 + (*(i_input+i+4))*8 + (*(i_input+i+5))*4 + (*(i_input+i+6))*2 + *(i_input+i+7);
            table[temp]++;//count
        }
        ///calculate
        float sum=0, temp_result=0;
        for(int i=0; i<256; i++)
        {
            temp_result=0;
            if(table[i] != 0)
            {
                float Px = table[i] / 65536;
                temp_result = (-1) * Px * log2(Px);
            }
            sum = sum + temp_result;
        }
        cout<<"\nEntropy = " << sum << endl;
    }
    system("PAUSE");
    return 0;
}
