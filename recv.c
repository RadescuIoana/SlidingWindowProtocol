#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(int argc,char** argv){
  msg r,t;
  int i, rec, out;
  init(HOST,PORT);

  //primesc numele fisierului
  if (recv_message(&r)<0){
    perror("Receive error\n");
    return -1;
  } 
  printf("[%s] Got msg with payload: %s %d\n",argv[0],r.payload, r.len);
  //creez fisierul de output
  int f_out =  open(r.payload, O_WRONLY | O_CREAT, 0644);
  int f_size = r.len;
  //trimit confirmare
  memcpy(t.payload,"ACK file", strlen("ACK file"));
  t.len = strlen(t.payload) + 1;
  send_message(&t);

  for(i = 0; i < f_size; i++) {
    rec = recv_message(&r);
    if(rec < 0) {
      perror("Receive message\n");
      return -1;
    }
    out = write(f_out, r.payload, r.len);
    if(out < 0) {
      perror("Write error\n");
      return -1;
    }
    memcpy(t.payload,"ACK", strlen("ACK"));
    t.len = strlen(t.payload);
    send_message(&t);
  }

  printf("Receiving done\n");

  close(f_out);
  return 0;
}
