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
  
#### Testavimo rezultatai:
 * Nepriklausomai nuo input'o dydžio, output'as visada yra 64 simboliai.
 * Tas pats input'as visada duoda tą patį output'ą
 * Hash funkcija, kai input'as yra konstitucija.txt failas, užtrunka 0.33411s
 * Tikrinant 100 000 eilučių failą poromis, skaitant, kad pasikartojantys hash yra tik tuo atvėju, kai nesutampa sugeneruotos eilutės, bet sutampa gauti jų hash, tokių atvėjų neaptikta.  
