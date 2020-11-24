### v0.2 versija


### Hash veikimo principas:
 - Visas input'as skirstomas į 4 konteinerius, jog būtų lengviau užtikrinti, kad hash visada bus 64 simboliai. Taip pat dėl skaičiavimų ir bitų maišymo.
 - Skaitant po eilutę, o tuomet  po kiekvieną eilutės simbolį, jis verčiamas į dvejetainę skaičiavimo sistęmą ir dedamas i vieną iš konteinerių.
 - Jei perskaičius visa input'ą konteineriai nėra pilnai užpildyti, jie užpildomi atliekant matematinius skaičiavimus. 
 - Jei visi konteineriai pilni, tačiau input'as dar nesibaigė, jis saugomas naujame konteineryje ir yra sukeičiamas su vienu iš esamų.
 - Kai visi konteineriai yra reikiamo dydžio, vyksta matematiniai skaičiavimai ir bitų maišymas.
 - Dvejatainė skaičiavimo sistema paverčiama į šešioliktainę skaičiavimo sistemą
 - Gaunamas rezultatas
  
  #### Testavimo rezultatai:
  
  | Input'as | Output'as                                                        |
  |----------|------------------------------------------------------------------|
  | lietuva  | 6de17db43572c1c64850001920a05c00918ab9c2df0fa1ff918ab9c2df0fa1ff |
  | Lietuva  | f96dad3554766b21020822a8189f3100bdf7dc4325200a77bdf7dc4325200a77 |
  | Lietuva! | 4e7cc0e425fc35010882004a0110a008963dfdb0f0cb5c70963dfdb0f0cb5c70 |
  
  | Input'as | Output'as                                                                   |
  |----------|-----------------------------------------------------------------------------|
  |          v          | 7fe8389d2798e38164411a2a020120099996a0d15d4e9fb49996a0d15d4e9fb4 |
  |          8          | 1835e7d1febe0a12162800062101e001a0d69b789af01dfca0d69b789af01dfc |
  |      1010 simb.     | 9a6917e8796b796b0090824611000208ea4d6da1ac6d2565ea4d6da1ac6d2565 |
  |      1010 simb.     | 4b04fdef146771724c1049450c0492522246a4aa226a2d2d2246a4aa226a2d2d |
  |    Tuščias failas   | 32bc783fb83e83bd440a20601c8649a49bf45196213886439bf4519621388643 |
  |1100 simb. skiriasi 1| 4750b53d3022ece90050089900100042692ca164ee6aad84692ca164ee6aad84 |
  |1100 simb. skiriasi 1| 9675961d104364e80c02144a82040410f029aba54c6ba9c7f029aba54c6ba9c7 |
  
|Inputo'o dydis | Output'o dydis |
|---------------|----------------|
|       1       |       64       |
|       10      |       64       |
|       100     |       64       |
|       1010    |       64       |
|       1100    |       64       |

|  Input'o failas  | laikas    |
|------------------|-----------|
| konstitucija.txt | 0.33411s  |

| String'o ilgis | eil. skaičius | pasikartojimai(collisions)|
|----------------|---------------|---------------------------|
|      10        |      25000    |            0              |
|      100       |      25000    |            0              |
|      500       |      25000    |            0              |
|      1000      |      25000    |            0              |
 
 | Skirtingumas  |       max     |      avg     |     min      |
 |---------------|---------------|--------------|--------------|
 |Hex'ų lygmenyje|     100%      |      80%     |      30%     |
 |Bitų lygmenyje |      53%      |      34%     |      11%     |

## Supaprastintas blokų grandinės kūrimas
### paleidimas
- g++ -c main.cpp Source.cpp hash.cpp class.cpp
- g++ -o test main.o Source.o hash.o class.o
- test

### klasės
Šioje versijoje sukurtos 3 klasės: 

1. users
  - name (vartotojo vardas)
  - public_key (viešasis raktas)
  - balance (turima pinigų suma)
 #### Galimi veiksmai su klase:
  	 pasiimti public_key reikšmę
  	 pasiimti turimą pinigų sumą
  	 pasiimti naudotojo vardą
 	 nustatyti balansą
2. transaction
  - id
  - user1 (siuntėjas)
  - user2 (gavėjas)
  - sum (siunčiama pinigų suma)
  - valid (ar transakcija validi)
 #### Galimi veiksmai su klase:
  	 pasiimti transakcijos id
	 pasiimti siuntėjo public_key
	 pasiimti gavėjo public_key
	 pasiimti siunčiamą sumą
	 nustatyti validumo reikšmę
  	 pasiimti validumo reikšmę
3. block
- prevBlockHash (pireš tai buvusio bloko hash)
- markelRootHash (transakcijų hash)
- version (versija)
- nonce (random skaičius)
- difTarget (sudėtingumas)
- timeStamp (laiko žymą)
- transactions (transakcijos)
#### Galimi veiksmai su klase:
	   nustatyti markelRootHash
	   nustatyti versiją
	   nustatyti nonce reikšmę
	   pasiimti prevBlockHash
	   pasiimti markelRootHash 
	   pasiimti versiją
	   pasiimti nonce reikšmę
	   pasiimti difTarget
	   pasiimti timeStamp
	   pasiimti kažkurią transakciją
	   pasiimti transakcijų skaičių
	   pašalinti transakciją
	   padidinti nonce vienetu
	   įdėti transakciją
  
  ### Įgyvendinimai v0.1 versijoje:
  1. Sukurtos 3 klasės
  2. Sukurtas transakcijų pool'as
  3. Transakcijų dėjimas į blokus
  4. Blokų kasimas
  5. Transakcijų šalinimas iš pool'o
  6. Transakcijų įvykdymas
  7. Bloko pridėjimas į grandinę
  8. Ciklas grandinei kurti
  9. Transakcijų hash 
  
  ### Patobulinimai v0.2 versijoje:
      Transakcijų hash gavimas padarytas pagal Markle Tree 
      Atliktas transakcijų verifikavimas tikrinant balansą ir transakcijos id
      Patobulintas kasimo procesas naudojant penkis blokus-kandidatus
