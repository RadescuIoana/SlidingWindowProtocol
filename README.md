Radescu Ioana

# Protocol cu fereastra glisanta
  Proiectul contine implementarea unui protocol cu fereastra glisanta folosit pentru a transmite un fisier. 
  Fisierul va fi citit de catre transmitator(send.c) si trimis catre receptor(recv.c). Protocolul implementat
  utilizeaza eficient legatura de date. 
  
# Send
  
  In fisierul sursa send.c se implemeteaza trimiterea unui fisier prin protocol cu fereastra glisanta. 
  Initial, se calculeaza dimensiunea ferestrei cu ajutorul parametrilor trimisi la rulare. Se calculeaza 
  dimensiunea si numarul de cadre ale fisierului. Aceasta dimensiune se transmite mai apoi catre receptor, 
  alaturi de numele fisierului in care acesta va salva datele. Se citesc si se trimit atatea cadre cate incap 
  in fereastra, fara a se astepta raspuns. Pentru cadrele ramase, se creeaza o bucla in care se asteapta raspuns, 
  iar in cazul in are acesta este primit, se citeste urmatorul cadru din fisierul sursa si se transmite catre 
  destinatie. Dupa trimiterea tuturor cadrelor, se mai asteapta raspunsurile pentru un numar de cadre egal cu cel 
  al ferestrei. 

# Receive

  Initial, se primesc detaliile referitoare la numele fisierului destinatie si numarul de cadre care vor fi primite.
  Se creeaza fisierul. Mai apoi, pentru fiecare cadru, se primesc informatiile trimise de send.c si se scriu in fisierul 
  creat anterior, dupa care se trimite confirmarea. 
