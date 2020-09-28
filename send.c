#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

int main(int argc,char** argv){
	init(HOST,PORT);
	msg t, r;
	int in, rec, count = 0, i = 0;
	int speed = atoi(argv[2]);
	int delay = atoi(argv[3]);
	FILE *f = fopen(argv[1], "rt");

	//calculez dimensiunea ferestrei
	int window_dim = (1000 * speed * delay ) / (sizeof(msg) * 8);
	//printf("%d\n", window_dim);
	int f_input = open(argv[1], O_RDONLY);
	char buffer[MSGSIZE];

	//calculez dimensiunea fisierului
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fclose(f);
	//nr total cadre
	int f_size = size / MSGSIZE;
	if(size % MSGSIZE != 0) {
		f_size += 1;
	}

	//se transmit numele fisierului care va fi creat si nr de cadre
	memcpy(t.payload, "recv_fileX", strlen("recv_fileX"));
	//printf("%s\n", t.payload);
	t.len = f_size;
	//printf("%d\n", f_size);
	send_message(&t);
	rec = recv_message(&r);
		if (rec < 0){
			perror("Receive error.\n");
			return -1;
		}
	printf("Sender: %s\n", r.payload);

	//int size = f_size * 8;
	lseek(f_input, 0, SEEK_SET);

	if(window_dim >= f_size){
		printf("mai mic\n");
		while(count < window_dim) {
		in = read(f_input, buffer, MSGSIZE);
		memcpy(t.payload, buffer, in);
		if(in < 0){
			printf("Reading FAILED\n");
			perror("read error");
		}else {
			t.len = in;
			send_message(&t);
		}
		count++;
		}

		for(i = 0; i < f_size; i++) {
		rec = recv_message(&r);
		if (rec < 0){
			perror("Receive error.\n");
			return -1;
		}
		}
		
	} else {

	//transmit numarul de cadre cuprinse de fereastra
	while(count < window_dim) {
		in = read(f_input, buffer, MSGSIZE);
		memcpy(t.payload, buffer, in);
		if(in < 0){
			printf("Reading FAILED\n");
			perror("read error");
		}else {
			t.len = in;
			send_message(&t);
		}
		count++;
	}
	printf("count %d\n", count);
	f_size -= count;
	printf("f_size %d\n", f_size);

	for(i = 0; i < f_size; i++) {
		rec = recv_message(&r);
		if(rec < 0) {
			perror("Receive error.\n");
			return -1;
		}else {
			printf("%d Received %s\n", i, r.payload);
			in = read(f_input, buffer, MSGSIZE);
			memcpy(t.payload, buffer, in);
			if(in < 0){
				printf("Reading FAILED\n");
				perror("read error");
			}else {
				t.len = in;
				send_message(&t);
			}
		}
	}

	for(i = 0; i < window_dim; i++) {
		rec = recv_message(&r);
		if (rec < 0){
			perror("Receive error.\n");
			return -1;
		}
		printf("ceva\n");
	}
}
	printf("Sending done\n");


	/*sprintf(t.payload,"Hello World of PC");
	t.len = strlen(t.payload)+1;
	send_message(&t);

	if (recv_message(&t)<0){
		perror("receive error");
	}
	else {
		printf("[%s] Got reply with payload: %s\n",argv[0],t.payload);
	}*/
	close(f_input);
	return 0;
}
