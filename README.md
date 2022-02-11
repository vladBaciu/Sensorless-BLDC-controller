# Sensorless-BLDC-code
Bachelor thesis code


# Controller BLDC fără senzori utilizând BEMF și detecția trecerii prin zero (ZCP)


Lucrarea de față își propune controlul unui motor BLDC (brushless DC motor) având ca feedback tensiunea electromotoare inversa (BEMF) a bobinei nealimentate. Pentru atingerea scopului au fost simulate, testate și implementate anumite topologii hardware. Partea software a fost dezvoltată pe o ahitectură ARM Cortex M4, iar codul respectă specificațiile standardului AUTOSAR (AUTomotive Open System ARchitecture) folosit în industria automotive.


# 1. Introducere

Această lucrare are ca scop conceperea unui sistem embedded pentru controlul nesenzorizat al unui motor BLDC utilizând metoda BEMF (back-electromotive force). Deoarece în industrie controlul nesenzorizat este folosit doar în aplicațiile unde sarcina motorului este fixă, prin această lucrare se testează comportamentul unui motor de 36V, 300W la diverse sarcini și funcționarea la viteze mici.


În general, pentru controlul motoarelor BLDC se folosește comutarea în șase pași. Fiecare fază conduce pentru 120°, iar la un moment dat doar două faze sunt acționate. Acest lucru face posibilă detecția BEMF (back electromotive force) pe cea de a treia fază neacționată, însă pentru detecția punctului de trecere prin zero este necesar accesul la nodul virtual al motorului, nod ce constituie referința semnalului BEMF. Deoarece nodul virtual nu este accesibil acesta se realizează cu ajutorul unei unei rețele de rezistențe. În Fig.1. este prezentat modul de construcție al nodului virtual și detecția punctului de trecere prin zero a BEMF


![image](https://user-images.githubusercontent.com/24388880/153602152-070da2fc-dd5c-455d-8a6a-2e212eee148e.png)

<b> *Fig. 1 Implementarea nodului virtual si detecția trecerii prin zero a BEMF* </b>

Din relația de mai jos se poate observa că amplitudinea BEMF este proporțională cu viteza rotorului, asta înseamnă că pentru controlul motorului există o limită inferioară a vitezei rotorului sub care detecția BEMF nu ar mai fi posibilă.

<b> V<sub>BEMF</sub> = B * L * v </b>


Deoarece la pornire amplitudinea BEMF este mica, iar circuitul de detecție nu poate semnaliza trecerea prin zero, s-a determinat experimental secvența optimă de pornire. Această secvență a fost implementată în software folosind un look-up table ce este citit cu ajutorul întreruperilor software. Deoarece în momentul pornirii poziția rotorului este necunoscută, a fost implementată o rutină software pentru punerea rotorului într-o poziție predefinită față de stator.


![image](https://user-images.githubusercontent.com/24388880/153603005-ef8fe3c8-750e-42d6-a287-8a6d75c07936.png)

<b> *Fig. 2a Modelare Simulink pentru controlul nesenzorizat* </b>

Pentru controlul motorului s-a ales proiectarea unui invertor realizat cu șașe tranzistori MOSFET de tip N. Pentru comanda tranzistorilor din partea de sus a invertorului s-au folosit drivere de comandă cu capacitoare de boostrap IR2101. Deși o implementare mult mai ușoară era folosirea tranzistorilor MOSFET de tip P, rezistența acestora în conducție este mai mare decât cea a tranzistorilor de tip N datorită tipului de purtători majoritari din regiunea de tip p.


![image](https://user-images.githubusercontent.com/24388880/153603072-65890214-c291-4284-84a8-d4f80b8e6f94.png)

<b> *Fig. 2b Tensiunea BEMF și punctul de trecere prin zero de pe fiecare fază. Simulare Simulink* </b>


![image](https://user-images.githubusercontent.com/24388880/153603184-962c2906-b3e2-43b8-b40d-ecfc5195c557.png)

<b> *Fig. 3 Arhitectura software bazată pe standardul AUTOSAR* </b>

# 3. Rezultate

În prezent, sistemul poate controla nesenzorizat un motor de hoverboard de 36V și 350W evidențiat în Figura 14 folosind detecția BEMF. Modulele electronice au fost proiectate în KiCad și imprimate folosind metoda de transfer de toner pentru a fixa imaginea cablajului pe laminatul de cupru. Vizualizarea semnalelor și depanarea s-a realizat cu ajutorul osciloscopului Hantek6022BE utilizat împreună cu limbajul de programare LabView unde s-a reazlizat un driver software ce apelează funcțiile dintr-un fișier DLL (Dynamic-link library) puse la dispoziție de producător.


![image](https://user-images.githubusercontent.com/24388880/153603255-8e72aeb5-21f0-4b49-8d7d-e7eb49b3b4a1.png)

<b> *Fig. 4 Ansamblu experimental* </b>

În ceea ce privește detecția punctului de trecere prin zero a semnalului BEMF au fost implementate filtre analogice pentru filtrarea semnalului PWM de 20 kHz.

Pentru corectitudinea detecției s-au comparat ieșirile senzorilor Hall cu ieșirile comparatoarelor, iar semnalele au un defazaj de 30°.


![image](https://user-images.githubusercontent.com/24388880/153603467-2fdb3206-2092-4eba-92e2-1f12034b9835.png)

<b> *Fig. 5 Ieșirea Hall și ieșirea comparatorului pentru faza B* </b>

Prin încercări experimentale s-a determinat un tabel pe baza căruia sunt acționate cele trei faze.

<b> *Tab. 1 Secvențele de comutare în funcție de ieșirile comparatoarelor* </b>

![image](https://user-images.githubusercontent.com/24388880/153603622-c824940b-3502-430e-b446-816e3bc04158.png)

În Figura 5 este evidențiată tensiunea pe faza A în raport cu nodul virtual realizat prin rețeaua de rezistențe. Acest semnal este numit în literatura de specialitate drept a treia armonică a semnalului BEMF și poate fi utilizat pentru detecția punctului de trecere prin zero a tensiunii electromotoare inverse. Aceste metode sunt numite metode indirecte de detecție a punctului de trecere prin zero și sunt folosite în industrie pentru controlul motoarelor la viteze reduse (RPM mic). Printre metodele indirecte se mai întânlesc metoda integrării BEMF, integrarea armonicii a treia a semnalului BEMF, măsurarea curentului fazelor și metoda ce utilizează diodele parazite (Free-Wheeling Diode) pentru detecția ZCP (zero crossing point).


![image](https://user-images.githubusercontent.com/24388880/153603802-7dbf2648-b808-4ee6-ae4e-e6149e4860f8.png)

 <b> *Fig.5 Tensiunea pe o fază avand ca referință nodul virtual* </b>

În Figura 6 se poate observa ca după filtrare tensiunea electromotoare inversă este asimetrică ceea ce duce la un dezechilibru în detecția ZCP. Acest lucru se datorează tipului de motor ales, acesta fiind tratat ca un sistem necunoscut deoarece nu s-au găsit informații de catalog de la producător. Dezechilibrul ZCP duce la un componament instabil al sistemului. Lucrarea "Unbalanced ZCP Compensation Method For Position Sensorless BLDC Motor" publicată în revista IEEE Transactions on Power Electronics, volumul 34, numărul 4 din aprilie 2019 propune o metodă de eliminare a acestui inconvenient. În Figura 74 a fost măsurată tensiunea electromotoare inversă pe un motor de 12V, punctul de trecere prin zero fiind simetric și la o distanță de 30° de grade de la ultima comutare.

![image](https://user-images.githubusercontent.com/24388880/153603960-ef6a4552-d4cc-4521-a38f-7d00db4db879.png)


<b> *Fig. 6 Detecția punctului de trecere prin zero* </b>

![image](https://user-images.githubusercontent.com/24388880/153604105-ef760424-524d-4070-a8c4-63920c0fcdb9.png)


<b> *Fig. 7 Detecția punctului de trecere prin zero. Semnal filtrat* </b>


![image](https://user-images.githubusercontent.com/24388880/153604166-9da9df7e-9dde-43fd-a476-22e474416112.png)


<b> *Fig. 8 BEMF echilibrat. Semnal nefiltrat. Galben – Faza A, Verde – Faza B* </b>

În Figura 9 este este evidențiată detecția punctului de trecere prin zero atunci cand factorul de umplere al semnalului PWM crește.


![image](https://user-images.githubusercontent.com/24388880/153604291-57538fc2-75d9-4f16-a323-4be021ee4e14.png)

<b> *Fig. 9 Detecția punctului de trecere prin zero în timpul accelerării. BEMF nefiltrat* </b>

În Figura 10 este evidențiată tensiunea nodului virtual, cunoscut drept nod de referință. După cum se poate vedea tensiunea de referință ce se găsește la intrarea inversoare a comparatoarelor nu este una constantă.


![image](https://user-images.githubusercontent.com/24388880/153604401-13f75a84-936f-4718-a3f1-7776164aff5c.png)

<b> *Fig. 10 Tensiunea BEMF și nodul virtual. Galben – BEMF, Verde – Nod virtual* </b>

Pe lângă partea experimentală și educațională, proiectul și-a propus crearea unui ESC ce respectă standardele din industrie și poate fi comercializa la scară largă. În Figura 11 este prezentat modulul electronic în tehnologie SMD (surface-mounted device).

![image](https://user-images.githubusercontent.com/24388880/153604481-4e73504c-ae69-445f-b3ba-b4d65bc7333e.png)


<b> *Fig. 11 Modul fizic realizat pentru comercializare* </b>

Pentru protecția modulului s-a realizat o carcasă 3D transformând fișierele 3D din KiCad în format step pentru a exporta dimensiunile modulului electronic. În Figura 11 și Figura 12 este prezentat modelul 3D realizat în FreeCad.

![image](https://user-images.githubusercontent.com/24388880/153604605-8c82ea52-e4ac-4589-9d25-3ae0a3b21fc3.png)


<b> *Fig. 12 Proiectare carcasă în FreeCad* </b>


![image](https://user-images.githubusercontent.com/24388880/153604698-e45bb6a8-c942-4c1b-9360-761db2c0397a.png)

<b> *Fig. 13 Carcasă printată 3D* </b>

# 4. Concluzii

Deoarece motoarele BLDC iau locul motoarelor cu perii, controlul nesenzorizat este de mare interes pentru dezvoltatorii de aplicații din domeniul automobilelor, aerospațial și HVAC (heating, ventilation and air conditioning). Eliminarea senzorilor scade costul de producție al motorului și dimensiunile lui. Putem spune că implementarea proiectului este de interes pentru companiile din domeniu și constituie un domeniu de cercetare în continuă dezvoltare. Proiectul și-a propus proiectarea și realizarea modulelor electronice în conformitate cu cerințele din industrie. De asemenea, partea software este în conformitate cu cerințele din industria automotive și respectă specificațiile AUTOSAR.

# Bibliografie

Microelctronics, S. T. (2007). Sensorless bldc motor control and bemf sampling methods with st7mc. AN1946 Application Note, 3-5.
Gamazo-Real, J. C., Vázquez-Sánchez, E., & Gómez-Gil, J. (2010). Position and speed control of brushless DC motors using sensorless techniques and application trends. Sensors, 10(7), 6901-6947.

Fürst, S., Mössinger, J., Bunzel, S., Weber, T., Kirschke-Biller, F., Heitkämper, P., ... & Lange, K. (2009, October). AUTOSAR–A Worldwide Standard is on the Road. In 14th International VDI Congress Electronic Systems for Vehicles, Baden-Baden (Vol. 62, p. 5).

Park, J. S., Lee, K. D., Lee, S. G., & Kim, W. H. (2018). Unbalanced ZCP Compensation Method for Position Sensorless BLDC Motor. IEEE Transactions on Power Electronics, 34(4), 3020-3024.

Bakare, M. R. S., & Jain, G. P. (2015). PSOC Based Speed Control of BLDC Motor. Asian Journal For Convergence In Technology (Founded by ISB &M School of Technology)), 1.


