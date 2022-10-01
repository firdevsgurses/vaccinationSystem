#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <cstdio>
#include <ctime>
#include <sstream>
using namespace std;
typedef struct USER {
	int age, dose;
	string name, surname, city, date, typeOfVaccine, ID;
};
USER u;
USER* user = &u;
void randomID(USER* user) { //random bir ID olusturularak gerekli yerlerde cagirilir
	srand(time(NULL));
	static const string numbersList = "0123456789";
	static const string lettersList = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string numbers;
	string letters;
	for (int i = 0;i < 2;i++) {
		letters += lettersList[rand() % lettersList.size()];
		numbers += numbersList[rand() % numbersList.size()];
	}
	(*user).ID = letters + numbers;
}
void signUpForSystem(USER* user) { // sisteme kayýtlar bu fonksiyon uzerinden yapilacaktir
	(*user).dose = 0;
	(*user).typeOfVaccine = "NULL";
	(*user).date = "01.06.2020";
	ofstream userInfo;
	userInfo.open("database.txt", ios::app); //yeni bilgi eklendiginde alt satira gecer
	cout << "Adinizi giriniz: ";
	cin >> ws;
	getline(cin, (*user).name);
	cout << "Soyadinizi giriniz: ";
	cin >> ws;
	getline(cin, (*user).surname);
	cout << "Yasinizi giriniz: ";
	cin >> (*user).age;
	cout << "Sehrinizi giriniz: ";
	cin >> ws;
	getline(cin, (*user).city);
	randomID(user); //random id fonksiyonu signup icerisnde cagirilarak kullanici profiline atanir 
	cout << "ID'niz: " << (*user).ID << " not aliniz! " << endl;
	userInfo << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine; // kullanicidan alinan verileri dosyaya bu sekilde yaziyoruz
}
void display(USER* user) { // sistemdeki kaydi goruntuleme islemi buradan yapilacaktir
	string checkID; //ID kontrolu vasitasiyla goruntulenmek istenen profilin bilgileri alinacak
	cout << "Goruntulemek istediginiz profilin ID'sini giriniz: ";
	cin >> checkID;
	ifstream userInfoOpen("database.txt"); // database dosyasýný acan satir
	while (!(userInfoOpen.eof())) {
		userInfoOpen >> (*user).ID >> (*user).name >> (*user).surname >> (*user).age >> (*user).city >> (*user).date >> (*user).dose >> (*user).typeOfVaccine; //dosyadaki bilgileri sirayla okuyoruz
		if (checkID == (*user).ID) { // eger kullanýcý ID'si ile goruntulenmek istenen profil ID'si eslesirse sartý
			cout << "ID: " << (*user).ID << ", AD: " << (*user).name << ", SOYAD: " << (*user).surname << ", YAS: " << (*user).age << ", SEHIR: " << (*user).city << ", TARIH: " << (*user).date << ", DOZ: " << (*user).dose << ", ASI TURU : " << (*user).typeOfVaccine << endl; //sart saglanirsa bilgileri cmd ekranýna yazdýrýr
			break;
		}
		else
			continue;
	}
}
void update(USER* user) { // kayit guncellemeleri bu fonksiyon ile yapilacaktir
	//bu fonksiyonda yine ID uzerinden kullanici bilgilerinde degisim yapilir. ID dogruysa istenen bilgiler menu dogrultusunda degisebilecektir.
	string checkID;
	int choice;
	cout << "ID'nizi giriniz: ";
	cin >> checkID;
	ifstream userInfoOpen("database.txt"); //database dosyasini aciyoruz
	ofstream tempFile("temp.txt"); //temp dosyamizi aciyoruz. verileri once temp'te tutacagiz
	while (!(userInfoOpen.eof())) {
		userInfoOpen >> (*user).ID >> (*user).name >> (*user).surname >> (*user).age >> (*user).city >> (*user).date >> (*user).dose >> (*user).typeOfVaccine;
		if (checkID == (*user).ID) {
			while (1) {
				cout << "(1) ID Guncelleme\n";
				cout << "(2) Ad Guncelleme\n";
				cout << "(3) Soyad Guncelleme\n";
				cout << "(4) Yas Guncelleme\n";
				cout << "(5) Sehir Guncelleme\n";
				cout << "(6) Ana Menuye Donus\n";
				cout << "Secimizini yapin: ";
				cin >> choice;
				if (choice == 1) {
					cout << "Yeni ID giriniz: ";
					cin >> (*user).ID;
				}
				if (choice == 2) {
					cout << "Adinizi giriniz: ";
					cin >> ws;
					getline(cin, (*user).name);
				}
				if (choice == 3) {
					cout << "Soyadinizi giriniz: ";
					cin >> ws;
					getline(cin, (*user).surname);
				}
				if (choice == 4) {
					cout << "Yasinizi giriniz: ";
					cin >> (*user).age;
				}
				if (choice == 5) {
					cout << "Sehrinizi giriniz: ";
					cin >> (*user).city;
				}
				if (choice == 6) {
					break;
				}
			}
			tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine; //degisen bilgileri temp.txt icine yazýyoruz
		}
		else {
			tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine; //eger ID eslesmemisse kullanici bilgileri ayni sekilde temp icerisine yazilir
		}
	}
	userInfoOpen.close(); // acilan dosya kapanir
	tempFile.close(); //acilan dosya kapanir
	remove("database.txt"); // database'i siliyoruz cünkü degisen bilgileri temp iceisine yazdik
	rename("temp.txt", "database.txt"); // temp.txt'i yeniden adlandýrýyoruz ki program her database.txt actiginda guncellenmis dosyayi acsin
}
int daysBetweenDates(string date1, string date2) {
	//bu fonksiyon iceriisnde iki tarih arasindaki fark hesaplanýr
	stringstream ss(date1 + "." + date2);
	int year, month, day;
	char dot;
	ss >> day >> dot >> month >> dot >> year;
	struct tm starttm = { 0, 0, 0, day, month - 1, year - 1900 };
	time_t start = mktime(&starttm);
	ss >> dot >> day >> dot >> month >> dot >> year;
	struct tm endtm = { 0, 0, 0, day, month - 1, year - 1900 };
	time_t end = mktime(&endtm);
	return abs(end - start) / 86400;
}
void signUpForVaccination(USER* user) { // asi kaydi buradan yapilacaktir
	string checkID, checkDate, checkType1, checkType2;
	cout << "ID'nizi giriniz: ";
	cin >> checkID;
	ifstream userInfoOpen("database.txt");
	ofstream tempFile("temp.txt");
	while (!(userInfoOpen.eof())) {
		userInfoOpen >> (*user).ID >> (*user).name >> (*user).surname >> (*user).age >> (*user).city >> (*user).date >> (*user).dose >> (*user).typeOfVaccine;
		if (checkID == (*user).ID && (*user).dose < 2 && (*user).age >= 18) {
			if ((*user).typeOfVaccine == "NULL") {
				cout << "Olmak istediginiz asi turunu seciniz (X veya Y) : ";
				cin >> checkType1;
				if (checkType1 == "X") {
					(*user).typeOfVaccine = checkType1;
					cout << "Asi olmak istediginiz tarihi giriniz (dd.mm.yyyy) : ";
					cin >> checkDate;
					if ((*user).dose == 0) {
						(*user).date = checkDate;
						(*user).dose++;
						tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
					}
					else if (daysBetweenDates((*user).date, checkDate) > 30 && (*user).dose == 1) {
						(*user).date = checkDate;
						(*user).dose++;
						tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
					}
					else if (daysBetweenDates((*user).date, checkDate) < 30 && checkID == (*user).ID && (*user).dose < 2) {
						cout << "Ilk asinizin uzerinden en az 30 gun gecmelidir!" << endl;
						tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
					}
				}
				if (checkType1 == "Y") {
					(*user).typeOfVaccine = checkType1;
					cout << "Asi olmak istediginiz tarihi giriniz (dd.mm.yyyy) : ";
					cin >> checkDate;
					if ((*user).dose == 0) {
						(*user).date = checkDate;
						(*user).dose++;
						tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
					}
					else if (daysBetweenDates((*user).date, checkDate) > 30 && (*user).dose == 1) {
						(*user).date = checkDate;
						(*user).dose++;
						tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
					}
					else if (daysBetweenDates((*user).date, checkDate) < 30 && checkID == (*user).ID && (*user).dose < 2) {
						cout << "Ilk asinizin uzerinden en az 30 gun gecmelidir!" << endl;
						tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
					}
				}
			}
			else {
				cout << "Olmak istediginiz asi turunu seciniz (X veya Y) : ";
				cin >> checkType2;
				if (checkType2 == (*user).typeOfVaccine) {
					(*user).typeOfVaccine = checkType2;
					cout << "Asi olmak istediginiz tarihi giriniz (dd.mm.yyyy) : ";
					cin >> checkDate;
					if ((*user).dose == 0) {
						(*user).date = checkDate;
						(*user).dose++;
						tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
					}
					else if (daysBetweenDates((*user).date, checkDate) > 30 && (*user).dose == 1) {
						(*user).date = checkDate;
						(*user).dose++;
						tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
					}
					else if (daysBetweenDates((*user).date, checkDate) < 30 && checkID == (*user).ID && (*user).dose < 2) {
						cout << "Ilk asinizin uzerinden en az 30 gun gecmelidir!" << endl;
						tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
					}
				}
				else if (checkType2 != (*user).typeOfVaccine) {
					cout << "Asi turleri ayni olmalidir!" << endl;
					tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
				}
			}
		}
		else if (checkID == (*user).ID && (*user).age < 18) {
			cout << "Asi olmak icin 18 yasindan buyuk olmalisiniz!" << endl;
			tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
		}
		else if (checkID == (*user).ID && (*user).dose >= 2 && (*user).age >= 18) {
			cout << "2'den fazla asi olamazsiniz!" << endl;
			tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
		}
		else {
			tempFile << endl << (*user).ID << " " << (*user).name << " " << (*user).surname << " " << (*user).age << " " << (*user).city << " " << (*user).date << " " << (*user).dose << " " << (*user).typeOfVaccine;
		}
	}
	userInfoOpen.close();
	tempFile.close();
	remove("database.txt");
	rename("temp.txt", "database.txt");
}
int main() {
	int choice;
	while (true) {
		cout << "(1) Yeni Kayit\n";
		cout << "(2) Kayit Guncelleme\n";
		cout << "(3) Kayit Goruntuleme\n";
		cout << "(4) Asi Kaydi\n";
		cout << "(5) Cikis\n";
		cout << "Secimizini yapin: ";
		cin >> choice;
		if (choice == 1)
			signUpForSystem(user);
		if (choice == 2)
			update(user);
		if (choice == 3)
			display(user);
		if (choice == 4)
			signUpForVaccination(user);
		if (choice == 5)
			exit(0);
	}
	system("pause");
}