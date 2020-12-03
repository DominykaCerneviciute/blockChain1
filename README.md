# version v0.3
## Šioje versijoje atlikti veiksmai:
          1. Buvo įdiegta papildoma biblioteka "libbitcoin-system: Bitcoin Cross-Platform C++ Development Toolkit"
          2. Integruota "create_merkle()" funkcija vietoj savo funkcijos, kuri apskaičiuoja merkle root hash'ą
          
## Paleidimas:
          1. g++ -std=c++11 -o test main.cpp hash.cpp class.cpp Source.cpp $(pkg-config --cflags --libs libbitcoin)
          2. ./test

## Testavimas

##### Block: 95000
##### Transakcijų hash'ai: 
   1. "82623ec828f8db0a311202fc65789c93212d641b9986f6a2ea213d4564eb1e0f"
   2. "3500b0e3452e801e648a0aff1a5a7bd6f2c3f9ce26fd4b1920a391e18d1f9d53"
#### Rezultatai:
   1. Merkle Root Hash: bb9f3f5820a7cb932f8799ed933afabd0598ddc6962eb3cdc0249d9a7948ae94
   2. Merkle Root Hash-2: 94ae48799a9d24c0cdb32e96c6dd9805bdfa3a93ed99872f93cba720583f9fbb
