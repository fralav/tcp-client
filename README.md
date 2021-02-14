# tcp-client
A little example of how to use socket API with TCP protocol.

1) Il client richiede la connessione al server.
2) Stabilita la connessione, il server invia al client la stringa "Connessione avvenuta".
3) Il client stampa la stringa ricevuta: dopodiché, legge due stringhe di caratteri dallo standard input e le invia al server.
4) Il server legge le stringhe inviate dal client:
    - le visualizza sullo standard output
    - converte la prima stringa ricevuta tutta in MAIUSCOLO, la seconda tutta in minuscolo
    - invia le nuove stringhe al client
    - rimane in ascolto
5) Il client legge la risposta inviata dal server.
    - visualizza la risposta sullo standard output
    - chiude la connessione corrente
    - termina il processo
