### v0.1 versija


### Hash veikimo principas:
 - Visas input'as skirstomas į 4 konteinerius, jog būtų lengviau užtikrinti, kad hash visada bus 64 simboliai. Taip pat dėl skaičiavimų ir bitų maišymo.
 - Skaitant po eilutę, o tuomet  po kiekvieną eilutės simbolį, jis verčiamas į dvejetainę skaičiavimo sistęmą ir dedamas i vieną iš konteinerių.
 - Jei perskaičius visa input'ą konteineriai nėra pilnai užpildyti, jie užpildomi atliekant matematinius skaičiavimus. 
 - Jei visi konteineriai pilni, tačiau input'as dar nesibaigė, jis saugomas naujame konteineryje ir yra sukeičiamas su vienu iš esamų.
 - Kai visi konteineriai yra reikiamo dydžio, vyksta matematiniai skaičiavimai ir bitų maišymas.
 - Dvejatainė skaičiavimo sistema paverčiama į šešioliktainę skaičiavimo sistemą
 - Gaunamas rezultatas
  
  
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
  
#### Testavimo rezultatai:
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
 
 |               |       max     |      avg     |     min      |
 |---------------|---------------|--------------|--------------|
 |  Skirtingumas |     100%      |      80%     |      30%     |


