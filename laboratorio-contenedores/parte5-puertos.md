# Parte 7: publicación de puertos

## Paso: docker run con el puerto 5000

**Qué se hizo:** Se ejecutó la aplicación Flask dentro de un contenedor llamado `app-puertos`, publicando el puerto `5000` del contenedor en el puerto `5000` del host.

**Comando ejecutado:**

```bash
docker run --name app-puertos -p 5000:5000 laboratorio-flask:1.0
```

**Explicación (para qué sirve el comando):** El comando `docker run` crea y ejecuta un contenedor a partir de la imagen `laboratorio-flask:1.0`. La opción `--name app-puertos` asigna un nombre al contenedor y la opción `-p 5000:5000` publica el puerto `5000` del contenedor en el puerto `5000` del host.

El formato utilizado por Docker es:

```text
-p PUERTO_HOST:PUERTO_CONTENEDOR
```

Por lo tanto, en:

```text
-p 5000:5000
```

el primer `5000` corresponde al puerto del host y el segundo `5000` corresponde al puerto del contenedor.

**Resultado obtenido:**

```text
* Serving Flask app 'app'
* Debug mode: off
WARNING: This is a development server. Do not use it in a production deployment. Use a production WSGI server instead.
* Running on all addresses (0.0.0.0)
* Running on http://127.0.0.1:5000
* Running on http://172.17.0.2:5000
Press CTRL+C to quit
172.17.0.1 - - [07/Oct/2026 19:26:53] "GET / HTTP/1.1" 200 -
172.17.0.1 - - [07/Oct/2026 19:26:53] "GET /favicon.ico HTTP/1.1" 404 -
172.17.0.1 - - [07/Oct/2026 19:29:10] "GET /info HTTP/1.1" 200 -
```

Debido a que el laboratorio se realizó en GitHub Codespaces, el acceso desde el navegador se hizo mediante la URL reenviada por Codespaces para el puerto `5000`, en lugar de utilizar directamente `http://localhost:5000`.

La página principal se mostró correctamente:

![Aplicación Flask funcionando](evidencias/parte7/puertoNormal.png)

También se verificó la ruta `/info`:

![Ruta info de la aplicación](evidencias/parte7/info.png)

**Reflexión:** La aplicación respondió correctamente tanto en la ruta principal `/` como en `/info`. Los códigos `200` observados en la terminal indican que ambas solicitudes fueron atendidas correctamente. Esto permitió comprobar que el mapeo `5000:5000` hizo accesible desde el host la aplicación que escucha en el puerto `5000` dentro del contenedor.

## Paso: detener y eliminar el contenedor app-puertos

**Qué se hizo:** Se detuvo y posteriormente se eliminó el contenedor `app-puertos`.

**Comandos ejecutados:**

```bash
docker stop app-puertos
docker rm app-puertos
```

**Explicación (para qué sirven los comandos):** `docker stop` detiene un contenedor que está en ejecución, mientras que `docker rm` elimina un contenedor que ya se encuentra detenido.

**Resultado obtenido:**

```text
app-puertos
app-puertos
```

**Reflexión:** El contenedor se detuvo y eliminó correctamente. Esto permitió liberar el puerto utilizado y continuar con la siguiente prueba del laboratorio.

## Paso: docker run con el puerto 8080

**Qué se hizo:** Se ejecutó nuevamente la aplicación Flask en un segundo contenedor llamado `app-puertos-2`, publicando el puerto `5000` del contenedor en el puerto `8080` del host.

**Comando ejecutado:**

```bash
docker run --name app-puertos-2 -p 8080:5000 laboratorio-flask:1.0
```

**Explicación (para qué sirve el comando):** En este caso, la opción:

```text
-p 8080:5000
```

indica que el puerto `8080` pertenece al host y se conecta con el puerto `5000` del contenedor.

La aplicación Flask no cambió su configuración y continuó escuchando internamente en el puerto `5000`. Únicamente cambió el puerto utilizado desde el host para acceder a ella.

**Resultado obtenido:**

```text
* Serving Flask app 'app'
* Debug mode: off
WARNING: This is a development server. Do not use it in a production deployment. Use a production WSGI server instead.
* Running on all addresses (0.0.0.0)
* Running on http://127.0.0.1:5000
* Running on http://172.17.0.2:5000
Press CTRL+C to quit
172.17.0.1 - - [07/Oct/2026 19:31:08] "GET / HTTP/1.1" 200 -
172.17.0.1 - - [07/Oct/2026 19:31:08] "GET /favicon.ico HTTP/1.1" 404 -
```

**Reflexión:** La aplicación funcionó correctamente utilizando el puerto `8080` del host, aunque Flask continuó ejecutándose en el puerto `5000` dentro del contenedor. Esto demuestra que el puerto del host y el puerto del contenedor no tienen que ser iguales.

## Paso: detener y eliminar el contenedor app-puertos-2

**Qué se hizo:** Se detuvo y eliminó el segundo contenedor después de completar la prueba.

**Comandos ejecutados:**

```bash
docker stop app-puertos-2
docker rm app-puertos-2
```

**Resultado obtenido:**

```text
app-puertos-2
app-puertos-2
```

**Reflexión:** El segundo contenedor se detuvo y eliminó correctamente, dejando el entorno preparado para continuar con las siguientes partes del laboratorio.

## Diferencia entre -p 5000:5000 y -p 8080:5000

En ambos casos, el segundo número corresponde al puerto dentro del contenedor y permanece en `5000`, porque ese es el puerto en el que escucha la aplicación Flask.

En:

```text
-p 5000:5000
```

el puerto `5000` del host se conecta con el puerto `5000` del contenedor.

En:

```text
-p 8080:5000
```

el puerto `8080` del host se conecta con el puerto `5000` del contenedor.

Por lo tanto, el puerto del host puede cambiar sin necesidad de modificar el puerto interno utilizado por la aplicación.

## Preguntas de reflexión

1. **¿Por qué no basta con que la aplicación escuche en el puerto 5000 dentro del contenedor?**

   Porque el puerto dentro del contenedor pertenece a su propio entorno de red. Para poder acceder a la aplicación desde el host, es necesario publicar ese puerto mediante la opción `-p`.

2. **¿Qué función cumple el mapeo de puertos?**

   El mapeo de puertos permite conectar un puerto del host con un puerto dentro del contenedor. De esta forma, las solicitudes que llegan al puerto publicado del host son dirigidas hacia el puerto donde escucha la aplicación dentro del contenedor.

3. **¿Cuál es la diferencia entre el puerto del host y el puerto del contenedor?**

   El puerto del host es el puerto utilizado desde fuera del contenedor para acceder al servicio. El puerto del contenedor es el puerto en el que la aplicación escucha internamente.

   Por ejemplo, en:

   ```text
   -p 8080:5000
   ```

   `8080` corresponde al host y `5000` corresponde al contenedor.

4. **¿Qué pasaría si dos contenedores intentan usar el mismo puerto del host?**

   Docker no podría publicar el mismo puerto del host para ambos contenedores al mismo tiempo. Uno de ellos tendría que utilizar otro puerto del host, por ejemplo `8080`, aunque ambos pueden seguir utilizando internamente el mismo puerto `5000`.


   # Parte 8: logs e inspección de contenedores

## Logs e inspección

## Paso: ejecutar el contenedor en segundo plano

**Qué se hizo:** Se ejecutó la aplicación Flask dentro de un contenedor llamado `app-logs` en segundo plano, publicando el puerto `5000` del contenedor en el puerto `5000` del host.

**Comando ejecutado:**

```bash
docker run -d --name app-logs -p 5000:5000 laboratorio-flask:1.0
```

**Explicación (para qué sirve el comando):** La opción `-d` permite ejecutar el contenedor en modo desacoplado o en segundo plano. Esto hace que el contenedor continúe ejecutándose sin mantener ocupada la terminal.

La opción `--name app-logs` asigna el nombre `app-logs` al contenedor y `-p 5000:5000` publica el puerto `5000` para poder acceder a la aplicación.

**Resultado obtenido:**

```text
4a4913e9b05cb79dd8601102ef1bceaf30c616103e5c380903b9de9e23454487
```

**Reflexión:** Al utilizar `-d`, Docker devolvió el identificador del contenedor y permitió seguir utilizando la terminal mientras la aplicación continuaba ejecutándose en segundo plano.

## Paso: docker logs

**Qué se hizo:** Se consultaron los mensajes generados por la aplicación dentro del contenedor.

**Comando ejecutado:**

```bash
docker logs app-logs
```

**Explicación (para qué sirve el comando):** El comando `docker logs` muestra la salida estándar y los mensajes generados por el proceso principal del contenedor.

En este caso permitió observar los mensajes de inicio de Flask y las solicitudes HTTP realizadas a la aplicación.

**Resultado obtenido:**

```text
* Serving Flask app 'app'
* Debug mode: off
WARNING: This is a development server. Do not use it in a production deployment. Use a production WSGI server instead.
* Running on all addresses (0.0.0.0)
* Running on http://127.0.0.1:5000
* Running on http://172.17.0.2:5000
Press CTRL+C to quit
172.17.0.1 - - [07/Oct/2026 20:00:29] "GET / HTTP/1.1" 200 -
172.17.0.1 - - [07/Oct/2026 20:00:29] "GET /favicon.ico HTTP/1.1" 404 -
```

**Reflexión:** Los logs permitieron comprobar que Flask inició correctamente y que la aplicación recibió una solicitud a la ruta `/`.

El código `200` confirmó que la solicitud fue atendida correctamente. El `404` correspondiente a `/favicon.ico` se debe a que la aplicación no tiene definido un ícono y no afecta su funcionamiento.

## Paso: docker logs -f

**Qué se hizo:** Se siguieron los logs del contenedor en tiempo real mientras se realizaron nuevas solicitudes a la aplicación.

**Comando ejecutado:**

```bash
docker logs -f app-logs
```

**Explicación (para qué sirve el comando):** La opción `-f` mantiene el comando activo y muestra nuevos mensajes conforme son generados por el contenedor.

Esto permite observar en tiempo real el comportamiento de una aplicación mientras está ejecutándose.

**Resultado obtenido:**

```text
* Serving Flask app 'app'
* Debug mode: off
WARNING: This is a development server. Do not use it in a production deployment. Use a production WSGI server instead.
* Running on all addresses (0.0.0.0)
* Running on http://127.0.0.1:5000
* Running on http://172.17.0.2:5000
Press CTRL+C to quit
172.17.0.1 - - [07/Oct/2026 20:00:29] "GET / HTTP/1.1" 200 -
172.17.0.1 - - [07/Oct/2026 20:00:29] "GET /favicon.ico HTTP/1.1" 404 -
172.17.0.1 - - [07/Oct/2026 20:01:31] "GET / HTTP/1.1" 200 -
172.17.0.1 - - [07/Oct/2026 20:01:31] "GET /favicon.ico HTTP/1.1" 404 -
172.17.0.1 - - [07/Oct/2026 20:01:43] "GET /info HTTP/1.1" 200 -
```

**Reflexión:** Mientras `docker logs -f` permanecía activo, se realizaron nuevas solicitudes a `/` y `/info`. Estas aparecieron inmediatamente en la terminal, demostrando que el comando permite observar los logs en tiempo real.

El comando se mantiene ejecutándose mientras se sigan los logs y se puede salir de esta visualización utilizando `Ctrl+C` sin detener el contenedor.

## Paso: docker inspect

**Qué se hizo:** Se inspeccionó la configuración y el estado interno del contenedor `app-logs`.

**Comando ejecutado:**

```bash
docker inspect app-logs
```

**Explicación (para qué sirve el comando):** `docker inspect` muestra información detallada de un contenedor en formato JSON. Entre los datos disponibles se encuentran el estado del contenedor, la imagen utilizada, el comando ejecutado, las variables de entorno, la configuración de red, los puertos, el directorio de trabajo y otros parámetros internos.

**Resultado obtenido:**

De la salida obtenida se identificaron, entre otros, los siguientes datos:

```text
"Name": "/app-logs"

"State": {
    "Status": "running",
    "Running": true
}

"Image": "laboratorio-flask:1.0"

"Cmd": [
    "python",
    "app.py"
]

"WorkingDir": "/app"
```

También se observó la configuración del puerto:

```text
"5000/tcp": [
    {
        "HostIp": "0.0.0.0",
        "HostPort": "5000"
    }
]
```

y la configuración de red:

```text
"Gateway": "172.17.0.1"
"IPAddress": "172.17.0.2"
```

**Reflexión:** `docker inspect` permitió obtener información mucho más detallada que otros comandos. Se pudo confirmar que el contenedor estaba en ejecución, que utilizaba la imagen `laboratorio-flask:1.0`, que ejecutaba `python app.py`, que trabajaba desde `/app` y que el puerto `5000` estaba publicado correctamente.

También se pudo observar que Docker asignó al contenedor una dirección IP interna dentro de su red.

## Paso: docker stats

**Qué se hizo:** Se observó el consumo de recursos del contenedor mientras se encontraba en ejecución.

**Comando ejecutado:**

```bash
docker stats
```

**Explicación (para qué sirve el comando):** El comando `docker stats` muestra estadísticas de uso de recursos de los contenedores en tiempo real.

Entre la información mostrada se encuentran:

- porcentaje de uso de CPU;
- memoria utilizada y límite disponible;
- porcentaje de memoria utilizada;
- tráfico de red;
- operaciones de entrada y salida;
- cantidad de procesos.

**Resultado obtenido:**

```text
CONTAINER ID   NAME       CPU %     MEM USAGE / LIMIT     MEM %     NET I/O           BLOCK I/O       PIDS
887f9fab510e   app-logs   0.01%     21.79MiB / 7.756GiB   0.27%     7.42kB / 3.58kB   844kB / 147kB   1
```

**Reflexión:** El resultado mostró que el contenedor estaba utilizando una cantidad pequeña de recursos durante la ejecución de la aplicación.

Se observó un uso de CPU de `0.01%`, un consumo de memoria de `21.79 MiB` de un total disponible de `7.756 GiB`, equivalente al `0.27%`, y un único proceso activo.

Esto permite comprobar que `docker stats` es útil para monitorear el consumo de recursos de los contenedores mientras están en funcionamiento.

## Paso: detener y eliminar el contenedor

**Qué se hizo:** Se detuvo y eliminó el contenedor después de completar las pruebas de logs e inspección.

**Comandos ejecutados:**

```bash
docker stop app-logs
docker rm app-logs
```

**Resultado obtenido:**

```text
app-logs
app-logs
```

**Reflexión:** El contenedor se detuvo y eliminó correctamente después de completar las pruebas. De esta manera se evitó dejar recursos innecesarios ejecutándose y se mantuvo organizado el ambiente de Docker.

## Preguntas de reflexión

1. **¿Por qué los logs son importantes al trabajar con contenedores?**

   Los logs permiten observar qué está ocurriendo dentro de una aplicación mientras se ejecuta. Son útiles para detectar errores, verificar que un servicio inició correctamente y revisar las solicitudes que recibe.

   En este ejercicio, los logs permitieron confirmar que Flask estaba activo y que las rutas `/` y `/info` respondieron correctamente.

2. **¿Qué diferencia hay entre ver logs históricos y logs en tiempo real?**

   `docker logs app-logs` muestra los mensajes que el contenedor ha generado hasta el momento en que se ejecuta el comando.

   En cambio, `docker logs -f app-logs` continúa ejecutándose y muestra también los nuevos mensajes que se generan posteriormente.

   Esto permitió observar nuevas solicitudes a `/` y `/info` inmediatamente después de realizarlas.

3. **¿Qué información útil se puede obtener con docker inspect?**

   `docker inspect` permite obtener información detallada sobre la configuración y el estado de un contenedor.

   En este ejercicio se pudo observar el estado `running`, la imagen utilizada, el comando `python app.py`, el directorio de trabajo `/app`, el puerto publicado, la dirección IP interna del contenedor y la configuración de red.

4. **¿Por qué es importante observar el consumo de recursos?**

   Observar el consumo de recursos permite identificar si un contenedor está utilizando demasiada CPU, memoria u otros recursos del sistema.

   Esto puede ayudar a detectar problemas de rendimiento y a conocer cuánto consume realmente una aplicación.

   En este ejercicio, `docker stats` mostró que la aplicación Flask utilizaba pocos recursos mientras se encontraba ejecutándose.