## Générer le fichier DOT

- La fonction `exportDotGraph(Abr* T, char* name)` permet de générer le fichier `.dot` correspondant à un arbre `T`.

## Afficher l'arbre

- On utilise l'utilitaire `dot` avec :

  ```bash
  dot -Tpng <fichier d'entrée>.dot -o <fichier de sortie>.png
  ```

Commande de compilation :

    ```gcc -Wall -DDEBUG -g -o main main.c && ./main```
    (08/05/25: désormais, dot -Tpng test.dot -o outfile.png s'exécute automatiquement dans le programme)

    (14/05/25: Commandes du makefile : (toujours clean avant !)
    - make
    - make debug
    - make clean
    
    Pour lancer : ./build/programme
    )

# Recommandations

- Ouvrir en fenêtre scindée le fichier PNG pour voir le résultat à chaque compilation.