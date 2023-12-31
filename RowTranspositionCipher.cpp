// Assignment 2 b)
#include<bits/stdc++.h>
using namespace std;

string encryptMessage(string msg,string const key,map<int,int> keyMap){
	int row,col,j;
	string cipher = "";
	
	col = key.length();
	row = msg.length()/col;
	
	if (msg.length() % col)
		row += 1;

	char matrix[row][col];
	for (int i=0,k=0; i < row; i++){
		for (int j=0; j<col; ){
			if(msg[k] == '\0'){
				matrix[i][j] = '_';	
				j++;
			}

			if( isalpha(msg[k]) || msg[k]==' '){
				matrix[i][j] = msg[k];
				j++;
			}
			k++;
		}
	}cout<<endl;

	cout<<"Matrix : "<<endl;
	for(int i=0; i < row; i++){
		for(int j=0; j<col; j++){
			cout<<matrix[i][j]<<" ";
		}cout<<endl;
	}cout<<endl;

	for (auto& it:keyMap){
		j=it.second;
		for (int i=0; i<row; i++){
			if( isalpha(matrix[i][j]) || matrix[i][j]==' ' || matrix[i][j]=='_')
				cipher += matrix[i][j];
		}
	}

	return cipher;
}

// Decryption
string decryptMessage(string cipher,string const key,map<int,int> keyMap){
	int col = key.length();
	int row = cipher.length()/col;
	char cipherMat[row][col];

	for (int j=0,k=0; j<col; j++)
		for (int i=0; i<row; i++)
			cipherMat[i][j] = cipher[k++];

	int index = 0;
	for( auto& it: keyMap)
		it.second = index++;

	char decCipher[row][col];
	int k = 0;
	for (int l=0,j; key[l]!='\0'; k++){
		j = keyMap[key[l++]];
		for (int i=0; i<row; i++){
			decCipher[i][k]=cipherMat[i][j];
		}
	}

	string msg = "";
	for (int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			if(decCipher[i][j] != '_')
				msg += decCipher[i][j];
		}
	}
	return msg;
}

int main(){
	string msg;
	cout<<"Enter string: ";
	getline(cin, msg);
	
    string key;
    cout<<"Enter key: ";
	getline(cin, key);
    map<int,int> keyMap;

    for(int i=0; i < key.length(); i++){
		keyMap[key[i]] = i;
	}

    // for(auto it:keyMap){
    //     cout<<it.first<<" "<<it.second<<endl;
    // }
		
	string cipher = encryptMessage(msg,key,keyMap);
	cout << "Encrypted Message: " << cipher << endl;
	cout<<endl;
	cout << "Decrypted Message: " << decryptMessage(cipher,key,keyMap) << endl;


	return 0;
}