# Parte 5: crear una aplicación sencilla

## Descripción de la aplicación

En esta parte del laboratorio se creó una aplicación web sencilla utilizando Flask. La aplicación contiene una página principal que muestra un mensaje en formato HTML y una segunda ruta `/info` que devuelve información sobre el laboratorio.

El archivo principal de la aplicación es `app.py`.

```python
from flask import Flask
import os

app = Flask(__name__)

@app.route("/")
def home():
    mensaje = os.environ.get("MENSAJE", "Hola desde Flask en Docker")
    return f"""
    <h1>{mensaje}</h1>
    <p>Esta aplicación se está ejecutando dentro de un contenedor.</p>
    """

@app.route("/info")
def info():
    return {
        "app": "Laboratorio de contenedores",
        "curso": "IE0417",
        "tema": "Docker"
    }

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
```

## Rutas de la aplicación

La aplicación contiene dos rutas principales.

### Ruta /

La ruta principal `/` ejecuta la función `home()`.

```python
@app.route("/")
def home():
    mensaje = os.environ.get("MENSAJE", "Hola desde Flask en Docker")
```

Esta función obtiene el valor de la variable de entorno `MENSAJE`. Si la variable no está definida, utiliza como valor predeterminado:

```text
Hola desde Flask en Docker
```

Luego genera una respuesta HTML que muestra el mensaje y un texto indicando que la aplicación se ejecuta dentro de un contenedor.

### Ruta /info

La ruta `/info` ejecuta la función `info()`:

```python
@app.route("/info")
def info():
    return {
        "app": "Laboratorio de contenedores",
        "curso": "IE0417",
        "tema": "Docker"
    }
```

Esta ruta devuelve información estructurada sobre la aplicación, el curso y el tema del laboratorio.

## Dependencia utilizada

La aplicación utiliza Flask como dependencia principal.

El archivo `requirements.txt` contiene:

```text
flask
```

Flask es el framework web utilizado para crear las rutas y ejecutar el servidor de la aplicación.

## Paso: instalación de dependencias

**Qué se hizo:** Se instalaron las dependencias definidas en el archivo `requirements.txt`.

**Comando ejecutado:**

```bash
pip install -r requirements.txt
```

**Explicación (para qué sirve el comando):** El comando `pip install -r requirements.txt` indica a `pip` que lea las dependencias especificadas en el archivo `requirements.txt` y las instale en el entorno de Python.

En este caso, la dependencia principal era Flask. Durante la instalación también se instalaron varias dependencias requeridas por Flask, como `blinker`, `click`, `itsdangerous` y `werkzeug`.

**Resultado obtenido:**

```text
Collecting flask (from -r requirements.txt (line 1))
Downloading flask-3.1.3-py3-none-any.whl.metadata (3.2 kB)
Collecting blinker>=1.9.0 (from flask->-r requirements.txt (line 1))
Collecting click>=8.1.3 (from flask->-r requirements.txt (line 1))
Collecting itsdangerous>=2.2.0 (from flask->-r requirements.txt (line 1))
Requirement already satisfied: jinja2>=3.1.2
Requirement already satisfied: markupsafe>=2.1.1
Collecting werkzeug>=3.1.0 (from flask->-r requirements.txt (line 1))

Installing collected packages: werkzeug, itsdangerous, click, blinker, flask

Successfully installed blinker-1.9.0 click-8.5.0 flask-3.1.3 itsdangerous-2.2.0 werkzeug-3.1.9
```

**Reflexión:** La instalación se realizó correctamente. Además de Flask, `pip` instaló automáticamente las dependencias necesarias para su funcionamiento. Esto muestra la utilidad de `requirements.txt`, ya que permite indicar las dependencias necesarias sin tener que instalarlas manualmente una por una.

## Paso: ejecución de la aplicación

**Qué se hizo:** Se ejecutó la aplicación Flask utilizando Python.

**Comando ejecutado:**

```bash
python app.py
```

**Explicación (para qué sirve el comando):** Este comando ejecuta el archivo `app.py`. Como el archivo contiene la instrucción:

```python
app.run(host="0.0.0.0", port=5000)
```

Flask inició su servidor de desarrollo y comenzó a escuchar conexiones en el puerto `5000`.

**Resultado obtenido:**

```text
* Serving Flask app 'app'
* Debug mode: off
WARNING: This is a development server. Do not use it in a production deployment.
Use a production WSGI server instead.
* Running on all addresses (0.0.0.0)
* Running on http://127.0.0.1:5000
* Running on http://10.0.11.192:5000
Press CTRL+C to quit
127.0.0.1 - - [07/Oct/2026 17:27:16] "GET / HTTP/1.1" 200 -
127.0.0.1 - - [07/Oct/2026 17:27:16] "GET /favicon.ico HTTP/1.1" 404 -
```

**Reflexión:** La salida confirmó que la aplicación Flask inició correctamente y quedó escuchando en el puerto `5000`. La línea `Running on all addresses (0.0.0.0)` indicó que Flask estaba escuchando en todas las interfaces de red disponibles.

También se observó una solicitud `GET / HTTP/1.1` con código `200`, lo que confirmó que la página principal respondió correctamente.

## Acceso a la aplicación desde GitHub Codespaces

Debido a que el laboratorio se realizó dentro de GitHub Codespaces, el acceso a la aplicación no se realizó directamente mediante `http://localhost:5000` desde la computadora local.

GitHub Codespaces detectó el puerto `5000` y realizó un reenvío del mismo. La aplicación se abrió mediante una dirección generada por Codespaces:

```text
https://humble-engine-q7p5jg5gqrgxc655q-5000.app.github.dev/
```

Esto permitió acceder desde el navegador a la aplicación que internamente se encontraba ejecutándose en el puerto `5000`.

**Reflexión:** Esta prueba permitió observar una diferencia entre ejecutar una aplicación directamente en una computadora y ejecutarla dentro de un entorno remoto como GitHub Codespaces. La aplicación continuó utilizando el puerto `5000`, pero Codespaces se encargó de reenviar ese puerto para poder acceder desde el navegador.

## Por qué se utiliza host="0.0.0.0"

La aplicación se ejecuta mediante:

```python
app.run(host="0.0.0.0", port=5000)
```

Utilizar `0.0.0.0` hace que Flask escuche conexiones en todas las interfaces de red disponibles y no únicamente en la interfaz local.

Esto es importante cuando la aplicación se ejecuta dentro de un contenedor, porque permite que conexiones provenientes de fuera del contenedor lleguen a la aplicación mediante los puertos publicados.

## Preguntas de reflexión de la Parte 5

1. **¿Qué hace Flask en esta aplicación?**

   Flask funciona como el framework web de la aplicación. Permite crear el servidor HTTP, definir las rutas `/` y `/info`, recibir solicitudes y devolver respuestas al cliente.

2. **¿Para qué sirve el archivo requirements.txt?**

   El archivo `requirements.txt` permite indicar las dependencias de Python necesarias para ejecutar la aplicación. En este caso contiene Flask, lo que permite instalar la dependencia mediante:

   ```bash
   pip install -r requirements.txt
   ```

3. **¿Por qué una aplicación dentro de un contenedor debe escuchar en 0.0.0.0?**

   Porque `0.0.0.0` permite que la aplicación escuche en todas las interfaces de red disponibles. Si Flask escuchara solamente en `127.0.0.1`, las conexiones quedarían limitadas al propio entorno o contenedor.

4. **¿Qué diferencia hay entre ejecutar la aplicación localmente y ejecutarla dentro de Docker?**

   Al ejecutar la aplicación localmente, esta depende directamente del entorno de Python y de las dependencias instaladas en el sistema. Dentro de Docker, la aplicación se ejecuta en un entorno aislado y reproducible definido mediante una imagen.

---

# Parte 6: construir una imagen con Dockerfile

## Dockerfile utilizado

Para construir una imagen personalizada de la aplicación Flask se utilizó el siguiente archivo `Dockerfile` dentro de la carpeta `app/`:

```dockerfile
FROM python:3.11-slim

WORKDIR /app

COPY requirements.txt .

RUN pip install --no-cache-dir -r requirements.txt

COPY . .

EXPOSE 5000

CMD ["python", "app.py"]
```

## Explicación de las instrucciones del Dockerfile

### FROM

```dockerfile
FROM python:3.11-slim
```

**Explicación:** La instrucción `FROM` especifica la imagen base a partir de la cual se construirá la nueva imagen.

En este caso se utiliza `python:3.11-slim`, que proporciona Python 3.11 sobre una imagen reducida de Linux. Esto evita tener que instalar Python manualmente.

### WORKDIR

```dockerfile
WORKDIR /app
```

**Explicación:** `WORKDIR` establece `/app` como directorio de trabajo dentro de la imagen.

Las instrucciones posteriores se ejecutarán tomando `/app` como directorio actual.

### COPY requirements.txt .

```dockerfile
COPY requirements.txt .
```

**Explicación:** Esta instrucción copia `requirements.txt` desde el directorio local hacia el directorio `/app` dentro de la imagen.

Como previamente se definió `WORKDIR /app`, el punto `.` representa ese directorio.

### RUN

```dockerfile
RUN pip install --no-cache-dir -r requirements.txt
```

**Explicación:** `RUN` ejecuta un comando durante el proceso de construcción de la imagen.

En este caso instala las dependencias especificadas en `requirements.txt`.

La opción `--no-cache-dir` evita que `pip` conserve archivos de caché innecesarios dentro de la imagen.

### COPY .

```dockerfile
COPY . .
```

**Explicación:** Esta instrucción copia el resto de los archivos del directorio actual hacia `/app` dentro de la imagen.

Entre estos archivos se encuentra `app.py`.

### EXPOSE

```dockerfile
EXPOSE 5000
```

**Explicación:** `EXPOSE` documenta que la aplicación que se ejecutará dentro del contenedor utiliza el puerto `5000`.

Esta instrucción no publica el puerto automáticamente hacia el host. Esto se realizará posteriormente mediante la opción `-p` de `docker run`.

### CMD

```dockerfile
CMD ["python", "app.py"]
```

**Explicación:** `CMD` define el comando predeterminado que se ejecutará cuando se cree e inicie un contenedor a partir de esta imagen.

En este caso se ejecutará:

```bash
python app.py
```

lo que inicia la aplicación Flask.

## Paso: construcción de la imagen

**Qué se hizo:** Se construyó una imagen personalizada utilizando el `Dockerfile`.

**Comando ejecutado:**

```bash
docker build -t laboratorio-flask:1.0 .
```

**Explicación (para qué sirve el comando):** El comando `docker build` construye una imagen siguiendo las instrucciones definidas en el `Dockerfile`.

La opción:

```text
-t laboratorio-flask:1.0
```

asigna a la imagen el nombre `laboratorio-flask` y la etiqueta `1.0`.

El punto final `.` indica que Docker debe utilizar el directorio actual como contexto de construcción.

**Resultado obtenido:**

```text
[+] Building 12.5s (11/11) FINISHED            docker:default
 => [internal] load build definition from Dockerfile     0.0s
 => => transferring dockerfile: 194B                     0.0s
 => [internal] load metadata for docker.io/library/python:3.11-slim  0.7s
 => [auth] library/python:pull token for registry-1.docker.io        0.0s
 => [internal] load .dockerignore                        0.0s
 => => transferring context: 2B                          0.0s
 => [1/5] FROM docker.io/library/python:3.11-slim        3.4s
 => [internal] load build context                        0.0s
 => => transferring context: 777B                        0.0s
 => [2/5] WORKDIR /app                                   2.5s
 => [3/5] COPY requirements.txt .                        0.0s
 => [4/5] RUN pip install --no-cache-dir -r requirements.txt  4.3s
 => [5/5] COPY . .                                       0.1s
 => exporting to image                                   1.3s
 => => exporting layers                                  0.8s
 => => naming to docker.io/library/laboratorio-flask:1.0 0.0s
 => => unpacking to docker.io/library/laboratorio-flask:1.0 0.4s
```

**Reflexión:** La construcción finalizó correctamente con `11/11` pasos completados. Durante el proceso Docker descargó la imagen base `python:3.11-slim`, estableció el directorio de trabajo, copió `requirements.txt`, instaló las dependencias y finalmente copió el resto de la aplicación.

Esto permitió generar una nueva imagen que contiene todo lo necesario para ejecutar la aplicación Flask.

## Qué significa construir una imagen

Construir una imagen significa procesar las instrucciones definidas en un `Dockerfile` para generar una imagen de Docker que contenga el entorno, dependencias, archivos y configuración necesarios para ejecutar una aplicación.

En este caso la imagen incluye:

- Python 3.11.
- El directorio `/app`.
- Flask y sus dependencias.
- El código de `app.py`.
- El puerto `5000` documentado.
- El comando para iniciar la aplicación.

## Paso: verificación de la imagen

**Qué se hizo:** Se listaron las imágenes disponibles para comprobar que la nueva imagen había sido creada.

**Comando ejecutado:**

```bash
docker images
```

**Resultado obtenido:**

```text
                                          i Info →   U  In Use
IMAGE                 ID             DISK USAGE   CONTENT SIZE
hello-world:latest    5e2309035332       25.9kB         9.49kB
laboratorio-flask:1.0
                      28ef4387a888        211MB         51.4MB
ubuntu:latest         f144425ff09b        162MB         45.6MB
```

**Explicación:** La imagen `laboratorio-flask:1.0` apareció en la lista con el identificador `28ef4387a888`, confirmando que la construcción se realizó correctamente.

**Reflexión:** A diferencia de las imágenes `hello-world` y `ubuntu`, que fueron descargadas previamente desde Docker Hub, `laboratorio-flask:1.0` fue construida localmente utilizando el `Dockerfile` creado para este laboratorio.

## Significado de laboratorio-flask:1.0

En:

```text
laboratorio-flask:1.0
```

`laboratorio-flask` corresponde al nombre de la imagen.

`1.0` corresponde a la etiqueta o `tag`, utilizada para identificar una versión concreta de la imagen.

Por ejemplo, en el futuro podrían existir:

```text
laboratorio-flask:1.0
laboratorio-flask:2.0
```

## Paso: ejecución del contenedor

**Qué se hizo:** Se creó y ejecutó un contenedor utilizando la imagen construida.

**Comando ejecutado:**

```bash
docker run --name app-lab laboratorio-flask:1.0
```

**Explicación (para qué sirve el comando):** `docker run` crea un nuevo contenedor utilizando la imagen indicada.

La opción:

```text
--name app-lab
```

asigna al contenedor el nombre `app-lab`.

Como el `Dockerfile` define:

```dockerfile
CMD ["python", "app.py"]
```

Docker ejecutó automáticamente la aplicación Flask.

**Resultado obtenido:**

```text
* Serving Flask app 'app'
* Debug mode: off
WARNING: This is a development server. Do not use it in a production deployment.
Use a production WSGI server instead.
* Running on all addresses (0.0.0.0)
* Running on http://127.0.0.1:5000
* Running on http://172.17.0.2:5000
Press CTRL+C to quit
```

**Reflexión:** La aplicación Flask se inició correctamente dentro del contenedor. La dirección `172.17.0.2` corresponde a una dirección de red asignada al contenedor dentro de la red de Docker.

En este punto todavía no se publicó el puerto `5000` hacia el host. Esto se puede observar posteriormente en `docker ps`, donde aparece únicamente `5000/tcp` y no un mapeo como `0.0.0.0:5000->5000/tcp`.

## Paso: verificación del contenedor desde otra terminal

**Qué se hizo:** Mientras la aplicación continuaba ejecutándose en una terminal, se utilizó una segunda terminal para verificar que el contenedor estuviera activo.

**Comando ejecutado:**

```bash
docker ps
```

**Resultado obtenido:**

```text
CONTAINER ID   IMAGE                   COMMAND           CREATED         STATUS         PORTS      NAMES
3da7e85914f3   laboratorio-flask:1.0   "python app.py"   3 minutes ago   Up 3 minutes   5000/tcp   app-lab
```

**Explicación:** El resultado confirmó que el contenedor `app-lab` estaba ejecutándose utilizando la imagen `laboratorio-flask:1.0`.

También se observó:

```text
COMMAND
"python app.py"
```

lo cual coincide con el comando definido mediante `CMD` en el Dockerfile.

El estado:

```text
Up 3 minutes
```

indicó que el contenedor se encontraba activo.

## Diferencia entre el nombre de la imagen y el nombre del contenedor

En este ejercicio, la imagen utilizada fue:

```text
laboratorio-flask:1.0
```

Mientras que el contenedor creado a partir de ella recibió el nombre:

```text
app-lab
```

La imagen funciona como una plantilla reutilizable. A partir de una misma imagen se pueden crear distintos contenedores.

El contenedor, en cambio, corresponde a una instancia concreta creada a partir de esa imagen.

## Paso: detener el contenedor

**Qué se hizo:** Se detuvo el contenedor `app-lab`.

**Comando ejecutado:**

```bash
docker stop app-lab
```

**Resultado obtenido:**

```text
app-lab
```

**Explicación:** El comando `docker stop` detiene un contenedor que se encuentra en ejecución sin eliminarlo.

**Reflexión:** El contenedor dejó de ejecutar la aplicación Flask, pero seguía existiendo dentro de Docker y podía ser eliminado posteriormente.

## Paso: eliminar el contenedor

**Qué se hizo:** Se eliminó el contenedor después de haberlo detenido.

**Comando ejecutado:**

```bash
docker rm app-lab
```

**Resultado obtenido:**

```text
app-lab
```

**Explicación:** El comando `docker rm` elimina un contenedor existente.

Esto eliminó la instancia `app-lab`, pero no eliminó la imagen `laboratorio-flask:1.0`, por lo que podría utilizarse nuevamente para crear otro contenedor.

**Reflexión:** Esta separación entre imagen y contenedor permite reutilizar una misma imagen para crear múltiples instancias sin tener que reconstruirla cada vez.

## Preguntas de reflexión de la Parte 6

1. **¿Qué es una imagen base?**

   Una imagen base es la imagen inicial utilizada como punto de partida para construir una nueva imagen.

   En este laboratorio se utilizó:

   ```dockerfile
   FROM python:3.11-slim
   ```

   Esta imagen proporciona un entorno Linux mínimo con Python 3.11 instalado, sobre el cual se agregaron las dependencias y el código de la aplicación.

2. **¿Por qué se usa una imagen slim?**

   Una imagen `slim` contiene una versión reducida del entorno, con solamente los componentes esenciales necesarios.

   Esto permite disminuir el tamaño de la imagen y evita incluir paquetes que no son necesarios para ejecutar la aplicación.

3. **¿Por qué se copian primero las dependencias y luego el resto del código?**

   Primero se copia:

   ```dockerfile
   COPY requirements.txt .
   ```

   y se ejecuta:

   ```dockerfile
   RUN pip install --no-cache-dir -r requirements.txt
   ```

   Posteriormente se copia el resto de la aplicación:

   ```dockerfile
   COPY . .
   ```

   Esta organización permite aprovechar la caché de capas de Docker. Si el código de la aplicación cambia pero `requirements.txt` permanece igual, Docker puede reutilizar la capa donde las dependencias ya fueron instaladas y evitar repetir esa instalación.

4. **¿Qué diferencia hay entre RUN y CMD?**

   `RUN` ejecuta un comando durante el proceso de **construcción de la imagen**.

   Por ejemplo:

   ```dockerfile
   RUN pip install --no-cache-dir -r requirements.txt
   ```

   instala las dependencias dentro de la imagen.

   `CMD`, en cambio, define el comando que se ejecutará cuando se inicie un **contenedor** creado a partir de esa imagen.

   En este caso:

   ```dockerfile
   CMD ["python", "app.py"]
   ```

   hizo que al ejecutar el contenedor se iniciara automáticamente la aplicación Flask.

   Esto pudo comprobarse con `docker ps`, ya que la columna `COMMAND` mostró:

   ```text
   "python app.py"
   ```

5. **¿Qué pasaría si se elimina la imagen pero no el Dockerfile?**

   Si se elimina la imagen `laboratorio-flask:1.0`, ya no estaría disponible localmente para crear nuevos contenedores.

   Sin embargo, mientras se conserven el `Dockerfile`, `app.py` y `requirements.txt`, se podría reconstruir nuevamente ejecutando:

   ```bash
   docker build -t laboratorio-flask:1.0 .
   ```

   Esto demuestra que el `Dockerfile` permite describir de forma reproducible cómo construir el entorno de la aplicación.