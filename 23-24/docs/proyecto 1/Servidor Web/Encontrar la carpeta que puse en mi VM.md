Al utilizar VM's, a veces se nos puede hacer complicado, sobretodo si somos nuevos, donde están las carpetas que "pongo" desde mi repositorio local, ¿Donde se ubican estos ficheros?.

Para ello recomiendo el uso de este comando:

```bash
find / -type d -name "nombre_de_la_carpeta"
```

Te dará la ruta donde se ubica el fichero que has puesto en tu VM.

Y para colocarlo en donde queramos use:

```bash
mv /ruta/a/tu/archivo /ruta/a/tu/destino
```

Ejemplo:

```bash
carlos@debian:/home$ sudo mv home/Escritorio home/carlos/Escritorio/
```