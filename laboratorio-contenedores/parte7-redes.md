# Parte 12: redes de Docker

## Redes de Docker

## Paso: crear una red personalizada

**Qué se hizo:** Se creó una red personalizada de Docker llamada `red-lab`.

**Comando ejecutado:**

```bash
docker network create red-lab
```

**Explicación (para qué sirve el comando):** `docker network create` permite crear una red administrada por Docker. Los contenedores conectados a una misma red pueden comunicarse entre sí sin depender de direcciones IP configuradas manualmente.

**Resultado obtenido:**

```text
37d7a6579216fdd8048e913497ea6a9ed7fc53e43248021379864f3bdc55781a
```

**Reflexión:** La red se creó correctamente y quedó disponible para conectar los contenedores que se utilizarían en la prueba.

## Paso: listar las redes disponibles

**Qué se hizo:** Se consultaron las redes existentes en Docker para verificar que `red-lab` hubiera sido creada.

**Comando ejecutado:**

```bash
docker network ls
```

**Explicación (para qué sirve el comando):** `docker network ls` muestra las redes disponibles, junto con su identificador, nombre, controlador y alcance.

**Resultado obtenido:**

```text
NETWORK ID     NAME      DRIVER    SCOPE
03bd677d8cd0   bridge    bridge    local
36cd52215daf   host      host      local
0fa8a70695aa   none      null      local
37d7a6579216   red-lab   bridge    local
```

**Reflexión:** La salida confirmó que `red-lab` existía y utilizaba el controlador `bridge`, adecuado para comunicar contenedores dentro del mismo host Docker.

## Paso: ejecutar el servidor Nginx

**Qué se hizo:** Se ejecutó un contenedor llamado `servidor-web` utilizando la imagen de Nginx y conectándolo a la red `red-lab`.

Debido a las características del entorno de ejecución, también se publicó el puerto `80` del contenedor mediante el puerto `8080` del host para completar la prueba de conectividad.

**Comando ejecutado:**

```bash
docker run -d --name servidor-web --network red-lab -p 8080:80 nginx
```

**Explicación (para qué sirve el comando):**

- `-d` ejecuta el contenedor en segundo plano.
- `--name servidor-web` asigna el nombre `servidor-web`.
- `--network red-lab` conecta el contenedor a la red personalizada.
- `-p 8080:80` publica el puerto `80` de Nginx mediante el puerto `8080` del host.
- `nginx` corresponde a la imagen utilizada.

**Resultado obtenido:**

```text
d4685854e22363ae1690845483641a29f96426be1a9981a078df2edcf02c305c
```

**Reflexión:** El contenedor se creó correctamente y quedó conectado a `red-lab`. Nginx quedó ejecutándose como servidor web dentro del contenedor.

## Paso: verificar el servidor en ejecución

**Comando ejecutado:**

```bash
docker ps
```

**Resultado obtenido:**

```text
CONTAINER ID   IMAGE     COMMAND                  CREATED          STATUS          PORTS                                     NAMES
d4685854e223   nginx     "/docker-entrypoint.…"   10 seconds ago   Up 10 seconds   0.0.0.0:8080->80/tcp, [::]:8080->80/tcp   servidor-web
```

**Explicación (para qué sirve el comando):** `docker ps` permite comprobar cuáles contenedores se encuentran activos.

La salida confirmó que `servidor-web` estaba en estado `Up` y que el puerto `8080` del host estaba conectado al puerto `80` del contenedor.

**Reflexión:** Esta verificación permitió confirmar que el servidor estaba funcionando antes de realizar la prueba desde otro contenedor.

## Paso: probar la comunicación desde un contenedor cliente

El procedimiento planteado originalmente consiste en utilizar un contenedor Ubuntu, instalar `curl` mediante `apt` y posteriormente consultar el servidor web.

Durante la ejecución se presentó una limitación de resolución DNS externa en el entorno utilizado, por lo que `apt update` no pudo descargar correctamente los índices de paquetes y no fue posible instalar `curl` dentro de ese contenedor.

Para mantener el objetivo de la práctica, se utilizó una imagen que ya incluye `curl`, conectada igualmente a la red `red-lab`.

**Comando ejecutado:**

```bash
docker run --rm \
  --name cliente \
  --network red-lab \
  --add-host=host.docker.internal:host-gateway \
  curlimages/curl \
  http://host.docker.internal:8080
```

**Explicación (para qué sirve el comando):**

El comando crea un contenedor temporal llamado `cliente` utilizando una imagen que ya contiene `curl`.

La opción:

```text
--network red-lab
```

conecta el cliente a la misma red utilizada por el servidor.

La opción:

```text
--rm
```

hace que el contenedor se elimine automáticamente al finalizar.

Debido a la restricción observada en el entorno, se utilizó:

```text
--add-host=host.docker.internal:host-gateway
```

para permitir que el cliente llegara al puerto publicado por Nginx mediante `host.docker.internal`.

**Resultado obtenido:**

```text
% Total    % Received % Xferd  Average Speed  Time    Time    Time   Current
                               Dload  Upload   Total   Spent   Left   Speed
0      0   0      0   0      0      0      0                              0<!DOCTYPE html>
<html>
<head>
<title>Welcome to nginx!</title>
<style>
html { color-scheme: light dark; }
body { width: 35em; margin: 0 auto;
font-family: Tahoma, Verdana, Arial, sans-serif; }
</style>
</head>
<body>
<h1>Welcome to nginx!</h1>
<p>If you see this page, nginx is successfully installed and working.
Further configuration is required for the web server, reverse proxy,
API gateway, load balancer, content cache, or other features.</p>

<p>For online documentation and support please refer to
<a href="https://nginx.org/">nginx.org</a>.<br/>
To engage with the community please visit
<a href="https://community.nginx.org/">community.nginx.org</a>.<br/>
For enterprise grade support, professional services, additional
security features and capabilities please refer to
<a href="https://f5.com/nginx">f5.com/nginx</a>.</p>

<p><em>Thank you for using nginx.</em></p>
</body>
</html>
100    896 100    896   0      0 101.2k      0                              0
```

**Reflexión:** La respuesta HTML de Nginx confirmó que el contenedor cliente logró comunicarse con el servicio web.

La página recibida contenía:

```html
<h1>Welcome to nginx!</h1>
```

lo cual demuestra que el servidor respondió correctamente a la solicitud HTTP.

## Resolución de nombres entre contenedores

Durante las pruebas también se verificó que Docker podía resolver el nombre `servidor-web` dentro de la red `red-lab`.

El resultado observado fue:

```text
172.18.0.2      servidor-web
```

Esto demuestra que Docker relacionó automáticamente el nombre del contenedor con su dirección IP dentro de la red.

**Reflexión:** Esta característica permite que los contenedores se comuniquen utilizando nombres fáciles de reconocer en lugar de depender de direcciones IP que pueden cambiar cuando los contenedores se recrean.

## Paso: detener el servidor

**Comando ejecutado:**

```bash
docker stop servidor-web
```

**Resultado obtenido:**

```text
servidor-web
```

**Explicación (para qué sirve el comando):** `docker stop` detiene un contenedor que se encuentra en ejecución.

## Paso: eliminar el servidor

**Comando ejecutado:**

```bash
docker rm servidor-web
```

**Resultado obtenido:**

```text
servidor-web
```

**Explicación (para qué sirve el comando):** `docker rm` elimina el contenedor después de que ha sido detenido.

## Paso: eliminar la red

**Comando ejecutado:**

```bash
docker network rm red-lab
```

**Resultado obtenido:**

```text
red-lab
```

**Reflexión:** Después de finalizar las pruebas se eliminaron tanto el contenedor como la red personalizada, evitando dejar recursos innecesarios creados en Docker.

## Qué es una red en Docker

Una red en Docker permite establecer comunicación entre contenedores y organizar cómo intercambian información.

Cuando varios contenedores están conectados a la misma red personalizada, Docker puede gestionar la comunicación y la resolución de nombres entre ellos.

En esta práctica se creó `red-lab` para conectar un servidor web y un contenedor cliente.

## Qué hace docker network create

El comando:

```bash
docker network create red-lab
```

crea una nueva red administrada por Docker.

En este caso Docker creó una red utilizando el controlador `bridge`, como se confirmó posteriormente con:

```bash
docker network ls
```

## Qué significa conectar contenedores a la misma red

Conectar varios contenedores a la misma red permite que formen parte de un mismo entorno de comunicación.

Docker administra la conectividad entre ellos y permite que los contenedores puedan identificarse por nombre.

En este ejercicio el contenedor `servidor-web` se conectó a `red-lab`, y el contenedor utilizado como cliente también fue conectado a esa misma red.

## Qué ocurrió al realizar la solicitud HTTP

La solicitud realizada desde el contenedor cliente recibió correctamente la página HTML predeterminada de Nginx.

Entre la respuesta obtenida se encontraba:

```html
<title>Welcome to nginx!</title>
```

y:

```html
<h1>Welcome to nginx!</h1>
```

Esto permitió confirmar que Nginx estaba ejecutándose correctamente y que el cliente logró comunicarse con el servicio web.

## Por qué se pudo usar el nombre servidor-web

Docker incorpora resolución de nombres dentro de las redes personalizadas.

Cuando un contenedor se conecta a una red con el nombre `servidor-web`, los demás contenedores de esa red pueden utilizar ese nombre para identificarlo en lugar de conocer previamente su dirección IP.

Durante la prueba se confirmó esta asociación mediante el resultado:

```text
172.18.0.2      servidor-web
```

Esta forma de comunicación resulta más conveniente porque las direcciones IP internas de los contenedores pueden cambiar al ser eliminados y creados nuevamente, mientras que los nombres pueden mantenerse.

## Preguntas de reflexión

1. **¿Por qué los contenedores necesitan redes?**

   Porque muchas aplicaciones necesitan comunicarse con otros servicios.

   Una red permite que diferentes contenedores intercambien información, por ejemplo una aplicación web que necesita comunicarse con una base de datos o con otro servicio de la aplicación.

2. **¿Qué ventaja tiene usar nombres de contenedor en lugar de direcciones IP?**

   Los nombres son más fáciles de recordar y no dependen de una dirección IP específica.

   Docker puede asignar direcciones IP diferentes cuando un contenedor es recreado, pero si se mantiene el mismo nombre, los demás servicios pueden seguir utilizando ese nombre para localizarlo.

3. **¿Qué diferencia hay entre publicar un puerto hacia el host y comunicarse dentro de una red Docker?**

   Publicar un puerto mediante `-p` permite acceder desde el host a un servicio que se encuentra dentro de un contenedor.

   La comunicación dentro de una red Docker está pensada para que los propios contenedores puedan intercambiar información entre ellos sin que necesariamente sea necesario publicar todos sus puertos hacia el exterior.

4. **¿Qué ejemplos reales podrían usar una red Docker?**

   Un ejemplo sería una aplicación web ejecutándose en un contenedor y una base de datos ejecutándose en otro.

   También podrían conectarse un servidor web, una API, un sistema de caché como Redis y una base de datos, manteniendo cada servicio separado pero permitiendo la comunicación entre ellos mediante una red Docker.