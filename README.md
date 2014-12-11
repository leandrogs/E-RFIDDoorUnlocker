E-RFIDDoorUnlocker
==================

December, 2014 - Leandro Gomes da Silva, Pablo Antunes Silva, Lucas Cedro de Lima

A simple solution to unlock the door using RFID tags and "authentication" over Internet. Hardware in use is a Galileo board which is compatible with Arduino uno.

This project is based on Omer Siar Baysal RFID project https://github.com/omersiar/RFID522-Door-Unlock and also on Victor Hugo Montes Aldir Santos project using aJSON parser https://bitbucket.org/victoraldir/ajson-aviseja

* **Hardware**

We are using a Intel Galileo board. It already have Ethernet connection so we decided to communicate with the server through it. This project also uses a RFID-RC522 shield (Compatible with MIFARI tags) and a RGB LED to give some output for users.

* **Web Interface**

This project allows an Administrator of the system to associate one UID for each user. As mentioned on Omer Siar Baysal project, it is still possible to create a master tag, but only if there is no UID on DB and a ADMIN user is lready defined.
Web Interface was built using CakePHP and MYSql database.

* **Security**

We still lack security. All we do is allow user to open the door only if his tag UID is already associated to one user on database. 
It is also a problem whe the server returns a response. The response is always 0 or 1 in a JSON format without any encryption.

* **Credits**

Main code based on:
RFID522 Door Unlock - Omer Siar Baysal https://github.com/omersiar/RFID522-Door-Unlock
aJSON AviseJá - Victor Hugo Montes Aldir Santos https://bitbucket.org/victoraldir/ajson-aviseja

aJSON Library
https://github.com/interactive-matter/aJson

MFRC522 Library
https://github.com/miguelbalboa/rfid
Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
Created by Miguel Balboa (circuitito.com), Jan, 2012.
Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 
(Translation to English, refactored, comments, anti collision, cascade levels.)

A BIG thanks to iMobilis (laboratory of mobile computing) at UFOP/ICEA for lending us the Galileo and the RFID shield.
iMobilis http://www.decom.ufop.br/imobilis/
UFOP http://www.ufop.br/
UFOP/ICEA http://www.icea.ufop.br/

* **License**

Feel FREE to use this code as you want to. Just remember to give the correct credits.
