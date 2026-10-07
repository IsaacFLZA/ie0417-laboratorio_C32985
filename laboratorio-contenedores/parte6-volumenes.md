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