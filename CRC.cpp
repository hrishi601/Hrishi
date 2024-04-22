



























































#include<iostream>

using namespace std;

string xorfun( string encoded , string crc)							
{
	int crclen = crc.length();
	
	for ( int i = 0 ; i <= (encoded.length() - crclen) ; )			
	{																
		for( int j=0 ; j < crclen ; j++)								
		{
			encoded[i+j] = encoded[i+j] == crc[j] ? '0' : '1' ;			
		}
	for( ; i< encoded.length() && encoded[i] != '1' ; i++) ;
	
	}
	
	return encoded;
}

int main()
{
	string data , crc , encoded = "";
	cout<<endl<<"-----------Sender Side --------------"<<endl;
	cout<<"Enter Data bits: "<<endl;								
	cin>>data;														
	
	cout<<"Enter Generator: "<<endl;
	cin>>crc;														
	
	encoded += data;												
	
	int datalen = data.length();
	int crclen = crc.length();
	
	for(int i=1 ; i <= (crclen - 1) ; i++)
		encoded += '0';												
	
	encoded = xorfun(encoded , crc);								
	
	cout<<"Checksum generated is: ";
	cout<<encoded.substr(encoded.length() - crclen + 1)<<endl<<endl;					
	cout<<"Message to be Transmitted over network: ";
	cout<<data + encoded.substr(encoded.length() - crclen + 1);    					
	
	
	
	
	cout<<endl<<"---------------Reciever Side-----------------"<<endl;



	cout<<"Enter the message recieved: "<<endl;
	string msg;																
	cin>>msg;
	
	msg = xorfun( msg , crc);												
	
	for( char i : msg.substr(msg.length() - crclen + 1))					
		if( i != '0' )
			{	
				cout<<"Error in communication "<<endl;						
				return 0;
			}
	
	cout<<"No Error !"<<endl;												
	return 0;
}