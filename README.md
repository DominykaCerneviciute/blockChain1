# version v0.3
## Šioje versijoje atlikti veiksmai:
          1. Buvo įdiegta papildoma biblioteka "libbitcoin-system: Bitcoin Cross-Platform C++ Development Toolkit"
          2. Integruota "create_merkle()" funkcija vietoj savo funkcijos, kuri apskaičiuoja merkle root hash'ą
          
## Paleidimas:
          1. g++ -std=c++11 -o test main.cpp hash.cpp class.cpp Source.cpp $(pkg-config --cflags --libs libbitcoin)
          2. ./test

          
