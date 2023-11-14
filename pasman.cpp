#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include "base64.cpp"
using namespace std;

string Encrypt(string password, string key){
    for(int i = 0; i < password.length(); i++){
        password[i] = (char)password[i] ^ key[i % (key.length() + 1)];
    } password = base64_encode(password);
    return password;
}
string Decrypt(string password, string key){
    password = base64_decode(password);
    for(int i = 0; i < password.length(); i++){
        password[i] = (char)password[i] ^ key[i % (key.length() + 1)];
    } 
    return password;
}

void DisplayAll(string key) {
    string content[10000][2];
    ifstream data("data.txt", ios::in); 
    if(data.is_open()){
        int i = 0;
        while(true){
            if(data.eof()){
                break;
            } 
            cout << i + 1 << ".";
            for(int j = 0; j < 2; j++){
                data >> content[i][j];
                cout << Decrypt(content[i][j], key) << " ";
            }
            cout << endl;
            i++;
        } 
    }
    data.close();
}

void GetPassword(int nomor) {
    string content[10000][2];
    ifstream data("data.txt"); 
    if(data.is_open()){
        //masukkan isi pass.txt ke array content[][]
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 2; j++){
                data >> content[i][j];
            }
        }
    }
    data.close();
    cout << content[nomor + 1][1];
}

void Saving(string saved[]) {
    ofstream myfile("data.txt", ios::out| fstream::app);
    
    if(myfile.is_open()){     
        for(int j = 0; j < 2; j++){ //inner untuk 2 input akun & pass
            myfile << saved[j] << " ";
        } 
        myfile << endl;
    }
    else {
        cout << "File tidak dapat dibuka/ditemukan";
    }
    myfile.close();
}

string generate(int panjang){
	const string cha = "1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:ZXCVBNM<>?";
	string pw;
	for (int i=0;i<panjang;i++){
		int chpw= rand() % cha.size();
		pw += cha[chpw];
		
	}
	return pw;
}

int main() {
    
        cout << R"(
 #####    ##       #####     ####     #####  
 ##       ##       ##  ##   ##  ##   ##      
 ####     ##       #####    ######    ####   
 ##       ##       ##       ##  ##       ##  
 #####    #####    ##       ##  ##   #####                                              
    )"; 
    cout << endl;
    cout << "======= Elins Password Manager v.0.1 ======";
    cout << endl;
    cout << endl;
    while(true){
    cout << "Silakan pilih fitur yang diinginkan : " << endl;
    cout << "1. Input Manual Password" << endl << "2. Auto-generated Password" << endl << "3. Look-up saved password" << endl << "4. Exit" ;
    cout << endl;
    
    int x;
    cout << "Masukkan angka (1 - 4) = ";
    cin >> x;

        if(x == 1){
            // //input manual
            string key;
            string InputAcc[2];
            cout << "Masukkan Key = ";
            cin >> key;
            cout << "Masukkan ID & Password = ";
            for(int i = 0; i < 2; i++){
                cin >> InputAcc[i];
                InputAcc[i] = Encrypt(InputAcc[i], key);
            }
            
            Saving(InputAcc);
            cout << "Data berhasil disimpan!" << endl;
            cout << endl;
            Sleep(1000);
            system("CLS");
        }
        else if(x == 2){
            //generate random
            string key;
            int ln;
            string InputAcc[2];
            cout << "Masukkan Key = ";
            cin >> key;
            cout << "Masukkan ID = ";
            cin >> InputAcc[0];
            cout << "Masukkan Panjang Password= ";
            cin >> ln;
            InputAcc[1] = generate(ln);
            for(int i = 0; i < 2; i++){
                InputAcc[i] = Encrypt(InputAcc[i], key);
            }
            Saving(InputAcc);
            cout << "Data berhasil disimpan!" << endl;
            cout << endl;
            system("CLS");
        }
        else if(x == 3){
            //lookup
            string key;
            cout << "Masukkan key = ";
            cin >> key;
            DisplayAll(key);
            cout << endl;
        } 
        else if(x == 4){
            //exit
            cout << "Terimakasih!";
            cout << endl;
            break;
        }else if(x == 0){
            cout << "Masukkan yg bener";
            cout << endl;
            continue;
        } else {
            cout << "Masukkan yg bener";
            cout << endl;
            continue;
        }
    }
}
