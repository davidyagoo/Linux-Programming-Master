void init_sockaddr(struct sockaddr_in *name, const char *hostname, 
                     const char *serv)
{
   struct hostent *hp;
   char *host, myname[255];
   if (hostname == NULL){
      gethostname(myname, sizeof(myname));
      host = myname;
   }
   else
      host = hostname;
   /* ���o�D�q����}�T�� */
   if ((hp = gethostbyname(host)) == NULL){
      printf("Unknown host: %s\n", host);
      exit(-1);
   }
   /* ��J���A����IP��}�M�q�T�� */
   bzero(name,sizeof(struct sockaddr));
   if (hp->h_addrtype == AF_INET){   
      name->sin_family = AF_INET;
      bcopy(hp->h_addr_list[0], &name->sin_addr, hp->h_length);
      if (serv == NULL)
         name->sin_port = htons(0); /* �Ѩt�ο���@�ӾA���q�T�� */
      else
         name->sin_port = htons(atoi(serv));
   } else {
      printf("Unknown address type\n");
      exit(-1);
   }
}
