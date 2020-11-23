# version v0.3
# Šioje versijoje:
          Buvo įdiegta papildoma biblioteka "libbitcoin-system: Bitcoin Cross-Platform C++ Development Toolkit"
          Integruota "create_merkle()" funkcija vietoj savo funkcijos, kuri apskaičiuoja merkle root hash'ą
          
## Paleidimas:
          g++ -std=c++11 -o test main.cpp hash.cpp class.cpp Source.cpp $(pkg-config --cflags --libs libbitcoin)
          ./test

          
