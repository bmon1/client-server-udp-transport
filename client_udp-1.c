/* client_udp.c is on zeus.cs.txstate.edu
   open a window on zeus.
   compile:
   $gcc -o c client_udp.c
   $./c eros.cs.txstate.edu 
*/

#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

main(int argc, char **argv)
{
  int s, server_address_size;
  unsigned short port;
  struct sockaddr_in server;
  char buf[32];
  struct hostent *hostnm;


  int num, id, score; 
  char fName[10];
  char lName[10];
  char msg[30];
  char eof[] = "End of File";


  if ((s = socket(AF_INET, SOCK_DGRAM, 0))<0)
   {printf("socket creation error");
   }

  server.sin_family = AF_INET; // Internet domain
  server.sin_port = htons(8000); // port
  hostnm = gethostbyname(argv[1]);  //get server's name
  server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr); 

  server_address_size = sizeof(server);

// communication starts from here

  while (1) {
	  printf("1: Add Student\n"); //
	  printf("2: Display Student Information\n");
	  printf("3: Display All Students Above A Score\n");
	  printf("4: Display All Students Information\n"); //////////
	  printf("5: Delete Student\n");
	  printf("6: Exit\n");//

	  printf("Enter integer of your choice: ");
	  scanf("%d", &num);

	  // send an integer to the server
	  sendto(s, &num, sizeof(num), 0, (struct sockaddr*)&server, server_address_size);

	  // receive a message from the server
	  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);

	  switch (num) {
	  case 1:

		  // get id from user
		  printf("Enter the ID of the student to be added: ");
		  scanf("%d", &id);

		  // send id to the server
		  sendto(s, &id, sizeof(id), 0, (struct sockaddr*)&server, server_address_size);

		  // receive a message from the server
		  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);

		  // get first name from user
		  printf("Enter the first name of the student to be added: ");
		  scanf("%19s", &fName);

		  // send an fName to the server
		  sendto(s, &fName, sizeof(fName), 0, (struct sockaddr*)&server, server_address_size);

		  // receive a message from the server
		  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);

		  // get last name from user
		  printf("Enter the last name of the student to be added: ");
		  scanf("%19s", &lName);

		  // send an lName to the server
		  sendto(s, &lName, sizeof(lName), 0, (struct sockaddr*)&server, server_address_size);

		  // receive a message from the server
		  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);

		  // get score from user
		  printf("Enter the score of the student to be added: ");
		  scanf("%d", &score);


		  // send score to the server
		  sendto(s, &score, sizeof(score), 0, (struct sockaddr*)&server, server_address_size);

		  // receive a message from the server
		  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);

		  break;

	  case 2:
		  // get id from user
		  printf("Enter the ID of the student to be added: ");
		  scanf("%d", &id);

		  // send id to the server
		  sendto(s, &id, sizeof(id), 0, (struct sockaddr*)&server, server_address_size);

		  // receive a message from the server
		  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);
		  printf("Receiving - %s - from server\n", msg);

		  break;

	  case 3:
		  // get score from user
		  printf("Enter the minimum score you want to see: ");
		  scanf("%d", &score);

		  // send score to the server
		  sendto(s, &score, sizeof(score), 0, (struct sockaddr*)&server, server_address_size);

		  // receive a student's info from the server
		  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);
		  printf("Receiving - %s - from server\n", msg);


		  while (strcmp(msg, eof)) {

			  // send received to server
			  strcpy(msg, "Received");
			  sendto(s, &msg, sizeof(msg), 0, (struct sockaddr*)&server, server_address_size);

			  // receive a student's info from the server
			  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);
			  printf("Receiving - %s - from server\n", msg);

		  }


		  break;
	  case 4:
		  // send ready to the server
		  strcpy(msg, "Ready");
		  sendto(s, &msg, sizeof(msg), 0, (struct sockaddr*)&server, server_address_size);

		  // receive a student's info from the server
		  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);
		  printf("Receiving - %s - from server\n", msg);

		  while (strcmp(msg, eof)) {

			  // send received to server
			  strcpy(msg, "Received");
			  sendto(s, &msg, sizeof(msg), 0, (struct sockaddr*)&server, server_address_size);

			  // receive a student's info from the server
			  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);
			  printf("Receiving - %s - from server\n", msg);

		  }
		  

		  break;
	  case 5:
		  // get id from user
		  printf("Enter the ID of the student to be deleted: ");
		  scanf("%d", &id);

		  // send id to the server
		  sendto(s, &id, sizeof(id), 0, (struct sockaddr*)&server, server_address_size);

		  // receive a message from the server
		  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_address_size);
		  printf("Receiving - %s - from server\n", msg);



		  break;
	  case 6:
		  exit(0);
		  break;
	  }
  }


  /*server_address_size = sizeof(server);

   // send an integer to the server
  printf("enter an integer: ");
  scanf("%d", &num);
  sendto(s, &num, sizeof(num), 0, (struct sockaddr *)&server, server_address_size);

   // receive a message from the server
  recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr *)&server, &server_address_size);
  printf("%s\n", msg);
  */

  close(s);
}
