# Parte 3: imágenes y contenedores

## Paso: docker pull ubuntu

**Qué se hizo:** Se descargó la imagen oficial de Ubuntu desde Docker Hub.

**Comando ejecutado:**

```bash
docker pull ubuntu
```

**Explicación (para qué sirve el comando):** El comando `docker pull` permite descargar una imagen desde un registro de contenedores. En este caso se descargó la imagen oficial de Ubuntu desde Docker Hub. Como no se especificó una versión concreta, Docker utilizó automáticamente la etiqueta `latest`.

**Resultado obtenido:**

```text
Using default tag: latest
latest: Pulling from library/ubuntu
06ad70e463aa: Pull complete
4e07a0f12b2c: Pull complete
8f70d2bfe91a: Download complete
Digest: sha256:f144425ff09be612d6d9ad965196e9cdc23dae1f42110a8a11a3e9a8198759f7
Status: Downloaded newer image for ubuntu:latest
docker.io/library/ubuntu:latest
```

**Reflexión:** Este comando permitió observar que las imágenes de Docker pueden descargarse por capas. También se pudo ver que, al no indicar una etiqueta específica, Docker utilizó `latest` de forma predeterminada. Después de completar la descarga, la imagen quedó disponible localmente para crear contenedores a partir de ella.

## Paso: docker images

**Qué se hizo:** Se consultaron las imágenes de Docker disponibles localmente.

**Comando ejecutado:**

```bash
docker images
```

**Explicación (para qué sirve el comando):** El comando `docker images` muestra las imágenes almacenadas en el sistema. Permite observar información como el nombre de la imagen, la etiqueta, su identificador y el espacio que ocupa.

**Resultado obtenido:**

```text
                                          i Info →   U  In Use
IMAGE                ID             DISK USAGE   CONTENT SIZE
hello-world:latest   5e2309035332       25.9kB         9.49kB
ubuntu:latest        f144425ff09b        162MB         45.6MB
```

**Reflexión:** En la salida se observaron las imágenes `hello-world:latest` y `ubuntu:latest`. Esto permitió comprobar que la imagen de Ubuntu descargada anteriormente quedó almacenada en el entorno local y ya podía utilizarse para crear uno o más contenedores.

## Paso: docker run -it ubuntu bash

**Qué se hizo:** Se creó y ejecutó un contenedor interactivo basado en la imagen de Ubuntu.

**Comando ejecutado:**

```bash
docker run -it ubuntu bash
```

**Explicación (para qué sirve el comando):** El comando `docker run` crea y ejecuta un nuevo contenedor a partir de una imagen. La opción `-i` mantiene la entrada estándar abierta y la opción `-t` asigna una terminal interactiva. Al indicar `bash`, se inició una shell Bash dentro del contenedor.

Esto permitió interactuar directamente con el sistema de archivos y ejecutar comandos dentro del contenedor.

**Resultado obtenido:**

```text
root@4150f881096b:/#
```

**Reflexión:** Al ejecutar el contenedor en modo interactivo, el prompt cambió y pasó a mostrar `root@4150f881096b:/#`. Esto indicó que la terminal ya no se encontraba directamente en el sistema anfitrión, sino dentro del contenedor de Ubuntu. El identificador mostrado en el prompt coincidió con el identificador del contenedor observado posteriormente con `docker ps -a`.

## Exploración dentro del contenedor

### Comando ls

**Qué se hizo:** Se listaron los archivos y directorios disponibles en la raíz del contenedor.

**Comando ejecutado:**

```bash
ls
```

**Resultado obtenido:**

```text
bin   dev  home  lib64  mnt  proc  run   srv  tmp  var
boot  etc  lib   media  opt  root  sbin  sys  usr
```

**Explicación:** El comando `ls` permitió observar la estructura básica de directorios disponible dentro del contenedor. La organización es similar a la de un sistema Linux tradicional, con directorios como `/etc`, `/usr`, `/var`, `/home` y `/root`.

**Reflexión:** Aunque el contenedor presenta una estructura de archivos parecida a la de un sistema Ubuntu completo, esto no significa que sea una máquina virtual. El contenedor utiliza un entorno aislado con los archivos necesarios para ejecutar sus procesos.

### Comando pwd

**Qué se hizo:** Se consultó el directorio actual dentro del contenedor.

**Comando ejecutado:**

```bash
pwd
```

**Resultado obtenido:**

```text
/
```

**Explicación:** El comando `pwd` muestra la ruta del directorio de trabajo actual. En este caso, la shell inició en el directorio raíz `/`.

**Reflexión:** Este resultado confirmó que al ingresar al contenedor se estaba trabajando desde la raíz de su propio sistema de archivos.

### Comando cat /etc/os-release

**Qué se hizo:** Se consultó la información de la distribución de Linux presente dentro del contenedor.

**Comando ejecutado:**

```bash
cat /etc/os-release
```

**Resultado obtenido:**

```text
PRETTY_NAME="Ubuntu 26.04.1 LTS"
NAME="Ubuntu"
VERSION_ID="26.04"
VERSION="26.04.1 LTS (Resolute Raccoon)"
VERSION_CODENAME=resolute
ID=ubuntu
ID_LIKE=debian
HOME_URL="https://www.ubuntu.com/"
SUPPORT_URL="https://help.ubuntu.com/"
BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
UBUNTU_CODENAME=resolute
LOGO=ubuntu-logo
```

**Explicación:** El archivo `/etc/os-release` contiene información que identifica la distribución de Linux presente en el entorno. En este caso, el contenedor utilizó Ubuntu 26.04.1 LTS, con nombre en código `Resolute Raccoon`.

**Reflexión:** Este resultado mostró que el entorno dentro del contenedor se presenta como Ubuntu y contiene sus archivos y herramientas de espacio de usuario. Sin embargo, esto no implica que exista un sistema operativo virtualizado completo, ya que el contenedor comparte el kernel con el host.

## Paso: exit

**Qué se hizo:** Se salió de la shell interactiva del contenedor.

**Comando ejecutado:**

```bash
exit
```

**Resultado obtenido:**

```text
exit
```

**Explicación:** El comando `exit` terminó la shell Bash que se estaba ejecutando como proceso principal del contenedor.

**Reflexión:** Como `bash` era el proceso principal del contenedor, al cerrarlo el contenedor dejó de ejecutarse. Por esta razón, posteriormente apareció con estado `Exited (0)`.

## Paso: docker ps -a

**Qué se hizo:** Se listaron todos los contenedores existentes para verificar el estado del contenedor de Ubuntu.

**Comando ejecutado:**

```bash
docker ps -a
```

**Explicación (para qué sirve el comando):** La opción `-a` permite mostrar tanto los contenedores activos como los que ya finalizaron su ejecución.

**Resultado obtenido:**

```text
CONTAINER ID   IMAGE         COMMAND    CREATED              STATUS                      PORTS     NAMES
4150f881096b   ubuntu        "bash"     About a minute ago   Exited (0) 11 seconds ago             stupefied_bassi
15c41e0e4d34   hello-world   "/hello"   53 minutes ago       Exited (0) 53 minutes ago             clever_merkle
f5ced7f9a653   hello-world   "/hello"   34 hours ago         Exited (0) 34 hours ago               amazing_einstein
```

**Reflexión:** El contenedor de Ubuntu apareció con el identificador `4150f881096b`, utilizando la imagen `ubuntu` y ejecutando el comando `bash`. Su estado `Exited (0)` confirmó que terminó correctamente después de salir de la shell interactiva. También se observó que el contenedor sigue existiendo aunque ya no esté ejecutándose.

## Diferencia entre una imagen y un contenedor

Una imagen de Docker es una plantilla que contiene los archivos y configuraciones necesarias para crear un entorno. No se ejecuta por sí misma y puede utilizarse para crear varios contenedores.

Un contenedor es una instancia creada a partir de una imagen. Puede encontrarse ejecutándose o detenido y tiene su propio estado durante su ciclo de vida.

En este ejercicio, `ubuntu:latest` corresponde a la imagen almacenada localmente, mientras que `4150f881096b` corresponde al contenedor creado a partir de esa imagen.

## Preguntas de reflexión

1. **¿La imagen Ubuntu es lo mismo que una máquina virtual Ubuntu?**

   No. La imagen de Ubuntu utilizada por Docker no corresponde a una máquina virtual completa. Contiene los archivos y herramientas necesarios para proporcionar un entorno Ubuntu, pero no incluye un kernel independiente ni virtualiza completamente el hardware. El contenedor utiliza el kernel del sistema anfitrión.

2. **¿Por qué el contenedor puede parecer un sistema Linux si no es una máquina virtual completa?**

   Porque el contenedor incluye gran parte del espacio de usuario de Linux, como directorios, comandos, bibliotecas y archivos de configuración. Esto hace que al interactuar con él se tenga una experiencia similar a utilizar un sistema Linux. Sin embargo, el contenedor no tiene un kernel propio, por lo que no constituye una máquina virtual completa.

3. **¿Qué significa que el contenedor comparta el kernel con el host?**

   Significa que los procesos que se ejecutan dentro del contenedor utilizan el mismo kernel Linux que utiliza la máquina anfitriona. Docker aísla estos procesos y sus recursos para que parezcan encontrarse en un entorno separado, pero no inicia un sistema operativo completo con su propio kernel.

4. **¿Qué diferencia hay entre una imagen descargada y un contenedor creado?**

   Una imagen descargada es una plantilla almacenada localmente que puede utilizarse múltiples veces para crear contenedores. Un contenedor creado es una instancia específica de esa imagen, con su propio identificador, nombre, estado y sistema de archivos asociado durante su existencia.

   En este ejercicio, la imagen `ubuntu:latest` quedó almacenada localmente después de ejecutar `docker pull ubuntu`, mientras que el contenedor `4150f881096b` fue creado posteriormente mediante `docker run -it ubuntu bash`.

---

# Parte 4: administración básica de contenedores

## Administración de contenedores

## Paso: creación de un contenedor con nombre

**Qué se hizo:** Se creó y ejecutó un nuevo contenedor basado en Ubuntu, asignándole manualmente el nombre `mi-ubuntu`.

**Comando ejecutado:**

```bash
docker run -it --name mi-ubuntu ubuntu bash
```

**Explicación (para qué sirve el comando):** El comando `docker run` crea un nuevo contenedor a partir de una imagen y lo ejecuta. Las opciones `-it` permiten utilizarlo de forma interactiva mediante una terminal, mientras que `--name mi-ubuntu` permite asignar un nombre específico al contenedor.

Asignar un nombre facilita la administración del contenedor, ya que permite utilizar `mi-ubuntu` en los comandos posteriores en lugar de tener que utilizar su identificador.

**Resultado obtenido:**

```text
root@610775a77470:/#
```

**Reflexión:** En la Parte 3 Docker había generado automáticamente un nombre para el contenedor. En este caso se utilizó `--name` para definir el nombre `mi-ubuntu`. Esto facilita identificar y administrar un contenedor cuando existen varios dentro del sistema.

## Paso: creación de un archivo dentro del contenedor

**Qué se hizo:** Se creó un archivo llamado `mensaje.txt` dentro del contenedor con un mensaje de prueba.

**Comando ejecutado:**

```bash
echo "Hola desde el contenedor" > mensaje.txt
```

**Explicación (para qué sirve el comando):** El comando `echo` genera el texto indicado y el operador `>` redirige esa salida hacia un archivo. En este caso se creó `mensaje.txt` dentro del sistema de archivos del contenedor.

**Resultado obtenido:**

El comando no mostró una salida en pantalla, ya que el texto fue redirigido al archivo `mensaje.txt`.

## Paso: verificación del archivo

**Qué se hizo:** Se comprobó que el archivo había sido creado correctamente y que contenía el mensaje esperado.

**Comando ejecutado:**

```bash
cat mensaje.txt
```

**Resultado obtenido:**

```text
Hola desde el contenedor
```

**Explicación:** El comando `cat` permitió mostrar en la terminal el contenido del archivo `mensaje.txt`.

**Reflexión:** El resultado confirmó que el archivo se creó correctamente dentro del sistema de archivos del contenedor. Este archivo permitió posteriormente comprobar qué ocurre con los datos cuando un contenedor se detiene, se vuelve a iniciar y finalmente se elimina.

## Paso: salida del contenedor

**Comando ejecutado:**

```bash
exit
```

**Resultado obtenido:**

```text
exit
```

**Explicación:** Al ejecutar `exit`, se cerró la shell Bash que funcionaba como proceso principal del contenedor. Como consecuencia, el contenedor dejó de ejecutarse.

## Paso: verificación del contenedor detenido

**Qué se hizo:** Se consultaron todos los contenedores para comprobar el estado de `mi-ubuntu`.

**Comando ejecutado:**

```bash
docker ps -a
```

**Resultado obtenido:**

```text
CONTAINER ID   IMAGE         COMMAND    CREATED             STATUS                         PORTS     NAMES
610775a77470   ubuntu        "bash"     48 seconds ago      Exited (0) 15 seconds ago                mi-ubuntu
4150f881096b   ubuntu        "bash"     19 minutes ago      Exited (0) 17 minutes ago                stupefied_bassi
15c41e0e4d34   hello-world   "/hello"   About an hour ago   Exited (0) About an hour ago             clever_merkle
f5ced7f9a653   hello-world   "/hello"   34 hours ago        Exited (0) 34 hours ago                  amazing_einstein
```

**Reflexión:** El contenedor `mi-ubuntu` seguía existiendo, pero aparecía con estado `Exited (0)`. Esto muestra que detener un contenedor no significa eliminarlo, ya que Docker conserva su información y su sistema de archivos mientras el contenedor exista.

## Paso: reinicio del contenedor

**Qué se hizo:** Se volvió a iniciar el contenedor `mi-ubuntu` que había quedado detenido.

**Comando ejecutado:**

```bash
docker start mi-ubuntu
```

**Resultado obtenido:**

```text
mi-ubuntu
```

**Explicación (para qué sirve el comando):** El comando `docker start` inicia un contenedor que ya existe pero se encuentra detenido. A diferencia de `docker run`, este comando no crea un contenedor nuevo.

**Reflexión:** El contenedor pudo iniciarse nuevamente conservando su mismo nombre, identificador y sistema de archivos. Esto demuestra que un contenedor detenido puede reanudarse sin necesidad de crear uno nuevo.

## Diferencia entre docker run y docker start

`docker run` crea un **nuevo contenedor** a partir de una imagen y posteriormente lo ejecuta.

En cambio, `docker start` inicia un **contenedor existente** que se encuentra detenido.

Por ejemplo:

```bash
docker run -it --name mi-ubuntu ubuntu bash
```

creó el contenedor `mi-ubuntu`, mientras que:

```bash
docker start mi-ubuntu
```

volvió a iniciar ese mismo contenedor después de haber sido detenido.

## Paso: acceso al contenedor con docker exec

**Qué se hizo:** Se abrió una nueva shell Bash dentro del contenedor `mi-ubuntu` que se encontraba en ejecución.

**Comando ejecutado:**

```bash
docker exec -it mi-ubuntu bash
```

**Resultado obtenido:**

```text
root@610775a77470:/#
```

**Explicación (para qué sirve el comando):** `docker exec` permite ejecutar un comando dentro de un contenedor que ya está en ejecución. En este caso, las opciones `-it` permitieron abrir una terminal interactiva y el comando `bash` inició una nueva shell dentro de `mi-ubuntu`.

A diferencia de `docker run`, `docker exec` no crea otro contenedor, sino que ejecuta un nuevo proceso dentro de uno que ya existe.

## Paso: comprobación de persistencia del archivo

**Qué se hizo:** Se comprobó si `mensaje.txt` continuaba existiendo después de detener e iniciar nuevamente el contenedor.

**Comando ejecutado:**

```bash
cat mensaje.txt
```

**Resultado obtenido:**

```text
Hola desde el contenedor
```

**Reflexión:** El archivo continuaba existiendo después de detener y volver a iniciar el contenedor. Esto demuestra que detener un contenedor no elimina automáticamente los cambios realizados en su sistema de archivos. Mientras el mismo contenedor siga existiendo, esos datos permanecen asociados a él.

## Paso: detener el contenedor

**Qué se hizo:** Se detuvo el contenedor `mi-ubuntu`.

**Comando ejecutado:**

```bash
docker stop mi-ubuntu
```

**Resultado obtenido:**

```text
mi-ubuntu
```

**Explicación (para qué sirve el comando):** `docker stop` detiene un contenedor que se encuentra en ejecución, pero no lo elimina. El contenedor continúa registrado en Docker y puede iniciarse nuevamente mediante `docker start`.

## Paso: eliminar el contenedor

**Qué se hizo:** Se eliminó el contenedor `mi-ubuntu` después de detenerlo.

**Comando ejecutado:**

```bash
docker rm mi-ubuntu
```

**Resultado obtenido:**

```text
mi-ubuntu
```

**Explicación (para qué sirve el comando):** El comando `docker rm` elimina un contenedor existente. A diferencia de `docker stop`, después de eliminarlo ya no puede reiniciarse mediante `docker start`.

Al eliminar el contenedor también se elimina su capa de escritura, por lo que el archivo `mensaje.txt` que se había creado dentro de este contenedor deja de estar disponible junto con él.

## Diferencia entre detener y eliminar un contenedor

Detener un contenedor mediante:

```bash
docker stop mi-ubuntu
```

finaliza su ejecución, pero mantiene el contenedor y sus cambios almacenados. Esto permite volver a iniciarlo posteriormente.

Eliminarlo mediante:

```bash
docker rm mi-ubuntu
```

borra el contenedor de Docker. Después de esto, ya no puede reiniciarse y los datos almacenados únicamente en su sistema de archivos dejan de estar disponibles.

## Paso: verificación final

**Qué se hizo:** Se comprobó que `mi-ubuntu` había sido eliminado correctamente.

**Comando ejecutado:**

```bash
docker ps -a
```

**Resultado obtenido:**

```text
CONTAINER ID   IMAGE         COMMAND    CREATED             STATUS                         PORTS     NAMES
4150f881096b   ubuntu        "bash"     20 minutes ago      Exited (0) 19 minutes ago                stupefied_bassi
15c41e0e4d34   hello-world   "/hello"   About an hour ago   Exited (0) About an hour ago             clever_merkle
f5ced7f9a653   hello-world   "/hello"   34 hours ago        Exited (0) 34 hours ago                  amazing_einstein
```

**Reflexión:** El contenedor `mi-ubuntu` ya no apareció en la lista de `docker ps -a`, lo que confirmó que fue eliminado correctamente. Los otros contenedores continuaron existiendo porque `docker rm` afectó únicamente al contenedor indicado.

## Qué ocurrió con el archivo creado dentro del contenedor

El archivo `mensaje.txt` permaneció disponible cuando el contenedor fue detenido y posteriormente iniciado nuevamente. Esto se comprobó al ingresar con `docker exec` y ejecutar:

```bash
cat mensaje.txt
```

obteniendo nuevamente:

```text
Hola desde el contenedor
```

Sin embargo, al ejecutar `docker rm mi-ubuntu`, el contenedor fue eliminado. Como `mensaje.txt` estaba almacenado únicamente dentro del sistema de archivos de ese contenedor y no se utilizó ningún volumen, el archivo dejó de estar disponible junto con el contenedor.

Este comportamiento permite diferenciar entre **detener un contenedor** y **eliminarlo**.

## Preguntas de reflexión de la Parte 4

1. **¿Qué ventaja tiene asignar nombres a los contenedores?**

   Asignar nombres permite identificar y administrar los contenedores de una forma más sencilla. En lugar de tener que recordar o copiar un identificador como `610775a77470`, se puede utilizar un nombre descriptivo como `mi-ubuntu` en comandos como `docker start`, `docker stop`, `docker exec` y `docker rm`.

2. **¿Qué diferencia hay entre crear un contenedor nuevo y reiniciar uno existente?**

   Crear un contenedor nuevo mediante `docker run` genera una nueva instancia a partir de una imagen, con su propio identificador, nombre y sistema de archivos. En cambio, iniciar nuevamente un contenedor existente mediante `docker start` conserva la misma instancia y los cambios que se hayan realizado previamente dentro de ella.

3. **¿Qué sucede con los datos creados dentro de un contenedor si este se elimina?**

   Los datos almacenados únicamente en el sistema de archivos del contenedor se eliminan junto con este. En este ejercicio, el archivo `mensaje.txt` permaneció mientras `mi-ubuntu` existía, incluso después de detenerlo y reiniciarlo. Sin embargo, al eliminar el contenedor con `docker rm`, ese archivo dejó de estar disponible.

   Para conservar información independientemente del ciclo de vida de un contenedor se pueden utilizar mecanismos de persistencia como los volúmenes de Docker, que serán utilizados posteriormente en el laboratorio.

4. **¿Por qué se dice que los contenedores son desechables?**

   Se dice que los contenedores son desechables porque pueden crearse, detenerse y eliminarse fácilmente a partir de una imagen. La imagen funciona como la base reproducible desde la cual se pueden generar nuevos contenedores cuando sea necesario.

   Por esta razón, no es recomendable depender del sistema de archivos interno de un contenedor para almacenar información importante de forma permanente. Los datos que deban sobrevivir a la eliminación del contenedor deben mantenerse fuera de él mediante mecanismos de persistencia.