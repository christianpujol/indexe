### synopsis

    indexe [ -g GOFILE | -s STOPFILE ]  [FILE]

### Quelques remarques: 

* si FILE n'est pas spécifié `indexe` lit `stdin`
* Le programme accepte une stoplist OU une golist, pas les deux. Le programme
  considèrera seulement la dernière option passé.
* Le Programme ne fonctionne que pour des fichiers textes ASCII. Pour d'autres
  encodages, le programme n'est pas efficace.
  
