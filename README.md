# ROCK the SHOP - Sistem de Gestiune (Proiect POO 2024)

Acesta este un proiect dezvoltat în C++ (Modern C++) pentru materia Programare Orientată pe Obiecte (POO). Aplicația simulează un sistem complet de management pentru un magazin de produse fizice (articole vestimentare și discuri vintage), incluzând gestiunea angajaților, a stocurilor și procesarea comenzilor cu simularea trecerii timpului.

##  Funcționalități Principale

### 1. Gestiunea Angajaților (Polimorfism și Moștenire)
Sistemul suportă mai multe tipuri de angajați, derivați din clasa de bază `angajati`:
- **Manageri**: Coordonează echipa.
- **Asistenți**: Ajută la procesele din magazin.
- **Operatori Comenzi**: Preiau și procesează activ comenzile.
* Notă: Vârsta și vechimea sunt calculate dinamic folosind timpul real al sistemului (`<ctime>`). Salariile sunt calculate polimorfic, luând în calcul vechimea, bonusuri de ziua de naștere și bonusuri de performanță (procent din valoarea comenzilor procesate).

### 2. Gestiunea Produselor
- **Articole Vestimentare**: Haine cu proprietăți specifice de brand, culoare.
- **Discuri / Discuri Vintage**: Produse muzicale ce pot avea un coeficient de raritate care le crește valoarea.

### 3. Simularea Timpului și a Comenzilor (Management Cozi)
O inovație a acestui proiect este "Simularea Timpului". 
- O comandă necesită "Timp de procesare".
- Operatorii pot prelua un număr maxim de 3 comenzi simultan.
- Comenzile noi care nu găsesc un operator liber sunt puse pe pauză într-o coadă de așteptare (`std::queue`).
- Prin opțiunea de "Avansează Timpul" din meniu, timpul trece în magazin -> comenzile operatorilor sunt finalizate -> angajații se eliberează -> comenzile din coadă sunt redistribuite automat celor eliberați.


##  Concepte POO Aplicate
* Încapsulare (Protected / Private memebers)
* Moștenire (Virtual classes)
* Polimorfism (Salarii calculate suprascris, Funcții virtuale de afișare)
* Clasa abstractă / Interfețe
* Pointeri și STL (Vectori `std::vector` și Cozi `std::queue`)
* Excepții (Blocuri de tip `try/catch` pentru invalidări de CNP)
