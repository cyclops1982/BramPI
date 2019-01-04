#include <iostream>
#include <thread>
using namespace std;


#define THREADCOUNT 100


void DoStuff(int nr) {
	for (int i=0;i<3;++i) {
		cout<<"["<<nr<<"] We are doing stuff:"<<i<<endl;
	}
}

int main(int argc, char **argv) 
{

	std::thread t[THREADCOUNT];

	cout<<"Starting threads..."<<endl;
	for (int i=0;i<THREADCOUNT; ++i) {
		t[i] = std::thread(DoStuff, i);
		cout<<"started "<<i<<endl;
	}


	for (int i=0;i<THREADCOUNT; ++i) {
		cout<<"Waiting for "<<i<<endl;
		t[i].join();
	}
	

	cout<<"done"<<endl;

	return 0;
}