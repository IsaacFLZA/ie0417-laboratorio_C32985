# Parte 10: persistencia con volúmenes

## Paso: crear el volumen datos-lab

**Qué se hizo:** Se creó un volumen de Docker llamado `datos-lab`.

**Comando ejecutado:**

```bash
docker volume create datos-lab
```

**Explicación (para qué sirve el comando):** El comando `docker volume create` crea un volumen administrado por Docker. Los volúmenes permiten almacenar información fuera del sistema de archivos interno de un contenedor, de manera que los datos puedan mantenerse aunque el contenedor sea eliminado.

**Resultado obtenido:**

```text
datos-lab
```

**Reflexión:** El volumen se creó correctamente y quedó disponible para ser utilizado por uno o varios contenedores. Esto permite separar los datos persistentes del ciclo de vida de los contenedores.

## Paso: listar los volúmenes

**Qué se hizo:** Se consultaron los volúmenes existentes en Docker.

**Comando ejecutado:**

```bash
docker volume ls
```

**Explicación (para qué sirve el comando):** `docker volume ls` muestra los volúmenes disponibles en el sistema y el controlador utilizado para administrarlos.

**Resultado obtenido:**

```text
DRIVER    VOLUME NAME
local     datos-lab
```

**Reflexión:** La salida confirmó que el volumen `datos-lab` fue creado correctamente y utiliza el controlador `local`.

## Paso: montar el volumen en un contenedor

**Qué se hizo:** Se creó un contenedor Ubuntu llamado `contenedor-volumen` y se montó el volumen `datos-lab` en el directorio `/datos` dentro del contenedor.

**Comando ejecutado:**

```bash
docker run -it --name contenedor-volumen -v datos-lab:/datos ubuntu bash
```

**Explicación (para qué sirve el comando):** La opción:

```text
-v datos-lab:/datos
```

indica que el volumen llamado `datos-lab` debe montarse en la ruta `/datos` dentro del contenedor.

De esta forma, cualquier información guardada en `/datos` se almacena en el volumen y no únicamente en el sistema de archivos interno del contenedor.

## Paso: crear un archivo dentro del volumen

**Qué se hizo:** Dentro del contenedor se creó un archivo llamado `archivo.txt` en el directorio `/datos`.

**Comando ejecutado:**

```bash
echo "Este archivo está en un volumen" > /datos/archivo.txt
```

**Explicación (para qué sirve el comando):** El comando `echo` generó el texto indicado y el operador `>` lo redirigió hacia el archivo `/datos/archivo.txt`.

Como `/datos` corresponde al volumen `datos-lab`, el archivo quedó almacenado en el volumen.

## Paso: verificar el contenido del archivo

**Comando ejecutado:**

```bash
cat /datos/archivo.txt
```

**Resultado obtenido:**

```text
Este archivo está en un volumen
```

**Reflexión:** El resultado confirmó que el archivo fue creado correctamente dentro del volumen y que podía ser leído desde el primer contenedor.

## Paso: salir y eliminar el primer contenedor

**Comando ejecutado:**

```bash
exit
```

Posteriormente:

```bash
docker rm contenedor-volumen
```

**Resultado obtenido:**

```text
contenedor-volumen
```

**Explicación:** El primer contenedor fue eliminado después de salir de la shell interactiva.

**Reflexión:** Aunque el contenedor fue eliminado, el volumen `datos-lab` no fue eliminado. Esto permitió comprobar posteriormente si el archivo seguía existiendo de forma independiente al contenedor.

## Paso: crear un segundo contenedor usando el mismo volumen

**Qué se hizo:** Se creó un segundo contenedor Ubuntu llamado `contenedor-volumen-2`, montando nuevamente el volumen `datos-lab` en `/datos`.

**Comando ejecutado:**

```bash
docker run -it --name contenedor-volumen-2 -v datos-lab:/datos ubuntu bash
```

**Explicación (para qué sirve el comando):** Este comando creó un nuevo contenedor independiente del anterior, pero utilizando el mismo volumen.

Esto permite verificar si los datos almacenados en el volumen continúan disponibles aunque el contenedor original ya no exista.

## Paso: verificar la persistencia del archivo

**Comando ejecutado:**

```bash
cat /datos/archivo.txt
```

**Resultado obtenido:**

```text
Este archivo está en un volumen
```

**Reflexión:** El archivo seguía existiendo dentro del segundo contenedor, aunque el primer contenedor había sido eliminado.

Esto demuestra que los datos almacenados en un volumen no dependen directamente del ciclo de vida de un contenedor. El volumen permaneció disponible y pudo ser reutilizado por otro contenedor.

## Paso: eliminar el segundo contenedor

Después de verificar el archivo se salió del contenedor:

```bash
exit
```

Posteriormente se eliminó:

```bash
docker rm contenedor-volumen-2
```

**Resultado obtenido:**

```text
contenedor-volumen-2
```

**Reflexión:** El segundo contenedor también fue eliminado, pero el volumen continuó existiendo de forma independiente.

## Paso: inspeccionar el volumen

**Qué se hizo:** Se consultó la información detallada del volumen `datos-lab`.

**Comando ejecutado:**

```bash
docker volume inspect datos-lab
```

**Explicación (para qué sirve el comando):** `docker volume inspect` muestra información detallada sobre un volumen, como su nombre, controlador, ubicación interna en el host, alcance y fecha de creación.

**Resultado obtenido:**

```json
[
    {
        "CreatedAt": "2026-10-07T21:04:09Z",
        "Driver": "local",
        "Labels": null,
        "Mountpoint": "/var/lib/docker/volumes/datos-lab/_data",
        "Name": "datos-lab",
        "Options": null,
        "Scope": "local"
    }
]
```

**Reflexión:** La inspección mostró que Docker administra el volumen utilizando el controlador `local` y que sus datos se almacenan internamente en:

```text
/var/lib/docker/volumes/datos-lab/_data
```

También se confirmó que el volumen mantiene su propio ciclo de vida y continúa existiendo aunque los contenedores que lo utilizaron hayan sido eliminados.

## Qué es un volumen

Un volumen es un mecanismo administrado por Docker para almacenar información fuera del sistema de archivos interno de un contenedor.

Esto permite que los datos puedan permanecer disponibles aunque el contenedor sea detenido o eliminado.

En este ejercicio, el volumen `datos-lab` conservó `archivo.txt` incluso después de eliminar el primer contenedor.

## Cómo se crea un volumen

Un volumen puede crearse mediante:

```bash
docker volume create datos-lab
```

Luego puede verificarse utilizando:

```bash
docker volume ls
```

## Cómo se monta un volumen en un contenedor

Para montar un volumen se utiliza la opción `-v` de `docker run`.

En este ejercicio se utilizó:

```text
-v datos-lab:/datos
```

donde:

```text
datos-lab
```

corresponde al nombre del volumen administrado por Docker y:

```text
/datos
```

corresponde a la ruta dentro del contenedor donde se monta.

## Qué pasó con el archivo después de eliminar el primer contenedor

El archivo `archivo.txt` permaneció disponible porque estaba almacenado en el volumen `datos-lab` y no únicamente en el sistema de archivos interno del contenedor.

Esto se comprobó al crear `contenedor-volumen-2` con el mismo volumen y ejecutar:

```bash
cat /datos/archivo.txt
```

obteniendo nuevamente:

```text
Este archivo está en un volumen
```

## Preguntas de reflexión

1. **¿Qué problema resuelven los volúmenes?**

   Los volúmenes permiten conservar información aunque un contenedor sea eliminado.

   Sin un volumen, los datos almacenados únicamente dentro del sistema de archivos del contenedor pueden perderse al eliminarlo.

2. **¿El volumen pertenece a un contenedor específico?**

   No. Un volumen existe de forma independiente a los contenedores que lo utilizan.

   En este ejercicio, `datos-lab` fue utilizado primero por `contenedor-volumen` y después por `contenedor-volumen-2`, conservando el mismo archivo entre ambos.

3. **¿Qué diferencia hay entre eliminar un contenedor y eliminar un volumen?**

   Eliminar un contenedor borra esa instancia del contenedor, pero no elimina automáticamente los volúmenes que existen de manera independiente.

   Eliminar un volumen, en cambio, elimina los datos almacenados dentro de ese volumen.

4. **¿Para qué casos reales se usarían volúmenes?**

   Los volúmenes pueden utilizarse cuando una aplicación necesita conservar información independientemente de los contenedores.

   Por ejemplo, pueden servir para almacenar datos de bases de datos, archivos generados por una aplicación, configuraciones persistentes o información que deba conservarse entre distintas ejecuciones de un servicio.


   # Parte 11: bind mounts

## Bind mounts

## Paso: ejecutar la aplicación utilizando un bind mount

**Qué se hizo:** Se ejecutó la aplicación Flask dentro de un contenedor llamado `app-bind`, montando la carpeta local `app/` del host dentro del directorio `/app` del contenedor.

**Comando ejecutado:**

```bash
docker run --name app-bind -p 5000:5000 -v "$(pwd)":/app laboratorio-flask:1.0
```

**Explicación (para qué sirve el comando):** La opción `-v "$(pwd)":/app` crea un bind mount entre la carpeta actual del host y el directorio `/app` dentro del contenedor.

En este caso, `$(pwd)` representa la ruta actual:

```text
/workspaces/ie0417-laboratorio_C32985/laboratorio-contenedores/app
```

y `/app` corresponde al directorio utilizado por la aplicación dentro del contenedor.

Por lo tanto, el contenido de la carpeta local queda disponible directamente dentro del contenedor.

**Resultado obtenido:**

```text
* Serving Flask app 'app'
* Debug mode: off
WARNING: This is a development server. Do not use it in a production deployment. Use a production WSGI server instead.
* Running on all addresses (0.0.0.0)
* Running on http://127.0.0.1:5000
* Running on http://172.17.0.2:5000
Press CTRL+C to quit
172.17.0.1 - - [07/Oct/2026 21:18:49] "GET / HTTP/1.1" 200 -
172.17.0.1 - - [07/Oct/2026 21:18:49] "GET /favicon.ico HTTP/1.1" 404 -
```

**Reflexión:** La aplicación inició correctamente utilizando los archivos disponibles en la carpeta local montada mediante el bind mount. Esto permitió que el código almacenado en el host estuviera disponible dentro del contenedor sin necesidad de copiarlo nuevamente a una imagen.

## Paso: modificar el código local

**Qué se hizo:** Se modificó el archivo `app.py` directamente desde GitHub Codespaces, cambiando el mensaje mostrado en la página principal.

El nuevo mensaje utilizado fue:

```text
Messi es el mejor de la historia
```

El cambio se realizó sobre el archivo local ubicado en la carpeta que estaba siendo montada dentro del contenedor.

**Reflexión:** Debido al bind mount, el contenedor utiliza los archivos de la carpeta local en lugar de depender únicamente de la copia incluida originalmente en la imagen. Esto permite trabajar directamente sobre el código del host durante el desarrollo.

## Paso: detener y eliminar el primer contenedor

**Qué se hizo:** Después de modificar el archivo local, se detuvo y eliminó el primer contenedor.

**Comandos ejecutados:**

```bash
docker stop app-bind
docker rm app-bind
```

**Resultado obtenido:**

```text
app-bind
app-bind
```

**Reflexión:** El contenedor se eliminó correctamente. El cambio realizado en `app.py` no se perdió porque el archivo pertenece a la carpeta del host y no al sistema de archivos interno del contenedor.

## Paso: ejecutar nuevamente la aplicación con el bind mount

**Qué se hizo:** Se creó un nuevo contenedor llamado `app-bind-2`, utilizando nuevamente la misma carpeta local como bind mount.

**Comando ejecutado:**

```bash
docker run --name app-bind-2 -p 5000:5000 -v "$(pwd)":/app laboratorio-flask:1.0
```

**Explicación (para qué sirve el comando):** El nuevo contenedor utilizó la misma imagen `laboratorio-flask:1.0`, pero el directorio `/app` fue reemplazado por el contenido actual de la carpeta local mediante el bind mount.

Por esta razón, el nuevo contenedor pudo utilizar directamente la versión modificada de `app.py` sin reconstruir la imagen.

**Resultado obtenido:**

```text
* Serving Flask app 'app'
* Debug mode: off
WARNING: This is a development server. Do not use it in a production deployment. Use a production WSGI server instead.
* Running on all addresses (0.0.0.0)
* Running on http://127.0.0.1:5000
* Running on http://172.17.0.2:5000
Press CTRL+C to quit
172.17.0.1 - - [07/Oct/2026 21:21:13] "GET / HTTP/1.1" 200 -
172.17.0.1 - - [07/Oct/2026 21:21:13] "GET /favicon.ico HTTP/1.1" 404 -
```

La página principal mostró correctamente el nuevo mensaje:

```text
Messi es el mejor de la historia
```


**Reflexión:** El cambio realizado en el archivo `app.py` del host apareció en el nuevo contenedor sin necesidad de modificar el Dockerfile ni ejecutar nuevamente `docker build`.

Esto demuestra que el bind mount permite utilizar directamente archivos del host dentro del contenedor, lo cual puede resultar útil durante el desarrollo de una aplicación.

## Paso: detener y eliminar el segundo contenedor

**Qué se hizo:** Después de verificar el cambio en la aplicación, se detuvo y eliminó el segundo contenedor.

**Comandos ejecutados:**

```bash
docker stop app-bind-2
docker rm app-bind-2
```

**Resultado obtenido:**

```text
app-bind-2
app-bind-2
```

**Reflexión:** El segundo contenedor se eliminó correctamente. El archivo `app.py` modificado permaneció en la máquina host, ya que el bind mount utiliza directamente los archivos locales y estos no dependen del ciclo de vida del contenedor.

## Diferencia entre datos-lab:/datos y "$(pwd)":/app

En la Parte 10 se utilizó:

```text
datos-lab:/datos
```

En este caso, `datos-lab` corresponde a un volumen administrado directamente por Docker. Docker se encarga de decidir dónde se almacenan físicamente esos datos.

En la Parte 11 se utilizó:

```text
"$(pwd)":/app
```

En este caso, `$(pwd)` corresponde a una carpeta real del host. Docker monta esa carpeta directamente dentro del contenedor en `/app`.

La diferencia principal es que un volumen es administrado por Docker, mientras que un bind mount utiliza directamente una ruta existente en el sistema anfitrión.

## Qué ocurrió al modificar el código local

Después de modificar `app.py` en el host y ejecutar nuevamente el contenedor con el mismo bind mount, la aplicación mostró el nuevo mensaje:

```text
Messi es el mejor de la historia
```

No fue necesario reconstruir la imagen `laboratorio-flask:1.0`.

Esto ocurrió porque el directorio `/app` del contenedor estaba utilizando directamente el contenido de la carpeta local mediante el bind mount.

## Por qué esto puede ser útil durante el desarrollo

Los bind mounts permiten modificar el código desde el editor del host y utilizar esos mismos archivos dentro del contenedor.

Esto evita tener que reconstruir una imagen cada vez que se realiza un cambio en el código durante el desarrollo.

De esta forma, el contenedor puede proporcionar el entorno de ejecución y las dependencias, mientras que el código puede seguir editándose directamente desde el sistema anfitrión.

## Preguntas de reflexión

1. **¿Qué diferencia hay entre un volumen y un bind mount?**

   Un volumen es un espacio de almacenamiento administrado por Docker. El usuario le asigna un nombre, como `datos-lab`, y Docker administra su ubicación en el sistema.

   Un bind mount conecta directamente una carpeta o archivo existente en el host con una ruta dentro del contenedor.

   En este laboratorio, `datos-lab:/datos` utilizó un volumen administrado por Docker, mientras que `"$(pwd)":/app` utilizó directamente la carpeta local del proyecto.

2. **¿Cuál parece más conveniente para desarrollo?**

   Un bind mount resulta conveniente durante el desarrollo porque permite editar los archivos directamente desde el host y utilizar esos mismos archivos dentro del contenedor.

   En este ejercicio, fue posible modificar `app.py` y observar el cambio sin reconstruir la imagen.

3. **¿Cuál parece más conveniente para datos persistentes de una aplicación?**

   Un volumen suele ser más conveniente para almacenar datos persistentes que no deberían depender directamente de una carpeta específica del host.

   En la Parte 10 se comprobó que el volumen `datos-lab` conservó el archivo incluso después de eliminar los contenedores que lo utilizaron.

4. **¿Qué riesgos podría tener montar carpetas del host dentro del contenedor?**

   Un bind mount da al contenedor acceso directo a archivos del host dentro de la ruta montada.

   Si el contenedor puede escribir en esa carpeta, también podría modificar o eliminar archivos del sistema anfitrión. Por esta razón, es importante montar únicamente las rutas necesarias y controlar qué acceso se proporciona al contenedor.