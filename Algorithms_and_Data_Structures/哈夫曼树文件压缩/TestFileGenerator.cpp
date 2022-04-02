#include <bits/stdc++.h>

using namespace std;

int main(){
	srand((unsigned)time(NULL));
	freopen("testfile.txt","w",stdout);
	
	int len = rand() + 1;
	for(int i = 0 ; i < len ; i++){
		int ch = rand()%256;
		printf("%c", ch);
	}
	puts("");
	return 0;
} 
