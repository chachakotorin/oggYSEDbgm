// stdafx.cpp : 標準インクルードファイルを含むソース ファイル
//              ogg.pch : 生成されるプリコンパイル済ヘッダー
//              stdafx.obj : 生成されるプリコンパイル済タイプ情報

#include "stdafx.h"

typedef char bit;

char btoc(bit *b, int len);
void ctob(bit *b, char *c, int ofst, int len);
bit bitat(char *c, int ofst);

//bit sequence(from 1 to 8) to char
char btoc(bit *b, int len){
	int i;
	char c = 0;
	for (i = 0; i < len; ++i){ c <<= 1; c |= b[i]; }
	return c;
}

//read bit sequence from *c + ofst for len (in bit)
void ctob(bit *b, char *c, int ofst, int len){
	int k;
	for (k = 0; k < len; ++k) b[k] = bitat(c, ofst + k);
}

//read bit at *c + ofst (in bit)
bit bitat(char *c, int ofst){
	c += ofst / 8;
	return ((*c) >> (7 - ofst % 8)) & 1;
}


char *b64_decode(char *s, int size,int &len){
	int i, tsize = 4 * ((size * 3) / 4);
	char *c = new char[tsize];
	for (i = 0; i < size; ++i) c[i] = b64_ctoi(s[i]);
	for (i = size; i < tsize; ++i) c[i] = 0;
	bit *b = new bit[6 * tsize];
	for (i = 0; i < tsize; ++i) ctob(b + 6 * i, c + i, 2, 6); // read 6 bit for each c with ofst 2
	char *de = (char *)malloc(sizeof(char) * (tsize / 4 * 3 + 1));
	for (i = 0; i < tsize / 4 * 3; ++i) de[i] = btoc(b + 8 * i, 8); // get c from b
	de[tsize / 4 * 3] = '\0';
	len = tsize / 4 * 3 - 1;
	delete [] c;
	delete [] b;
	return de;
}

int b64_ctoi(char c){
	if ('A' <= c && c <= 'Z') return c - 'A';
	if ('a' <= c && c <= 'z') return c - 'a' + 26;
	if ('0' <= c && c <= '9') return c - '0' + 52;
	if (c == '+') return 62;
	if (c == '/') return 63;
	return 0;
}