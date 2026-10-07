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
  Downloading blinker-1.9.0-py3-none-any.whl.metadata (1.6 kB)
Collecting click>=8.1.3 (from flask->-r requirements.txt (line 1))
  Downloading click-8.5.0-py3-none-any.whl.metadata (2.6 kB)
Collecting itsdangerous>=2.2.0 (from flask->-r requirements.txt (line 1))
  Downloading itsdangerous-2.2.0-py3-none-any.whl.metadata (1.9 kB)
Requirement already satisfied: jinja2>=3.1.2 in /home/codespace/.local/lib/python3.14/site-packages (from flask->-r requirements.txt (line 1)) (3.1.6)
Requirement already satisfied: markupsafe>=2.1.1 in /home/codespace/.local/lib/python3.14/site-packages (from flask->-r requirements.txt (line 1)) (3.0.3)
Collecting werkzeug>=3.1.0 (from flask->-r requirements.txt (line 1))
  Downloading werkzeug-3.1.9-py3-none-any.whl.metadata (4.1 kB)
Downloading flask-3.1.3-py3-none-any.whl (103 kB)
Downloading blinker-1.9.0-py3-none-any.whl (8.5 kB)
Downloading click-8.5.0-py3-none-any.whl (125 kB)
Downloading itsdangerous-2.2.0-py3-none-any.whl (16 kB)
Downloading werkzeug-3.1.9-py3-none-any.whl (228 kB)
Installing collected packages: werkzeug, itsdangerous, click, blinker, flask
Successfully installed blinker-1.9.0 click-8.5.0 flask-3.1.3 itsdangerous-2.2.0 werkzeug-3.1.9
```

**Reflexión:** La instalación se realizó correctamente. Además de Flask, `pip` instaló automáticamente las dependencias que Flask necesita para funcionar. Esto muestra la utilidad de `requirements.txt`, ya que permite indicar las dependencias necesarias sin tener que instalarlas manualmente una por una.

## Paso: ejecución de la aplicación

**Qué se hizo:** Se ejecutó la aplicación Flask desde Python.

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
WARNING: This is a development server. Do not use it in a production deployment. Use a production WSGI server instead.
* Running on all addresses (0.0.0.0)
* Running on http://127.0.0.1:5000
* Running on http://10.0.11.192:5000
Press CTRL+C to quit
127.0.0.1 - - [07/Oct/2026 17:27:16] "GET / HTTP/1.1" 200 -
127.0.0.1 - - [07/Oct/2026 17:27:16] "GET /favicon.ico HTTP/1.1" 404 -
```

**Reflexión:** La salida confirmó que la aplicación Flask se inició correctamente y quedó escuchando en el puerto `5000`. La línea:

```text
Running on all addresses (0.0.0.0)
```

indica que Flask está escuchando en todas las interfaces de red disponibles dentro del entorno.

También se observó una solicitud:

```text
"GET / HTTP/1.1" 200
```

El código de estado `200` indica que la página principal fue solicitada correctamente y que el servidor respondió sin errores.

La solicitud:

```text
"GET /favicon.ico HTTP/1.1" 404
```

corresponde al intento automático del navegador de obtener un ícono para la página. El código `404` se debe a que la aplicación no define ningún archivo o ruta para `favicon.ico` y no afecta el funcionamiento de la aplicación.

## Acceso a la aplicación desde GitHub Codespaces

El laboratorio indica que se debe abrir:

```text
http://localhost:5000
```

Sin embargo, en este caso la aplicación se ejecutó dentro de un GitHub Codespace y no directamente en la computadora local.

Cuando Flask comenzó a escuchar en el puerto `5000`, GitHub Codespaces detectó este puerto y realizó automáticamente un reenvío del mismo. Como resultado, la aplicación se abrió mediante una dirección proporcionada por Codespaces:

```text
https://humble-engine-q7p5jg5gqrgxc655q-5000.app.github.dev/
```

Por lo tanto, aunque Flask internamente se estaba ejecutando en el puerto `5000`, el acceso desde el navegador se realizó utilizando la URL generada por GitHub Codespaces.

Esto no representa un error en la aplicación. Es una consecuencia de trabajar en un entorno remoto: `localhost` dentro del Codespace hace referencia al propio entorno remoto y no necesariamente a la computadora desde la cual se accede al navegador.

**Reflexión:** Esta prueba permitió observar una diferencia entre ejecutar una aplicación directamente en una computadora y hacerlo dentro de un entorno remoto como GitHub Codespaces. La aplicación continuó utilizando el puerto `5000`, pero Codespaces se encargó de reenviar ese puerto y proporcionar una URL accesible desde el navegador.

## Por qué se utiliza host="0.0.0.0"

La aplicación se inicia mediante:

```python
app.run(host="0.0.0.0", port=5000)
```

Utilizar `0.0.0.0` hace que Flask escuche conexiones en todas las interfaces de red disponibles y no únicamente en la interfaz local del proceso.

Si la aplicación utilizara únicamente `localhost` o `127.0.0.1`, el servidor aceptaría conexiones solamente desde el mismo entorno en el que se está ejecutando. Esto podría impedir el acceso desde fuera del contenedor o desde mecanismos de reenvío de puertos.

En este ejercicio, escuchar en `0.0.0.0` permitió que GitHub Codespaces detectara y reenviara correctamente el puerto `5000`. Posteriormente, cuando la aplicación se ejecute dentro de Docker, este mismo comportamiento permitirá que el puerto del contenedor pueda ser publicado hacia el host.

## Preguntas de reflexión

1. **¿Qué hace Flask en esta aplicación?**

   Flask funciona como el framework web de la aplicación. Permite crear el servidor HTTP y definir las rutas que responden a las solicitudes del navegador.

   En este caso se utilizaron las rutas `/` y `/info`. Flask recibe las solicitudes dirigidas a estas rutas, ejecuta la función correspondiente y devuelve una respuesta al cliente.

2. **¿Para qué sirve el archivo requirements.txt?**

   El archivo `requirements.txt` permite indicar las dependencias de Python necesarias para ejecutar la aplicación.

   En este laboratorio contiene:

   ```text
   flask
   ```

   Esto permite instalar la dependencia utilizando:

   ```bash
   pip install -r requirements.txt
   ```

   De esta manera, otra persona o posteriormente una imagen de Docker puede instalar las dependencias necesarias de forma reproducible sin tener que conocerlas previamente.

3. **¿Por qué una aplicación dentro de un contenedor debe escuchar en 0.0.0.0?**

   Porque `0.0.0.0` hace que la aplicación escuche en todas las interfaces de red disponibles dentro del entorno.

   Si Flask escuchara únicamente en `127.0.0.1`, las conexiones quedarían limitadas al propio contenedor. Al utilizar `0.0.0.0`, la aplicación puede recibir conexiones que lleguen desde fuera del contenedor mediante los puertos que Docker publique hacia la máquina anfitriona.

   En esta ejecución local dentro de GitHub Codespaces se observó el mismo principio, ya que el puerto `5000` pudo ser reenviado por Codespaces y accedido mediante una URL externa.

4. **¿Qué diferencia hay entre ejecutar la aplicación localmente y ejecutarla dentro de Docker?**

   Al ejecutar la aplicación localmente, el proceso de Python utiliza directamente el entorno donde se ejecutó el comando, incluyendo la versión de Python y las dependencias instaladas en ese sistema.

   Cuando la aplicación se ejecuta dentro de Docker, se ejecuta dentro de un entorno aislado definido por una imagen. La versión de Python, las dependencias, los archivos y otras configuraciones necesarias pueden quedar definidas mediante el `Dockerfile`.

   Esto permite que la aplicación tenga un entorno más reproducible y que no dependa directamente de la configuración de Python instalada en la máquina anfitriona.