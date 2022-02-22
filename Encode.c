//Tree traversal in C - pointer implementation
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>
typedef struct node{
	int freq;
	char data;
	struct node *left,*right;
}NODE;

void *buildNode(char *table[],int size);
void *readfile_decode();
void decode(char *encodedMsg, struct node *root);
void saveEncodedMsg();
void saveHex(char filename[255] ,char *data, int size);

NODE *newNode(int freq, char data){
	NODE *n = (NODE*) malloc(sizeof(NODE)); //allocate memory for node
	n->freq = freq; // node to node
	n->data = data;
	n->left = NULL;
	n->right = NULL;
}

struct node *list[255] = {0}; //255 = 0; //CREATING FOLDER
void freq_get(int *freq,char *message){
	for(int i = 0; i < strlen(message);i++){
		freq[message[i]] += 1; 
	}
	int list_index = 0;
	for(int i = 0;i<255;i++){
		if(freq[i] != 0){ // i != 0 null value
			NODE *ip; //= (NODE *)malloc(sizeof(NODE)); // new node
			ip = newNode(freq[i], i); // occurence , character value ascii
			list[list_index] = ip; // address of node => occurence, character value asciii // access to node
			list_index += 1;
		}
	}

}

struct binCode{
	int freq;
	char code[100];
	char ascii;
}bin;

int bindex = 0;
struct binCode binArr[255] = {0};
void checkNode(struct node *n, char *code){
	char bin[100] = {0};
	char leftBin[100] = {0};
	char rightBin[100] = {0};
	strcpy(bin,code);//code 100{0} to bin 100{0}
	char left[1] = {'0'};
	char right[1] = {'1'};
	struct node *m = n; //address of root copy to *m
	if(m->left != 0){//if left may laman
		strcpy(leftBin,bin);// 0 -> 0
		strncat(leftBin,left,1);//00  //ex. hello world = 8 characters repp = 8;
		checkNode(m->left,leftBin);// check all nodes that has left until no left get the char , freq;
		//return and check right node
	}
	if(m->right != 0){
		strcpy(rightBin,bin);
		strncat(rightBin,right,1);
		checkNode(m->right,rightBin);
	}
	//if(m->left == 0 && m->right == 0){
	if(m->data != 0){
		strcpy(binArr[bindex].code,bin);//array[0] examp. 001
		binArr[bindex].ascii = m->data;// array[0] examp. C
		binArr[bindex].freq = m->freq;//  array[0] examp. 11
		bindex += 1;
		return;
	}
}

int arrSize(){
	int i = 0;
	while(1){
		if(list[i] == NULL){
			break;
		}
		i += 1;
	}
	return i;
}

int binSize(){
	int i = 0;
	while(1){
		if(binArr[i].freq == 0){
			break;
		}
		i += 1;
	}
	return i;
}

void huffMan(){
	while(arrSize()>1){
		while(1){
			int re_sort = 0;
			for(int i = 0;i<arrSize()-1;i++){
				if(list[i]->freq < list[i+1]->freq){
					NODE *temp; //addres to address
					temp = list[i];
					list[i] = list[i+1];
					list[i+1] = temp;
					re_sort = 1;
				}
			}
			if(!re_sort){
				break;
			}
		}
		/*
		printf("Sorted\n");
		for(int i = 0;i<arrSize();i++){
			printf("hex:%x char:%c freq:%d \n", list[i]->data, list[i]->data,list[i]->freq);
		}
		system("pause");
		/**/

			NODE *ip; // (NODE *)malloc(sizeof(NODE));

			int addFreq = list[arrSize()-1]->freq + list[arrSize()-2]->freq; // adding the two freq in last index
			list[arrSize()] = list[arrSize()-2]; // 13 = 11 address of 11 copy to new arraysize = 14

			ip = newNode(addFreq,'\0');
			ip->left = list[arrSize()-2]; // c
			ip->right = list[arrSize()-1];// b
			list[arrSize()-3] = ip; //  13,'0',left - c, right - b

			list[arrSize()-1] = NULL;
			list[arrSize()-1] = NULL;
	}
}
char encodedBin[20480] = {'\0'};//2048 limit
char encodeMessage(struct binCode *code,char *message){
	for(int i = 0; i< strlen(message);i++){
		if(message[i] == 0){// end of message
			break;
		}
		int j = 0;
		while(1){
			if(code[j].ascii == 0){//end of binarr
				break;
			}
			if(code[j].ascii == message[i]){
				strcat(encodedBin,code[j].code);
			}
			j++;
		}
	}
}
/**/

void *readfile(){
	FILE *filePointer;
	char *code; //4bytes
    char *ch;
    char text[255] = "sample.txt";
    printf("Input your file: ");
    scanf("%s",&text);
    system("cls");
    filePointer = fopen(text,"r");

	int i = 0;
    if (filePointer == NULL){
        printf("File is not available \n");
    }
    else{
		fseek(filePointer, 0L, SEEK_END);
		int fsize = ftell(filePointer);
		fseek(filePointer, 0, SEEK_SET);
		
		code = (char*)calloc(fsize+2,sizeof(char)); 
		fread(code, sizeof(char), fsize, filePointer);
		//system("pause");
    }
    fclose(filePointer);
    //code[i] = '\0';
	return code;
    //printf("%s  \n",code);
}


int main(){
    int choys;
    char *message;

    //char encodeText[] = "00000111010110001010001101111100101100100000111010110001010010001100001111001010";
    message = readfile(); //address of code
    
	int freq[255] = {0};
	freq_get(freq,message);

	huffMan();
	char code[100] = {'\0'};
	int index = 0;
	checkNode(list[0],code);// list[0] = root
	/**/
	while(1){
		int re_sort = 0;
		for(int i = 0; i<binSize()-1;i++){
			if(binArr[i].freq > binArr[i+1].freq){//binarray = {frq,code,character}
				struct binCode temp;
				temp = binArr[i];
				binArr[i] = binArr[i+1];
				binArr[i+1] = temp;
				re_sort = 1;
			}
		}
		if(!re_sort){
			break;
		}
	}
	/*
	printf("DATA	");
	printf("FREQ	");
	printf("CODE\n");
	for(int i = 0; i<binSize();i++){
		printf("%c	",binArr[i].ascii);
		printf("%i	",binArr[i].freq);
		printf("%s\n",binArr[i].code);
	}
	*/
	encodeMessage(binArr,message);
	saveEncodedMsg();
	printf("\nInput size: ");
	printf("%i Byte \n",strlen(message));

	int output = strlen(encodedBin)/8;//examp. 00001110 011011 (00001110 = 8 bit == 1 byte) 'C' = 1 byte
	if(strlen(encodedBin)%8){
		output++;
	}
	
	printf("Output size: ");
	printf("%i Byte \n\n",output);
	/*
    printf("Text Message: ");
    printf("%s\n",message);
	
	printf("Encoded Message Size: ");
	printf("%d\n\n\n",strlen(encodedBin));
	
	
	//char fnEnBin[255] = "encode.bin";
	saveHex("encode.bin",encodedBin,strlen(encodedBin));
	
    printf("Encoded Message: ");
	printf("%s\n\n\n",encodedBin);
	/**/
	//printf("%s \n\n\n\n\n",encodedBin);
	printf("Data Extracted to hotmans.bin\n\n\n");
	/*
	index = strlen(encodedBin);

	for(int i = 0; i<binSize();i++){
		encodedBin[strlen(encodedBin)] = 0x0A;
		strcat(encodedBin,binArr[i].code);
		encodedBin[strlen(encodedBin)] = binArr[i].ascii;
	}
	/*
	decode(encodedBin,list[0]);
	
	/**/
	system("pause");
	return 0;
}


void decode(char *encodedMsg, struct node *root){
	//char encodeText[] = "1100101011011100111110100011101000001101101010";
	NODE *curNode;
	curNode = root;
	int msg_i = 0;

	while(1){

		if(curNode->data != 0){
			printf("%c",curNode->data);
			curNode = root;
		}
		if(encodedMsg[msg_i] == '0'){
			curNode = curNode->left;
		}else if(encodedMsg[msg_i] == '1'){
			curNode = curNode->right;
		}
		if(encodedMsg[msg_i] == 0){
			break;
		}
		msg_i++;
	}
	printf("\n\n");
}

void *buildNode(char *table[],int size){
	char *data;

	NODE *root,*child;
	root = newNode(0,'\0');
	child = root;
	int c = 0;

	for(int c = 1; c < size; c++){
		data = table[c];
		for(int i = 0; i<strlen(data)-1;i++){
			if(data[i] == '0'){
				if(child->left == NULL){
					child->left = newNode(0,'\0');
				}
				child = child->left;
			}else if(data[i] == '1'){
				if(child->right == NULL){
					child->right = newNode(0,'\0');
				}
				child = child->right;
			}

			if((i+1) == strlen(data)-1){
				child->freq = 1;
				child->data = data[i+1];
			}
		}
		child = root;
	}
	/**/
	return root;
}

int binTdec(char binary[]){
	int result = 0;
	int multiplier = 1;
	int temp;
	for(int i = strlen(binary)-1; i >= 0; i--){
		temp = 0;
		if(binary[i] == '1'){
			temp = multiplier;
		}
		result += temp;
		multiplier *= 2;
	}
	return result;
}

char decTbin(char *bin, int decimal){
	char indx = 0;
	int temp = decimal;
	for(int i = 128; i >= 1; i/=2){
		if(temp >= i){
			temp = temp - i;
			bin[indx] = '1';
		}else{
			bin[indx] = '0';
		}
		indx++;
	}
}


void saveHex(char filename[255] ,char *data, int size){
	FILE *fptr;
	fptr = fopen(filename,"wb");
	if(fptr == NULL){
		printf("Error!");
		system("pause");	  
		exit(1);             
	}
	for(int i = 0; i < size; i++){
		putc((unsigned int)data[i], fptr);
	}
	/**/
	fclose(fptr);
}

void saveEncodedMsg(){
	char *cryptData;
	long int buffer_size = 1024*1024*1024;
	cryptData = malloc(buffer_size);
	memset(cryptData,0,buffer_size);
	/*
	char cryptData[20480];
	printf("\ncryptData Address\n%x\n\n",&cryptData);
	memset(cryptData,0,20480);
	*/
	int j = 0;
	int size = 0;
	
	for(int i = 0; i<binSize();i++){
		int memIndx = j + i;
		int codlen = strlen(binArr[i].code);
		cryptData[memIndx] = binArr[i].ascii;
		cryptData[memIndx+1] = codlen;
		if(8 > codlen){
			cryptData[memIndx+2] = 0x00;
			cryptData[memIndx+3] = binTdec(binArr[i].code);
		}else{
			char codeBuff[18] = {0};
			memcpy(codeBuff,binArr[i].code,codlen); 
			//printf("low:%s",codeBuff+(codlen-8));
			cryptData[memIndx+3] = binTdec(codeBuff+(codlen-8));
			codeBuff[codlen-8] = 0x00;
			cryptData[memIndx+2] = binTdec(codeBuff);
			//printf(" high:%s",codeBuff);
			//printf("Code Length: %d ascii: %c codebuff: %x %x", strlen(binArr[i].code),binArr[i].ascii,(unsigned char)cryptData[memIndx+2],(unsigned char)cryptData[memIndx+3]);
			//system("pause");
			
		}
		size += 4;
		j += 3;
	}
	int ebLen = strlen(encodedBin);//Getting binCode length
	char* ebP = (char*)&ebLen;//Accessing tru char pointer
	cryptData[size++] = 0xAB;
	cryptData[size++] = 0xCD;
	cryptData[size++] = (unsigned char)ebP[0];//Length of binCode
	cryptData[size++] = (unsigned char)ebP[1];//Length of binCode
	//cryptData[size++] = 0xEF;//Length of binCode
	//cryptData[size++] = 0xFF;//Length of binCode
	
	char buffer[9] = {0};
	int buffNdx = 0;
	for(int i = 1; i <= strlen(encodedBin); i++){
		//printf("%c",encodedBin[i-1]);
		buffer[buffNdx] = encodedBin[i-1];
		buffNdx++;
		if((i%8 == 0 && i != 0) || (i >= strlen(encodedBin))){
			//printf(" %s %i\n",buffer,binTdec(buffer));
			cryptData[size++] = binTdec(buffer);
			memset(buffer,0,sizeof(buffer));
			buffNdx = 0;
		}
		/**/
	}
	saveHex("hotmans.bin",cryptData,size);
}

