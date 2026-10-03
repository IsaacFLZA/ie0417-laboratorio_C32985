# Parte 3: imágenes y contenedores

<!-- Documentacion requerida (borrar este comentario al terminar):
- [ ] Qué hace docker pull
- [ ] Qué muestra docker images
- [ ] Qué significa ejecutar un contenedor en modo interactivo
- [ ] Qué observé dentro del contenedor Ubuntu
- [ ] Qué ocurrió al salir del contenedor
-->

## Paso: docker pull ubuntu

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker pull ubuntu
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: docker images

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker images
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Contenedor interactivo de Ubuntu (comandos dentro del contenedor)

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run -it ubuntu bash
# dentro del contenedor:
ls
pwd
cat /etc/os-release
exit
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: docker ps -a (después de salir)

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker ps -a
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Preguntas de reflexión

1. **¿La imagen Ubuntu es lo mismo que una máquina virtual Ubuntu?**

   Respuesta: 

2. **¿Por qué el contenedor puede parecer un sistema Linux si no es una máquina virtual completa?**

   Respuesta: 

3. **¿Qué significa que el contenedor comparta el kernel con el host?**

   Respuesta: 

4. **¿Qué diferencia hay entre una imagen descargada y un contenedor creado?**

   Respuesta: 


---

## Administración de contenedores

<!-- Parte 4. Documentar: uso de --name; diferencia entre docker start y docker run; uso de docker exec; diferencia entre detener y eliminar; qué pasó con el archivo creado dentro del contenedor. -->

## Paso: Crear contenedor con nombre y un archivo dentro

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run -it --name mi-ubuntu ubuntu bash
# dentro del contenedor:
echo "Hola desde el contenedor" > mensaje.txt
cat mensaje.txt
exit
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Verificar el contenedor detenido

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker ps -a
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Iniciar de nuevo y entrar con docker exec

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker start mi-ubuntu
docker exec -it mi-ubuntu bash
# dentro del contenedor:
cat mensaje.txt
exit
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Detener y eliminar

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker stop mi-ubuntu
docker rm mi-ubuntu
docker ps -a
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

### Preguntas de reflexión (administración)

1. **¿Qué ventaja tiene asignar nombres a los contenedores?**

   Respuesta: 

2. **¿Qué diferencia hay entre crear un contenedor nuevo y reiniciar uno existente?**

   Respuesta: 

3. **¿Qué sucede con los datos creados dentro de un contenedor si este se elimina?**

   Respuesta: 

4. **¿Por qué se dice que los contenedores son desechables?**

   Respuesta: 

