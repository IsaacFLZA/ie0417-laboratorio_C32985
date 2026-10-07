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