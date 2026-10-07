# Parte 14: limpieza del ambiente

## Limpieza del ambiente

## Paso: listar los contenedores existentes

**Qué se hizo:** Se revisaron todos los contenedores existentes antes de realizar la limpieza.

**Comando ejecutado:**

```bash
docker ps -a
```

**Explicación (para qué sirve el comando):** `docker ps -a` muestra todos los contenedores, tanto los que están en ejecución como los que se encuentran detenidos.

**Resultado obtenido:**

```text
CONTAINER ID   IMAGE         COMMAND    CREATED        STATUS                    PORTS     NAMES
4150f881096b   ubuntu        "bash"     6 hours ago    Exited (0) 6 hours ago              stupefied_bassi
15c41e0e4d34   hello-world   "/hello"   7 hours ago    Exited (0) 7 hours ago              clever_merkle
f5ced7f9a653   hello-world   "/hello"   40 hours ago   Exited (0) 40 hours ago             amazing_einstein
```

**Reflexión:** La salida mostró que quedaban tres contenedores detenidos de partes anteriores del laboratorio. Estos contenedores ya no estaban siendo utilizados, por lo que podían eliminarse de forma segura durante la limpieza.

## Paso: listar las imágenes disponibles

**Qué se hizo:** Se revisaron las imágenes almacenadas localmente antes de ejecutar la limpieza.

**Comando ejecutado:**

```bash
docker images
```

**Explicación (para qué sirve el comando):** `docker images` permite listar las imágenes disponibles en el sistema, junto con su identificador y el espacio que ocupan.

**Resultado obtenido:**

```text
                                                              i Info →   U  In Use
IMAGE                    ID             DISK USAGE   CONTENT SIZE   EXTRA
curlimages/curl:latest   58adaa4e8dca       35.4MB         10.7MB        
hello-world:latest       5e2309035332       25.9kB         9.49kB    U   
laboratorio-flask:1.0    28ef4387a888        211MB         51.4MB        
nginx:latest             f9ea18bfa4fa        243MB         66.7MB        
redis:latest             2c2dff791878        213MB         57.6MB        
ubuntu:latest            f144425ff09b        162MB         45.6MB    U   
```

**Reflexión:** Se observaron varias imágenes utilizadas durante las diferentes partes del laboratorio, incluyendo Ubuntu, Nginx, Redis, Curl y la imagen personalizada de Flask.

## Paso: listar los volúmenes

**Qué se hizo:** Se revisaron los volúmenes existentes antes de la limpieza.

**Comando ejecutado:**

```bash
docker volume ls
```

**Explicación (para qué sirve el comando):** `docker volume ls` muestra los volúmenes administrados por Docker que existen en el sistema.

**Resultado obtenido:**

```text
DRIVER    VOLUME NAME
local     datos-lab
```

**Reflexión:** El volumen `datos-lab`, creado durante la práctica de persistencia, todavía se encontraba disponible.

## Paso: listar las redes

**Qué se hizo:** Se revisaron las redes existentes en Docker.

**Comando ejecutado:**

```bash
docker network ls
```

**Explicación (para qué sirve el comando):** `docker network ls` permite listar las redes disponibles en Docker.

**Resultado obtenido:**

```text
NETWORK ID     NAME      DRIVER    SCOPE
03bd677d8cd0   bridge    bridge    local
36cd52215daf   host      host      local
0fa8a70695aa   none      null      local
```

**Reflexión:** Solo permanecían las redes predeterminadas de Docker. Las redes personalizadas creadas durante las prácticas anteriores ya habían sido eliminadas.

## Paso: eliminar contenedores detenidos

**Qué se hizo:** Se eliminaron todos los contenedores detenidos que ya no eran necesarios.

**Comando ejecutado:**

```bash
docker container prune
```

**Explicación (para qué sirve el comando):** `docker container prune` elimina los contenedores que se encuentran detenidos y que ya no están siendo utilizados.

Antes de realizar la eliminación, Docker solicita confirmación.

**Resultado obtenido:**

```text
WARNING! This will remove all stopped containers.
Are you sure you want to continue? [y/N] y
Deleted Containers:
4150f881096bfd05e868635b1d8f383485f3c8df1d45267147288b339498f0d6
15c41e0e4d3415fd223de8fa4554bcb446ab0438b85f6c915e858ba9ea5d5c37
f5ced7f9a653cce09645d699c00294d87f6f81fa652f5edb24ca9e0f3b3015bf

Total reclaimed space: 20.48kB
```

**Reflexión:** Docker eliminó los tres contenedores detenidos que habían quedado de partes anteriores del laboratorio y recuperó `20.48 kB` de espacio.

## Paso: eliminar imágenes no utilizadas

**Qué se hizo:** Se intentó eliminar imágenes sin referencia que ya no fueran necesarias.

**Comando ejecutado:**

```bash
docker image prune
```

**Explicación (para qué sirve el comando):** `docker image prune` elimina imágenes colgantes, es decir, imágenes que no tienen una etiqueta asociada y que no son utilizadas por ningún contenedor.

**Resultado obtenido:**

```text
WARNING! This will remove all dangling images.
Are you sure you want to continue? [y/N] y
Total reclaimed space: 0B
```

**Reflexión:** No había imágenes colgantes para eliminar, por lo que Docker no recuperó espacio en este paso.

## Paso: eliminar volúmenes no utilizados

**Qué se hizo:** Se ejecutó una limpieza de volúmenes que no estaban siendo utilizados.

**Comando ejecutado:**

```bash
docker volume prune
```

**Explicación (para qué sirve el comando):** `docker volume prune` elimina volúmenes locales que Docker considera seguros para limpiar y que no están siendo utilizados por contenedores.

**Resultado obtenido:**

```text
WARNING! This will remove anonymous local volumes not used by at least one container.
Are you sure you want to continue? [y/N] y
Total reclaimed space: 0B
```

**Reflexión:** No se eliminó ningún volumen y no se recuperó espacio. El volumen `datos-lab` permaneció disponible después de la limpieza.

## Paso: revisar el uso de espacio de Docker

**Qué se hizo:** Se revisó cuánto espacio estaban utilizando los diferentes recursos de Docker después de realizar la limpieza.

**Comando ejecutado:**

```bash
docker system df
```

**Explicación (para qué sirve el comando):** `docker system df` muestra un resumen del espacio utilizado por imágenes, contenedores, volúmenes y caché de construcción.

También indica cuánto espacio podría recuperarse eliminando recursos que no se encuentran activos.

**Resultado obtenido:**

```text
TYPE            TOTAL     ACTIVE    SIZE      RECLAIMABLE
Images          6         0         629.4MB   511.9MB (81%)
Containers      0         0         0B        0B
Local Volumes   1         0         33B       33B (100%)
Build Cache     11        0         211.6MB   28.67kB
```

**Reflexión:** Después de la limpieza no quedaron contenedores, pero todavía permanecían seis imágenes, un volumen y la caché de construcción.

La mayor cantidad de espacio recuperable correspondía a las imágenes, con `511.9 MB` disponibles para liberar si se eliminaran recursos adicionales.

## Recursos que quedaron creados

Después de completar las prácticas anteriores se encontraron los siguientes recursos:

- Tres contenedores detenidos.
- Seis imágenes de Docker.
- Un volumen llamado `datos-lab`.
- Las redes predeterminadas de Docker.
- Caché generada durante la construcción de imágenes.

Los tres contenedores detenidos fueron eliminados durante esta parte.

## Comandos de limpieza ejecutados

Los comandos utilizados para realizar la limpieza fueron:

```bash
docker container prune
docker image prune
docker volume prune
```

También se utilizó:

```bash
docker system df
```

para revisar el estado del espacio utilizado después de la limpieza.

No se ejecutó:

```bash
docker system prune
```

porque era un paso opcional y se prefirió realizar únicamente las operaciones específicas indicadas para contenedores, imágenes y volúmenes.

## Diferencia entre limpiar contenedores, imágenes y volúmenes

Los contenedores, imágenes y volúmenes representan recursos diferentes dentro de Docker.

Los contenedores son instancias creadas a partir de imágenes. Si un contenedor está detenido y ya no se necesita, puede eliminarse sin borrar necesariamente la imagen utilizada para crearlo.

Las imágenes funcionan como plantillas para crear contenedores. Eliminar una imagen libera el espacio que ocupa, pero si posteriormente se necesita nuevamente será necesario descargarla o reconstruirla.

Los volúmenes se utilizan para almacenar datos de forma independiente a los contenedores. Por esta razón, deben eliminarse con mayor cuidado, ya que podrían contener información que se desea conservar.

## Preguntas de reflexión

1. **¿Por qué Docker puede consumir mucho espacio en disco?**

   Porque Docker almacena imágenes, contenedores, volúmenes y caché de construcción.

   Con el tiempo, si se crean muchos contenedores o se construyen varias imágenes, estos recursos pueden acumularse y ocupar una cantidad considerable de almacenamiento.

   En este ejercicio, `docker system df` mostró que las imágenes ocupaban `629.4 MB` y la caché de construcción `211.6 MB`.

2. **¿Qué diferencia hay entre eliminar un contenedor y eliminar una imagen?**

   Eliminar un contenedor borra una instancia creada a partir de una imagen.

   La imagen puede seguir existiendo y utilizarse posteriormente para crear nuevos contenedores.

   En cambio, eliminar una imagen borra la plantilla almacenada localmente. Si se necesita nuevamente, será necesario descargarla o construirla otra vez.

3. **¿Por qué se debe tener cuidado al eliminar volúmenes?**

   Porque los volúmenes pueden contener información persistente que no depende del ciclo de vida de los contenedores.

   Por ejemplo, durante este laboratorio el volumen `datos-lab` almacenó un archivo que permaneció disponible incluso después de eliminar el contenedor original.

   Si un volumen con información importante se elimina, esos datos también pueden perderse.

4. **¿Qué buenas prácticas aplicaría para mantener limpio su ambiente local?**

   Revisaría periódicamente los contenedores, imágenes y volúmenes existentes antes de eliminarlos.

   También eliminaría contenedores detenidos que ya no sean necesarios y evitaría mantener imágenes antiguas o recursos que no se estén utilizando.

   Antes de eliminar volúmenes verificaría siempre que no contengan información importante.

   Además, utilizaría comandos como `docker system df` para conocer el espacio ocupado antes de realizar una limpieza.