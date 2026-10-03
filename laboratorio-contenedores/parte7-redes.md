# Parte 12: redes de Docker

<!-- Documentacion requerida (borrar este comentario al terminar):
- [ ] Qué es una red en Docker
- [ ] Qué hace docker network create
- [ ] Qué significa conectar contenedores a la misma red
- [ ] Qué ocurrió al ejecutar curl http://servidor-web
- [ ] Por qué se pudo usar el nombre servidor-web
-->

## Paso: Crear y listar la red

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker network create red-lab
docker network ls
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Servidor Nginx en la red

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run -d --name servidor-web --network red-lab nginx
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Cliente Ubuntu en la misma red

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run -it --name cliente --network red-lab ubuntu bash
# dentro del contenedor:
apt update
apt install -y curl
curl http://servidor-web
exit
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Limpieza de la parte 12

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker stop servidor-web
docker rm servidor-web
docker rm cliente
docker network rm red-lab
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Preguntas de reflexión

1. **¿Por qué los contenedores necesitan redes?**

   Respuesta: 

2. **¿Qué ventaja tiene usar nombres de contenedor en lugar de direcciones IP?**

   Respuesta: 

3. **¿Qué diferencia hay entre publicar un puerto hacia el host y comunicarse dentro de una red Docker?**

   Respuesta: 

4. **¿Qué ejemplos reales podrían usar una red Docker?**

   Respuesta: 


---

## Comunicación entre servicios

<!-- Parte 13. Documentar: qué es Redis en este ejemplo; qué representa redis-lab; cómo se conectó el cliente al servidor; qué significa recibir PONG; qué enseñanza deja sobre aplicaciones con varios contenedores. -->

## Paso: Red y contenedor Redis

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker network create red-app
docker run -d --name redis-lab --network red-app redis
docker ps
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Cliente Redis

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run -it --name cliente-redis --network red-app redis redis-cli -h redis-lab
# dentro del cliente Redis:
ping
set curso IE0417
get curso
exit
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Limpieza de la parte 13

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker stop redis-lab
docker rm redis-lab
docker rm cliente-redis
docker network rm red-app
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

### Preguntas de reflexión (comunicación entre servicios)

1. **¿Por qué una aplicación web podría necesitar comunicarse con una base de datos?**

   Respuesta: 

2. **¿Por qué ambos contenedores deben estar en la misma red?**

   Respuesta: 

3. **¿Qué ventaja tiene separar servicios en contenedores distintos?**

   Respuesta: 

4. **¿Qué limitación tiene hacerlo manualmente con varios comandos docker run?**

   Respuesta: 

