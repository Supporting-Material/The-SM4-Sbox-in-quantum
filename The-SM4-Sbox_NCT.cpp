#include<stdio.h>
#include<iostream>
#include<bitset>
#include <iomanip>
using namespace std;
int sbox[256] = { 
0xd6, 0x90, 0xe9, 0xfe ,0xcc ,0xe1, 0x3d, 0xb7, 0x16, 0xb6, 0x14, 0xc2, 0x28, 0xfb, 0x2c, 0x05,
0x2b, 0x67, 0x9a, 0x76 ,0x2a ,0xbe, 0x04, 0xc3, 0xaa, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99,
0x9c, 0x42, 0x50, 0xf4 ,0x91 ,0xef, 0x98, 0x7a, 0x33, 0x54, 0x0b, 0x43, 0xed, 0xcf, 0xac, 0x62,
0xe4, 0xb3, 0x1c, 0xa9 ,0xc9 ,0x08, 0xe8, 0x95, 0x80, 0xdf, 0x94, 0xfa, 0x75, 0x8f, 0x3f, 0xa6,
0x47, 0x07, 0xa7, 0xfc ,0xf3 ,0x73, 0x17, 0xba, 0x83, 0x59, 0x3c, 0x19, 0xe6, 0x85, 0x4f, 0xa8,
0x68, 0x6b, 0x81, 0xb2 ,0x71 ,0x64, 0xda, 0x8b, 0xf8, 0xeb, 0x0f, 0x4b, 0x70, 0x56, 0x9d, 0x35,
0x1e, 0x24, 0x0e, 0x5e ,0x63 ,0x58, 0xd1, 0xa2, 0x25, 0x22, 0x7c, 0x3b, 0x01, 0x21, 0x78, 0x87,
0xd4, 0x00, 0x46, 0x57 ,0x9f ,0xd3, 0x27, 0x52, 0x4c, 0x36, 0x02, 0xe7, 0xa0, 0xc4, 0xc8, 0x9e,
0xea, 0xbf, 0x8a, 0xd2 ,0x40 ,0xc7, 0x38, 0xb5, 0xa3, 0xf7, 0xf2, 0xce, 0xf9, 0x61, 0x15, 0xa1,
0xe0, 0xae, 0x5d, 0xa4 ,0x9b ,0x34, 0x1a, 0x55, 0xad, 0x93, 0x32, 0x30, 0xf5, 0x8c, 0xb1, 0xe3,
0x1d, 0xf6, 0xe2, 0x2e ,0x82 ,0x66, 0xca, 0x60, 0xc0, 0x29, 0x23, 0xab, 0x0d, 0x53, 0x4e, 0x6f,
0xd5, 0xdb, 0x37, 0x45 ,0xde ,0xfd, 0x8e, 0x2f, 0x03, 0xff, 0x6a, 0x72, 0x6d, 0x6c, 0x5b, 0x51,
0x8d, 0x1b, 0xaf, 0x92 ,0xbb ,0xdd, 0xbc, 0x7f, 0x11, 0xd9, 0x5c, 0x41, 0x1f, 0x10, 0x5a, 0xd8,
0x0a, 0xc1, 0x31, 0x88 ,0xa5 ,0xcd, 0x7b, 0xbd, 0x2d, 0x74, 0xd0, 0x12, 0xb8, 0xe5, 0xb4, 0xb0,
0x89, 0x69, 0x97, 0x4a ,0x0c ,0x96, 0x77, 0x7e, 0x65, 0xb9, 0xf1, 0x09, 0xc5, 0x6e, 0xc6, 0x84,
0x18, 0xf0, 0x7d, 0xec ,0x3a ,0xdc, 0x4d, 0x20, 0x79, 0xee, 0x5f, 0x3e, 0xd7, 0xcb, 0x39, 0x48};

int t[60] = {0};

//Toffoli Depth = 3
/*
#Toffoli: 12
#CNOT   : 58
#Pauli_x: 4
*/
void f_1(int *x)
{
int a = 0; 

x[4] = x[4] ^ x[5];
x[4] = x[4] ^ x[3];
x[4] = x[4] ^ x[2];
x[4] = x[4] ^ 1;
x[5] = x[5] ^ x[3];
x[5] = x[5] ^ x[1];
x[5] = x[5] ^ x[0];
x[7] = x[7] ^ x[4];
x[7] = x[7] ^ x[3];
x[7] = x[7] ^ x[1];
x[6] = x[6] ^ x[7];
x[6] = x[6] ^ 1;
x[3] = x[3] ^ x[5];
x[2] = x[2] ^ x[7];
x[2] = x[2] ^ x[1];
x[2] = x[2] ^ 1;
x[0] = x[0] ^ 1;
x[1] = x[5] ^ x[1];
	t[26] = t[26] ^ x[4]&x[5];
	t[28] = t[28] ^ x[7]&x[6];
	t[24] = t[24] ^ x[3]&x[2];
	a = a ^ x[0]&x[1];

t[26] = t[26] ^ a;
t[28] = t[28] ^ t[26];
t[20] = t[20] ^ t[28];
t[20] = t[20] ^ a;

x[4] = x[7] ^ x[4] ^ x[3] ^ x[0];
x[1] = x[6] ^ x[5] ^ x[2] ^ x[1];
x[0] = x[4] ^ x[3] ^ x[0];
x[5] = x[6] ^ x[5];
x[7] = x[7] ^ x[4] ^ x[3];
x[6] = x[6] ^ x[2] ^ x[1];
	t[20] = t[20] ^ x[4]&x[1];
	t[26] = t[26] ^ x[0]&x[5];
	t[24] = t[24] ^ x[7]&x[6];
	t[28] = t[28] ^ x[3]&x[2];

t[24] = t[24] ^ t[26];

x[0] = x[4] ^ x[3] ^ x[0];
x[2] = x[5] ^ x[2] ^ x[1];
x[4] = x[7] ^ x[4];
x[1] = x[6] ^ x[1];
x[3] = x[3] ^ x[0];
x[5] = x[6] ^ x[5] ^ x[1];
	a = a ^ x[0]&x[2];
	t[20] = t[20] ^ x[7]&x[6];
	t[24] = t[24] ^ x[4]&x[1];
	t[26] = t[26] ^ x[3]&x[5];  

t[20] = t[20] ^ t[26];

x[7] = x[7] ^ x[6] ^ x[5] ^ x[3] ^ x[2] ^ x[0];
	t[20] = t[20] ^ x[7];
x[4] = x[5] ^ x[4] ^ x[3] ^ x[1];
	t[24] = t[24] ^ x[4];
x[7] = x[7] ^ x[5] ^ x[3];
	t[26] = t[26] ^ x[7];
x[4] = x[4] ^ x[2] ^ x[0];
	t[28] = t[28] ^ x[4];
}

//Toffoli Depth = 6
/*
#Toffoli: 6
#CNOT   : 4
*/
void S_4_6()
{int a = 0;

////////4-bit S-box:(20, 24, 26, 28) -> (33, 37, 41, 44)/:02641ce79d358baf//////////////////////////////////////
t[24] = t[24] ^ (t[20] & t[26]);
t[20] = t[20] ^ t[24];
t[26] = t[26] ^ (t[20] & t[28]);
t[20] = t[20] ^ (t[24] & t[26]);
t[24] = t[24] ^ t[20];
t[26] = t[26] ^ t[28];
t[28] = t[28] ^ (t[20] & t[26]);
a = a ^ (t[26] & t[24]);
t[20] = t[20] ^ (a & t[28]);
t[28] = t[28] ^ t[26];

// t[33] = t[24];
// t[37] = t[28];
// t[41] = t[26];
// t[44] = t[20];
}

void S_4()
{
	int a = 0;
	int b = 0;
	
////////4-bit S-box:(20, 24, 26, 28) -> (33, 37, 41, 44)/:02641ce79d358baf//////////////////////////////////////
t[24] = t[24] ^ (t[20] & t[26]);
t[20] = t[20] ^ t[24];
t[26] = t[26] ^ (t[20] & t[28]);
t[20] = t[20] ^ (t[24] & t[26]);
t[24] = t[24] ^ t[20];
t[26] = t[26] ^ t[28];

b = b ^ t[26];
t[28] = t[28] ^ (t[20] & b);
a = a ^ (t[26] & t[24]);

t[20] = t[20] ^ (a & t[28]);
t[28] = t[28] ^ t[26];

// t[33] = t[24];
// t[37] = t[28];
// t[41] = t[26];
// t[44] = t[20];
}


//Toffoli Depth = 6
/*
#Toffoli: 23
#CNOT   : 67 + 12(for reset ancilla qubits)
#Pauli_x: 5
*/
void f_2(int *x, int *s)
{
	for(int i = 0; i < 8; i++)
	{
		s[i] = 0;
	}

///////12 operations for the case that the initial calue of (s[0],...,s[7]) is equal not (0,0,...,0).
s[1] = s[1] ^ s[6]; 
s[6] = s[6] ^ s[4];
s[7] = s[7] ^ s[3];  
s[5] = s[5] ^ s[7]; 
s[3] = s[3] ^ s[6]; 
s[6] = s[6] ^ s[2];
s[2] = s[2] ^ s[5];  
s[2] = s[2] ^ s[1];
s[5] = s[5] ^ s[4];
s[5] = s[5] ^ s[3];
s[0] = s[0] ^ s[3];
s[7] = s[7] ^ s[6];


t[24] = t[24] ^ t[20];
t[28] = t[28] ^ t[26];
t[26] = t[26] ^ t[20];
x[5] = x[5] ^ x[2];
x[4] = x[5] ^ x[4] ^ x[1];
x[6] = x[6] ^ x[1];
	s[3] = s[3] ^ t[24] & x[5];
	s[6] = s[6] ^ t[28] & x[4];
	s[5] = s[5] ^ t[26] & x[6];
	s[7] = s[7] ^ t[20] & x[3];

t[26] = t[28] ^ t[26] ^ t[24];
t[20] = t[26] ^ t[24] ^ t[20];
x[5] = x[5] ^ x[1];
x[6] = x[6] ^ x[1];
x[3] = x[3] ^ x[0];
x[7] = x[7] ^ x[6] ^ x[2];
	s[3] = s[3] ^ t[28] & x[5];
	s[4] = s[4] ^ t[26] & x[6]; 
	s[6] = s[6] ^ t[24] & x[3];
	s[1] = s[1] ^ t[20] & x[7];

s[7] = s[7] ^ s[6];
s[0] = s[0] ^ s[3]; 

t[26] = t[26] ^ t[20];
t[20] = t[28] ^ t[20];
x[4] = x[7] ^ x[4];
	s[3] = s[3] ^ t[26] & x[2];
	s[4] = s[4] ^ t[28] & x[5];
	s[7] = s[7] ^ t[20] & x[4];

s[5] = s[5] ^ s[3];

t[28] = t[28] ^ t[20];
t[26] = t[28] ^ t[26];
t[24] = t[28] ^ t[26] ^ t[24] ^ t[20];
x[2] = x[6] ^ x[2];
x[7] = x[7] ^ x[0];
x[5] = x[5] ^ x[2];
x[3] = x[4] ^ x[3] ^ x[0];
	s[3] = s[3] ^ t[28] & x[2];
	s[2] = s[2] ^ t[26] & x[7];
	s[0] = s[0] ^ t[20] & x[5];
	s[1] = s[1] ^ t[24] & x[3];

s[5] = s[5] ^ s[4];
s[2] = s[2] ^ s[1];

t[28] = t[28] ^ t[26];
t[24] = t[26] ^ t[24];
t[26] = t[28] ^ t[26] ^ t[20];
x[3] = x[7] ^ x[3];
x[7] = x[7] ^ x[4] ^ x[0];
	s[4] = s[4] ^ t[20] & x[5];
	s[6] = s[6] ^ t[28] & x[0];
	s[1] = s[1] ^ t[24] & x[3];
	s[2] = s[2] ^ t[26] & x[7];

t[26] = t[26] ^ t[20];
t[28] = t[28] ^ t[26] ^ t[24] ^ t[20];
x[7] = x[7] ^ x[4];
x[6] = x[6] ^ x[5] ^ x[1];
	s[1] = s[1] ^ t[20] & x[4];
	s[4] = s[4] ^ t[24] & x[1];
	s[6] = s[6] ^ t[26] & x[7];
	s[0] = s[0] ^ t[28] & x[6];

s[2] = s[2] ^ s[5];  
s[6] = s[6] ^ s[2];
s[3] = s[3] ^ s[6]; 
s[5] = s[5] ^ s[7]; 
s[7] = s[7] ^ s[3];  
s[6] = s[6] ^ s[4]; 
s[1] = s[1] ^ s[6]; 

	s[0] = s[0] ^ 1;
	s[1] = s[1] ^ 1;
	s[3] = s[3] ^ 1;
	s[6] = s[6] ^ 1;
	s[7] = s[7] ^ 1;
}

void sm4_forward_sbox(int *x, int *s)
{
	t[20] = 0;
	t[24] = 0;
	t[26] = 0;
	t[28] = 0;
	f_1(x);
	S_4();
	f_2(x, s);
}

int main()
{
	

	for (int i = 0; i < 256; i++)
	{ //i = 76543210
		int in[8] = { 0 };
		int out[8] = { 0 };

		in[0] = (i & 1);
		in[1] = (i >> 1 & 1);
		in[2] = (i >> 2 & 1);
		in[3] = (i >> 3 & 1);
		in[4] = (i >> 4 & 1);
		in[5] = (i >> 5 & 1);
		in[6] = (i >> 6 & 1);
		in[7] = (i >> 7 & 1);

		sm4_forward_sbox(in, out);

		int sum = out[0] * 128 + out[1] * 64 + out[2] * 32 + out[3] * 16 + out[4] * 8 + out[5] * 4 + out[6] * 2 + out[7];
		if ((i != 0) && ((i % 16 == 0)))
		{
			cout << endl;
		}
		if (sum == sbox[i])
		{
			cout << "0 ";
		}
		else if (sum != sbox[i])
		{
			cout << "1 ";
		}
		// cout<<(sum^sbox[i])<<" ";
		
	}
	cout << endl;
	return 0;
}