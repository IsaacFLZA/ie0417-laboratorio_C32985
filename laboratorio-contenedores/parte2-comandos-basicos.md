# Parte 2: primer contenedor

## Paso: docker run hello-world

**Qué se hizo:** Se ejecutó el primer contenedor utilizando la imagen `hello-world` de Docker.

**Comando ejecutado:**

```bash
docker run hello-world
```

**Explicación (para qué sirve el comando):** El comando `docker run` permite crear y ejecutar un contenedor a partir de una imagen. En este caso se utilizó la imagen `hello-world`. Como la imagen no estaba disponible localmente, Docker la descargó automáticamente desde Docker Hub, creó un nuevo contenedor a partir de ella y ejecutó el programa `/hello`, que mostró un mensaje en la terminal.

**Resultado obtenido:**

```text
Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/
```

**Reflexión:** Este comando permitió comprobar de forma práctica cómo funciona el proceso básico de Docker. Al ejecutar una sola instrucción, Docker pudo buscar la imagen necesaria, descargarla, crear un contenedor y ejecutar el programa que contenía. También observé que no tuve que descargar la imagen manualmente antes de utilizarla, ya que `docker run` se encargó de hacerlo cuando no la encontró en el sistema.

## Paso: docker ps

**Qué se hizo:** Se consultaron los contenedores que se encontraban actualmente en ejecución.

**Comando ejecutado:**

```bash
docker ps
```

**Explicación (para qué sirve el comando):** Este comando muestra únicamente los contenedores que están ejecutándose en ese momento. Permite consultar información como el identificador del contenedor, la imagen utilizada, el comando que está ejecutando, su estado, los puertos publicados y el nombre asignado.

**Resultado obtenido:**

```text
CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES
```

**Reflexión:** El resultado no mostró ningún contenedor activo. Esto ocurre porque el contenedor creado con `hello-world` únicamente ejecuta el programa que imprime el mensaje y luego termina. Por lo tanto, cuando ejecuté `docker ps`, el contenedor ya había finalizado su ejecución y no aparecía en la lista.

## Paso: docker ps -a

**Qué se hizo:** Se consultaron todos los contenedores existentes, incluyendo los que ya habían terminado su ejecución.

**Comando ejecutado:**

```bash
docker ps -a
```

**Explicación (para qué sirve el comando):** La opción `-a` hace que `docker ps` muestre todos los contenedores existentes y no solamente los que se encuentran en ejecución. Esto permite observar también contenedores detenidos o que ya finalizaron su proceso.

**Resultado obtenido:**

```text
CONTAINER ID   IMAGE         COMMAND    CREATED          STATUS                      PORTS     NAMES
15c41e0e4d34   hello-world   "/hello"   53 seconds ago   Exited (0) 51 seconds ago             clever_merkle
f5ced7f9a653   hello-world   "/hello"   33 hours ago     Exited (0) 33 hours ago               amazing_einstein
```

**Reflexión:** A diferencia de `docker ps`, este comando sí mostró los contenedores creados con la imagen `hello-world`. Ambos aparecen con el estado `Exited (0)`, lo que indica que el programa dentro de ellos terminó correctamente y sin errores. También pude observar que Docker conserva los contenedores aunque hayan terminado su ejecución, hasta que sean eliminados explícitamente.

## Diferencia entre docker ps y docker ps -a

El comando `docker ps` muestra únicamente los contenedores que están actualmente en ejecución. En cambio, `docker ps -a` muestra todos los contenedores existentes, tanto los que están ejecutándose como los que ya finalizaron o fueron detenidos.

En este ejercicio, `docker ps` no mostró ningún contenedor porque `hello-world` ya había terminado. Sin embargo, `docker ps -a` sí mostró los dos contenedores creados anteriormente a partir de la imagen `hello-world`.

## Qué ocurrió cuando la imagen no estaba descargada

Al ejecutar:

```bash
docker run hello-world
```

Docker verificó si la imagen `hello-world` estaba disponible localmente. Al no encontrarla, el Docker daemon la descargó automáticamente desde Docker Hub. Después utilizó esa imagen para crear el contenedor y ejecutar el programa `/hello`.

Esto demuestra que no siempre es necesario ejecutar manualmente `docker pull` antes de utilizar una imagen, ya que `docker run` puede descargarla automáticamente cuando no existe en el sistema.

## Preguntas de reflexión

1. **¿Qué es la imagen hello-world?**

   `hello-world` es una imagen pequeña preparada para comprobar que Docker puede ejecutar correctamente un contenedor. Contiene un programa sencillo que imprime el mensaje `Hello from Docker!` y explica de manera resumida los pasos que Docker realizó para ejecutarlo. En este laboratorio sirve como una primera prueba del flujo completo entre el cliente de Docker, el daemon, la imagen y el contenedor.

2. **¿El contenedor quedó ejecutándose después de imprimir el mensaje?**

   No. El contenedor ejecutó el programa `/hello`, imprimió el mensaje en la terminal y después terminó. Esto se puede comprobar porque no apareció al ejecutar `docker ps` y en `docker ps -a` su estado apareció como `Exited (0)`.

3. **¿Por qué aparece en docker ps -a pero no necesariamente en docker ps?**

   Porque `docker ps` solamente muestra contenedores que están ejecutándose actualmente, mientras que `docker ps -a` también incluye los que ya terminaron. Como el proceso de `hello-world` finaliza después de imprimir su mensaje, el contenedor deja de estar activo pero continúa existiendo en Docker hasta que sea eliminado.

4. **¿Qué demuestra este primer ejemplo sobre Docker?**

   Este ejemplo demuestra el flujo básico de trabajo de Docker. El cliente envía la orden al daemon, el daemon obtiene la imagen si todavía no está disponible, crea un contenedor a partir de ella, ejecuta el programa contenido en la imagen y devuelve su salida a la terminal. También muestra que un contenedor no tiene que permanecer ejecutándose permanentemente: puede realizar una tarea específica y finalizar una vez que esta termina.