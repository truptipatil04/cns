// Assignment 2 a)
#include <bits/stdc++.h>
using namespace std;

string encryptRailFence(string text, int key){
	char rail[key][(text.length())];

	for (int i=0; i < key; i++)
		for (int j = 0; j < text.length(); j++)
			rail[i][j] = '_';

	bool dir_down = false;
	int row = 0, col = 0;

	for (int i=0; i < text.length(); i++){
		if (row == 0 || row == key-1)
			dir_down = !dir_down;

		rail[row][col++] = text[i];
		dir_down?row++ : row--;
	}cout<<endl;

	cout<<"Matrix : "<<endl;
	for(int i=0; i < key; i++){
		for (int j=0; j < text.length(); j++){
			cout<<rail[i][j]<<" ";
		}cout<<endl;
	}cout<<endl;

	string result;
	for (int i=0; i < key; i++)
		for (int j=0; j < text.length(); j++)
			if (rail[i][j]!='_')
				result.push_back(rail[i][j]);

	return result;
}

string decryptRailFence(string cipher, int key){
	char rail[key][cipher.length()];

	for (int i=0; i < key; i++)
		for (int j=0; j < cipher.length(); j++)
			rail[i][j] = '_';

	bool dir_down;
	int row = 0, col = 0;

	for (int i=0; i < cipher.length(); i++){
		if (row == 0)
			dir_down = true;
		if (row == key-1)
			dir_down = false;

		rail[row][col++] = '*';
		dir_down?row++ : row--;
	}

	int index = 0;
	for (int i=0; i<key; i++)
		for (int j=0; j<cipher.length(); j++)
			if (rail[i][j] == '*' && index<cipher.length())
				rail[i][j] = cipher[index++];
	
	cout<<endl;

	cout<<"Matrix : "<<endl;
	for(int i=0; i < key; i++){
		for (int j=0; j < cipher.length(); j++){
			cout<<rail[i][j]<<" ";
		}cout<<endl;
	}cout<<endl;

	string result;
	row = 0, col = 0;
	for (int i=0; i< cipher.length(); i++){
		if (row == 0)
			dir_down = true;

		if (row == key-1)
			dir_down = false;

		if (rail[row][col] != '*')
			result.push_back(rail[row][col++]);

		dir_down?row++: row--;
	}
	return result;
}

int main(){
    string s;
	cout<<"Enter 1 for encryption and 2 for decryption: ";
	int x;
	int key;
	cin>>x;

	switch (x){
	case 1:
		cout<<"Plain text : ";
		cin>>s;

		cout<<"Key : ";
		cin>>key;
		cout << "Encrypted text : " <<encryptRailFence(s, key) << endl;
		break;
	case 2:
		cout<<"Cipher text : ";
		cin>>s;
		
		cout<<"Key : ";
		cin>>key;
		cout <<"Decrptyed text : " << decryptRailFence(s, key) << endl;
		break;
	default:
		break;
	}
	return 0;
}
