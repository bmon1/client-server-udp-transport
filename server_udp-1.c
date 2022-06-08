/* server_udp.c is on eros.cs.txstate.edu
   open a window on eros.
   compile and run the server program first:
   $gcc -o s server_udp.c
   $./s
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>


int write_to_file(int id, char* fName, char* lName, int score) {
    FILE* file;
    char student_info[7];
    file = fopen("database.txt", "a+");
    snprintf(student_info, 10, "%d", id);
    fprintf(file, student_info);
    fprintf(file, " ");
    fprintf(file, fName);
    fprintf(file, " ");
    fprintf(file, lName);
    fprintf(file, " ");
    snprintf(student_info, 10, "%d", score);
    fprintf(file, student_info);
    fprintf(file, "\n");

    fclose(file);
    return 0;
}


main(int argc, char **argv)
{
  int s, num, score, id, check, namelen, client_address_size;
  struct sockaddr_in server, client;
  FILE* file;
  FILE* file2;
  char msg[30];
  char fName[10];
  char lName[10];
  char name[10];
  char student[40];

  /* Create a datagram socket in the internet domain and 
   use the UDP protocol. */
   s = socket(AF_INET, SOCK_DGRAM, 0);
   server.sin_family = AF_INET; /* Server is in Internet Domain */
   server.sin_port = htons(8000); /* port */
   server.sin_addr.s_addr = INADDR_ANY; /* Server's Internet Address */

   bind(s, (struct sockaddr *)&server, sizeof(server));

   // communication starts from here
   client_address_size = sizeof(client);

   while (1) {

       // receive an integer from the client
       recvfrom(s, &num, sizeof(num), 0, (struct sockaddr*)&client, &client_address_size);

       if (num == 0) {
           exit(0);
       }

       // send a reply message to the client
       strcpy(msg, "integer received");
       sendto(s, msg, sizeof(msg), 0, (struct sockaddr*)&client, sizeof(client));



       switch (num) {
       case 1:
           // receive an ID from the client
           recvfrom(s, &id, sizeof(id), 0, (struct sockaddr*)&client, &client_address_size);
           printf("ID received: %d\n", id);

           // send a reply message to the client
           strcpy(msg, "id received");
           sendto(s, msg, sizeof(msg), 0, (struct sockaddr*)&client, sizeof(client));
           printf("sending \"ID received\" to client. ID: %d\n", id);

           // receive a fName from the client
           recvfrom(s, &name, sizeof(name), 0, (struct sockaddr*)&client, &client_address_size);
           strcpy(fName, name);
           printf("fName received: %s\n", fName);
           printf("fName length: %d\n", strlen(fName));
           /////////////////printf("fName received: %d\n", ntohl(fName));

           // send a reply message to the client
           strcpy(msg, "fName received");
           sendto(s, msg, sizeof(msg), 0, (struct sockaddr*)&client, sizeof(client));
           printf("sending \"fName received\" to client. fName: %s\n", fName);
           ///////////////////scanf("%29s", msg);

           // receive a lName from the client
           recvfrom(s, &name, sizeof(name), 0, (struct sockaddr*)&client, &client_address_size);
           strcpy(lName, name);
           printf("lName received: %s\n", lName);
           printf("lName length: %d\n", strlen(lName));
           printf("lName length: %d\n", strlen(lName));

           // send a reply message to the client
           strcpy(msg, "lName received");
           sendto(s, msg, sizeof(msg), 0, (struct sockaddr*)&client, sizeof(client));
           printf("sending \"lName received\" to client. lName: %s\n", lName);

           // receive a score from the client
           recvfrom(s, &score, sizeof(score), 0, (struct sockaddr*)&client, &client_address_size);
           printf("Score received: %d\n", score);

           // send a reply message to the client
           strcpy(msg, "score received");
           sendto(s, msg, sizeof(msg), 0, (struct sockaddr*)&client, sizeof(client));
           printf("sending \"score received\" to client. ID: %d\n", score);


           //write student info to file
           write_to_file(id, fName, lName, score);

           break;
       case 2:
           
           file = fopen("database.txt", "r");

           // receive an ID from the client
           recvfrom(s, &id, sizeof(id), 0, (struct sockaddr*)&client, &client_address_size);
           printf("ID received: %d\n", id);

           // find id in database and send to client
           check = 1;
           while (student[0] - '0' != id && check != 0) {
               check = fgets(student, sizeof(student), file);
               if (check == 0) {
                   // send "student id not found" to the client
                   strcpy(msg, "Student ID not found");
                   sendto(s, msg, sizeof(msg), 0, (struct sockaddr*)&client, sizeof(client));
                   printf("Sending student id not found to client \n");
               }
               if (student[0] - '0' == id) {
                   // send student info to the client
                   sendto(s, student, sizeof(student), 0, (struct sockaddr*)&client, sizeof(client));
                   printf("Sending student found info to client \n");
               }
           }

           fclose(file);
           break;

       case 3:

           file = fopen("database.txt", "r");

           // receive a score from the client
           recvfrom(s, &score, sizeof(score), 0, (struct sockaddr*)&client, &client_address_size);
           printf("Score received: %d\n", score);

           check = fgets(student, sizeof(student), file);


           while (check != 0) {


               if (/*student grade > score*/ 1 ) {
                   
                   // send student info to client
                   sendto(s, student, sizeof(student), 0, (struct sockaddr*)&client, sizeof(client));
                   printf("Sending - %s - to client\n", student);

                   // receive ok from the client
                   recvfrom(s, &msg, sizeof(msg), 0, (struct sockaddr*)&client, &client_address_size);
                   printf("Received - %s - from client\n", msg);
               }

               //check for end of database
               check = fgets(student, sizeof(student), file);
               
           }

           break;
       case 4:
           file = fopen("database.txt", "a+");

           // reveive ready message from client
           recvfrom(s, &msg, sizeof(msg), 0, (struct sockaddr*)&client, &client_address_size);
           printf("Received - %s - from client\n", msg);

           check = 1;
           check = fgets(student, sizeof(student), file);
           while (check != 0) {
               // send student info to client
               sendto(s, student, sizeof(student), 0, (struct sockaddr*)&client, sizeof(client));
               printf("Sending - %s - to client\n", student);

               // receive ok from the client
               recvfrom(s, &msg, sizeof(msg), 0, (struct sockaddr*)&client, &client_address_size);
               printf("Received - %s - from client\n", msg);

               //check for end of database
               check = fgets(student, sizeof(student), file);

           }
           // send end of file to client
           strcpy(msg, "End of File");
           sendto(s, msg, sizeof(msg), 0, (struct sockaddr*)&client, sizeof(client));
           printf("Sending - %s - to client\n", msg);

           fclose(file);

           break;
       case 5:
           // open previous database file and new file to fill
           file = fopen("database.txt", "a+");
           file2 = fopen("database1.txt", "w");

           // receive an ID from the client
           recvfrom(s, &id, sizeof(id), 0, (struct sockaddr*)&client, &client_address_size);
           printf("ID received: %d\n", id);

           // find the student to be deleted
           check = fgets(student, sizeof(student), file);

           int id_present = 0;
           while (check != 0) {
               // write each line to file 2 except the file to delete
               if (student[0] - '0' == id) {

                   // send "student id not found" to the client
                   strcpy(msg, "Student deleted");
                   sendto(s, msg, sizeof(msg), 0, (struct sockaddr*)&client, sizeof(client));
                   printf("Sending - %s - to client \n", msg);
                   id_present = 1;
               }
               else {
                   fprintf(file2, "%s\n", student);
               }

               check = fgets(student, 50, file);
           }

           if (id_present == 0) {
               // send "student id not found" to the client
               strcpy(msg, "Student ID not found");
               sendto(s, msg, sizeof(msg), 0, (struct sockaddr*)&client, sizeof(client));
               printf("Sending - %s - to client \n", msg);
           }

           // delete old database file
           if (remove("database.txt") == 0)
               printf("Deleted successfully \n");
           else
               printf("Unable to delete the file \n");

           // rename new database file to old name
           int result = rename("database1.txt", "database.txt");
           if (result == 0) {
               printf("The file is renamed successfully. \n");
           }
           else {
               printf("The file could not be renamed. \n");
           }

           fclose(file);
           fclose(file2);


           break;
       case 6:
           exit(0);
           break;
       }
   }

  close(s);
}

