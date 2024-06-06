# TetrisOnTerminal
Progetto di Programmazione (00819), Università di Bologna, A.A. 2023-24;

# Esecuzione
**Installazione delle librerie necessarie:**

**Linux**: `sudo  apt-get  install  libncurses5-dev  libncursesw5-dev`

**macOS**: `brew install ncurses`

**Windows**: Configurare i pacchetti `pdcurses, libncurses, libpdcurses, ncurses` da un tool di compilazione come `sourceforge.net/projects/mingw/`


**Compilazione ed esecuzione del gioco:**

**Linux, macOS**: `g++ *.cpp -lncurses -o Tetris && ./Tetris`

**Windows**: `g++ -I/mingw64/include/ncurses -o Tetris *.cpp -lncurses -L/mingw64/bin -static`, dopodiché eseguire con `Tetris` oppure `./Tetris`;

# Comandi
**Menù:**

**'↑'** e **'↓'** per scorrere le opzioni;

**'→'** oppure **'ENTER'** per selezionare l'opzione;

**'ESC'** per chiudere il programma;

**Leaderboard:**

**'↑'** e **'↓'** per scorrere la lista;

**'C'** per eliminare tutti i nomi e punteggi della lista;

**'ESC'** oppure **'BACKSPACE'** per tornare al menù;

**In-Game:**

**'←'** e **'→'** per lo spostamento del tetramino di una posizione lungo la riga;

**'↓'** oppure **'ENTER'** per lo spostamento del tetramino di una posizione verso il basso;

**'↑'** oppure **'R'** per la rotazione del tetramino in senso orario;

**'Q'** per la rotazione del tetramino in senso antiorario;

**'E'** per lo spostamento/recupero del tetramino in *HOLD*;

**'ESC'** oppure **'BACKSPACE'** per tornare al menù;
# Autori
Ilaria Commodaro, Mirco Quartieri, Lorenzo Raffini, Alessandro Zanaglia

