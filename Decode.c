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

NODE *newNode(int freq, char data){
	NODE *n = (NODE*) malloc(sizeof(NODE)); //allocate memory for node
	n->freq = freq; // node to node
	n->data = data;
	n->left = NULL;
	n->right = NULL;
}

struct node *list[255] = {0}; //255 = 0; //CREATING FOLDER



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



int decode(char *buffer, char *encodedMsg, struct node *root){
	//char encodeText[] = "1100101011011100111110100011101000001101101010";
	NODE *curNode;
	curNode = root;
	int msg_i = 0;
	int buff_i = 0;
	while(1){

		if(curNode->data != 0){
			buffer[buff_i++] = curNode->data;
			//printf("%c",curNode->data);
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
	return buff_i;
	//printf("\n\n");
}

void *buildNode(char *table[],int size){
	//char a[] = "1001A";
	//char b[] = "1011B";
	//char *tempCode[] = {a,b};
	char *data;
	
	NODE *root,*child;
	root = newNode(0,'\0');
	child = root;
	int c = 0;
	
	//for(int c = 0; c < size; c++){
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

void *readfile(){
	FILE *filePointer;
	char *code; //4bytes
    char ch;
    char *text;
    filePointer = fopen("decoded.log", "r");
	code = malloc(1000); 
	memset(code, 0, 1000); 
	int i = 0;
	//int size = 0;
    if (filePointer == NULL){
        printf("File is not available \n");
    }
    else{
        while ((ch = fgetc(filePointer)) != EOF){
			if(ch == 0x0a){
				code[i++] = ';';
			}else{
				code[i++] = ch;
			}
			
			//printf("%x ",ch);
        }
    }
    fclose(filePointer);
	code[i++] = ';';
    code[i] = '\0';
	return code;
    //printf("%s  \n",code);
}

int binTdec(char binary[]){
	//char binary[] = "11111111";
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
	//char bin[9] = "00000000";
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

void *loadFile(char filen[255], int *size){
	FILE *filep;
	char *buffer;
	char ch;
	int filepos = 0;
	
    filep = fopen(filen, "rb");
    if (filep == NULL){
        //printf("File is not available \n");
		*size = 0;
		//return buffer;
    }else{
        fseek(filep, 0L, SEEK_END);
		int fsize = ftell(filep);
		fseek(filep, 0, SEEK_SET);
		
		buffer = (char*)calloc(fsize+2,sizeof(char)); 
		fread(buffer, sizeof(char), fsize, filep);
		
		fclose(filep);
		*size = fsize;
		return buffer;
    }
}


int loadDecodedMsg(char *codeTable[]){
	char *cod;
	char *buffer;
	int size = 0;
	char codeReset[9] = {0};
	char codeBuff[18] = {0};
	cod = loadFile("hotmans.bin",&size);
	
	
	if(size == 0){
		printf("Data not Available \n");
	}else{
		int Indx = 1;
		for(int i = 0; i<size;i+=4){
			//system("pause");
			if((unsigned char)(cod[i]) == 0xAB && (unsigned char)(cod[i+1]) == 0xCD){
				//system("pause");
				char csize[4] = {0};
				csize[0] = cod[i+2];
				csize[1] = cod[i+3];
				int encSize; //Hold binCode length to be strip
				memcpy(&encSize, csize, sizeof(encSize));
				buffer = (char*)calloc((size - i)*8,sizeof(char)); 
				for(int bt = i+4; bt < size; bt++){
					char high[8] = {0};
					decTbin(high,(unsigned char)(cod[bt]));
					strncat(buffer,high,8);
				}
				buffer[encSize] = 0x00;
				
				codeTable[0] = buffer;
				return Indx;
				break;
			}
			char high[8] = {0};
			char low[8] = {0};
			
			decTbin(high,(unsigned char)cod[i+2]);
			decTbin(low,(unsigned char)cod[i+3]);
			
			memcpy(codeBuff,high,8);
			memcpy(codeBuff+8,low,8);
			
			codeBuff[16] = cod[i];
			
			
			buffer = (char*)calloc(cod[i+1]+2,sizeof(char)); 
			memcpy(buffer,codeBuff+(16-cod[i+1]),cod[i+1]+1);
			//printf("char:%c size:%d high:%x low:%x bin:%s finalbin:%s	",cod[i],cod[i+1],(unsigned char)cod[i+2],(unsigned char)cod[i+3],codeBuff,buffer);
			//system("pause");
			codeTable[Indx] = buffer;
			Indx++;	
		}
		/**/
	}
}

int main(){
	char *tempCode[255];
	int rowSize = loadDecodedMsg(tempCode);
	NODE *root = buildNode(tempCode,rowSize);
	char code[100] = {'\0'};
	int index = 0;
	checkNode(root,code);// list[0] = root
	/*
	for(int i = 0; i<binSize();i++){
		printf("%c	",binArr[i].ascii);
		printf("%s\n",binArr[i].code);
	}
	*/
	
	char *decoded_buffer;
	long int buffer_size = 1024*1024*1024;
	decoded_buffer	= malloc(buffer_size);
	memset(decoded_buffer,0,buffer_size);
	int decoded_size = decode(decoded_buffer,tempCode[0],root);
	printf("\nActual Size: %d Byte\n\n",strlen(decoded_buffer));
	//printf("Message: %s",decoded_buffer);
	saveHex("decoded.bin",decoded_buffer,decoded_size);
	printf("Data Extracted to decoded.bin\n\n\n");
	/**/
	system("pause");
	return 0;
}
