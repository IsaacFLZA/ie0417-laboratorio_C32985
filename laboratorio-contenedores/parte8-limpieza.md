# Parte 14: limpieza del ambiente

<!-- Documentacion requerida (borrar este comentario al terminar):
- [ ] Qué recursos quedaron creados
- [ ] Qué comandos de limpieza ejecuté
- [ ] Diferencia entre limpiar contenedores, imágenes y volúmenes
- [ ] Resultado de docker system df
-->

## Recursos que quedaron creados (antes de limpiar)


## Paso: Listar recursos

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker ps -a
docker images
docker volume ls
docker network ls
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Limpiar contenedores detenidos

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker container prune
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Limpiar imágenes no utilizadas

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker image prune
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Limpiar volúmenes no utilizados

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker volume prune
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Espacio utilizado por Docker

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker system df
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Diferencia entre limpiar contenedores, imágenes y volúmenes


## Preguntas de reflexión

1. **¿Por qué Docker puede consumir mucho espacio en disco?**

   Respuesta: 

2. **¿Qué diferencia hay entre eliminar un contenedor y eliminar una imagen?**

   Respuesta: 

3. **¿Por qué se debe tener cuidado al eliminar volúmenes?**

   Respuesta: 

4. **¿Qué buenas prácticas aplicaría para mantener limpio su ambiente local?**

   Respuesta: 

