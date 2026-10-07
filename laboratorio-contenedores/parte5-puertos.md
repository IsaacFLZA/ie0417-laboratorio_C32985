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