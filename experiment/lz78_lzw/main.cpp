#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <errno.h>
#include "Tree_node.h"
#include "Tree_node.cpp"
#include "util.c"

using namespace std;

int main(int argc, char *argv[]) {

	bool ascii = false;
	bool enc = false;
	bool dec = false;
	int bits = 25;

	for(int i = 1; i < argc; i++ ) {
		if(argv[i][0] == '-'){
			if(argv[i][1] == 'a') {
				ascii = true;
			} else if (argv[i][1] == 'e') {
				enc = true;
			} else if (argv[i][1] == 'd') {
				dec = true;
			} else if (argv[i][1] == 'b') {
				i += 1;
				bits = (int) atol(argv[i]);
			} else if (argv[i][1] == 'h') {
				usage();
				exit(1);
			}
		}


	}

	if(enc) {
		encrypt(ascii, (1 << bits));
	} else if( dec ) {
		if(ascii) decrypt_ascii();
		else decrypt((1 << bits));
	} else {
		usage();
	}
	return 0;
}

//encrypt
void encrypt(bool ascii_compress, int max_label){
	int count = 1;
	Tree_node *head = new Tree_node(NULL, 0, (Tree_node *)NULL);
	Tree_node *cur = head;
	while(cin.peek() != EOF){
		char c;
		cin.get(c);
		Trre_node *loc = cur->find_child(c);
		if(loc == NULL){
			if(ascii_compress){
				cout << cur->label << " ";
				cout.put(c);
			}else {
				print_label(cur->label,max_label);
				print_letter(c);
			}
			cur->insert_child(c,count);
			count++;
			if(count >= max_label){
				cerr << "ERROR: Number of label exceeded maximum number set.\n\n";
				return;
			}
			cur = head;
		}else {
			cur = loc;
		}
	}
	if(!ascii_compress){
		print_final_label(cur->label, max_label);
	}else {
		cout << cur->label << "";
	}
}


//decrypt_ascii
void decypt_ascii(){

