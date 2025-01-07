#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

#include<cstdlib>

string bookName[15] = {""};
string bookAuthor[15] = {""};
string bookGenre[15] = {""};
short bookID[15] = {0.0};
string issued[15] = {""};

//User Login Authentication
bool login(short *user){
	string username, password, username_check, password_check;
	short choice, choose;
	fstream admin_login, user_login;		//Declare both admin and user file seperately to keep the user data organized
	cout<<"___Login Authentication__\n";
	cout<<"Press 1 for Admin\n";
	cout<<"Press 2 for Member\n";
	cout<<"Enter your choice:";
	cin>>choice;
	*user = choice;
	switch(choice){
    	case 1:
		//Admin Login Authentication
    		cout<<"\nPress 1 for Login\n";
		cout<<"Press 2 to Add Another Admin\n";
		cout<<"Enter your choice:";
    		cin>>choose;
    		admin_login_verify:
    		if(choose == 1){
    			admin_login.open("Admin_Login.txt", ios::app | ios::in);	//Open File
    			if(!admin_login){	//To check for error while opening file
    				cout<<"\nError! file does not exist"<<endl;
    				return 0;
			}
			else{
				//Admin Login Portal
				cout<<"\n__Admin Login__\n";
				cout<<"Enter username: ";
				cin>>username;
				cout<<"Enter password: ";
				cin>>password;
				bool check = false;	//Input verification in file
				while(admin_login >> username_check >> password_check){	//Read username then password from the file
					if(username == username_check && password == password_check){
						check = true;	//When input matches the data in file, check becomes true otherwise stays false
					}
				}
				//Login Result
				if(check){
					cout<<"\nLogin Successful!\n";
					system("cls");
					return 1;
				}
				else{
					cout<<"\nInvalid username or password!\n";
					return 0;
				}
			}
			admin_login.close();
		}
		//Add another member as an admin Portal
		else if(choose==2){
			admin_login.open("Admin_Login.txt", ios::app | ios::in);	//Open File
			if(!admin_login){	//File Open Verification
    				cout<<"Error! file does not exist"<<endl;
    				return 0;
			}
			else{
				short passkey_confirm = 1234, passkey;	//To verify the admin
				cout<<"\nEnter passkey to continue:";
				cin>>passkey;
				if(passkey == passkey_confirm){
					cout<<"\n__Admin Signup__\n";
					cout<<"Enter Username:";
					cin>>username;
					cout<<"Password:";
					cin>>password;
					admin_login<<username<<endl<<password<<endl	;
					cout<<"\nSignUp Successful!\n";
				}
				else{
					cout<<"\nInvalid passkey!\n";
					return 0;
				}
			}
		}
		admin_login.close();	//Close File
		choose = 1;
		goto admin_login_verify;
		break;
	case 2:
		//Member login Authentication
    		cout<<"\nPress 1 for Login\n";
		cout<<"Press 2 for SignUp\n";
		cout<<"Enter your choice:";
    		cin>>choose;
    		if(choose==1){
    			member_login_verify:
    			user_login.open("User_Login.txt", ios::app | ios::in);	//Open File
    			if(!user_login){	//File Open Verification
    				cout<<"Error! file does not exist"<<endl;
    				return 0;
			}
			else{
				//Member Login Authentication
				cout<<"\n__Member Login__\n";
				cout<<"Enter username: ";
				cin>>username;
				cout<<"Enter password: ";
				cin>>password;
				bool check = false;	
				while(user_login >> username_check >> password_check){
					if(username == username_check && password == password_check){	//Verify input username & password from file
						check = true;
					}
				}
				//Login Result
				if(check){
					cout<<"\nLogin Successful!\n";
					system("cls");
					return 1; 
				}
				else{
					cout<<"\nInvalid username or password!\n";
					return 0;
				}
			}
			user_login.close();
		}
		else if(choose==2){
			user_login.open("User_Login.txt", ios::app | ios::in);	//Open File
			if(!user_login){	//File Open Verification
    				cout<<"\nError! file does not exist\n"<<endl;
    				return 0;
			}
			else{
				//Member Sign Up Portal
				cout<<"\n__Member Signup__\n";
				cout<<"Username:";
				cin>>username;
				cout<<"Password:";
				cin>>password;
				user_login<<username<<endl<<password<<endl;
				cout<<"\n\nSignUp Successful!\n";
			}
		}
		user_login.close();	//Close File
		goto member_login_verify;
		break;
	default:
		//Invalid User Input
		cout<<"\nYour choice is invalid"<<endl;
		return 0;
		break;
	}
	return 0;
}

//Library Books Data
void localBooks(){
	ifstream bookData;
	bookData.open("Library.txt");	//Open File
	if (!bookData) {	//File Open Verification
        cout << "Error opening file!" << endl;
        return;
    }
	int i = 0;
	while(bookData>>bookName[i]>>bookGenre[i]>>bookAuthor[i]>>bookID[i]>>issued[i]){	//Store the book data from file in arrays using loop
    	i++;
    	if(i>=15)
		break;
	}
	cout<<endl;
	//Print all the books in stock and their data
	cout<<left<<setw(25)<<"Book Name"
        <<setw(20)<<"Genre"
        <<setw(25)<<"Author"
        <<setw(10)<<"Book ID"
        <<setw(10)<<"Book Issued"<<endl;
	for (int j=0;j<i;++j) {
     	cout<<left<<setw(25)<<bookName[j]
            <<setw(20)<<bookGenre[j]
            <<setw(25)<<bookAuthor[j]
            <<setw(10)<<bookID[j]
            <<setw(10)<<issued[j] << endl;
	}
	bookData.close();	//Close File
}

//Show all the members who signed up to admin
void members_view(){
	string usernames;
	int choice;
	//Ask admin if he wants to view members
	cout<<"\nDo you want to view members list?\n";
	cout<<"Press 1 for Yes\n";
	cout<<"Press 2 for No\n";
	cout<<"Enter your choice:";
	cin>>choice;
	if(choice == 1){	//Show members list
		ifstream members_data;
		members_data.open("User Login.txt");	//Open File
		if(!members_data){	//File Open Verification
			cout<<"Error! File does not exist.\n";
		}
		//Print usernames
		short i = 1;
		cout<<"\nMembers list (Usernames)\n";
		while(members_data >> usernames){	
			if(i % 2 != 0){
				cout<<usernames<<endl;
			}
			i++;
		}
		members_data.close();	//Close File
	}
}

//To issue a book
void book_issued(){
	short choice = 0;
	cout<<"\nDo you want to issue a book?\n";
	cout<<"Press 1 for Yes\n";
	cout<<"Press 2 for No\n";
	cout<<"Enter your choice:";
	cin>>choice;
	if(choice == 1){
		ifstream read_bookData;
		ofstream write_bookData;
		localBooks();
		short id = 0, j = 0;
		cout<<"Enter Book ID:";
		cin>>id;
		if(id > 0 && id < 200){
		short i = 0;
		read_bookData.open("Library.txt");
		if(!read_bookData){
			cout<<"\nError! File does not exist.\n";
		}
		else{
			while(read_bookData>>bookName[i]>>bookGenre[i]>>bookAuthor[i]>>bookID[i]>>issued[i]){
				if(bookID[i] == id){
					j = i;
				}
				i++;
				if(i>=15){
					break;
				}
			}
		read_bookData.close();
		}
		if(issued[j] == "Yes"){
			cout<<"\nThe book is already issued.\n";
		}
		else{
			cout<<left<<setw(25)<<"Book Name"
        				<<setw(20)<<"Genre"
        				<<setw(25)<<"Author"
	        			<<setw(10)<<"Book ID"
	     	   		<<setw(10)<<"Book Issued"<<endl;
	        	cout<<left<<setw(25)<<bookName[j]
     	       		<<setw(20)<<bookGenre[j]
          	  		<<setw(25)<<bookAuthor[j]
            			<<setw(10)<<bookID[j]
	     	       	<<setw(10)<<issued[j] << endl;
     		short choice = 0;
     		cout<<"\nIssuance Confirmation\n";
	     	cout<<"Press 1 to Accept\n";
     		cout<<"Press 2 to Decline\n";
     		cout<<"Enter your choice:";
	     	cin>>choice;
     		if(choice == 1){
     		     cout<<"\nThe book has been issued.\n";
     			issued[j] = "Yes";
	     		write_bookData.open("Library.txt");
	     		if(!write_bookData){
	     			cout<<"\nError! File does not exit.\n";
				}
				else{
     		     	short k = 0;
					while(k < 15){
						write_bookData << bookName[k] << " " << bookGenre[k] << " " << bookAuthor[k] << " " << bookID[k] << " " << issued[k] << endl;
						k++;
						if(bookName[k] == ""){
								break;
							}
						}
					write_bookData.close();
				}
			}
			else{
				cout<<"\nThe issuance of book has been declined.\n";
			}
     	}}
     	else{
     		cout<<"\nInvalid Book ID!\n";
     		return;
		}
	}
	else{
		return;
	}
}

//To return a book
void book_return(){
	short choice = 0;
	cout<<"\nDo you want to return a book?\n";
	cout<<"Press 1 for Yes\n";
	cout<<"Press 2 for No\n";
	cout<<"Enter your choice:";
	cin>>choice;
	if(choice == 1){
		ifstream read_bookData;
		ofstream write_bookData;
		localBooks();
		short id = 0, j = 0;
		cout<<"\nEnter Book ID:";
		cin>>id;
		if(id > 0 && id < 200){
		short i = 0;
		read_bookData.open("Library.txt");
		if(!read_bookData){
			cout<<"\nError! File does not exist.\n";
		}
		else{
			while(read_bookData>>bookName[i]>>bookGenre[i]>>bookAuthor[i]>>bookID[i]>>issued[i]){
				if(bookID[i] == id){
					j = i;
				}
				i++;
				if(i>=15){
					break;
				}
			}
		read_bookData.close();
		}
		if(issued[j] == "No"){
			cout<<"\nThe book is already returned.\n";
		}
		else{
			cout<<left<<setw(25)<<"Book Name"
        				<<setw(20)<<"Genre"
        				<<setw(25)<<"Author"
	        			<<setw(10)<<"Book ID"
	     	   		<<setw(10)<<"Book Issued"<<endl;
	        	cout<<left<<setw(25)<<bookName[j]
     	       		<<setw(20)<<bookGenre[j]
          	  		<<setw(25)<<bookAuthor[j]
            			<<setw(10)<<bookID[j]
	     	       	<<setw(10)<<issued[j] << endl;
     		short choice = 0;
     		cout<<"\nReturn Confirmation\n";
	     	cout<<"Press 1 to Accept\n";
     		cout<<"Press 2 to Decline\n";
     		cout<<"Enter your choice:";
	     	cin>>choice;
     		if(choice == 1){
     		     cout<<"\nThe book has been returned.\n";
     			issued[j] = "No";
	     		write_bookData.open("Library.txt");
	     		if(!write_bookData){
	     			cout<<"\nError! File does not exit.\n";
				}
				else{
     		     	short k = 0;
					while(k < 15){
						write_bookData << bookName[k] << " " << bookGenre[k] << " " << bookAuthor[k] << " " << bookID[k] << " " << issued[k] << endl;
						k++;
						if(bookName[k] == ""){
								break;
							}
						}
					write_bookData.close();
				}
			}
			else{
				cout<<"\nThe book couldn't be returned.'\n";
			}
     	}}
     	else{
     		cout<<"\nInvlid Book ID!\n";
     		return;
		}
	}
	else{
		return;
	}
}

//To update the data of a book
void book_update(){

	ifstream read_bookData;
	ofstream write_bookData;
	short i = 0, choose = 0;
	do{
		localBooks();
		short id = 0, j = 0;
		cout<<"\nEnter Book ID:";
		cin>>id;
		if(id > 0 && id < 200){
		short choice = 0;
		cout<<"\nWhat do you want to update?\n";
		cout<<"Press 1 for Book Name\n";
		cout<<"Press 2 for Book Genre\n";
		cout<<"Press 3 for Book Author\n";
		cout<<"Enter your choice:";
		cin>>choice;
		if(choice == 1){
			string book_name;
			cout<<"\nEnter book name:";
			cin>>book_name;
			read_bookData.open("Library.txt");
			if(!read_bookData){
				cout<<"\nError! File does not exist.\n";
			}
			else{
				while(read_bookData>>bookName[i]>>bookGenre[i]>>bookAuthor[i]>>bookID[i]>>issued[i]){
					if(bookID[i] == id){
						j = i;
						}
						i++;
						if(i>=15){
							break;
						}
					}
				read_bookData.close();
				}
				if(bookName[j] == book_name){
					cout<<"\nThe book name is same.\n";
				}
				else{
	     			short choice = 0;
	     			cout<<"\nUpdate Confirmation\n";
		     		cout<<"Press 1 to Accept\n";
	     			cout<<"Press 2 to Decline\n";
     				cout<<"Enter your choice:";
			     	cin>>choice;
     				if(choice == 1){
	     		     	cout<<"\nThe book has been updated.\n";
		     			write_bookData.open("Library.txt");
	     				if(!write_bookData){
	     					cout<<"\nError! File does not exit.\n";
						}
						else{
							bookName[j] = book_name;
     			     		short k = 0;
							while(k < 15){
								write_bookData << bookName[k] << " " << bookGenre[k] << " " << bookAuthor[k] << " " << bookID[k] << " " << issued[k] << endl;
								k++;
								if(bookName[k] == ""){
										break;
									}
								}
							write_bookData.close();
						}
					}
					else{
						cout<<"\nThe book couldn't be updated.'\n";
					}
     			}
     		}
     		else if(choice == 2){
     			string book_genre;
				cout<<"\nEnter book genre:";
				cin>>book_genre;
				read_bookData.open("Library.txt");
				if(!read_bookData){
					cout<<"\nError! File does not exist.\n";
				}
				else{
					while(read_bookData>>bookName[i]>>bookGenre[i]>>bookAuthor[i]>>bookID[i]>>issued[i]){
						if(bookID[i] == id){
							j = i;
						}
						i++;
						if(i>=15){
							break;
						}
					}
				read_bookData.close();
				}
				if(bookGenre[j] == book_genre){
					cout<<"\nThe book name is same.\n";
				}
				else{
	     			short choice = 0;
	     			cout<<"\nUpdate Confirmation\n";
		     		cout<<"Press 1 to Accept\n";
	     			cout<<"Press 2 to Decline\n";
     				cout<<"Enter your choice:";
			     	cin>>choice;
     				if(choice == 1){
	     		     	cout<<"\nThe book has been updated.\n";
		     			write_bookData.open("Library.txt");
	     				if(!write_bookData){
	     					cout<<"\nError! File does not exit.\n";
						}
						else{
							bookGenre[j] = book_genre;
     			     		short k = 0;
							while(k < 15){
								write_bookData << bookName[k] << " " << bookGenre[k] << " " << bookAuthor[k] << " " << bookID[k] << " " << issued[k] << endl;
								k++;
								if(bookName[k] == ""){
										break;
									}
								}
							write_bookData.close();
						}
					}
					else{
						cout<<"\nThe book couldn't be updated.'\n";
					}
				}
			}
			else if(choice == 3){
				string book_author;
				cout<<"\nEnter book author:";
				cin>>book_author;
				read_bookData.open("Library.txt");
				if(!read_bookData){
					cout<<"\nError! File does not exist.\n";
				}
				else{
					while(read_bookData>>bookName[i]>>bookGenre[i]>>bookAuthor[i]>>bookID[i]>>issued[i]){
						if(bookID[i] == id){
							j = i;
						}
						i++;
						if(i>=15){
							break;
						}
					}
				read_bookData.close();
				}
				if(bookAuthor[j] == book_author){
					cout<<"\nThe book name is same.\n";
				}
				else{
	     			short choice = 0;
	     			cout<<"\nUpdate Confirmation\n";
		     		cout<<"Press 1 to Accept\n";
	     			cout<<"Press 2 to Decline\n";
     				cout<<"Enter your choice:";
			     	cin>>choice;
     				if(choice == 1){
	     		     	cout<<"\nThe book has been updated.\n";
		     			write_bookData.open("Library.txt");
	     				if(!write_bookData){
	     					cout<<"\nError! File does not exit.\n";
						}
						else{
							bookAuthor[j] = book_author;
     			     		short k = 0;
							while(k < 15){
								write_bookData << bookName[k] << " " << bookGenre[k] << " " << bookAuthor[k] << " " << bookID[k] << " " << issued[k] << endl;
								k++;
								if(bookName[k] == ""){
										break;
									}
								}
							write_bookData.close();
						}
					}
					else{
						cout<<"\nThe book couldn't be updated.'\n";
					}
				}
			}
		}
     	cout<<"\nDo you want to again updata data of a book?\n";
     	cout<<"Press 1 for Yes\n";
     	cout<<"Press 2 for No\n";
     	cout<<"Enter your choice:";
     	cin>>choose;
	}while(choose == 1);
}

//To view or add new books in the library
void libraryBooks(){
	int choice;
	cout<<"\nDo you want view current books or to add new books or to remove existing books?\n";
	cout<<"Press 1 to View\n";
	cout<<"Press 2 to Add\n";
	cout<<"Press 3 to Remove\n";
	cout<<"Press 4 to Update\n";
	cout<<"Press 5 for None\n";
	cout<<"Enter your choice:";
	cin>>choice;
	if(choice == 1){
		localBooks();
	}
	else if(choice == 2){
		string bookdata = "";
		short num = 0;
		localBooks();
		ofstream outbookData;
		outbookData.open("library.txt", ios::app);	//Open the file
		do{
			short choice = 0;
			//Enter new book in the file
			cout<<"Enter Book Name:";
			cin>>bookdata;
			outbookData<<bookdata<<" ";
			cout<<"Enter Book Genre:";
			cin>>bookdata;
			outbookData<<bookdata<<" ";
			cout<<"Enter Book Author:";
			cin>>bookdata;
			outbookData<<bookdata<<" ";
			cout<<"Enter Book ID:";
			cin>>num;
			outbookData<<num<<" ";
			cout<<"Enter Book Issuance:";
			cin>>bookdata;
			outbookData<<bookdata<<endl;
			//To ask if he wants to enter another
			outbookData.close();	//Close the file
			cout<<"\nDo you want to enter another book?\n";
			cout<<"Press 1 for Yes\n";
			cout<<"Press 2 for No\n";
			cout<<"Enter your choice:";
			cin>>choice;
		}while(choice == 1);
	}
	else if(choice == 3){
		short id = 0, choice = 0;
		ifstream read_bookData;
		ofstream remove_bookData;
		read_bookData.open("Library.txt");
		do{
			cout<<"\nEnter Book ID:";
			cin>>id;
			if(id > 0 && id < 200){
			short i = 0;
			while(read_bookData>>bookName[i]>>bookGenre[i]>>bookAuthor[i]>>bookID[i]>>issued[i]){
				i++;
			}
			read_bookData.close();
			remove_bookData.open("Library.txt");
			i = 0;
			bool check = false;
			while(i < 15){
				if(bookName[i] == ""){
					break;
				}
				if(bookID[i] == id){
					check = true;
				}
				if(bookID[i] != id){
					remove_bookData << bookName[i] << " " << bookGenre[i] << " " << bookAuthor[i] << " " << bookID[i] ;
					remove_bookData << " " << issued[i] << endl;
				}
				i++;
			}
			if(check){
				cout<<"\nBook removed successfuly!\n";
			}
			else{
				cout<<"\nBook not found.\n";
			}}
			else{
				cout<<"\nInvalid Book ID!\n";
				return;
			}
			cout<<"\nDo you want to remove another book?\n";
			cout<<"Press 1 for Yes\n";
			cout<<"Press 2 for No\n";
			cout<<"Enter your choice:";
			cin>>choice;
		}while(choice == 1);
	}
	else if(choice == 4){
		book_update();	//To update the data of a book
	}
	else if(choice == 5){
		return;	//To exit the function
	}
	else{
		cout<<"Your choice is invalid";	//For invalid input
	}
}

//Membership authentication
bool libraryMemberships(){
	int check;	//To check for membership
	
	//Yes or No Prompt
	cout<<"_____________________________\n\n";
	cout<<"Press 1 for Yes\n";
	cout<<"Press 2 for No\n";
	cout<<"_____________________________\n";
	cout<<"\nDo you have a membership ?\n";
	cout<<"Enter your choice:";
	cin>>check;		//Membership ask
	
	if(check == 1){
		return 1;	//Exit if has membership
	}
	else if(check == 2){
		//Show Fees & Durarion & Return Day Limit & Fine Rate 
		cout<<" \n__________________________________________\n";
		cout<<"|Membership Fees            $5             |\n";
		cout<<"|Membership Duration        6 Months       |\n";
		cout<<"|Return Days                30 days        |\n";
		cout<<"|Fine Rate                  $0.5per_day    |\n";
		cout<<"|__________________________________________|\n";	
		cout<<"\nDo you want to become a member?"<<endl;	//Ask for willingness
		cout<<"Press 1 for Yes\n";
		cout<<"Press 2 for No\n";
		cout<<"Enter your choice:";
		cin>>check;
		
		if(check == 1){
			cout<<"\nHave you paid the membership fees ?\n";	//Ask for fees payment
			cout<<"Enter your choice:";
			cin>>check;
			
			if(check == 1){
				cout<<"\nNow, you are a member of library."<<endl;	//Accept the membership request
				return 1;
			}
			
			else{
				cout<<"\nPlease pay the membership fees.\n";		//Decline the membership request
				return 0;
			}
			
		}
		
		else{
			cout<<"\nYou have just checked the requirments to become the member"<<endl;	//Show he just view the detatils of memebrship
			return 0;
		}
	}
	
	else{
		cout<<"\nYour choice is invalid!\n";	//To identify invalid input
		return 0;
	}
	return 0;
}

//Issuance of book & Reutrning of book & Fine Calculation & Report Generation
void libraryMatters(int user){
	short fine = 0.0;
	short choice = 0;
	short i = 0;
	short days = 0;
	ofstream outReport;
	switch(user){
		case 1:{
			book_issued();	//To issue a book
			book_return();	//To return a book
			//To calculate the fine
			cout<<"\nDo you want to calculate the fine on a member?\n";
			cout<<"Press 1 for Yes\n";
			cout<<"Press 2 for No\n";
			cout<<"Enter your choice:";
			cin>>choice;
			if(choice == 1){
				cout<<"\nEnter how many days have passed after the deadline (Enter 0 if none):";	//Days input
				cin>>days;
				//Calculation
				if(days <= 30 && days >= 0){
					while(i < days && i < 10){
						fine += 20;
						i++;
					}
					while(i < days && i < 20){
						fine += 50;
						i++;
					}
					while(i < days && i < 30){
						fine += 100;
						i++;
					}
					cout<<"\nThe fine on the member:"<<fine<<endl;
				}
				else	if(days > 30){	//Membership revoked
					cout<<"\nThe membership has been cancelled!\n";
				}
				else{	//Invalid days authenticate
					cout<<"\nInvalid days input!\n";
				}
			}
			else if(choice != 2){	//Invalid input authenticate
				cout<<"\nYour choice is invalid!\n";
			}
			outReport.open("Report.txt", ios::app);	//Open Report File
			//To generate the report of member
			cout<<"\nDo you want to generate the report card of the member?\n";
			cout<<"Press 1 for Yes\n";
			cout<<"Press 2 for No\n";
			cout<<"Enter the choice:";
			cin>>choice;
			if(choice == 1){
				//Show report on console
				cout<<"\n--------------------------------------------\n";
				cout<<"|         BOOK RETURN DETAILS              |\n";
				cout<<"--------------------------------------------\n";
				cout<<left<<setw(25)<<"| Late Days"<<"      |    "<<left<<setw(2)<< days <<"     |\n";
				if (days > 30) {
     				cout<<left<<setw(25)<<"| Membership Status"<< "      | Cancelled      |\n";
     				cout<<"--------------------------------------------\n";
				}
				else{
				cout<<left<<setw(25)<<"| Membership Status"<<"      | Active    |\n";
				cout<<left<<setw(25)<<"| Fine"<<"      |   "<<left<<setw(4)<< fine <<"Rs  |\n";
        			cout<<"--------------------------------------------\n";
				}
				//Save report in file
				outReport<<"\n--------------------------------------------\n";
				outReport<<"|         BOOK RETURN DETAILS              |\n";
				outReport<<"--------------------------------------------\n";
				outReport<<left<<setw(25)<<"| Late Days"<<"      |    "<<left<<setw(2)<< days <<"     |\n";
				if (days > 30) {
     				cout<<left<<setw(25)<<"| Membership Status"<< "      | Cancelled      |\n";
     				cout<<"--------------------------------------------\n";
				}
				else{
				outReport<<left<<setw(25)<<"| Membership Status"<<"      | Active    |\n";
				outReport<<left<<setw(25)<<"| Fine"<<"      |   "<<left<<setw(4)<< fine <<"Rs  |\n";
        			outReport<<"--------------------------------------------\n";
				}
			}
			
			else if(choice == 2){
				outReport.close();	//Close File if condition True
				return;	//To exit the function
			}
			else{
				cout<<"\nYour choice is invalid!\n";
			}
			outReport.close();	//Close File
			break;	//Exit switch body
		}
		case 2:{
			book_issued();	//To issue a book
			book_return();	//To return a book
			//To calculate the fine
			cout<<"\nDo you want to calculate your fine?\n";
			cout<<"Press 1 for Yes\n";
			cout<<"Press 2 for No\n";
			cout<<"Enter your choice:";
			cin>>choice;
			
			if(choice == 1){
				cout<<"\nEnter how many days have passed after the deadline (Enter 0 if none):";	//Days late input
				cin>>days;
				//Calculation
				if(days <= 30 && days >= 0){
					while(i < days && i < 10){
						fine += 20;
						i++;
					}
					while(i < days && i < 20){
						fine += 50;
						i++;
					}
					while(i < days && i < 30){
						fine += 100;
						i++;
					}
					cout<<"\nThe fine on the member:"<<fine<<endl;
				}
				else	if(days > 30){	//Membership revoked
					cout<<"\nThe membership has been cancelled!\n";
				}
				else{	//Invalid days authenticate
					cout<<"\nInvalid days input!\n";
				}
			}
			else if(choice != 2){	//Invalid input authenticate
				cout<<"\nYour choice is invalid!\n";
			}
			outReport.open("Report.txt", ios::app);	//Report File
			//To generate the report of member
			cout<<"\nDo you want to generate the report card of the member?\n";
			cout<<"Press 1 for Yes\n";
			cout<<"Press 2 for No\n";
			cout<<"Enter the choice:";
			cin>>choice;
			
			if(choice == 1){
				//Show report on console
				cout<<"\n--------------------------------------------\n";
				cout<<"|         BOOK RETURN DETAILS              |\n";
				cout<<"--------------------------------------------\n";
				cout<<left<<setw(25)<<"| Late Days"<<"      |    "<<left<<setw(2)<< days <<"     |\n";
				
				if (days > 30) {
     				cout<<left<<setw(25)<<"| Membership Status"<< "      | Cancelled      |\n";
     				cout<<"--------------------------------------------\n";
				}
				else{
				cout<<left<<setw(25)<<"| Membership Status"<<"      | Active    |\n";
				cout<<left<<setw(25)<<"| Fine"<<"      |   "<<left<<setw(4)<< fine <<"Rs  |\n";
        			cout<<"--------------------------------------------\n";
				}
				//Save report in file
				outReport<<"\n--------------------------------------------\n";
				outReport<<"|         BOOK RETURN DETAILS              |\n";
				outReport<<"--------------------------------------------\n";
				outReport<<left<<setw(25)<<"| Late Days"<<"      |    "<<left<<setw(2)<< days <<"     |\n";
				
				if (days > 30) {
     				cout<<left<<setw(25)<<"| Membership Status"<< "      | Cancelled      |\n";
     				cout<<"--------------------------------------------\n";
				}
				else{
				outReport<<left<<setw(25)<<"| Membership Status"<<"      | Active    |\n";
				outReport<<left<<setw(25)<<"| Fine"<<"      |   "<<left<<setw(4)<< fine <<"Rs  |\n";
        			outReport<<"--------------------------------------------\n";
				}
			}
			break;
		}
	}
}

int main(){
	short user = 0, choice = 0;		//1 for admin, 2 for member
	if(login(&user)){	//To validate the login and get return in user depending on admin or member
		do{
			switch(user){
				case 1:	//Admin Portion
					libraryBooks();			//To view or add a book and their respective data
					members_view();			//To view the list of members
					libraryMatters(user);		//To issue or return a book and to calculate fine of members and generate a report
					break;
				case 2:	//Member Portion
					if(libraryMemberships()){	//To validate if user has membership
						localBooks();			//To show books and their data
						libraryMatters(user);	//To issue or return a book and to calculate fine of members and generate a report	
					}
					break;
			}
			cout	<<"\nDo you want to restart?\n";
			cout	<<"Press 1 for Yes\n";
			cout	<<"Press 2 for No\n";
			cout	<<"Enter your choice:";
			cin	>>choice;
		}while(choice == 1);
	}	
	return 0;
}
